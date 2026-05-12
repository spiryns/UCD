# Bill of Materials (BOM)
## SensePath → Develop 3 finaal prototype

Deze BOM beschrijft de componenten van het **Develop 3 prototype**: een 3D-geprint handvat dat op een standaard lange witte stok geklikt wordt, met geïntegreerde haptische feedback. Dit is de configuratie waarmee de finale gebruikerstests werden uitgevoerd (N=5).

> Voor de bredere technische context: zie [wiring.md](wiring.md) voor het schakelschema en [build_guide.md](build_guide.md) voor de bouwinstructies.

---

## 1. Besturingselektronica

| Onderdeel | Specificatie | Aantal | Productlink |
|---|---|---|---|
| Microcontroller | Seeed Studio XIAO ESP32-S3 | 1 | https://www.seeedstudio.com/XIAO-ESP32S3-p-5627.html |
| Haptische driver | Adafruit DRV2605L (I2C breakout) | 1 | https://www.adafruit.com/product/2305 |

Waarom deze componenten: de XIAO ESP32-S3 biedt WiFi (nodig voor de Wizard-of-Oz controller) en deep-sleep capaciteit in een compacte footprint die in het handvat past. De DRV2605L heeft een ingebouwde ROM met 123 effecten en kan een LRA aansturen zonder dat de microcontroller golfvormen real-time moet genereren.

---

## 2. Haptische actuator

| Onderdeel | Specificatie | Aantal | Productlink |
|---|---|---|---|
| LRA-trilmotor | Linear Resonant Actuator, ~200 Hz, 3 mm dik | 1 | https://www.adafruit.com/product/1201 |

De keuze voor één LRA (in plaats van de eerdere 3-motor opstelling uit Develop 1 of de coin vibration motors uit semester 1) gebeurde in Develop 2 op basis van gebruikersfeedback: één duidelijk gelokaliseerd signaal werkt beter dan meerdere overlappende motoren. Een LRA biedt scherpere onset/offset dan een ERM, wat de microinteractie M4/M6/M9 herkenbaarder maakt.

---

## 3. Bedieningselementen

| Onderdeel | Specificatie | Aantal | Productlink |
|---|---|---|---|
| POM-knop | Mechanische drukknop, POM-kop voor tactiele herkenbaarheid | 2 | https://www.tinytronics.nl/shop/nl/schakelaars/drukknoppen/ |

Eén knop = start/stop route, één knop = "geef volledig overzicht" (zie design requirement D3.4). POM is gekozen omdat het glad en kleurvast is, en visueel duidelijk verschilt van de TPE-grip.

---

## 4. Behuizing en grip

| Onderdeel | Specificatie | Aantal | Toelichting |
|---|---|---|---|
| Handvat-core | 3D-print in PA6 (unfilled) of PETG-fallback | 1 | Draagt de elektronica en het kompasmechanisme. PA6 voor slag- en slijtvastheid. |
| Overmold-grip | TPE Shore 65A | 1 | Zachte buitenlaag voor comfortabele grip. Bij prototype: geprint of giet-overmold. |
| Kompaselement | Sferisch contactoppervlak, laagste gleufpositie | 1 | Voorkeurconfiguratie uit Develop 2 (zie design requirements D6.1–D6.4). |
| Aluminium pin | M3 doorgaande as voor kompas-rotatie | 1 | Laag-frictie draaipunt. |
| Heatset insert | M3, messing | 2 | Voor montage op de witte stok. |

CMF-onderbouwing: zie Develop 3 sectie in [README.md](../README.md).

---

## 5. Voeding (huidig prototype)

| Onderdeel | Specificatie | Aantal | Productlink |
|---|---|---|---|
| USB-C kabel | USB-C, lengte ~1.5 m | 1 | (commodity) |

Het huidige prototype draait op USB-voeding. Batterijintegratie staat gepland voor de Deliver-fase (zie sectie 6).

---

## 6. Geplande batterijintegratie (Deliver-fase, nog niet in prototype)

| Onderdeel | Specificatie | Aantal | Productlink |
|---|---|---|---|
| Li-ion accu | 18650, ~3000 mAh of 1S 1000 mAh LiPo | 1 | https://www.tinytronics.nl/shop/nl/batterijen/ |
| Laadcircuit | TP4056 USB-C met overcharge/over-discharge protectie | 1 | https://www.tinytronics.nl/shop/nl/power/laders/tp4056-usb-c-li-ion-lader |
| Batterijhouder | 18650-houder | 1 | https://www.tinytronics.nl/shop/nl/batterijen/batterijhouders/18650 |

Theoretische schatting: ESP32-S3 in deep-sleep tussen pulses + LRA-pulses → 6 tot 8 uur autonomie op 1000 mAh. Empirisch nog niet gevalideerd (open punt voor Deliver-fase).

---

## 7. Overige prototyping-materialen

- Perfboard of mini-PCB (voor DRV2605L ↔ XIAO bedrading)
- JST-PH connectoren (2-pin voor LRA, 3-pin voor knoppen)
- AWG28 bedrading (intern handvat)
- Krimpkous Ø2 mm
- Soldeer (Sn60/Pb40 of loodvrij) + flux
- Schroeven M2/M3 set
- Dubbelzijdige tape of epoxy (voor LRA-fixatie tegen handvatwand)

---

## 8. Totale kost (indicatie, Develop 3 configuratie zonder batterij)

| Categorie | Richtprijs |
|---|---|
| Elektronica (XIAO ESP32-S3 + DRV2605L + LRA + knoppen) | €25 → €35 |
| Print-/grondstoffen (PA6 + TPE-filament, ~80 g totaal) | €5 → €10 |
| Hardware (inserts, pin, schroeven, connectoren) | €5 → €10 |
| **Totaal basisprototype (USB-voeding)** | **€35 → €55** |
| Batterijintegratie (Deliver-fase, additioneel) | +€10 → €15 |

---

## 9. Vergelijking met voorgaande iteraties

| Component | Semester 1 | Develop 1 | Develop 2 | Develop 3 (huidig) |
|---|---|---|---|---|
| Microcontroller | ESP32 DevKit | ESP32 DevKit | XIAO ESP32-S3 | XIAO ESP32-S3 |
| Afstandssensoren | 2× VL53L0X | 2× VL53L0X | geen | geen |
| Mechanische feedback | Stepper 28BYJ-48 + ULN2003 | Mechanisch kompas | Mechanisch kompas | Mechanisch kompas (sferisch contact) |
| Trilmotoren | 2× coin vibration | 3× LRA | 1× LRA + DRV2605L | 1× LRA + DRV2605L |
| Audio | Speaker + MAX98357A | geen | geen | geen |
| Voeding | 18650 + TP4056 + MT3608 | 18650 + TP4056 | USB | USB (batterij gepland) |

Reductie van complexiteit was doelbewust: elke iteratie schrapte componenten die in tests niet bijdroegen aan de kerninteractie (haptische richtingaanwijzing via één duidelijk signaal in de hand).
