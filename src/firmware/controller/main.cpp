// ═══════════════════════════════════════════════════════
// SensePath — CONTROLLER firmware (XIAO ESP32-C3)
//
// Wizard-of-Oz controller-module. Leest de KY-040 roterende encoder en
// stuurt de positie draadloos via ESP-NOW naar het handvat (ESP32-S3),
// dat op zijn beurt de servo (mechanisch kompas) aanstuurt.
//
// Pinout (uit docs/wiring.md, XIAO ESP32-C3 — gebruik de Dx-labels):
//   Encoder CLK (A)  D0  → KY-040 CLK   (interrupt)
//   Encoder DT  (B)  D1  → KY-040 DT
//   Encoder SW       D2  → KY-040 drukknop (interne pull-up)
//   Encoder +        3V3
//   Encoder GND      GND
// ═══════════════════════════════════════════════════════

#include <Arduino.h>
#include <WiFi.h>
#include <esp_now.h>
#include <esp_wifi.h>

#include "protocol.h"
#include "secrets.h"   // WIFI_SSID + WIFI_PASSWORD van de hotspot (lokaal, gitignored)

// ─── Pinnen (Dx-labels van het XIAO-C3 board) ────────────
// Servo-rotatie-encoder (de goede) op D3/D4/D5.
constexpr uint8_t PIN_ENC_CLK  = D3;
constexpr uint8_t PIN_ENC_DT   = D4;
constexpr uint8_t PIN_ENC_SW   = D5;
// Oude encoder: enkel zijn drukknop gebruiken voor de afslag-cues.
constexpr uint8_t PIN_CUE_SW   = D2;

// ─── Encoder-positie (robuuste quadrature-decoder) ───────
// Telt precies 1 stap per detent en negeert contact-bounce via een
// transitietabel: lrsum bereikt alleen ±4 na een volledige geldige
// klik-sequentie. Interrupt op BEIDE pinnen (CLK én DT), CHANGE.
volatile int32_t encPos = 0;
volatile uint8_t encMem = 3;
volatile int8_t  encSum = 0;
const int8_t ENC_TRANS[16] = {0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0};

void IRAM_ATTR onEncoder() {
    encMem = ((encMem & 0x03) << 2) | (digitalRead(PIN_ENC_CLK) << 1) | digitalRead(PIN_ENC_DT);
    encSum += ENC_TRANS[encMem & 0x0f];
    if (encSum >= 4)      { encPos++; encSum = 0; }   // 1 detent met de klok mee
    else if (encSum <= -4){ encPos--; encSum = 0; }   // 1 detent tegen de klok in
}

// Gevoeligheid: elke encoder-detent telt ENC_SCALE keer mee → minder draaien
// nodig om de bol naar de rand te brengen (~90° i.p.v. ~275°).
constexpr int ENC_SCALE = 3;

// ─── Cue-state (afslag-waarschuwingen via oude encoder-knop) ─
uint8_t curCue = sensepath::CUE_NONE;
uint8_t cueId  = 0;                 // hoogt op bij elke nieuwe cue
uint32_t cueBtnTotalDbg = 0;        // diagnose: totaal aantal D2-drukken

void fireCue(uint8_t cue, const char* naam) {
    curCue = cue;
    cueId++;
    Serial.printf("CUE afgevuurd: %s (id=%u)\n", naam, cueId);
}

// ─── ESP-NOW ─────────────────────────────────────────────
esp_now_peer_info_t peer = {};
uint8_t  seq = 0;
uint32_t lastSendMs = 0;
uint32_t sentOk = 0, sentFail = 0;

void onSent(const uint8_t* mac, esp_now_send_status_t status) {
    if (status == ESP_NOW_SEND_SUCCESS) sentOk++;
    else                                sentFail++;
}

// WiFi-presets uit secrets.h, in volgorde van voorkeur geprobeerd
// (identiek aan handle/secrets.h zodat beide op hetzelfde kanaal komen).
struct WifiPreset { const char* ssid; const char* pass; };
static WifiPreset WIFI_NETS[] = WIFI_PRESETS;
static const int  WIFI_N = sizeof(WIFI_NETS) / sizeof(WIFI_NETS[0]);

