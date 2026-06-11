// ═══════════════════════════════════════════════════════
// SensePath — HANDVAT bring-up firmware (XIAO ESP32-S3)
//
// Doel van deze build:
//   1. ESP-NOW ontvanger → de servo (mechanisch kompas) volgt de encoder
//      van de controller-module draadloos.
//   2. Serieel testmenu → elk component los valideren/finetunen.
//
// Nog NIET de volledige eindfirmware (geen deep-sleep, geen volledige
// haptiek-engine). Wel de eerste integratiestap: de draadloze link.
//
// Pinout (uit docs/wiring.md, XIAO ESP32-S3):
//   I2C SDA   D4  GPIO5   → DRV2605L SDA
//   I2C SCL   D5  GPIO6   → DRV2605L SCL
//   Knop      D3  GPIO4   → HOTUT (interne pull-up, naar GND)
//   Servo PWM D9  GPIO8   → MG90S signaal
//   Audio SD  D10 GPIO9   → MAX98357A SD-gate (+ 100k pull-down)
//   I2S BCLK  D6  GPIO43 / LRC D7 GPIO44 / DIN D8 GPIO7  (audio, later)
// ═══════════════════════════════════════════════════════

#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>
#include <ESPmDNS.h>
#include <Preferences.h>   // NVS-opslag voor app-instellingen
#include <Adafruit_DRV2605.h>
#include <ESP32Servo.h>
#include "driver/i2s.h"
#include "driver/rtc_io.h"
#include "esp_sleep.h"

#include <WebServer.h>   // softAP-webserver voor de telefoon-app (digital twin)
#include "protocol.h"   // gedeeld ESP-NOW packet-formaat (shared/protocol.h)
#include "audio_clips.h" // ingebedde spraak-clips (gegenereerd uit WAV)
#include "webapp.h"      // de hele telefoon-app als PROGMEM-string (INDEX_HTML)
#include "secrets.h"     // GOOGLE_MAPS_API_KEY (lokaal bestand, gitignored)

// ─── Pin-constanten (GPIO-nummers, zie wiring.md) ────────
constexpr uint8_t PIN_I2C_SDA  = 5;   // D4
constexpr uint8_t PIN_I2C_SCL  = 6;   // D5
constexpr uint8_t PIN_BUTTON   = 4;   // D3  (RTC-GPIO, later wake-pin)
constexpr uint8_t PIN_SERVO    = 8;   // D9
constexpr uint8_t PIN_AUDIO_SD = 9;   // D10 (MAX98357A shutdown-gate)
constexpr int     PIN_I2S_BCLK = 43;  // D6  → MAX98357A BCLK
constexpr int     PIN_I2S_LRC  = 44;  // D7  → MAX98357A LRC
constexpr int     PIN_I2S_DIN  = 7;   // D8  → MAX98357A DIN

// ─── Globale objecten ────────────────────────────────────
Adafruit_DRV2605 drv;
Servo compassServo;
WebServer server(80);          // serveert de app + /api/servo (digital twin)
Preferences prefs;             // NVS-opslag voor de app-instellingen

// ── App-instellingen (gesynced met webapp.h, persistent in NVS) ──────────
// Defaults zijn zo gekozen dat ze het HUIDIGE handvat-gedrag behouden:
// korte druk = ETA-clip, dubbel = locatie-clip, sterkte = Medium (= nu).
struct Settings {
    int btn_short     = 7;    // 7 = Spreek ETA op handvat   (= huidig gedrag)
    int btn_double    = 8;    // 8 = Spreek locatie op handvat (= huidig gedrag)
    int btn_long      = 0;    // 0 = Niets
    int vib_intensity = 1;    // 0=Laag 1=Medium(huidige sterkte) 2=Hoog
    int vib_m4         = 47;  // effect bij obstakel        (DRV ROM-id, preview)
    int vib_m6         = 12;  // effect bij koersafwijking
    int vib_turn_right = 1;   // afslag rechts (1x klik) → turn-pattern id
    int vib_turn_left  = 2;   // afslag links  (2x klik) → turn-pattern id
    int audio_enabled = 1;    // handvat-audioclips aan/uit
    int tts_rate      = 10;   // spraaksnelheid (app-zijde, *10)
    String emergency  = "";   // noodcontact-nummer (app gebruikt het)
};
Settings cfg;
float  hapticFactor   = 1.0f; // sterkte-multiplier voor de haptiek-engine
String pendingCommand = "";   // stok→app commando (app polt GET /api/pending)
int    pendingClip    = 0;    // 0=geen, 1=ETA, 2=locatie (in loop afgespeeld)
int    lastClip       = 0;    // laatst gespeelde clip (voor "herhaal laatste")
bool drvFound = false;
bool servoAttached = false;

// ─── Knop-debounce / press-classificatie (bring-up versie) ─
int lastButtonState = HIGH;
uint32_t buttonChangedAt = 0;
uint32_t buttonPressedAt = 0;

// ─── Servo: veilig aansturen ─────────────────────────────
// DRIE onafhankelijke beveiligingen zodat de servo NOOIT kan blijven
// blokkeren (de oorzaak van de oververhitting):
//   1. AUTO-DETACH: zodra de servo stilstaat, gaat het PWM-signaal uit →
//      geen koppel = geen stall-stroom = geen warmte.
//   2. WATCHDOG: de servo wordt nooit langer dan SERVO_MAX_ENERGIZED_MS
//      onafgebroken aangestuurd, wat er ook gebeurt (vangt elke bug).
//   3. JOG-KALIBRATIE: kalibreren gebeurt in kleine stapjes, niet door
//      continu tegen een wand te schuiven.
// Daarbovenop: slew-rate-limiting (nooit springen) + harde clamps.
// ── Gemeten servo-kalibratie (handvat-prototype, Develop 3) ──────────
//   onderrand (mechanische wand) : 1406 µs
//   bovenrand (mechanische wand) : 2106 µs
//   nulpunt (midden)             : 1756 µs   (totaal bereik ~700 µs)
// Het werkbereik ligt 14 µs binnen de wanden om wand-stall te vermijden.
// Deze waarden vormen de basis voor de latere encoder→servo mapping.
constexpr int SERVO_CENTER_US = 1756;     // nulpunt
constexpr int SERVO_MIN_US    = 1420;     // ~onderrand (14 µs marge)
constexpr int SERVO_MAX_US    = 2092;     // ~bovenrand (14 µs marge)

