# Bill of Materials (BOM)
## SensePath → MVP-prototype voor Deliver-validatie

> Documentatie van **ons MVP-prototype**, niet van het beoogde eindproduct. Voor het verschil tussen beide en de productie-vision (RTK GNSS, smartphone-app, ToF-obstakeldetectie, PA6 + TPE-materialen): zie de [Deliver-sectie in de hoofdrapportage](../README.md#deliver).

Deze BOM beschrijft de exacte componenten die voor het MVP-prototype zijn besteld en geïntegreerd. SensePath bestaat uit **drie fysieke modules**:

1. **Stok-onderstuk** ; conventionele lange witte stok met 3D-geprinte schroefdraad bovenaan en verwisselbare pin-tip onderaan. Geen elektronica.
2. **Tech-handvat** ; schroeft op het stok-onderstuk via een mee-geprinte schroefdraad. Bevat de XIAO ESP32-S3, DRV2605L + coin vibratiemotor, MG90S servo voor mechanisch kompas, opt-in MAX98357A + speaker, HOTUT drukknop (dubbele rol: functie + power-control via XIAO deep-sleep), eigen Li-Po + TP4056 USB-C. **Geen rocker-switch** ; physical-design constraint, power wordt softwarematig geregeld.
3. **Wizard-of-Oz controller** ; **fysiek aparte module** voor de testleider. Bevat een XIAO ESP32-C3, KY-040 roterende encoder, eigen Li-Po + TP4056 USB-C. **Draadloos** (ESP-NOW) verbonden met het tech-handvat ; geen kabel tussen testleider en gebruiker.

Modules 2 en 3 hebben elk hun eigen voeding en kunnen onafhankelijk aan- en uitgezet worden. Het tech-handvat is dagelijks omwisselbaar met een gewone handgreep via dezelfde 3D-geprinte schroefverbinding op het stok-onderstuk.

> Voor de bredere technische context: zie [wiring.md](wiring.md) voor het schakelschema en [build_guide.md](build_guide.md) voor de bouwinstructies.

---

# MODULE A → Tech-handvat (op de stok geschroefd)

Alle onderdelen in secties 1 tot en met 8 zitten in de **tech-handvat module** die de gebruiker in de hand heeft. Voor de Wizard-of-Oz controller-module zie sectie 9.

---

## 1. Besturingselektronica handvat

| Onderdeel | Specificatie | Aantal |
|---|---|---|
| Microcontroller | Seeed Studio XIAO ESP32-S3 (2.4 GHz WiFi + BLE 5.0, dual-core, met onboard Li-Po batterijlading) | 1 |
| Haptische driver | Adafruit DRV2605L Haptic Motor Controller [ADA2305] | 1 |

De XIAO ESP32-S3 is gekozen omwille van de compacte footprint (21 × 17.5 mm) en de ingebouwde Li-Po laad-ondersteuning ; minder externe componenten in het handvat. Hij ontvangt **draadloos via ESP-NOW** richting-updates van de controller-module en stuurt op basis daarvan de servo aan. De DRV2605L bevat een ROM met 123 haptische effecten en kan zowel ERM- als LRA-motoren aansturen.

---

## 2. Haptische actuator

| Onderdeel | Specificatie | Aantal |
|---|---|---|
| Coin vibratiemotor | DC 3 V, 80 mA, 11 000 RPM, 10 × 2.7 mm platte muntvorm (GERUI 1027-type) | 1 (uit pakket van 10) |

Een coin vibration motor is een ERM-type (Eccentric Rotating Mass) die door de DRV2605L wordt aangedreven in ERM-modus. De platte muntvorm laat een lage profielmontage toe tegen de binnenkant van het handvat, zonder dat de buitenmaten beïnvloed worden.

---

## 3. Mechanisch kompas

| Onderdeel | Specificatie | Aantal |
|---|---|---|
| Mini-servo | VUNIVERSUM MG90S, metalen tandwielen, 25 cm JR-kabel | 1 |

De MG90S stuurt het sferisch kompaselement aan. De assenpositie volgt de doelrichting die binnenkomt via de roterende encoder (Wizard-of-Oz) of, in een toekomstige autonome versie, via GPS-routing. Metalen tandwielen zijn gekozen voor langere levensduur onder herhaalde aansturing.

---

## 4. Wizard-of-Oz interface ; ontvangstkant

De KY-040 encoder zelf zit **niet** in het handvat ; die zit in een aparte controller-module (sectie 9). Het handvat ontvangt enkel de richtingsdata draadloos en stuurt daarmee de servo aan. Er is dus geen encoder-bedrading in het handvat zelf.

---

## 5. Audio (opt-in fallback)

| Onderdeel | Specificatie | Aantal |
|---|---|---|
| I2S audio-versterker | AZDelivery MAX98357A I2S Klasse D 3 W [ADA3006-compatible] | 1 |
| Speaker | Weewooday 2 W 8 Ω metalen behuizing, magneet, ronde mini-speaker | 1 (uit pakket van 6) |

Standaard staat de audio-output **uit**. Op gebruikersverzoek (zie Develop 3 → Jelle's suggestie) kan een spraak-fallback geactiveerd worden bij vastgelopen routes of onbekende situaties. Hierdoor blijft de "ear-free" positionering intact voor reguliere gebruikers, terwijl een opt-in noodvariant beschikbaar is.

---

## 6. Bedieningselementen handvat

| Onderdeel | Specificatie | Aantal |
|---|---|---|
| Drukknop | HOTUT IP67 waterdichte momentary drukknop, 12 mm hoge kop, metaal (variant: zwarte 32 mm momentary) | 1 (uit pakket van 6) |

Eén knop, drie functies via press-type onderscheid in firmware:
- **Short-press** (<500 ms) → start/stop route
- **Double-press** (binnen 400 ms) → "geef overzicht"
- **Long-press** (≥3 s) → XIAO gaat in deep-sleep (functioneel "uit")
- **Druk uit deep-sleep** → wake via EXT0 op RTC-GPIO 4

> **Geen rocker-switch op het handvat** ; physical-design constraint (geen plek in de huidige cap-geometrie). Power-control is volledig softwarematig via deep-sleep. Trade-off: het handvat trekt nog ~10 mA quiescent in deep-sleep (MT3608, MG90S idle, DRV2605L blijven onder spanning), wat neerkomt op ~4 dagen autonomie in opslag op een volle Li-Po. Voor langere opslag: USB-C aangesloten laten of de Li-Po-stekker fysiek loskoppelen van de TP4056.

---

## 7. Voeding handvat

| Onderdeel | Specificatie | Aantal |
|---|---|---|
| Li-Po accu | EEMB 3.7 V 1000 mAh met JST-PH connector | 1 |
| Laadcircuit | Aideepen TP4056 USB-C 5 V 1 A Li-Ion laadbord met overcharge en over-discharge protectie | 1 (uit pakket van 6) |
| Boost converter | MT3608 step-up DC-DC 2-24 V → 5-28 V verstelbaar (afgeregeld op 5 V voor audio-rail) | 1 (uit pakket van 3) |
| USB-C laad-poort | KUOQIY USB-C female 2-draads (VBUS + GND, alleen laden) | 1 (uit pakket van 6) |

De Li-Po levert 3.7 V direct aan de XIAO en (via de DRV2605L OUT-pinnen) de coin motor. De **MG90S servo** vraagt volgens datasheet 4.8-6 V om aan koppel-spec te draaien, en de **MAX98357A audio-versterker** heeft eveneens 5 V nodig. Daarvoor is de MT3608 boost ingezet die de 3.7 V opwaardeert naar een stabiele 5 V rail. De MT3608 staat **altijd aan** (servo moet altijd kunnen reageren op richting-updates); de audio-amp wordt apart in stand-by gezet via zijn SD-pin wanneer audio-fallback niet actief is, zodat de speaker geen stroom trekt. De externe USB-C female-breakout (2-draads) dient enkel voor opladen via TP4056; firmware-flashen gebeurt via de USB-C poort op de XIAO ESP32-S3 zelf.

---

## 8. Behuizing en grip handvat

| Onderdeel | Specificatie | Aantal | Toelichting |
|---|---|---|---|
| Handvat-core | 3D-print in PLA (productie-doel: PA6 unfilled) | 1 | Draagt de elektronica, het kompasmechanisme en de servo. PLA voor prototype-snelheid. |
| Overmold-grip | (productie-doel: TPE Shore 65A; in prototype niet aanwezig) | 0 | CMF-keuze gevalideerd in Develop 3, niet geïntegreerd in MVP-print. |
| Kompaselement | Sferisch contactoppervlak, laagste gleufpositie | 1 | Voorkeurconfiguratie uit Develop 2. |
| Mee-geprinte schroefdraad | 3D-geprint in PLA (geen los onderdeel) | 0 | In de bodem van het tech-handvat, voor de schroefverbinding met het stok-onderstuk. |

CMF-onderbouwing: zie Develop 3 in [README.md](../README.md).

---

# MODULE B → Wizard-of-Oz controller (fysiek apart, draadloos)

De controller is een **op zichzelf staande module** voor de testleider. Hij bevat zijn eigen microcontroller, encoder, batterij en oplaadcircuit. De data gaat draadloos via ESP-NOW naar het handvat ; er is geen kabel tussen beide modules.

## 9. Besturingselektronica controller

| Onderdeel | Specificatie | Aantal |
|---|---|---|
| Microcontroller | Seeed Studio XIAO ESP32-C3 (BLE 5.0 + WiFi, RISC-V, 21 × 17.5 mm, onboard Li-Po laad) | 1 |

De C3 is kleiner en zuiniger dan de S3 ; voor de controller hoeven we alleen encoder-deltas te verzenden, geen audio of servo aan te sturen. Dezelfde fysieke footprint en pinout-stijl als de S3, zodat dezelfde XIAO-ecosystem-bibliotheken hergebruikt kunnen worden.

## 10. Wizard-of-Oz input (controller)

| Onderdeel | Specificatie | Aantal |
|---|---|---|
| Roterende encoder | QWORK KY-040, 360° met geïntegreerde drukknop | 1 (uit pakket van 5) |

De testleider draait de KY-040 om de gewenste route-richting in te stellen. De ESP32-C3 leest CLK/DT/SW uit en verstuurt elke positie-update via ESP-NOW naar de ESP32-S3 in het handvat, die op zijn beurt de MG90S servo aanstuurt. De drukknop op de encoder dient als bevestiging of mode-wissel.

## 11. Voeding controller

| Onderdeel | Specificatie | Aantal |
|---|---|---|
| Li-Po accu | EEMB 3.7 V 1000 mAh met JST-PH connector | 1 |
| Laadcircuit | Aideepen TP4056 USB-C 5 V 1 A Li-Ion laadbord met overcharge en over-discharge protectie | 1 (uit pakket van 6) |
| USB-C laad-poort | KUOQIY USB-C female 2-draads (VBUS + GND, alleen laden) | 1 (uit pakket van 6) |

Identiek voedingsschema als het handvat (USB-C → TP4056 → Li-Po → 3.7 V rail) maar zonder MT3608 (geen 5 V rail nodig, geen audio).

## 12. Behuizing controller

| Onderdeel | Specificatie | Aantal | Toelichting |
|---|---|---|---|
| Controller-case | 3D-print in PLA, klein doosje (~60 × 40 × 25 mm) | 1 | Bevat ESP32-C3, batterij, TP4056, en heeft een opening bovenaan voor de KY-040 encoder-as. |

---

# MODULE C → Stok-onderstuk (passief, geen elektronica)

## 13. Stok-onderstuk

| Onderdeel | Specificatie | Aantal | Toelichting |
|---|---|---|---|
| Witte stok-onderstuk | Conventionele lange witte stok met verwisselbare pin-tip (productie-doel: aluminium of glasvezel; in prototype gemodificeerd standaardmodel) | 1 | Het onderstuk volgt de bestaande witte-stok-conventie. Wij integreren bovenaan een 3D-geprint draadstuk (vast op het uiteinde) waarop het tech-handvat geschroefd wordt. |
| 3D-geprint draadstuk | PLA, ~15 mm | 1 | Vast op het top-uiteinde van de stok. Schroeft in de mee-geprinte schroefdraad van het tech-handvat. |
| Verwisselbare pin-tip | Conventionele tip (rolling ball, ceramic, of glide tip) | 1 | Aan het loop-uiteinde, exact zoals bij commerciële witte stokken. |

---

# PROJECT-WIDE

## 14. Overige prototyping-materialen

| Onderdeel | Specificatie | Aantal |
|---|---|---|
| Dupont jumper wires | ZDE 10 cm, Female-Female, Male-Female, Male-Male, 120 stuks | Kit |
| Perfboard of mini-PCB | Voor DRV2605L ↔ XIAO bedrading (handvat) en ESP32-C3 ↔ encoder (controller) | 2 |
| Soldeer + flux | Sn60/Pb40 of loodvrij | naar wens |

---

## 15. Totale kost (indicatie, MVP-prototype als geheel)

**Module A → tech-handvat**

| Categorie | Richtprijs |
|---|---|
| XIAO ESP32-S3 + Adafruit DRV2605L | €25 → €35 |
| Coin vibration motor + speaker + MAX98357A | €10 → €15 |
| MG90S servo | €5 → €10 |
| HOTUT knop + USB-C laad-poort | €8 → €12 |
| TP4056 + MT3608 + Li-Po 1000 mAh | €10 → €15 |
| 3D-print (PLA, ~80 g) + hardware | €8 → €15 |
| **Subtotaal handvat** | **€66 → €102** |

**Module B → Wizard-of-Oz controller**

| Categorie | Richtprijs |
|---|---|
| XIAO ESP32-C3 | €8 → €12 |
| KY-040 encoder | €2 → €4 |
| TP4056 + Li-Po 1000 mAh | €8 → €12 |
| USB-C laad-poort | €2 → €4 |
| 3D-print case + hardware | €4 → €8 |
| **Subtotaal controller** | **€24 → €40** |

**Module C → Stok-onderstuk**

| Categorie | Richtprijs |
|---|---|
| Witte stok-onderstuk + 3D-geprint draadstuk | €15 → €30 |
| **Subtotaal stok** | **€15 → €30** |

| **Totaal MVP-prototype (alle drie modules)** | **€105 → €172** |

---

