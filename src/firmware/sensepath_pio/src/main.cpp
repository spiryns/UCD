// ═══════════════════════════════════════════════════════
// SensePath ; trilmotor test + OTA
// Voor XIAO ESP32-S3 + DRV2605L + coin vibration motor
// ═══════════════════════════════════════════════════════

#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include <Adafruit_DRV2605.h>

// === WiFi atelier ===
const char* WIFI_SSID     = "interwebland_705";
const char* WIFI_PASSWORD = "MaDiWoeDo-1";

Adafruit_DRV2605 drv;

struct VibeEffect {
    uint8_t id;
    const char *name;
};

VibeEffect effects[] = {
    {1,  "Strong Click 100%"},
    {14, "Strong Buzz 100%"},
    {47, "Long Buzz (sustained)"},
    {15, "750 ms Alert 100%"},
    {10, "Double Click 100%"},
    {12, "Triple Click 100%"},
};
const int N_EFFECTS = sizeof(effects) / sizeof(effects[0]);

bool drvFound = false;

void delayOTA(unsigned long ms) {
    unsigned long start = millis();
    while (millis() - start < ms) {
        ArduinoOTA.handle();
        delay(10);
    }
}

void playEffect(uint8_t id) {
    if (!drvFound) return;
    drv.setWaveform(0, id);
    drv.setWaveform(1, 0);
    drv.go();
}

void setupWiFiAndOTA() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("WiFi connecting met ");
    Serial.print(WIFI_SSID);
    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < 15000) {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println();
        Serial.print("Verbonden! IP: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println();
        Serial.println("WiFi mislukt, fallback AP");
        WiFi.mode(WIFI_AP);
        WiFi.softAP("SensePath", "sensepath123");
        Serial.print("AP IP: ");
        Serial.println(WiFi.softAPIP());
    }

    ArduinoOTA.setHostname("sensepath");
    ArduinoOTA.onStart([]() { Serial.println(">>> OTA upload start"); });
    ArduinoOTA.onEnd([]()   { Serial.println("\n>>> OTA klaar, reboot"); });
    ArduinoOTA.onProgress([](unsigned int p, unsigned int t) {
        Serial.printf("OTA: %u%%\r", (p * 100) / t);
    });
    ArduinoOTA.begin();
    Serial.println("OTA listener actief");
}

void setup() {
    Serial.begin(115200);
    delay(1500);
    Serial.println();
    Serial.println("=== SensePath trilmotor + OTA ===");

    // I2C + DRV2605L
    Wire.begin();
    if (drv.begin()) {
        drvFound = true;
        Serial.println("OK: DRV2605L gevonden op 0x5A");
        drv.selectLibrary(1);
        drv.setMode(DRV2605_MODE_INTTRIG);
    } else {
        Serial.println("WAARSCHUWING: DRV2605L niet gevonden op 0x5A");
        Serial.println("              OTA blijft wel actief voor remote update");
    }

    // WiFi + OTA (altijd, ook bij DRV-fout)
    setupWiFiAndOTA();

    Serial.println();
    Serial.println("Start trilling-loop...");
    Serial.println();
}

void loop() {
    ArduinoOTA.handle();

    if (!drvFound) {
        delay(1000);
        return;
    }

    for (int i = 0; i < N_EFFECTS; i++) {
        Serial.printf("[%d/%d] effect %d: %s\n",
                      i + 1, N_EFFECTS, effects[i].id, effects[i].name);
        playEffect(effects[i].id);
        delayOTA(1500);
    }

    Serial.println("--- pauze 3 sec ---");
    Serial.println();
    delayOTA(3000);
}