bool calMode = false;                     // kalibratie-modus actief?
int  calMarks = 0;                        // aantal gemarkeerde limieten (0/1/2)
int  calLimit1 = 0, calLimit2 = 0;        // gemeten uiterste posities
int  servoUs = SERVO_CENTER_US;           // huidige (gecommandeerde) pulsbreedte
int  servoTargetUs = SERVO_CENTER_US;     // doel waar we traag naartoe gaan
uint32_t lastServoStep = 0;
uint32_t servoAttachedAt = 0;             // moment van attach (voor watchdog)
constexpr int SERVO_BOOT_US = SERVO_CENTER_US;  // rust = nulpunt
constexpr int SERVO_STEP_US = 6;          // 6 µs per stap → ~servo-maximum = real-time volgen
constexpr uint32_t SERVO_STEP_MS = 1;     // elke 1 ms een stap
constexpr int SERVO_CLAMP_MIN = SERVO_MIN_US;   // kan fysiek niet voorbij de randen
constexpr int SERVO_CLAMP_MAX = SERVO_MAX_US;
constexpr int JOG_STEP_US = 25;           // verplaatsing per jog-druk ('[' / ']')
constexpr uint32_t SERVO_IDLE_DETACH_MS = 700;      // stil → loskoppelen (veilig)
constexpr uint32_t SERVO_MAX_ENERGIZED_MS = 10000;  // backstop; idle-detach is de hoofdbeveiliging
bool servoIdle = false;
uint32_t servoReachedAt = 0;

// ─── Motor aan/uit-toestand (toggle met de HOTUT-knop) ───
bool motorOn = false;

void setMotor(bool on) {
    motorOn = on;
    if (!drvFound) { Serial.println("  MOTOR: DRV niet gevonden!"); return; }
    drv.setMode(DRV2605_MODE_REALTIME);   // directe analoge drive
    drv.setRealtimeValue(on ? 127 : 0);   // 127 = volle kracht
    Serial.printf("  MOTOR: %s\n", on ? "AAN (vol)" : "UIT");
}

// ═════════════════════════════════════════════════════════
//  Haptiek pattern-engine (non-blocking, segment-gebaseerd)
//  Geport uit de oude firmware: speelt trilpatronen via RTP op de
//  DRV2605L. Elke cue start een patroon; updateHaptics() stapt erdoor.
// ═════════════════════════════════════════════════════════
struct Segment { uint32_t durationMs; uint8_t targetPercent; bool ramp; };
constexpr uint8_t MAX_SEGMENTS = 32;

struct PatternState {
    Segment  segments[MAX_SEGMENTS];
    uint8_t  count = 0, index = 0;
    bool     active = false, loop = false;
    uint32_t segStartedAt = 0;
    uint8_t  segStartPercent = 0, outputPercent = 0;
    const char* name = "idle";
};
PatternState pat;
uint8_t lastRtp = 255;
uint32_t cueDispatchCount = 0;            // diagnose: aantal afgespeelde cues
uint8_t  patMaxRtp = 0;                   // diagnose: hoogste RTP tijdens patroon
uint32_t patWrites = 0;                   // diagnose: aantal motor-schrijfacties

uint8_t clampPct(int v) { return v < 0 ? 0 : (v > 100 ? 100 : (uint8_t)v); }
uint8_t pctToRtp(uint8_t p) { return map(clampPct(p), 0, 100, 0, 127); }

void hapticWrite(uint8_t pct) {
    pat.outputPercent = clampPct(pct);
    if (!drvFound) return;
    // Sterkte-instelling (Laag/Medium/Hoog) schaalt elke haptiek-uitgang.
    uint8_t scaled = clampPct((int)(pat.outputPercent * hapticFactor + 0.5f));
    uint8_t rtp = pctToRtp(scaled);
    if (rtp == lastRtp) return;
    drv.setRealtimeValue(rtp);
    lastRtp = rtp;
    if (rtp > patMaxRtp) patMaxRtp = rtp;
    patWrites++;
}

void hapticStop() {
    if (patWrites > 0)
        Serial.printf("  patroon klaar: maxRtp=%u writes=%lu\n", patMaxRtp, (unsigned long)patWrites);
    pat.active = false; pat.loop = false; pat.count = 0; pat.index = 0;
    pat.name = "idle"; pat.segStartPercent = 0;
    hapticWrite(0);
}

void hapticAddSeg(uint32_t ms, uint8_t pct, bool ramp = false) {
    if (pat.count >= MAX_SEGMENTS) return;
    pat.segments[pat.count++] = {ms, clampPct(pct), ramp};
}

void hapticClear() { pat.count = 0; pat.index = 0; pat.segStartPercent = pat.outputPercent; }

void hapticBegin(const char* name, bool loop = false) {
    pat.name = name; pat.loop = loop; pat.index = 0;
    pat.active = pat.count > 0;
    pat.segStartedAt = millis(); pat.segStartPercent = pat.outputPercent;
    motorOn = false;                              // engine neemt de motor over
    lastRtp = 255;                                // forceer verse motor-schrijf
    patMaxRtp = 0; patWrites = 0;                 // diagnose-tellers resetten
    if (drvFound) drv.setMode(DRV2605_MODE_REALTIME);
    if (!pat.active) hapticStop();
    Serial.printf("  HAPTIEK: %s\n", name);
}

// Eén puls met fade-in, daarna optioneel een stilte (offMs).
void hapticPulse(uint16_t onMs, uint8_t pct, uint32_t offMs = 0, uint16_t fadeInMs = 80) {
    uint32_t hold = onMs > fadeInMs ? onMs - fadeInMs : 0;
    hapticAddSeg(fadeInMs, pct, true);
    if (hold > 0) hapticAddSeg(hold, pct, false);
    hapticAddSeg(20, 0, false);
    if (offMs > 0) hapticAddSeg(offMs, 0, false);
}

void updateHaptics() {
    if (!pat.active || pat.count == 0) return;
    uint32_t now = millis();
    Segment& s = pat.segments[pat.index];
    uint32_t elapsed = now - pat.segStartedAt;

    if (elapsed >= s.durationMs) {
        hapticWrite(s.targetPercent);
        pat.index++;
        if (pat.index >= pat.count) {
            if (pat.loop) pat.index = 0;
            else { hapticStop(); return; }
        }
        pat.segStartedAt = now; pat.segStartPercent = pat.outputPercent;
        return;
    }
    if (s.ramp && s.durationMs > 0) {
        int delta = (int)s.targetPercent - (int)pat.segStartPercent;
        uint8_t v = pat.segStartPercent + (delta * (int)elapsed) / (int)s.durationMs;
        hapticWrite(v);
    } else {
        hapticWrite(s.targetPercent);
    }
}

// Speelt een INSTELBAAR afslag-trilpatroon (id uit TURN_PATTERNS in webapp.h;
// cfg.vib_turn_right / cfg.vib_turn_left bepalen welk patroon per richting).
// Coin-ERM voelt alleen lange pulsen, dus elk patroon bestaat uit pulsen van
// >=350 ms op vol vermogen (geschaald door de sterkte-instelling).
void playTurnPattern(int id) {
    hapticClear();
    constexpr uint16_t SHORT_MS = 350, GAP_MS = 200, LONG_MS = 600;
    switch (id) {
        case 2:  hapticPulse(SHORT_MS, 100, GAP_MS, 40);                      // 2 trillingen
                 hapticPulse(SHORT_MS, 100, 0, 40); break;
        case 3:  hapticPulse(SHORT_MS, 100, GAP_MS, 40);                      // 3 trillingen
                 hapticPulse(SHORT_MS, 100, GAP_MS, 40);
                 hapticPulse(SHORT_MS, 100, 0, 40); break;
        case 4:  hapticPulse(LONG_MS, 100, 0, 50); break;                     // 1 lange trilling
        case 5:  hapticPulse(SHORT_MS, 100, GAP_MS, 40);                      // kort dan lang
                 hapticPulse(LONG_MS, 100, 0, 50); break;
        default: hapticPulse(SHORT_MS, 100, 0, 40); break;                    // 1 trilling (id 1)
    }
    hapticBegin("afslag");
}

