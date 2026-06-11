# Build guide → SensePath MVP-prototype

> Bouwinstructies voor **ons MVP-prototype**, niet voor het beoogde eindproduct. Zie de [Deliver-sectie in de hoofdrapportage](../README.md#deliver) voor wat in een productie-versie nog toegevoegd zou worden (RTK GNSS-ontvangst, BLE-app, ToF-obstakeldetectie, PA6 + TPE-materialen).

Stap-voor-stap instructies om het SensePath MVP zelf te bouwen. Het systeem bestaat uit **drie modules** die elk afzonderlijk gebouwd worden:

- **Module A → Tech-handvat** (XIAO ESP32-S3 + servo + motor + audio + HOTUT-knop met dubbele rol + batterij; geen rocker-switch, power via deep-sleep) → secties 1 tot 5
- **Module B → Wizard-of-Oz controller** (XIAO ESP32-C3 + KY-040 encoder + eigen batterij) → sectie 6
- **Module C → Stok-onderstuk** (conventionele witte stok met M3-stud) → sectie 1.5 (samen met de print-stappen)

Lees eerst [bom.md](bom.md) voor de onderdelen en [wiring.md](wiring.md) voor het schakelschema. Geschatte bouwtijd: 6 → 10 uur (exclusief 3D-print). De controller-module voegt ongeveer 1.5 uur toe op de handvat-bouwtijd.

> Dit is een **werkversie**: voldoende om de bouwvolgorde te volgen, maar enkele detail-keuzes (firmware-pinout, ESP-NOW pairing, audio-volume defaults) worden tijdens de eindintegratie nog gefinetuned.

---

## Sectie 1 → 3D-print

### Bestanden

Open [cad/exports/](../cad/exports/) en download:
- `handvat_dev3_core.stl` ; PA6 buitenwand met gleufpositie + servo-cavity + batterij-cavity
- `handvat_dev3_kompas.stl` ; sferisch kompaselement, koppelt op servo-as
- `handvat_dev3_cap.stl` ; afsluit-dop met knop-, encoder- en switch-openingen

> Zolang de exports nog niet aanwezig zijn: open de NX-files in [cad/](../cad/) en exporteer zelf naar STL (export → faceted body → coarse mesh).

### Aanbevolen print-instellingen

| Parameter | Waarde | Opmerking |
|---|---|---|
| Laagdikte | 0.16 mm | Balans tussen detail en tijd |
| Infill | 40 % gyroid | Stevigheid handvat zonder gewichtspenalty |
| Wandlagen | 4 | Voor slijtvastheid grip-zone |
| Print-oriëntatie | Handvat verticaal, gleuf naar boven | Minimale supports |
| Supports | Tree, alleen overhangen >50° | Trees breken makkelijk vrij |
| Materiaal core | PA6 unfilled | Slag- en slijtvast |
| Materiaal cap | PETG (alt: PLA) | Vlotter te printen, minder belast |

### Post-processing

1. Supports verwijderen en gleuf-rand met fijn schuurpapier (P800) gladstrijken.
2. Heatset-insert M3 onderaan het tech-handvat plaatsen met soldeerbout-tip op 220 °C ; verticaal indrukken tot oppervlakte gelijk. Dit is de schroefverbinding met het stok-onderstuk.
3. Sferisch kompaselement op de servo-as schuiven (kruisbout meegeleverd met MG90S) en testen op vrije rotatie binnen de gleuf.

### Stok-onderstuk voorbereiden

1. Conventionele lange witte stok nemen (aluminium of glasvezel) ; we behouden de bestaande pin-tip aan het loop-uiteinde, exact zoals bij commerciële witte stokken.
2. Standaard handgreep van de stok verwijderen (meestal vastgelijmd of geklemd).
3. M3-stud (~15 mm) **epoxy-vast integreren** in het top-uiteinde van de stok, zorgvuldig gecentreerd en met voldoende uithardingstijd. Dit is het mannelijke deel van de schroefverbinding.
4. Na uitharding: het tech-handvat op de stud schroeven. Bij goed alignement is het tech-handvat dagelijks omwisselbaar met een standaard handgreep met M3-insert.

---

## Sectie 2 → Elektronica solderen

### Volgorde (zie [wiring.md](wiring.md) voor pinout)

1. **XIAO ESP32-S3** op een mini-perfboard solderen met header-strip aan onderzijde.
2. **DRV2605L breakout** ernaast monteren.
3. **TP4056 USB-C laadcircuit** op het perfboard plaatsen.
4. **MT3608 boost converter** ernaast ; output afregelen op 5 V vóór montage. Voedt zowel de MG90S servo (altijd actief) als de MAX98357A audio-amp (opt-in, via SD-pin gegated).
5. **MAX98357A I2S versterker** plaatsen. Belangrijk: SD-pin **niet floating laten** (onbepaald gedrag). Default-stand = stand-by via 100 kΩ pull-down naar GND, met software-override via XIAO D10 (zie stap 7). GAIN-pin direct aan GND voor 15 dB max gain.
6. **I2C-bedrading** tussen XIAO en DRV2605L:
   - XIAO D4 (SDA) → DRV2605L SDA
   - XIAO D5 (SCL) → DRV2605L SCL
   - XIAO 3V3 → DRV2605L Vin
   - XIAO GND → DRV2605L GND
7. **I2S-bedrading + SD-control + GAIN** tussen XIAO en MAX98357A:
   - XIAO D6 (GPIO 43) → MAX98357A BCLK
   - XIAO D7 (GPIO 44) → MAX98357A LRC
   - XIAO D8 (GPIO 7) → MAX98357A DIN
   - **XIAO D10 (GPIO 9) → MAX98357A SD** (software gate; LOW = shutdown, HIGH = amp aan)
   - **100 kΩ weerstand** tussen MAX98357A SD-pin en GND (pull-down voor gedefinieerde boot-state)
   - **MAX98357A GAIN → direct aan GND** (één jumperdraadje, geen weerstand) voor 15 dB max gain
   - MT3608 5V → MAX98357A Vin
   - GND gemeenschappelijk

   > **Niet floating laten**: SD-pin zonder verbinding leidt tot pseudo-random kanaal-selectie (4-staats input) en pop-geluiden. De pull-down + GPIO-aansturing is essentieel.
8. **Coin vibration motor** ; 2× AWG28 draad van DRV2605L OUT+ en OUT− naar JST-PH 2-pin connector. Motor-zijde idem; polariteit is niet kritisch voor een ERM-coin motor.
9. **MG90S servo** ; standaard 3-pins JR-stekker:
   - Bruin (GND) → gemeenschappelijke GND
   - Rood (V+) → **5 V rail** uit MT3608 boost (zelfde rail als MAX98357A Vin) ; **niet** rechtstreeks aan Li-Po, want MG90S-datasheet vraagt 4.8-6 V
   - Oranje (signaal) → XIAO D9 (GPIO 8). 3.3 V PWM is voldoende voor de MG90S, geen level shifter nodig. Een 1 kΩ serie-weerstand is optioneel als defensieve GPIO-bescherming maar niet vereist
   - **Decoupling**: zet een **220-470 µF elco** tussen V+ en GND vlak bij de servo-stekker ; vangt stroompieken op zodat de XIAO niet reset
10. **HOTUT drukknop** (dubbele rol → functie + power-control via deep-sleep) ; 2-pins JST-PH connector:
    - Pin 1 (signaal) → XIAO D3 (= GPIO 4, RTC-GPIO ; vereist voor EXT0 wake-up uit deep-sleep)
    - Pin 2 → GND
    - Geen externe pull-up nodig (XIAO interne pull-up wordt in firmware geactiveerd)
11. **Geen rocker switch** in deze configuratie. TP4056 OUT+ gaat **direct** naar XIAO 5V-pad én MT3608 input. Power-control zit in de firmware (zie sectie 3 → long-press triggert deep-sleep, druk uit deep-sleep wekt opnieuw via EXT0 op D3).
12. **Speaker** ; 2-pins JST-PH connector vanaf MAX98357A speaker-output naar de mini-speaker.
13. **Batterij** ; Li-Po via JST-PH 2-pin connector aan TP4056 BAT+ / BAT−.
14. **USB-C laad-poort** ; KUOQIY 2-draads breakout (VBUS + GND) doorgelust naar TP4056 IN+ / IN−. Deze externe USB-C is **alleen voor opladen** ; firmware-flashen gebeurt via de USB-C poort op de XIAO ESP32-S3 zelf.

> De KY-040 encoder zit **niet** in het handvat. Die hangt aan de aparte controller-module ; zie [Sectie 6 → Controller-module bouwen](#sectie-6--controller-module-bouwen).

### Solder-tips

- Gebruik flux op de XIAO-pads ; klein formaat, makkelijk overspringen.
- Coin motor draden zijn dun (AWG30) ; krimpkous na elke soldeer voor trekontlasting.
- I2C-bedrading kort houden (<10 cm) om ruis te vermijden.
- I2S-bedrading idem: zo kort mogelijk, anders treedt aliasing-ruis op.
- Servo-voeding: plaats de **220-470 µF elco** tussen servo V+ en GND zo dicht mogelijk bij de servo-stekker (niet aan de MT3608-uitgang) ; daar vangt hij de korte stroompieken het effectiefst op.
- Li-Po: nooit batterij solderen onder spanning. Altijd via JST-connector aansluiten zodat ze later veilig losgekoppeld kan worden.

---

## Sectie 3 → Firmware flashen

### Arduino IDE setup

1. **Board manager URL**: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
2. **Install**: `esp32` board package (versie 2.0.14 of hoger).
3. **Selecteer board**: Tools → Board → ESP32 Arduino → XIAO_ESP32S3.
4. **Libraries** via Library Manager:
   - `Adafruit DRV2605 Library` (versie 1.2.x of hoger)
   - `ESP32Servo` (voor MG90S aansturing)
   - `ESP32-audioI2S` of `AudioFileSourcePROGMEM` + `AudioOutputI2S` (voor audio-fallback)
   - Eventueel `Encoder` library (Paul Stoffregen) voor KY-040, of zelf interrupt-handler schrijven

### Code

Open [../src/firmware/sensepath_esp32/sensepath_esp32.ino](../src/firmware/sensepath_esp32/sensepath_esp32.ino).

**Belangrijk**: de huidige firmware in de repo dateert van vóór de finale integratie en is geschreven voor de ESP32 DevKit. Bij de finale build moet de **handvat-firmware** code:
- I2C-pinnen aanpassen naar XIAO (SDA = 5, SCL = 6).
- Een ESP-NOW-ontvanger toevoegen die encoder-updates leest van de controller-module (zie sectie 6) en de servo-doelhoek bijwerkt.
- Een servo-aansturing via ESP32Servo aansluiten op D9.
- Een I2S-audio-pipeline opzetten op D6/D7/D8 met **D10 als SD-pin gate** (HIGH = amp aan, LOW = stand-by).
- **HOTUT-knop press-detector** (D3, RTC-GPIO 4) met onderscheid tussen short-press, double-press en long-press (≥3 s). Long-press triggert de power-down sequence:
  1. Speel een korte vibratie-cue (1 puls van 100 ms via DRV2605L) als acknowledgement
  2. `digitalWrite(AUDIO_SD_PIN, LOW)` → audio-amp in stand-by
  3. Servo naar neutraalpositie (90°), dan `servo.detach()` om PWM uit te zetten
  4. `esp_sleep_enable_ext0_wakeup(GPIO_NUM_4, 0)` → wake op falling edge van HOTUT
  5. `esp_deep_sleep_start()` → XIAO gaat slapen, ~14 µA draw

  Bij wake-up boot de XIAO opnieuw vanaf `setup()` ; geen "resume from sleep" gedrag.

De **controller-firmware** (apart project, draait op de XIAO ESP32-C3) moet de KY-040 uitlezen en via ESP-NOW de positie versturen naar het MAC-adres van de handvat-S3. Beide firmware-projecten worden los geflasht.

### Flash

1. XIAO via USB-C verbinden (de USB-C poort van het handvat dient dus dubbel ; opladen + flashen).
2. Serial Monitor openen op 115200 baud.
3. Upload via Sketch → Upload.
4. Na boot verschijnt in Serial Monitor:
   ```
   SensePath start
   DRV2605L gevonden op 0x5A
   ESP32Servo gestart op D9
   Encoder gestart op D0/D1, knop op D2
   AP gestart, IP: 192.168.4.1
   Webserver start
   ```

---

## Sectie 4 → Assembleren

1. Perfboard met XIAO + DRV2605L + TP4056 + MT3608 + MAX98357A in de handvat-core schuiven, oriëntatie zo dat de USB-C laad-poort en de HOTUT drukknop toegankelijk blijven via hun respectievelijke openingen in de cap. Geen rocker-opening meer nodig.
2. **MG90S servo** in zijn aparte cavity plaatsen, servo-as in lijn met de kompasbol-rotatie-as. Servo vastschroeven met de 2× M2-meegeleverde schroefjes.
3. **Kompasbol** op de servo-as schuiven (kruisarm-adapter), uitlijning controleren door de servo handmatig te draaien.
4. **Li-Po batterij** in zijn aparte cavity plaatsen, dubbelzijdige tape voor fixatie, JST-connector aansluiten op TP4056.
5. **Coin vibration motor** met dubbelzijdige 3M-VHB tape tegen de hypothenar-zijde van de handvat-wand fixeren (zo dicht mogelijk bij de muis-van-de-hand; dat is de meest gevoelige perceptiezone uit Develop 2).
6. **Speaker** in de cap-opening klikken, JST-connector aansluiten op MAX98357A.
7. **Cap** met 2× M3-schroeven (8 mm) sluiten.

---

## Sectie 5 → Handvat testen (los van controller)

### Functionele check (zonder controller, via WiFi-fallback)

1. Li-Po-stekker aansluiten op TP4056 ; de XIAO ESP32-S3 moet binnen ~1 s booten (LED op de XIAO knippert). Bij eerste aansluiting boot het handvat altijd op (geen latching aan/uit-mechaniek).
2. Voor losse handvat-test: smartphone WiFi → verbinden met SSID `SensePath`, wachtwoord `sensepath`. Browser → `http://192.168.4.1/`. (Voor de echte sessie: zie sectie 7 → integratie.)
3. **Coin motor test**: trigger M4 (obstakel) → twee korte trillingen voelbaar.
4. **Coin motor test**: trigger M6 (koersafwijking) → drie snelle trillingen.
5. **Coin motor test**: trigger M9 (bocht-aankondiging) → één langere oplopende trilling.
6. **Drukknop short-press test**: HOTUT-knop kort indrukken ; status-melding in Serial Monitor (start/stop route).
7. **Drukknop long-press test**: HOTUT-knop ≥3 s ingedrukt houden ; korte vibratie-cue als acknowledgement, dan stilte (XIAO in deep-sleep). Stroommeting via USB-C inline meter moet ~10 mA draw tonen i.p.v. ~40 mA.
8. **Wake-up test**: HOTUT kort indrukken vanuit deep-sleep ; XIAO boot opnieuw, "SensePath start" verschijnt in Serial Monitor.
9. **Audio test (opt-in)**: via webcontroller audio-fallback inschakelen → MAX98357A SD-pin gaat HIGH → kort testbericht "audio actief" hoorbaar via speaker.
10. **Laadtest**: USB-C kabel in de handvat-USB-C laad-poort steken → rode LED op TP4056 (laden) brandt; volle laad → blauwe LED.

### Acceptatiecriteria handvat

- Coin motor voelbaar in de hand zonder bijgeluiden (zo niet → motor niet stevig genoeg tegen handvat-wand).
- Knop reageert binnen <50 ms voor short-press (zo niet → debounce-time-out in firmware verhogen).
- Long-press detecteerbaar bij precies 3 s ingedrukt houden ; geen accidentele triggers bij langere short-press (>500 ms maar <3 s).
- DRV2605L wordt herkend → "DRV2605L gevonden" in Serial Monitor.
- TP4056 LED's: rood bij laden, blauw bij volle accu. Handvat moet autonoom werken op Li-Po na unplug van USB-C.
- Deep-sleep current draw ~10 mA bij stroommeting (XIAO in slaap, andere componenten quiescent).

---

## Sectie 6 → Controller-module bouwen

De controller is een **fysiek aparte unit** die de testleider in de hand houdt. Klein 3D-geprint doosje (~60 × 40 × 25 mm) met de KY-040 encoder bovenaan, een rocker-switch en USB-C poort op de zijkant.

### Componenten

Zie [bom.md sectie 9 → 12](bom.md). Kort: XIAO ESP32-C3, KY-040 encoder, Li-Po 1000 mAh, TP4056 USB-C, rocker switch, USB-C laad-poort, mini perfboard.

### Soldeerstappen controller

1. **XIAO ESP32-C3** op een klein perfboard solderen met header-strip aan onderzijde.
2. **TP4056 USB-C laadcircuit** ernaast plaatsen.
3. **Voeding**:
   - TP4056 BAT+ ↔ Li-Po + (via JST-PH)
   - TP4056 BAT- ↔ Li-Po - (via JST-PH)
   - TP4056 OUT+ → rocker-switch → XIAO 5V-pad
   - TP4056 GND → gemeenschappelijke GND-bus
   - USB-C female VBUS / GND → TP4056 IN+ / IN-
4. **KY-040 encoder bedrading** (5-pins, korte draadjes):
   - Encoder + (Vcc) → XIAO 3V3
   - Encoder GND → gemeenschappelijke GND
   - Encoder CLK → XIAO D0
   - Encoder DT → XIAO D1
   - Encoder SW → XIAO D2

### Firmware controller

Aparte sketch voor de ESP32-C3. Pseudocode:

```
1. Init WiFi in station mode (geen AP) for ESP-NOW
2. Init ESP-NOW with handvat-S3 MAC-adres als peer
3. Init KY-040 pins als input met interne pull-up
4. Hardware-interrupt op encoder CLK → update absolute positie
5. Hoofdlus: elke 20 ms (~50 Hz) een EncoderUpdate-pakket versturen
```

De MAC-adres van de handvat-S3 wordt eenmalig hardcoded in de controller-sketch (of via een pairing-procedure bij eerste boot).

### Test controller los

1. Rocker AAN → XIAO C3 boot.
2. Serial Monitor (via USB-C op de C3) toont encoder-deltas terwijl je draait.
3. Controleer dat ESP-NOW pakketten verstuurd worden (success-callback prints in Serial).

### Behuizing controller

3D-geprint doosje, twee helften die met M2 of M3-schroefjes sluiten. Openingen: KY-040 encoder bovenaan (knop en knurled wiel), rocker-switch zijkant, USB-C poort zijkant.

---

## Sectie 7 → Integratie + Deliver-test

### Pairing controller ↔ handvat

1. Beide modules op AAN zetten.
2. Handvat-firmware moet "ESP-NOW receiver actief" tonen in Serial Monitor.
3. Controller-firmware moet "ESP-NOW peer geconfigureerd" tonen.
4. Encoder draaien op de controller → de servo in het handvat moet 1-op-1 meedraaien binnen ~100 ms.

### Volgende stap → echte testsessie

Wizard-of-Oz testsessie opzetten met een echte gebruiker. Zie [reports and protocols/protocol_sensepath_develop3_PDF.pdf](../reports%20and%20protocols/protocol_sensepath_develop3_PDF.pdf) voor het testprotocol dat we eerder gebruikten. Voor de Deliver-validatie: testleider houdt de controller-module vast en draait de KY-040 encoder terwijl hij of zij achter de gebruiker loopt, en de blinde gebruiker volgt het mechanisch kompas + de drie haptische cues op een onbekende route. De controller-module zorgt dat de testleider niet langer een telefoon-webpagina hoeft te bedienen ; rotatie is fysiek, direct, met haptische klik per stap.

---

## Troubleshooting

| Symptoom | Vermoedelijke oorzaak | Fix |
|---|---|---|
| DRV2605L niet gevonden | I2C-bedrading gekruist, of pinnen niet ingesteld | Pinout checken in [wiring.md](wiring.md), I2C-scanner sketch draaien |
| Coin motor voelt zwakjes | Motor niet stevig tegen handvat-wand | Meer VHB-tape, of motor verplaatsen naar hypothenar-zijde |
| Servo trilt of jittert | Voeding instabiel (te kleine of geen elco), of PWM-signaal te dichtbij ruisbron | Vergroot decoupling cap naar 220-470 µF op servo V+-lijn, plaatsen vlak bij servo-stekker. Signaaldraad weghouden van I2S-lijnen |
| XIAO reset bij servo-beweging | Stroompiek van servo doet 5 V rail kortstondig inzakken | Decoupling-elco vergroten of dichter bij servo zetten ; eventueel MT3608 output checken op 5.0 V (niet 4.5 V) |
| Encoder slaat stappen over | Debounce-tijd te kort of interrupts niet geconfigureerd | Hardware-interrupt op CLK gebruiken (`attachInterrupt`) ipv polling |
| Knop registreert dubbel | Debounce te kort | `BUTTON_DEBOUNCE_MS` in firmware naar 50 ms verhogen |
| WiFi AP niet zichtbaar | XIAO niet juist geboot | Serial Monitor checken, eventueel reset-knop |
| Audio ruis of vervormd | Boost converter niet stabiel op 5 V, of I2S-pinnen gekruist | Boost-uitgang met multimeter checken, I2S BCLK/LRC pinout verifiëren |
| Trilling vibrato/onstabiel | Power-supply ruis | Decoupling cap op DRV2605L Vin (10 µF) |
| Handvat laadt niet op USB-C | TP4056 IN+/IN− niet correct doorgelust | USB-C breakout-board pinout checken, polariteit verifiëren |
| Handvat schakelt uit kort na boot | Li-Po onder discharge-cutoff | Opladen ; TP4056 schakelt uit onder ~2.5 V om de accu te beschermen |
| Handvat gaat niet in deep-sleep bij long-press | Long-press detectie niet ingebouwd, of `esp_sleep_enable_ext0_wakeup` niet correct geconfigureerd | Firmware long-press timer checken (≥3 s), `esp_deep_sleep_start()` aanroep verifiëren, RTC-GPIO 4 als wake-pin bevestigen |
| Handvat wakkert niet uit deep-sleep | EXT0 wake-up trigger niet armed of HOTUT niet correct bedraad | `esp_sleep_enable_ext0_wakeup(GPIO_NUM_4, 0)` aanroepen vóór `esp_deep_sleep_start()`, HOTUT pin-bedrading naar D3 verifiëren |
| Hoge stroom in "uit"-stand (>20 mA) | XIAO niet in echte deep-sleep, of MT3608 trekt te veel quiescent | Serial Monitor uitlezen tijdens transitie, MT3608 quiescent meten met multimeter (verwacht ~1-3 mA) |