void setup() {
    Serial.begin(115200);
    delay(300);
    Serial.println();
    Serial.println("=== SensePath CONTROLLER (XIAO ESP32-C3) ===");

    pinMode(PIN_ENC_CLK, INPUT_PULLUP);
    pinMode(PIN_ENC_DT,  INPUT_PULLUP);
    pinMode(PIN_ENC_SW,  INPUT_PULLUP);
    pinMode(PIN_CUE_SW,  INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(PIN_ENC_CLK), onEncoder, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_ENC_DT),  onEncoder, CHANGE);

    // Join dezelfde hotspot als het handvat, zodat ESP-NOW automatisch op het
    // hotspot-kanaal zit. Lukt de hotspot niet, terugval op kanaal 1 (zoals het
    // handvat). De controller heeft GEEN webserver nodig; het joint de WiFi enkel
    // om op het juiste ESP-NOW-kanaal te komen.
    WiFi.mode(WIFI_STA);
    // Probeer elke preset (max 10 s) tot er één verbindt.
    for (int i = 0; i < WIFI_N && WiFi.status() != WL_CONNECTED; i++) {
        Serial.printf("WiFi proberen: '%s' ", WIFI_NETS[i].ssid);
        WiFi.begin(WIFI_NETS[i].ssid, WIFI_NETS[i].pass);
        uint32_t wt0 = millis();
        while (WiFi.status() != WL_CONNECTED && millis() - wt0 < 10000) { delay(300); Serial.print("."); }
        Serial.println();
        if (WiFi.status() != WL_CONNECTED) WiFi.disconnect();
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.printf("Verbonden met '%s', kanaal %d (ESP-NOW volgt dit)\n",
                      WiFi.SSID().c_str(), WiFi.channel());
    } else {
        WiFi.disconnect();
        esp_wifi_set_channel(sensepath::ESPNOW_CHANNEL, WIFI_SECOND_CHAN_NONE);
        Serial.println("Geen netwerk gevonden -> ESP-NOW terugval op kanaal 1");
    }
    esp_wifi_set_ps(WIFI_PS_NONE);   // power-save uit -> stabielere ESP-NOW
    Serial.print("Controller MAC: ");
    Serial.println(WiFi.macAddress());

    if (esp_now_init() != ESP_OK) {
        Serial.println("FOUT: ESP-NOW init mislukt");
        return;
    }
    esp_now_register_send_cb(onSent);

    memcpy(peer.peer_addr, sensepath::HANDLE_MAC, 6);
    peer.channel = 0;   // 0 = huidig kanaal (volgt de hotspot, of de terugval op 1)
    peer.encrypt = false;
    if (esp_now_add_peer(&peer) != ESP_OK) {
        Serial.println("FOUT: peer (handvat) toevoegen mislukt");
        return;
    }
    Serial.printf("ESP-NOW zender klaar, kanaal %d. Draai de encoder.\n",
                  sensepath::ESPNOW_CHANNEL);
}

void loop() {
    uint32_t now = millis();

    // (Recenter zit nu aan de handvat-kant: de knop-bit gaat mee in het pakket;
    //  het handvat zet de huidige encoder-stand als nieuw midden.)

    // Afslag-knop (oude encoder, D2): 1x druk = rechts, 2x = links.
    static int cueLast = HIGH;
    static uint32_t cueLastChange = 0, cueFirstPress = 0;
    static uint8_t cuePresses = 0;
    constexpr uint32_t DOUBLE_WINDOW_MS = 350;
    static uint32_t cueBtnTotal = 0;     // diagnose: totaal aantal drukken op D2
    int cueBtn = digitalRead(PIN_CUE_SW);
    if (cueBtn != cueLast && now - cueLastChange > 30) {
        cueLastChange = now;
        if (cueBtn == LOW) {             // ingedrukt
            cueBtnTotal++;
            if (cuePresses == 0) { cueFirstPress = now; cuePresses = 1; }
            else                 { cuePresses = 2; }
        }
        cueLast = cueBtn;
    }
    cueBtnTotalDbg = cueBtnTotal;
    if (cuePresses > 0 && now - cueFirstPress > DOUBLE_WINDOW_MS) {
        if (cuePresses == 1) fireCue(sensepath::CUE_TURN_RIGHT, "afslag RECHTS");
        else                 fireCue(sensepath::CUE_TURN_LEFT,  "afslag LINKS");
        cuePresses = 0;
    }

    if (now - lastSendMs < 20) return;   // ~50 Hz
    lastSendMs = now;

    noInterrupts();
    int32_t pos = encPos;
    interrupts();

    sensepath::EncoderUpdate u;
    u.version  = sensepath::PROTOCOL_VERSION;
    u.absolute = (int16_t)(pos * ENC_SCALE);
    u.delta    = 0;
    u.buttons  = (digitalRead(PIN_ENC_SW) == LOW) ? 1 : 0;
    u.cue      = curCue;
    u.cueId    = cueId;
    u.sequence = seq++;
    esp_now_send(sensepath::HANDLE_MAC, (const uint8_t*)&u, sizeof(u));

    // elke ~500 ms een statusregel voor debug
    static uint32_t lastDbg = 0;
    if (now - lastDbg >= 500) {
        lastDbg = now;
        Serial.printf("encoder=%ld  recenter-knop=%d  afslag-drukken=%lu  cueId=%u  tx_ok=%lu\n",
                      (long)pos, u.buttons, (unsigned long)cueBtnTotalDbg, cueId,
                      (unsigned long)sentOk);
    }
}