// Wake-bevestiging: 3 oplopende pulsen ("ta-ta-TAAA"), als een power-on.
// Bewust 3 pulsen → onderscheidt van de afslag-tikken (1 of 2) en de slaap-buzz.
void hapticWake() {
    hapticClear();
    hapticPulse(250, 100, 150, 40);
    hapticPulse(300, 100, 150, 40);
    hapticPulse(500, 100, 0,   40);
    hapticBegin("wake-bevestiging");
}

// Centrale cue → respons dispatcher (fase 2 vult de rest aan).
void dispatchCue(uint8_t cue) {
    cueDispatchCount++;
    Serial.printf("  CUE ontvangen: %u\n", cue);
    switch (cue) {
        case sensepath::CUE_TURN_RIGHT: playTurnPattern(cfg.vib_turn_right); break;
        case sensepath::CUE_TURN_LEFT:  playTurnPattern(cfg.vib_turn_left);  break;
        default: break;
    }
}

// ═════════════════════════════════════════════════════════
//  ESP-NOW link (ontvangt encoder-updates van de controller)
// ═════════════════════════════════════════════════════════
constexpr float US_PER_COUNT = 22.0f;     // servo-µs per encoder-detent (afstembaar)

volatile bool     linkRx = false;         // nieuw pakket ontvangen?
volatile int16_t  linkAbsolute = 0;       // laatst ontvangen encoder-positie
volatile uint8_t  linkButtons = 0;        // laatst ontvangen knop-bits (bit0 = recenter)
volatile uint8_t  linkCue = 0;            // laatst ontvangen cue-waarde
volatile uint8_t  linkCueId = 0;          // cue-event-id (verandert per nieuwe cue)
volatile uint32_t linkRxCount = 0;        // diagnose: aantal ontvangen pakketten
int16_t  encoderOffset = 0;               // encoder-stand die als "midden" geldt
uint32_t linkLastRxMs = 0;                // tijdstip laatste pakket (link-loss later)

// ESP-NOW receive-callback (core 2.x signatuur). Houdt het kort: alleen data
// opslaan, het echte werk gebeurt in serviceLink() in de hoofdlus.
void onEspNowRecv(const uint8_t* mac, const uint8_t* data, int len) {
    if (len < (int)sizeof(sensepath::EncoderUpdate)) return;
    const sensepath::EncoderUpdate* u = (const sensepath::EncoderUpdate*)data;
    if (u->version != sensepath::PROTOCOL_VERSION) return;
    linkAbsolute = u->absolute;
    linkButtons = u->buttons;
    linkCue = u->cue;
    linkCueId = u->cueId;
    linkRxCount++;
    linkRx = true;
}

// Verbindt met de telefoon-hotspot (STA) zodat de telefoon internet heeft voor
// Google Maps op hetzelfde netwerk. ESP-NOW volgt automatisch het hotspot-kanaal,
// dus de controller (die ook de hotspot joint) blijft bereikbaar. Lukt de
// hotspot niet, dan valt het handvat terug op een eigen AP op kanaal 1 (de twin
// werkt dan nog, zonder internet); de controller valt dan ook terug op kanaal 1.
bool wifiOnHotspot = false;

// WiFi-presets uit secrets.h, in volgorde van voorkeur geprobeerd.
struct WifiPreset { const char* ssid; const char* pass; };
static WifiPreset WIFI_NETS[] = WIFI_PRESETS;
static const int  WIFI_N = sizeof(WIFI_NETS) / sizeof(WIFI_NETS[0]);

void setupNetwork() {
    WiFi.persistent(false);
    WiFi.mode(WIFI_STA);

    // Probeer elke preset (max 10 s) tot er één verbindt.
    for (int i = 0; i < WIFI_N && WiFi.status() != WL_CONNECTED; i++) {
        Serial.printf("WiFi proberen: '%s' ", WIFI_NETS[i].ssid);
        WiFi.begin(WIFI_NETS[i].ssid, WIFI_NETS[i].pass);
        uint32_t t0 = millis();
        while (WiFi.status() != WL_CONNECTED && millis() - t0 < 10000) { delay(300); Serial.print("."); }
        Serial.println();
        if (WiFi.status() != WL_CONNECTED) WiFi.disconnect();
    }

    if (WiFi.status() == WL_CONNECTED) {
        wifiOnHotspot = true;
        Serial.printf(">>> Verbonden met '%s'. Handvat-IP: ", WiFi.SSID().c_str());
        Serial.println(WiFi.localIP());
        Serial.printf(">>> WiFi-kanaal %d (ESP-NOW volgt dit kanaal)\n", WiFi.channel());
        if (MDNS.begin("sensepath")) {
            MDNS.addService("http", "tcp", 80);
            Serial.println(">>> Bereikbaar op http://sensepath.local/  (of het IP hierboven)");
        }
    } else {
        Serial.println(">>> Hotspot niet gevonden → eigen AP 'SensePath' op kanaal 1 (geen internet)");
        WiFi.mode(WIFI_AP_STA);
        WiFi.softAP("SensePath", "sensepath123", sensepath::ESPNOW_CHANNEL);
        Serial.println(">>> Bereikbaar op http://192.168.4.1/");
    }
    Serial.print(">>> Handvat STA-MAC (staat al in de controller): ");
    Serial.println(WiFi.macAddress());

    esp_wifi_set_ps(WIFI_PS_NONE);   // power-save uit → stabielere ESP-NOW naast WiFi
    if (esp_now_init() != ESP_OK) {
        Serial.println("FOUT: ESP-NOW init mislukt");
        return;
    }
    esp_now_register_recv_cb(onEspNowRecv);
    Serial.printf("ESP-NOW ontvanger actief op kanaal %d\n", WiFi.channel());
}

// ═════════════════════════════════════════════════════════
//  App-instellingen: NVS-opslag + toepassing op het handvat
//  De telefoon-app POST't instellingen naar /api/settings; ze worden hier
//  persistent bewaard (NVS) en meteen toegepast: sterkte → haptiek-multiplier,
//  knop-acties → executeAction, audio → clip-poort.
// ═════════════════════════════════════════════════════════
void applyIntensity() {
    // Coin-ERM zit bij Medium al op vol vermogen (geen marge erboven), dus
    // Hoog == Medium; Laag halveert ongeveer. Medium = de huidige sterkte.
    switch (cfg.vib_intensity) {
        case 0:  hapticFactor = 0.60f; break;  // Laag
        case 2:  hapticFactor = 1.00f; break;  // Hoog
        default: hapticFactor = 1.00f; break;  // Medium (= huidig gedrag)
    }
}

