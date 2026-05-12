# Build guide → SensePath Develop 3 prototype

Stap-voor-stap instructies om het SensePath handvat zelf te bouwen. Lees eerst [bom.md](bom.md) voor de onderdelen en [wiring.md](wiring.md) voor het schakelschema. Geschatte bouwtijd: 3 → 5 uur (exclusief 3D-print).

> Dit is een **lichte versie** ; voldoende om de bouwvolgorde te volgen, maar niet uitputtend op alle finetuning-stappen. Een volledig uitgewerkte versie volgt in de Deliver-fase.

---

## Sectie 1 → 3D-print

### Bestanden

Open [cad/exports/](../cad/exports/) en download:
- `handvat_dev3_core.stl` ; PA6 buitenwand met gleufpositie
- `handvat_dev3_kompas.stl` ; sferisch kompaselement
- `handvat_dev3_cap.stl` ; afsluit-dop met knop-openingen

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
3. Sferisch kompaselement op de aluminium M3-pin schuiven, krimpkous Ø2 mm op de uiteinden om frictie te beperken.

---

## Sectie 2 → Elektronica solderen

### Volgorde (zie [wiring.md](wiring.md) voor pinout)

1. **XIAO ESP32-S3** op een mini-perfboard solderen (header-strip aan onderzijde).
2. **DRV2605L breakout** ernaast op hetzelfde perfboard.
3. **TP4056 USB-C laadcircuit** ernaast monteren. Dit module wordt later via een korte USB-C extender doorgekoppeld naar de USB-C poort van het handvat.
4. **I2C-bedrading** tussen XIAO en DRV2605L:
   - XIAO D4 (SDA) → DRV2605L SDA
   - XIAO D5 (SCL) → DRV2605L SCL
   - XIAO 3V3 → DRV2605L Vin
   - XIAO GND → DRV2605L GND
5. **Batterij-circuit**:
   - TP4056 BAT+ → Li-Po + (via JST-PH 2-pin connector)
   - TP4056 BAT− → Li-Po − (via dezelfde connector)
   - TP4056 BAT+ → XIAO BAT-pad (aan onderzijde van XIAO ESP32-S3)
   - TP4056 GND → gemeenschappelijke GND-bus
   - TP4056 IN+/IN− → USB-C poort 5V / GND (zie volgende stap)
6. **USB-C poort**: gebruik een USB-C breakout-board dat zowel VBUS+GND naar het TP4056-circuit doorlust als de D+/D− datalijnen naar de XIAO USB-poort. Zo werkt één enkele USB-C poort voor zowel opladen als firmware-flashen.
7. **LRA**: 2× AWG28 draad van DRV2605L OUT+ en OUT− naar JST-PH 2-pin connector. LRA-zijde idem.
8. **Knoppen**: 2× JST-PH 3-pin connector (signaal + GND + reserve). Signaal-draad naar XIAO D2 (knop 1) en D3 (knop 2). GND-draden samen naar XIAO GND.

### Solder-tips

- Gebruik flux op de XIAO-pads (klein formaat, makkelijk overspringen).
- LRA-draden zijn dun (AWG30) ; krimpkous na elke soldeer voor trekontlasting.
- I2C-bedrading kort houden (<10 cm) om ruis te vermijden.
- Bij Li-Po: nooit batterij solderen onder spanning. Altijd via JST-connector aansluiten zodat de batterij later veilig losgekoppeld kan worden voor service.

---

## Sectie 3 → Firmware flashen

### Arduino IDE setup

1. **Board manager**: voeg de URL toe: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
2. **Install**: `esp32` board package (versie 2.0.14 of hoger).
3. **Selecteer board**: Tools → Board → ESP32 Arduino → XIAO_ESP32S3.
4. **Libraries** via Library Manager:
   - `Adafruit DRV2605 Library` (versie 1.2.x of hoger)

### Code

Open [../src/firmware/sensepath_esp32/sensepath_esp32.ino](../src/firmware/sensepath_esp32/sensepath_esp32.ino).

