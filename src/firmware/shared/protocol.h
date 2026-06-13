// ═══════════════════════════════════════════════════════
// SensePath — gedeeld ESP-NOW protocol tussen controller en handvat.
// Beide modules includen dit bestand zodat het packet-formaat nooit
// uit elkaar loopt. (Nog niet gebruikt in de bring-up firmware.)
// ═══════════════════════════════════════════════════════
#pragma once
#include <stdint.h>

namespace sensepath {

// Protocol-versie. Verhoog bij elke wijziging van EncoderUpdate.
constexpr uint8_t PROTOCOL_VERSION = 2;

// ESP-NOW WiFi-kanaal. Controller en handvat MOETEN gelijk zijn.
constexpr uint8_t ESPNOW_CHANNEL = 1;

// MAC-adres van het handvat (XIAO ESP32-S3), peer voor de controller.
// Uitgelezen via WiFi.macAddress() op de S3 (commando 'a' in de handvat-firmware).
constexpr uint8_t HANDLE_MAC[6] = {0x1C, 0xDB, 0xD4, 0x75, 0x57, 0x0C};

// Discrete haptische cues die de wizard kan afvuren.
enum Cue : uint8_t {
    CUE_NONE = 0,
    CUE_TURN_RIGHT = 1,  // afslag rechts over 5 m  → M4 crescendo
    CUE_TURN_LEFT  = 2,  // afslag links over 5 m   → M4 crescendo
    CUE_STRAIGHT   = 3,  // rechtdoor / on-course    → M5 tik
    CUE_OFFROUTE   = 4,  // van route af             → M6 ademend
    CUE_ARRIVED    = 5,  // bestemming bereikt       → M8 warme puls
    CUE_BATTERY    = 6,  // batterij laag (nep, WoZ) → M9 triple-tick
};

// Pakket dat de controller ~50 Hz naar het handvat stuurt.
struct __attribute__((packed)) EncoderUpdate {
    uint8_t version;  // = PROTOCOL_VERSION
    int16_t absolute; // encoder-positie → servo-kompas
    int16_t delta;    // rotatie sinds vorige update
    uint8_t buttons;  // bit0 = encoder-SW ingedrukt
    uint8_t cue;      // huidige Cue-waarde
    uint8_t cueId;    // hoogt op bij ELKE nieuwe cue → handvat triggert op verandering
    uint8_t sequence; // wraparound-teller voor packet-loss-detectie
};

}  // namespace sensepath