void loadSettings() {
    prefs.begin("sensepath", true);            // read-only
    cfg.btn_short     = prefs.getInt("btn_short",     cfg.btn_short);
    cfg.btn_double    = prefs.getInt("btn_double",    cfg.btn_double);
    cfg.btn_long      = prefs.getInt("btn_long",      cfg.btn_long);
    cfg.vib_intensity = prefs.getInt("vib_intensity", cfg.vib_intensity);
    cfg.vib_m4         = prefs.getInt("vib_m4",     cfg.vib_m4);
    cfg.vib_m6         = prefs.getInt("vib_m6",     cfg.vib_m6);
    cfg.vib_turn_right = prefs.getInt("vib_turn_r", cfg.vib_turn_right);
    cfg.vib_turn_left  = prefs.getInt("vib_turn_l", cfg.vib_turn_left);
    cfg.audio_enabled = prefs.getInt("audio_enabled", cfg.audio_enabled);
    cfg.tts_rate      = prefs.getInt("tts_rate",      cfg.tts_rate);
    cfg.emergency     = prefs.getString("emergency",  cfg.emergency);
    prefs.end();
    applyIntensity();
}

void storeSettings() {
    prefs.begin("sensepath", false);           // read-write
    prefs.putInt("btn_short",     cfg.btn_short);
    prefs.putInt("btn_double",    cfg.btn_double);
    prefs.putInt("btn_long",      cfg.btn_long);
    prefs.putInt("vib_intensity", cfg.vib_intensity);
    prefs.putInt("vib_m4",     cfg.vib_m4);
    prefs.putInt("vib_m6",     cfg.vib_m6);
    prefs.putInt("vib_turn_r", cfg.vib_turn_right);
    prefs.putInt("vib_turn_l", cfg.vib_turn_left);
    prefs.putInt("audio_enabled", cfg.audio_enabled);
    prefs.putInt("tts_rate",      cfg.tts_rate);
    prefs.putString("emergency",  cfg.emergency);
    prefs.end();
    applyIntensity();
}

// Speelt een DRV ROM-effect (voor de effect-preview vanuit de app).
void playRomEffect(uint8_t id) {
    if (!drvFound) return;
    hapticStop();                              // stop een eventueel lopend patroon
    drv.selectLibrary(1);
    drv.setMode(DRV2605_MODE_INTTRIG);
    drv.setWaveform(0, id);
    drv.setWaveform(1, 0);
    drv.go();
}

// Speelt een clip via de handvat-speaker (1=ETA, 2=locatie) en onthoudt hem
// voor "herhaal laatste". Respecteert de audio-instelling.
void speakClip(int clip) {
    if (!cfg.audio_enabled || clip <= 0) return;
    pendingClip = clip;
    lastClip = clip;
}

void enterDeepSleep();   // vooruit-declaratie (definitie verderop in het bestand)

// Voert een knop-ACTIE uit (ids gesynced met ACTIONS in webapp.h). ALLE
// spraak komt uit de HANDVAT-SPEAKER (clips), niet via de telefoon-TTS.
void executeAction(int id) {
    switch (id) {
        case 0:  break;                                              // Niets
        case 1:  speakClip(2); break;                                // Vraag locatie  → locatie-clip
        case 2:  speakClip(1); break;                                // Vraag route    → ETA-clip
        case 3:  speakClip(lastClip); break;                         // Herhaal laatste clip
        case 4:  hapticClear(); hapticPulse(250, 100, 0, 40);        // trilling-bevestiging
                 hapticBegin("knop-bevestiging"); break;
        case 5:  pendingCommand = "EMERGENCY";                       // noodhulp: telefoon belt op
                 hapticClear(); hapticPulse(400, 100, 0, 50);
                 hapticBegin("noodhulp"); break;
        case 6:  cfg.audio_enabled = !cfg.audio_enabled; storeSettings();  // audio aan/uit
                 hapticClear(); hapticPulse(150, 100, 0, 30);
                 hapticBegin("audio-toggle"); break;
        case 7:  speakClip(1); break;                                // ETA-clip op handvat
        case 8:  speakClip(2); break;                                // locatie-clip op handvat
        case 9:  enterDeepSleep(); break;                            // slaapstand (keert niet terug)
        default: break;
    }
    Serial.printf("  ACTIE uitgevoerd: id=%d\n", id);
}

// Minimale parser voor een platte JSON-body: "key":123  of  "key":"tekst".
static int jsonInt(const String& body, const char* key, int fallback) {
    String tag = String("\"") + key + "\"";
    int k = body.indexOf(tag);
    if (k < 0) return fallback;
    int c = body.indexOf(':', k + tag.length());
    if (c < 0) return fallback;
    return body.substring(c + 1).toInt();
}
static String jsonStr(const String& body, const char* key, const String& fallback) {
    String tag = String("\"") + key + "\"";
    int k = body.indexOf(tag);
    if (k < 0) return fallback;
    int c = body.indexOf(':', k + tag.length());
    if (c < 0) return fallback;
    int q1 = body.indexOf('"', c + 1);
    if (q1 < 0) return fallback;
    int q2 = body.indexOf('"', q1 + 1);
    if (q2 < 0) return fallback;
    return body.substring(q1 + 1, q2);
}

// ═════════════════════════════════════════════════════════
//  Webserver (softAP) — serveert de telefoon-app + digital-twin spiegel
//  De app polt GET /api/servo (100 ms) en draait de SVG-kompasnaald mee met
//  de fysieke servo. De overige endpoints zijn minimale stubs zodat de app
//  netjes opstart. Zonder internet draait de app in manuele modus (geen
//  Google Maps); de twin en de hele UI werken wel.
// ═════════════════════════════════════════════════════════

// Servostand (µs) → hoek voor de twin-naald. De MG90S draait fysiek maar ~15°
// per kant binnen ons gekalibreerde µs-bereik; de twin toont exact die uitwijking
// (90 = nulpunt, naald rechtop) i.p.v. een uitvergrote 0-180°, zodat het scherm
// overeenkomt met de echte servo. Pas TWIN_EDGE_DEG aan als je anders meet.
constexpr float TWIN_EDGE_DEG = 15.0f;
int twinAngle() {
    float span   = (float)(SERVO_MAX_US - SERVO_CENTER_US);          // µs naar de rand
    float devDeg = (float)(servoUs - SERVO_CENTER_US) / span * TWIN_EDGE_DEG;
    // Min-teken: spiegelt de schermrichting zodat de naald dezelfde kant op
    // draait als de fysieke servo (servo/encoder zelf blijven ongewijzigd).
    int a = (int)lroundf(90.0f - devDeg);                            // 90 = nulpunt
    return a < 0 ? 0 : (a > 180 ? 180 : a);
}