**Belangrijk**: pas de I2C-pinconstanten aan voor XIAO:
```cpp
constexpr uint8_t I2C_SDA_PIN = 5;  // was 21 voor ESP32 DevKit
constexpr uint8_t I2C_SCL_PIN = 6;  // was 22 voor ESP32 DevKit
```

### Flash

1. XIAO via USB-C verbinden.
2. Serial Monitor openen op 115200 baud.
3. Upload via Sketch → Upload.
4. Na boot moet er staan:
   ```
   SensePath start
   DRV2605L gevonden
   AP gestart, IP: 192.168.4.1
   Webserver start
   ```

---

## Sectie 4 → Assembleren

1. Perfboard met XIAO + DRV2605L + TP4056 in de handvat-core schuiven, oriëntatie zo dat de USB-C poort toegankelijk blijft via de achterkant-opening.
2. Li-Po batterij in zijn aparte cavity plaatsen, met dubbelzijdige tape gefixeerd. JST-connector aansluiten op het TP4056-circuit.
3. LRA met dubbelzijdige 3M-VHB tape tegen de **hypothenar-zijde** van de handvat-wand fixeren (zo dicht mogelijk bij de muis-van-de-hand; dat is de meest gevoelige perceptiezone uit Develop 2).
4. Knoppen door de cap-openingen schroeven (M3-bevestiging).
5. JST-connectoren vastklikken (LRA, knoppen, batterij).
6. Cap met 2× M3-schroeven (8 mm) sluiten.

---

## Sectie 5 → Testen

### Functionele check

1. Smartphone WiFi → verbinden met SSID `SensePath`, wachtwoord `sensepath`.
2. Browser → `http://192.168.4.1/`.
3. Trigger M4 (obstakel): twee korte scherpe trillingen.
4. Trigger M6 (koersafwijking): drie snelle trillingen achter elkaar.
5. Trigger M9 (bocht): één langere oplopende trilling.

### Acceptatiecriteria

- LRA voelbaar in de hand zonder bijgeluiden (zo niet → motor niet stevig genoeg tegen handvat-wand).
- Knoppen reageren binnen <50 ms (zo niet → debounce-time-out in firmware verhogen).
- WiFi-AP bereikbaar binnen 5 s na boot.
- DRV2605L wordt herkend → "DRV2605L gevonden" in Serial Monitor (zo niet → I2C-bedrading + pull-up-resistors checken).
- TP4056 LED's: rode LED bij opladen, blauwe LED bij volle accu. USB-C kabel insteken en uitschakelen ; het handvat moet autonoom blijven werken op de Li-Po.

### Volgende stap

Wizard-of-Oz testsessie opzetten met een echte gebruiker. Zie [reports and protocols/protocol_sensepath_develop3_PDF.pdf](../reports%20and%20protocols/protocol_sensepath_develop3_PDF.pdf) voor het testprotocol dat we zelf gebruikten.

---

## Troubleshooting

| Symptoom | Vermoedelijke oorzaak | Fix |
|---|---|---|
| DRV2605L niet gevonden | I2C-bedrading gekruist, of pinnen niet ingesteld | Pinout checken in [wiring.md](wiring.md), I2C-scanner sketch draaien |
| LRA voelt zwakjes | Motor niet stevig tegen handvat-wand | Meer VHB-tape, of motor verplaatsen naar hypothenar-zijde |
| Knop registreert dubbel | Debounce te kort | `BUTTON_DEBOUNCE_MS` in firmware naar 50 ms verhogen |
| WiFi AP niet zichtbaar | XIAO niet juist geboot | Serial Monitor checken, eventueel reset-knop |
| Trilling vibrato/onstabiel | Power-supply ruis | USB-kabel met ferrite, of beter: aparte 3V3-LDO voor DRV2605L |
| Handvat laadt niet op USB-C | TP4056 IN+/IN− niet correct doorgelust | USB-C breakout-board pinout checken, polariteit verifiëren |
| Handvat schakelt uit kort na boot | Li-Po onder discharge-cutoff | Opladen ; TP4056 schakelt uit onder ~2.5V om de accu te beschermen |
