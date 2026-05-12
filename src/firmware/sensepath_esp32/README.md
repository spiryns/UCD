# SensePath firmware (XIAO ESP32-S3)

Prototypefirmware voor de XIAO ESP32-S3 + DRV2605L haptiekcontroller.

> De `.ino`-broncode in deze map dateert van vóór de migratie naar XIAO en gebruikt nog de oorspronkelijke ESP32 DevKit-pinout (SDA = 21, SCL = 22). Bij compilatie voor de finale MVP-build moeten de I2C-pinconstanten aangepast worden naar de XIAO-mapping (SDA = D4 = GPIO 5, SCL = D5 = GPIO 6). Zie [docs/wiring.md](../../../docs/wiring.md) en [docs/build_guide.md](../../../docs/build_guide.md) voor de volledige pinout en build-procedure.

## Hardware

- Seeed Studio XIAO ESP32-S3 (WiFi + BLE 5.0, onboard Li-Po laadondersteuning)
- Adafruit DRV2605L via I2C (ERM-modus voor coin vibratiemotor)
- Coin vibratiemotor 10 × 2.7 mm op de DRV2605L OUT-pinnen
- MG90S servo voor mechanisch kompas (PWM via D9)
- KY-040 roterende encoder als Wizard-of-Oz controller (CLK = D0, DT = D1, SW = D2)
- HOTUT IP67 drukknop op D3
- Optioneel: MAX98357A I2S audio-versterker + speaker (BCLK = D6, LRC = D7, DIN = D8)

## I2C-pinout (finale XIAO-build)

| Signaal | XIAO pin |
|---|---:|
| SDA | D4 (GPIO 5) |
| SCL | D5 (GPIO 6) |
| 3V3 | 3V3 |
| GND | GND |

## Arduino IDE

1. Board manager URL toevoegen: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
2. Installeer `esp32` board package (versie 2.0.14 of hoger).
3. Installeer libraries:
   - `Adafruit DRV2605 Library`
   - `ESP32Servo` (voor MG90S aansturing)
   - Optioneel `Encoder` (Paul Stoffregen) voor KY-040, of zelf interrupt-handler
4. Open `sensepath_esp32.ino`.
5. Pas de I2C-pinconstanten aan (zie note hierboven).
6. Kies Tools → Board → ESP32 Arduino → XIAO_ESP32S3.
7. Upload naar de XIAO via USB-C.

## Gebruik

Na opstarten verschijnt in Serial Monitor:

```text
SensePath start
DRV2605L gevonden
AP gestart, IP: 192.168.4.1
Webserver start
```

Verbind daarna met wifi:

- SSID: `SensePath`
- Wachtwoord: `sensepath`
- Controller: `http://192.168.4.1/`

## API

- `GET /api/status`
- `GET /api/pattern?name=m1`
- `GET /api/pattern?name=m4&direction=left`
- `GET /api/pattern?name=m4&direction=right`
- `GET /api/stop`
- `GET /api/intensity?level=low|medium|high`

Ondersteunde patronen: `m1`, `m2`, `m3`, `m4`, `m5`, `m6`, `m7`, `m8`, `m9`. De drie kernsignalen voor de Develop 3 + Deliver tests zijn `m4` (obstakel), `m6` (koersafwijking) en `m9` (bocht-aankondiging).