void handleRoot() {
    // INDEX_HTML staat in flash. We vervangen de Google-key-placeholder zonder
    // een 66 KB kopie in RAM te maken (dat faalt naast de WiFi-heap → witte
    // pagina). Daarom streamen we in stukken: deel vóór de key, dan de key,
    // dan de rest. Bij geen geldige key blijft de app in manuele modus.
    static const char MARKER[] = "PLAK_HIER_JE_KEY";
    const char* pos = strstr(INDEX_HTML, MARKER);
    server.setContentLength(CONTENT_LENGTH_UNKNOWN);
    server.send(200, "text/html", "");
    if (pos) {
        server.sendContent_P(INDEX_HTML, pos - INDEX_HTML);   // alles vóór de key
        server.sendContent(GOOGLE_MAPS_API_KEY);              // de echte key
        server.sendContent_P(pos + sizeof(MARKER) - 1);       // alles ná de key
    } else {
        server.sendContent_P(INDEX_HTML);
    }
    server.sendContent("");   // lege chunk = einde van de stream
}

void handleGetServo() {              // ← digital twin: telefoon polt dit elke 100 ms
    char buf[24];
    snprintf(buf, sizeof(buf), "{\"angle\":%d}", twinAngle());
    server.send(200, "application/json", buf);
}

void handleGetSettings() {
    String j = "{";
    j += "\"btn_short\":"      + String(cfg.btn_short);
    j += ",\"btn_double\":"    + String(cfg.btn_double);
    j += ",\"btn_long\":"      + String(cfg.btn_long);
    j += ",\"vib_intensity\":" + String(cfg.vib_intensity);
    j += ",\"vib_m4\":"         + String(cfg.vib_m4);
    j += ",\"vib_m6\":"         + String(cfg.vib_m6);
    j += ",\"vib_turn_right\":" + String(cfg.vib_turn_right);
    j += ",\"vib_turn_left\":"  + String(cfg.vib_turn_left);
    j += ",\"audio_enabled\":" + String(cfg.audio_enabled);
    j += ",\"tts_rate\":"      + String(cfg.tts_rate);
    j += ",\"emergency\":\""   + cfg.emergency + "\"";
    j += "}";
    server.send(200, "application/json", j);
}

void handlePostSettings() {
    String body = server.hasArg("plain") ? server.arg("plain") : "";
    cfg.btn_short     = jsonInt(body, "btn_short",     cfg.btn_short);
    cfg.btn_double    = jsonInt(body, "btn_double",    cfg.btn_double);
    cfg.btn_long      = jsonInt(body, "btn_long",      cfg.btn_long);
    cfg.vib_intensity = jsonInt(body, "vib_intensity", cfg.vib_intensity);
    cfg.vib_m4         = jsonInt(body, "vib_m4",         cfg.vib_m4);
    cfg.vib_m6         = jsonInt(body, "vib_m6",         cfg.vib_m6);
    cfg.vib_turn_right = jsonInt(body, "vib_turn_right", cfg.vib_turn_right);
    cfg.vib_turn_left  = jsonInt(body, "vib_turn_left",  cfg.vib_turn_left);
    cfg.audio_enabled = jsonInt(body, "audio_enabled", cfg.audio_enabled);
    cfg.tts_rate      = jsonInt(body, "tts_rate",      cfg.tts_rate);
    cfg.emergency     = jsonStr(body, "emergency",     cfg.emergency);
    storeSettings();
    Serial.printf("  INSTELLINGEN opgeslagen (sterkte=%d, kort=%d, dubbel=%d, lang=%d)\n",
                  cfg.vib_intensity, cfg.btn_short, cfg.btn_double, cfg.btn_long);
    server.send(200, "text/plain", "ok");
}

void handleResetSettings() {
    prefs.begin("sensepath", false);
    prefs.clear();
    prefs.end();
    cfg = Settings();            // terug naar de defaults
    applyIntensity();
    Serial.println("  INSTELLINGEN gereset naar default");
    server.send(200, "text/plain", "ok");
}

void handleGetPending() {       // consume-on-read: app polt dit elke 600 ms
    server.send(200, "text/plain", pendingCommand);
    pendingCommand = "";
}

void handleTriggerEffect() {    // preview vanuit de instellingen-pagina
    int id = server.hasArg("id") ? server.arg("id").toInt() : 0;
    if (id <= 0) {
        // sterkte-preview: standaard RTP-puls die de huidige sterkte volgt
        hapticClear(); hapticPulse(300, 100, 0, 40); hapticBegin("sterkte-test");
    } else {
        playRomEffect((uint8_t)id);   // effect-preview voor de trilling-keuzes
    }
    server.send(200, "text/plain", "ok");
}

void handleTurnPreview() {       // preview van een afslag-trilpatroon (TURN_PATTERNS)
    int id = server.hasArg("id") ? server.arg("id").toInt() : 1;
    playTurnPattern(id);
    server.send(200, "text/plain", "ok");
}

void handleGetDestinations() { server.send(200, "application/json", "[]"); }
void handleGetState()        { server.send(200, "application/json", "{\"route_active\":true,\"destination\":\"\"}"); }
void handleOk()              { server.send(200, "text/plain", "ok"); }

void setupWebServer() {
    server.on("/",                  HTTP_GET,  handleRoot);
    server.on("/api/servo",         HTTP_GET,  handleGetServo);   // digital twin
    server.on("/api/settings",      HTTP_GET,  handleGetSettings);
    server.on("/api/settings",      HTTP_POST, handlePostSettings);
    server.on("/api/settings/reset",HTTP_POST, handleResetSettings);
    server.on("/api/destinations",  HTTP_GET,  handleGetDestinations);
    server.on("/api/destinations",  HTTP_POST, handleOk);
    server.on("/api/route/start",   HTTP_POST, handleOk);
    server.on("/api/route/stop",    HTTP_POST, handleOk);
    server.on("/api/state",         HTTP_GET,  handleGetState);
    server.on("/api/pending",       HTTP_GET,  handleGetPending);
    server.on("/api/trigger-effect",HTTP_POST, handleTriggerEffect);
    server.on("/api/turn-preview",  HTTP_POST, handleTurnPreview);
    server.onNotFound([]() { server.send(404, "text/plain", "niet gevonden"); });
    server.begin();
    Serial.println("Webserver actief (settings + pending + twin gekoppeld)");
}

// ═════════════════════════════════════════════════════════
//  DRV2605L + coin vibratiemotor (ERM)
// ═════════════════════════════════════════════════════════
void setupDRV() {
    Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);
    drvFound = drv.begin();
    if (drvFound) {
        drv.selectLibrary(1);              // library 1-5 = ERM (coin motor)
        drv.setMode(DRV2605_MODE_INTTRIG); // ROM-effecten via go()
        drv.useERM();
        Serial.println("OK : DRV2605L gevonden op 0x5A (ERM-modus)");
    } else {
        Serial.println("FOUT: DRV2605L NIET gevonden — check I2C-bedrading (SDA=D4, SCL=D5)");
    }
}

void testMotorEffects() {
    if (!drvFound) { Serial.println("  motor: DRV niet gevonden"); return; }
    const uint8_t effects[] = {1, 14, 47, 10, 12};  // click, buzz, long buzz, double, triple
    const char *names[] = {"Strong Click", "Strong Buzz", "Long Buzz", "Double Click", "Triple Click"};
    for (int i = 0; i < 5; i++) {
        Serial.printf("  motor-effect %d: %s\n", effects[i], names[i]);
        drv.setWaveform(0, effects[i]);
        drv.setWaveform(1, 0);
        drv.go();
        delay(1200);
    }
    Serial.println("  motor-test klaar");
}

