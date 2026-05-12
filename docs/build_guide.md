# Build guide → SensePath finale integratie

Stap-voor-stap instructies om het SensePath-handvat zelf te bouwen. Lees eerst [bom.md](bom.md) voor de onderdelen en [wiring.md](wiring.md) voor het schakelschema. Geschatte bouwtijd: 5 → 8 uur (exclusief 3D-print).

> Dit is een **werkversie**: voldoende om de bouwvolgorde te volgen, maar enkele detail-keuzes (firmware-pinout, audio-volume defaults) worden tijdens de eindintegratie nog gefinetuned.

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
2. Heatset-inserts (M3) in de 2 montagegaten plaatsen met soldeerbout-tip op 220 °C ; verticaal indrukken tot oppervlakte gelijk.
3. Sferisch kompaselement op de servo-as schuiven (kruisbout meegeleverd met MG90S) en testen op vrije rotatie binnen de gleuf.

---

## Sectie 2 → Elektronica solderen

### Volgorde (zie [wiring.md](wiring.md) voor pinout)

1. **XIAO ESP32-S3** op een mini-perfboard solderen met header-strip aan onderzijde.
2. **DRV2605L breakout** ernaast monteren.
3. **TP4056 USB-C laadcircuit** op het perfboard plaatsen.
4. **MT3608 boost converter** ernaast (alleen actief bij audio-fallback ; output afregelen op 5 V vóór montage).
5. **MAX98357A I2S versterker** kunt u nu ook plaatsen, maar laat SD-pin open / naar GND in default-config om hem in stand-by te houden.
6. **I2C-bedrading** tussen XIAO en DRV2605L:
   - XIAO D4 (SDA) → DRV2605L SDA
   - XIAO D5 (SCL) → DRV2605L SCL
   - XIAO 3V3 → DRV2605L Vin
   - XIAO GND → DRV2605L GND
7. **I2S-bedrading** tussen XIAO en MAX98357A:
   - XIAO D6 (GPIO 43) → MAX98357A BCLK
   - XIAO D7 (GPIO 44) → MAX98357A LRC
   - XIAO D8 (GPIO 7) → MAX98357A DIN
   - MT3608 5V → MAX98357A Vin
   - GND gemeenschappelijk
8. **Coin vibration motor** ; 2× AWG28 draad van DRV2605L OUT+ en OUT− naar JST-PH 2-pin connector. Motor-zijde idem; polariteit is niet kritisch voor een ERM-coin motor.
9. **MG90S servo** ; standaard 3-pins JR-stekker:
   - Bruin (GND) → gemeenschappelijke GND
   - Rood (V+) → 3.7 V rail (Li-Po direct)
   - Oranje (signaal) → XIAO D9 (GPIO 8) via 1 kΩ serie-weerstand (beschermt GPIO bij short)
10. **KY-040 roterende encoder** ; 5-pins:
    - GND → GND
    - + (Vcc) → XIAO 3V3
    - CLK → XIAO D0
    - DT → XIAO D1
    - SW → XIAO D2
11. **HOTUT drukknop** ; 2-pins JST-PH connector:
    - Pin 1 (signaal) → XIAO D3
    - Pin 2 → GND
12. **SS12F44 schuifschakelaar** ; in serie met de positieve rail tussen Li-Po+ en XIAO 5V-pad / boost converter input.
13. **Speaker** ; 2-pins JST-PH connector vanaf MAX98357A speaker-output naar de mini-speaker.
14. **Batterij** ; Li-Po via JST-PH 2-pin connector aan TP4056 BAT+ / BAT−.
15. **USB-C connector** ; KUOQIY 4-pins breakout doorgelust:
    - VBUS + GND → TP4056 IN+ / IN−
    - D+ en D− → XIAO USB-data lijnen (voor firmware-flashen via dezelfde poort)

### Solder-tips

- Gebruik flux op de XIAO-pads ; klein formaat, makkelijk overspringen.
- Coin motor draden zijn dun (AWG30) ; krimpkous na elke soldeer voor trekontlasting.
- I2C-bedrading kort houden (<10 cm) om ruis te vermijden.
- I2S-bedrading idem: zo kort mogelijk, anders treedt aliasing-ruis op.
- Servo-signaal: gebruik een 1 kΩ serie-weerstand op de signaal-lijn om de XIAO GPIO te beschermen.
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

**Belangrijk**: de huidige firmware in de repo dateert van vóór de finale integratie en is geschreven voor de ESP32 DevKit. Bij de finale build moet de code:
- I2C-pinnen aanpassen naar XIAO (SDA = 5, SCL = 6).
- Een encoder-handler toevoegen die CLK/DT polt op D0/D1 en SW op D2.
- Een servo-aansturing via ESP32Servo aansluiten op D9.
- Een I2S-audio-pipeline opzetten op D6/D7/D8 met SD-pin van MAX98357A enabled wanneer audio-fallback actief.

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