void testMotorRamp() {
    if (!drvFound) { Serial.println("  motor: DRV niet gevonden"); return; }
    Serial.println("  RTP-ramp 0->100->0% (analoge drive-test)");
    drv.setMode(DRV2605_MODE_REALTIME);
    for (int v = 0; v <= 127; v += 8) { drv.setRealtimeValue(v); delay(40); }
    for (int v = 127; v >= 0; v -= 8) { drv.setRealtimeValue(v); delay(40); }
    drv.setRealtimeValue(0);
    drv.setMode(DRV2605_MODE_INTTRIG);  // terug naar ROM-modus
    Serial.println("  ramp klaar");
}

// ═════════════════════════════════════════════════════════
//  MG90S servo (mechanisch kompas)
// ═════════════════════════════════════════════════════════
void detachServo() {
    if (servoAttached) {
        compassServo.detach();
        servoAttached = false;
        servoIdle = false;
    }
}

void ensureServoAttached() {
    if (!servoAttached) {
        compassServo.setPeriodHertz(50);
        compassServo.attach(PIN_SERVO, 500, 2500);  // MG90S puls-bereik
        servoAttached = true;
        servoAttachedAt = millis();                 // start watchdog-klok
        compassServo.writeMicroseconds(servoUs);    // huidige stand → geen slam
    }
    servoIdle = false;
}

// Beweegt de servo traag naar servoTargetUs en bewaakt de beveiligingen.
// In loop() aangeroepen.
void serviceServo() {
    if (!servoAttached) return;
    uint32_t now = millis();

    // BEVEILIGING 2 — harde watchdog: nooit langer dan X ms onafgebroken
    // aangestuurd, ongeacht de oorzaak. Vangt elke denkbare blokkade af.
    if (now - servoAttachedAt > SERVO_MAX_ENERGIZED_MS) {
        detachServo();
        Serial.println("  WATCHDOG: servo te lang actief -> losgekoppeld");
        return;
    }

    // BEVEILIGING 1 — auto-detach zodra hij stilstaat op zijn doel.
    if (servoUs == servoTargetUs) {
        if (!servoIdle) { servoIdle = true; servoReachedAt = now; }
        else if (now - servoReachedAt > SERVO_IDLE_DETACH_MS) detachServo();
        return;
    }
    servoIdle = false;

    // Slew-rate-limited stap richting doel (binnen harde clamps).
    if (now - lastServoStep < SERVO_STEP_MS) return;
    lastServoStep = now;
    if (servoUs < servoTargetUs)      servoUs += SERVO_STEP_US;
    else if (servoUs > servoTargetUs) servoUs -= SERVO_STEP_US;
    if (servoUs < SERVO_CLAMP_MIN) servoUs = SERVO_CLAMP_MIN;
    if (servoUs > SERVO_CLAMP_MAX) servoUs = SERVO_CLAMP_MAX;
    compassServo.writeMicroseconds(servoUs);
}

// BEVEILIGING 3 — kalibratie via kleine jog-stapjes. De servo beweegt alleen
// op commando een klein stukje en koppelt daarna vanzelf los; hij kan dus
// nooit doorlopend tegen een wand blijven duwen.
void startCalibration() {
    setMotor(false);
    calMode = true;
    calMarks = 0;
    calLimit1 = calLimit2 = 0;
    Serial.println("  KALIBRATIE-modus (veilig, met jog-stapjes).");
    Serial.println("  Jog de servo met:  ] = beetje omhoog   [ = beetje omlaag");
    Serial.println("  Druk op de KNOP als de kompasbol op een uiterste stand zit.");
    Serial.println("  Doe dat 2x (eerste en tweede rand). 'x' stopt, 'd' koppelt los.");
}

void jogServo(int delta) {
    if (!calMode) { Serial.println("  jog kan alleen in kalibratie-modus ('c')"); return; }
    ensureServoAttached();
    servoTargetUs += delta;
    if (servoTargetUs < SERVO_CLAMP_MIN) servoTargetUs = SERVO_CLAMP_MIN;
    if (servoTargetUs > SERVO_CLAMP_MAX) servoTargetUs = SERVO_CLAMP_MAX;
    Serial.printf("  jog -> doel %d us\n", servoTargetUs);
}

// Aangeroepen vanuit pollButton bij een knopdruk in kalibratie-modus.
void markCalibrationLimit() {
    if (calMarks == 0) {
        calLimit1 = servoUs;
        calMarks = 1;
        Serial.printf("  LIMIET 1 = %d us. Jog nu naar de andere rand en druk weer.\n", calLimit1);
    } else if (calMarks == 1) {
        calLimit2 = servoUs;
        calMarks = 2;
        calMode = false;
        int center = (calLimit1 + calLimit2) / 2;
        int range  = abs(calLimit2 - calLimit1);
        Serial.printf("  LIMIET 2 = %d us\n", calLimit2);
        Serial.println("  -- KALIBRATIE-RESULTAAT --");
        Serial.printf("    limiet 1 : %d us\n", calLimit1);
        Serial.printf("    limiet 2 : %d us\n", calLimit2);
        Serial.printf("    NULPUNT  : %d us  (totaal bereik %d us)\n", center, range);
        servoTargetUs = center;          // traag naar nulpunt, daarna auto-detach
        ensureServoAttached();
    }
}

void testServoSweep() {
    // Volledige gekalibreerde slag: wisselt tussen onder- en bovenrand.
    ensureServoAttached();
    servoTargetUs = (servoUs > SERVO_CENTER_US) ? SERVO_MIN_US : SERVO_MAX_US;
    Serial.printf("  servo -> %d us (volledige gekalibreerde slag)\n", servoTargetUs);
}

// Verwerkt een ontvangen ESP-NOW pakket: mapt de encoder-positie naar de
// servo binnen het gekalibreerde bereik. In loop() aangeroepen.
void serviceLink() {
    if (!linkRx) return;
    linkRx = false;
    linkLastRxMs = millis();

    // Cue-detectie: trigger alleen op een NIEUWE cueId → overleeft packet-loss
    // en dubbel-triggert niet. Eerste pakket alleen synchroniseren.
    static bool cueInit = false;
    static uint8_t lastCueId = 0;
    uint8_t cid = linkCueId, cval = linkCue;
    if (!cueInit) { cueInit = true; lastCueId = cid; }
    else if (cid != lastCueId) { lastCueId = cid; dispatchCue(cval); }

    // Encoder-offset: bij het EERSTE pakket (boot/wake) én bij de recenter-knop
    // wordt de huidige encoder-stand het nieuwe midden. Zo start het kompas op
    // het nulpunt na wake en blijft het daar tot je draait.
    static bool offsetInit = false;
    static uint8_t lastBtns = 0;
    int16_t absVal = linkAbsolute;
    uint8_t btns = linkButtons;
    if (!offsetInit) { offsetInit = true; encoderOffset = absVal; }
    if ((btns & 1) && !(lastBtns & 1)) encoderOffset = absVal;   // recenter (rising edge)
    lastBtns = btns;

    if (calMode) return;                  // tijdens kalibratie geen servo-override
    int target = constrain(
        SERVO_CENTER_US - (int)((absVal - encoderOffset) * US_PER_COUNT),
        SERVO_MIN_US, SERVO_MAX_US);
    if (target != servoTargetUs) {        // nieuwe richting → volgen
        servoTargetUs = target;
        ensureServoAttached();
        servoAttachedAt = millis();       // watchdog resetten zolang we actief volgen
    }
}