1. Perfboard met XIAO + DRV2605L + TP4056 + MT3608 + MAX98357A in de handvat-core schuiven, oriëntatie zo dat de USB-C poort, de SS12F44 schuifschakelaar en de HOTUT drukknop toegankelijk blijven via hun respectievelijke openingen in de cap.
2. **MG90S servo** in zijn aparte cavity plaatsen, servo-as in lijn met de kompasbol-rotatie-as. Servo vastschroeven met de 2× M2-meegeleverde schroefjes.
3. **Kompasbol** op de servo-as schuiven (kruisarm-adapter), uitlijning controleren door de servo handmatig te draaien.
4. **Li-Po batterij** in zijn aparte cavity plaatsen, dubbelzijdige tape voor fixatie, JST-connector aansluiten op TP4056.
5. **Coin vibration motor** met dubbelzijdige 3M-VHB tape tegen de hypothenar-zijde van de handvat-wand fixeren (zo dicht mogelijk bij de muis-van-de-hand; dat is de meest gevoelige perceptiezone uit Develop 2).
6. **Speaker** in de cap-opening klikken, JST-connector aansluiten op MAX98357A.
7. **KY-040 encoder** in zijn opening in de cap monteren, 5-pins kabel naar het perfboard leiden. Bij wireless-variant: encoder in apart extern doosje monteren met eigen XIAO of ESP-NOW koppeling.
8. **Cap** met 2× M3-schroeven (8 mm) sluiten.

---

## Sectie 5 → Testen

### Functionele check

1. SS12F44 op AAN zetten ; de XIAO moet booten (LED op de XIAO knippert).
2. Smartphone WiFi → verbinden met SSID `SensePath`, wachtwoord `sensepath`.
3. Browser → `http://192.168.4.1/`.
4. **Coin motor test**: trigger M4 (obstakel) → twee korte trillingen voelbaar.
5. **Coin motor test**: trigger M6 (koersafwijking) → drie snelle trillingen.
6. **Coin motor test**: trigger M9 (bocht-aankondiging) → één langere oplopende trilling.
7. **Servo test**: draai de KY-040 encoder ; de kompasbol moet meedraaien in de handpalm.
8. **Drukknop test**: HOTUT-knop indrukken ; status-melding in Serial Monitor.
9. **Audio test (opt-in)**: via webcontroller audio-fallback inschakelen → boost converter activeert → kort testbericht "audio actief" hoorbaar via speaker.
10. **Laadtest**: USB-C kabel insteken → rode LED op TP4056 (laden) brandt; volle laad → blauwe LED.

### Acceptatiecriteria

- Coin motor voelbaar in de hand zonder bijgeluiden (zo niet → motor niet stevig genoeg tegen handvat-wand).
- Knop reageert binnen <50 ms (zo niet → debounce-time-out in firmware verhogen).
- Encoder-rotatie geeft 1-op-1 servo-respons binnen 100 ms.
- WiFi-AP bereikbaar binnen 5 s na boot.
- DRV2605L wordt herkend → "DRV2605L gevonden" in Serial Monitor.
- TP4056 LED's: rood bij laden, blauw bij volle accu. USB-C kabel insteken en uitschakelen ; handvat moet autonoom blijven werken op de Li-Po.

### Volgende stap

Wizard-of-Oz testsessie opzetten met een echte gebruiker. Zie [reports and protocols/protocol_sensepath_develop3_PDF.pdf](../reports%20and%20protocols/protocol_sensepath_develop3_PDF.pdf) voor het testprotocol dat we eerder gebruikten. Voor de Deliver-validatie: testleider draait de KY-040 encoder terwijl hij of zij achter de gebruiker loopt, en de blinde gebruiker volgt het mechanisch kompas + de drie haptische cues op een onbekende route.

---

## Troubleshooting

| Symptoom | Vermoedelijke oorzaak | Fix |
|---|---|---|
| DRV2605L niet gevonden | I2C-bedrading gekruist, of pinnen niet ingesteld | Pinout checken in [wiring.md](wiring.md), I2C-scanner sketch draaien |
| Coin motor voelt zwakjes | Motor niet stevig tegen handvat-wand | Meer VHB-tape, of motor verplaatsen naar hypothenar-zijde |
| Servo trilt of jittert | Voeding instabiel, of PWM-signaal te dichtbij ruisbron | Aparte decoupling cap (100 µF) op servo +-lijn, signaaldraad weghouden van I2S-lijnen |
| Encoder slaat stappen over | Debounce-tijd te kort of interrupts niet geconfigureerd | Hardware-interrupt op CLK gebruiken (`attachInterrupt`) ipv polling |
| Knop registreert dubbel | Debounce te kort | `BUTTON_DEBOUNCE_MS` in firmware naar 50 ms verhogen |
| WiFi AP niet zichtbaar | XIAO niet juist geboot | Serial Monitor checken, eventueel reset-knop |
| Audio ruis of vervormd | Boost converter niet stabiel op 5 V, of I2S-pinnen gekruist | Boost-uitgang met multimeter checken, I2S BCLK/LRC pinout verifiëren |
| Trilling vibrato/onstabiel | Power-supply ruis | Decoupling cap op DRV2605L Vin (10 µF) |
| Handvat laadt niet op USB-C | TP4056 IN+/IN− niet correct doorgelust | USB-C breakout-board pinout checken, polariteit verifiëren |
| Handvat schakelt uit kort na boot | Li-Po onder discharge-cutoff | Opladen ; TP4056 schakelt uit onder ~2.5 V om de accu te beschermen |
| Handvat blijft draaien wanneer SS12F44 op UIT | Schakelaar niet in serie met hoofdrail | Verifieer dat de SS12F44 inderdaad de positieve rail naar XIAO 5V-pad onderbreekt |