// ═════════════════════════════════════════════════════════
//  Deep-sleep (power-uit) + wake op de HOTUT-knop (D3 = GPIO4)
// ═════════════════════════════════════════════════════════
void enterDeepSleep() {
    Serial.println("  >>> DEEP SLEEP — druk de knop om te wekken");
    Serial.flush();
    // korte vibratie-ack zodat de gebruiker weet dat hij uitgaat
    if (drvFound) { drv.setMode(DRV2605_MODE_REALTIME); drv.setRealtimeValue(127); }
    delay(150);
    if (drvFound) drv.setRealtimeValue(0);
    digitalWrite(PIN_AUDIO_SD, LOW);              // audio uit

    // servo vloeiend naar het nulpunt vóór het slapen (blocking ramp)
    ensureServoAttached();
    int v = servoUs;
    while (v != SERVO_CENTER_US) {
        v += (v < SERVO_CENTER_US) ? 1 : -1;
        compassServo.writeMicroseconds(v);
        delay(3);
    }
    servoUs = servoTargetUs = SERVO_CENTER_US;
    delay(120);                                   // even laten settelen
    detachServo();                                // servo loskoppelen (limp)

    // wacht tot de knop losgelaten is, anders wekt wake-op-LAAG meteen weer
    while (digitalRead(PIN_BUTTON) == LOW) delay(10);
    delay(50);
    // wake wanneer D3 (GPIO4) LAAG wordt (knop ingedrukt)
    rtc_gpio_pullup_en(GPIO_NUM_4);
    rtc_gpio_pulldown_dis(GPIO_NUM_4);
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_4, 0);
    esp_deep_sleep_start();                        // keert nooit terug; wake = reboot
}

// ═════════════════════════════════════════════════════════
//  HOTUT-knop (D3) — druk-type detectie (kort / dubbel / lang / heel lang)
// ═════════════════════════════════════════════════════════
constexpr uint32_t BTN_DEBOUNCE_MS = 20;
constexpr uint32_t BTN_DOUBLE_MS   = 400;    // venster voor dubbel-druk
constexpr uint32_t BTN_LONG_MS     = 3000;   // lang → ETA-zin
constexpr uint32_t BTN_VERYLONG_MS = 6000;   // heel lang → deep-sleep

void pollButton() {
    static uint32_t pressStart = 0;
    static bool sleepTriggered = false;
    static uint8_t pendingClicks = 0;
    static uint32_t lastReleaseAt = 0;
    int state = digitalRead(PIN_BUTTON);
    uint32_t now = millis();

    // tijdens vasthouden: bij ≥6 s direct in deep-sleep (met ack)
    if (state == LOW && pressStart && !sleepTriggered && !calMode
        && now - pressStart >= BTN_VERYLONG_MS) {
        sleepTriggered = true;
        enterDeepSleep();                         // keert niet terug
    }

    if (state != lastButtonState && now - buttonChangedAt > BTN_DEBOUNCE_MS) {
        buttonChangedAt = now;
        if (state == LOW) {                        // ingedrukt
            pressStart = now;
            sleepTriggered = false;
            if (calMode) markCalibrationLimit();   // kalibratie: limiet markeren
        } else {                                   // losgelaten
            uint32_t held = now - pressStart;
            pressStart = 0;
            if (calMode) { /* niets */ }
            else if (held >= BTN_VERYLONG_MS) { /* sleep al afgehandeld */ }
            else if (held >= BTN_LONG_MS) {
                Serial.println("  KNOP lang");
                executeAction(cfg.btn_long);       // geconfigureerde lange-druk-actie
            } else {                               // korte druk → tel voor dubbel/enkel
                pendingClicks++;
                lastReleaseAt = now;
            }
        }
        lastButtonState = state;
    }

    // korte druk(ken) afhandelen na het dubbel-venster
    if (pendingClicks > 0 && now - lastReleaseAt > BTN_DOUBLE_MS && state == HIGH) {
        if (pendingClicks >= 2) { Serial.println("  KNOP dubbel"); executeAction(cfg.btn_double); }
        else                    { Serial.println("  KNOP enkel");  executeAction(cfg.btn_short); }
        pendingClicks = 0;
    }
}

// ═════════════════════════════════════════════════════════
//  MAX98357A audio-gate (alleen SD-pin test, geen I2S-toon hier)
// ═════════════════════════════════════════════════════════
void testAudioTone() {
    Serial.println("  audio: 1 kHz toon ~1.2s via MAX98357A (let op de speaker)");
    digitalWrite(PIN_AUDIO_SD, HIGH);          // amp wakker (left-channel mode)

    i2s_config_t cfg = {};
    cfg.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX);
    cfg.sample_rate = 16000;
    cfg.bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT;
    cfg.channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT;
    cfg.communication_format = I2S_COMM_FORMAT_STAND_I2S;
    cfg.intr_alloc_flags = 0;
    cfg.dma_buf_count = 8;
    cfg.dma_buf_len = 256;
    cfg.use_apll = false;
    cfg.tx_desc_auto_clear = true;

    i2s_pin_config_t pins = {};
    pins.bck_io_num = PIN_I2S_BCLK;
    pins.ws_io_num = PIN_I2S_LRC;
    pins.data_out_num = PIN_I2S_DIN;
    pins.data_in_num = I2S_PIN_NO_CHANGE;

    if (i2s_driver_install(I2S_NUM_0, &cfg, 0, NULL) != ESP_OK) {
        Serial.println("  FOUT: I2S kon niet starten");
        digitalWrite(PIN_AUDIO_SD, LOW);
        return;
    }
    i2s_set_pin(I2S_NUM_0, &pins);

    const int   sampleRate = 16000;
    const float freq = 1000.0f;
    const int   totalSamples = sampleRate * 1.2;   // ~1.2 s
    size_t wrote;
    for (int i = 0; i < totalSamples; i++) {
        int16_t s = (int16_t)(sinf(2.0f * PI * freq * i / sampleRate) * 7000);
        int16_t frame[2] = {s, s};               // L + R gelijk
        i2s_write(I2S_NUM_0, frame, sizeof(frame), &wrote, portMAX_DELAY);
    }

    i2s_zero_dma_buffer(I2S_NUM_0);
    i2s_driver_uninstall(I2S_NUM_0);
    digitalWrite(PIN_AUDIO_SD, LOW);             // amp terug in shutdown
    Serial.println("  audio-toon klaar, amp uit");
}

// Speelt een ingebedde PCM-clip (mono int16) via de MAX98357A. Blocking —
// duurt zolang de clip (~3 s); prima voor een knop-getriggerde status-melding.
void playClip(const int16_t* pcm, uint32_t len, uint32_t rate) {
    Serial.printf("  audio: clip (%lu samples @ %lu Hz)\n",
                  (unsigned long)len, (unsigned long)rate);
    digitalWrite(PIN_AUDIO_SD, HIGH);

    i2s_config_t cfg = {};
    cfg.mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX);
    cfg.sample_rate = rate;
    cfg.bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT;
    cfg.channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT;
    cfg.communication_format = I2S_COMM_FORMAT_STAND_I2S;
    cfg.intr_alloc_flags = 0;
    cfg.dma_buf_count = 8;
    cfg.dma_buf_len = 256;
    cfg.use_apll = false;
    cfg.tx_desc_auto_clear = true;

    i2s_pin_config_t pins = {};
    pins.bck_io_num = PIN_I2S_BCLK;
    pins.ws_io_num = PIN_I2S_LRC;
    pins.data_out_num = PIN_I2S_DIN;
    pins.data_in_num = I2S_PIN_NO_CHANGE;

    if (i2s_driver_install(I2S_NUM_0, &cfg, 0, NULL) != ESP_OK) {
        Serial.println("  FOUT: I2S kon niet starten");
        digitalWrite(PIN_AUDIO_SD, LOW);
        return;
    }
    i2s_set_pin(I2S_NUM_0, &pins);

    size_t wrote;
    for (uint32_t i = 0; i < len; i++) {
        int16_t frame[2] = {pcm[i], pcm[i]};     // mono → L + R
        i2s_write(I2S_NUM_0, frame, sizeof(frame), &wrote, portMAX_DELAY);
    }
    i2s_zero_dma_buffer(I2S_NUM_0);
    i2s_driver_uninstall(I2S_NUM_0);
    digitalWrite(PIN_AUDIO_SD, LOW);
    Serial.println("  audio klaar");
}

// ═════════════════════════════════════════════════════════
//  I2C-scanner — debug-hulp bij 'DRV niet gevonden'
// ═════════════════════════════════════════════════════════
void scanI2C() {
    Serial.println("  I2C-scan op SDA=D4/SCL=D5:");
    int found = 0;
    for (uint8_t addr = 1; addr < 127; addr++) {
        Wire.beginTransmission(addr);
        if (Wire.endTransmission() == 0) {
            Serial.printf("   - device op 0x%02X\n", addr);
            found++;
        }
    }
    if (found == 0) Serial.println("   geen devices gevonden (check bedrading/voeding)");
}

// ═════════════════════════════════════════════════════════
//  Serieel menu
// ═════════════════════════════════════════════════════════
void printMenu() {
    Serial.println();
    Serial.println("─── SensePath handvat — bring-up test ───");
    Serial.println("  m = motor AAN/UIT togglen (vol vermogen)");
    Serial.println("  1 = motor ROM-effecten");
    Serial.println("  2 = motor RTP-ramp");
    Serial.println("  3 = servo volledige slag (onder- <-> bovenrand)");
    Serial.println("  n = servo naar nulpunt");
    Serial.println("  c = servo HERKALIBREREN  → jog met ] (omhoog) en [ (omlaag)");
    Serial.println("                          knop markeert de 2 limieten");
    Serial.println("  x = kalibratie stoppen / d = servo loskoppelen (nood)");
    Serial.println("  4 = audio 1kHz toon (MAX98357A + speaker)");
    Serial.println("  i = I2C-scan");
    Serial.println("  ? = dit menu");
    Serial.println("  (HOTUT-knop togglet de motor; servo kan nooit blokkeren)");
    Serial.println("─────────────────────────────────────────");
}

void handleSerial() {
    if (!Serial.available()) return;
    char c = Serial.read();
    switch (c) {
        case 'm': case 'M': setMotor(!motorOn); break;
        case '1': testMotorEffects(); break;
        case '2': testMotorRamp();    break;
        case '3': testServoSweep();   break;
        case 'c': case 'C': startCalibration(); break;
        case ']': jogServo(+JOG_STEP_US); break;
        case '[': jogServo(-JOG_STEP_US); break;
        case 'n': case 'N':
            ensureServoAttached();
            servoTargetUs = SERVO_CENTER_US;
            Serial.printf("  servo -> nulpunt %d us\n", SERVO_CENTER_US);
            break;
        case 'x': case 'X':
            calMode = false;
            servoTargetUs = servoUs;         // stop direct waar hij is
            Serial.println("  KALIBRATIE gestopt, servo blijft staan");
            break;
        case 'd': case 'D': detachServo(); break;
        case '4': testAudioTone();    break;
        case '5': dispatchCue(sensepath::CUE_TURN_RIGHT); break;  // test M4 crescendo rechts
        case '6': dispatchCue(sensepath::CUE_TURN_LEFT);  break;  // test M4 crescendo links
        case '7':                                                 // test: 1 lange sterke puls
            hapticClear();
            hapticPulse(600, 100, 0, 50);
            hapticBegin("test lange puls 100%");
            break;
        case '8': hapticWake(); break;                            // test wake-patroon
        case '9': pendingClip = 1; break;                         // test ETA-zin
        case '0': pendingClip = 2; break;                         // test locatie-zin
        case 'a': case 'A':
            Serial.print(">>> Handvat MAC: ");
            Serial.println(WiFi.macAddress());
            break;
        case 'g': case 'G':
            Serial.printf("  LINK: rx=%lu cue=%u cueId=%u dispatched=%lu patroon=%s actief=%d\n",
                          (unsigned long)linkRxCount, linkCue, linkCueId,
                          (unsigned long)cueDispatchCount, pat.name, pat.active);
            break;
        case 'i': case 'I': scanI2C(); break;
        case '?': case 'h': printMenu(); break;
        case '\n': case '\r': break;
        default: Serial.printf("  onbekend commando '%c' — '?' voor menu\n", c);
    }
}

// ═════════════════════════════════════════════════════════
void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println();
    Serial.println("=== SensePath HANDVAT bring-up (XIAO ESP32-S3) ===");

    pinMode(PIN_BUTTON, INPUT_PULLUP);
    pinMode(PIN_AUDIO_SD, OUTPUT);
    digitalWrite(PIN_AUDIO_SD, LOW);  // audio default uit

    setupDRV();
    loadSettings();   // app-instellingen uit NVS (sterkte, knop-acties, audio)

    // Gewekt uit deep-sleep? → warme bevestigingspuls (speelt in loop).
    if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_EXT0) {
        Serial.println("Gewekt uit deep-sleep (knop)");
        hapticWake();
    }

    setupNetwork();
    setupWebServer();
    printMenu();
}

void loop() {
    server.handleClient();   // telefoon-app serveren + twin-polling beantwoorden
    serviceLink();
    handleSerial();
    pollButton();
    serviceServo();
    updateHaptics();
    if (pendingClip == 1)      { pendingClip = 0; playClip(eta_pcm, eta_len, eta_rate); }
    else if (pendingClip == 2) { pendingClip = 0; playClip(locatie_pcm, locatie_len, locatie_rate); }
    delay(1);
}
