# Bill of Materials (BOM)
## SensePath → finale integratie voor Deliver-validatie

Deze BOM beschrijft de exacte componenten die voor het finale SensePath-prototype zijn besteld en geïntegreerd. Het ontwerp omvat:

- Haptisch kanaal → coin vibratiemotor aangestuurd via DRV2605L
- Mechanisch kompas → MG90S servo draait het sferisch kompaselement
- **Wizard-of-Oz controller via roterende encoder** → de testleider stuurt het kompas aan via een KY-040 encoder; dit overbrugt de Develop-fase (Wizard-of-Oz via telefoon) naar de Deliver-validatie zonder eerst een volledig autonoom GPS-systeem te moeten bouwen
- Opt-in audio-fallback → speaker + I2S-versterker, default uit
- Autonoom inzetbaar → 900 mAh Li-Po met USB-C opladen
- Stevige bediening → metalen drukknop, schuifschakelaar voor aan/uit

> Voor de bredere technische context: zie [wiring.md](wiring.md) voor het schakelschema en [build_guide.md](build_guide.md) voor de bouwinstructies.

---

## 1. Besturingselektronica

| Onderdeel | Specificatie | Aantal | Productlink |
|---|---|---|---|
| Microcontroller | Seeed Studio XIAO ESP32-S3 (2.4 GHz WiFi + BLE 5.0, dual-core, met onboard Li-Po batterijlading) | 1 | https://www.seeedstudio.com/XIAO-ESP32S3-p-5627.html |
| Haptische driver | Adafruit DRV2605L Haptic Motor Controller [ADA2305] | 1 | https://www.adafruit.com/product/2305 |

De XIAO ESP32-S3 is gekozen omwille van de compacte footprint (21 × 17.5 mm) en de ingebouwde Li-Po laad-ondersteuning ; minder externe componenten in het handvat. De DRV2605L bevat een ROM met 123 haptische effecten en kan zowel ERM- als LRA-motoren aansturen.

---

## 2. Haptische actuator

| Onderdeel | Specificatie | Aantal | Productlink |
|---|---|---|---|
| Coin vibratiemotor | DC 3 V, 80 mA, 11 000 RPM, 10 × 2.7 mm platte muntvorm (GERUI 1027-type) | 1 (uit pakket van 10) | https://www.amazon.nl/dp/B0CXJ4G5PG/ |

Een coin vibration motor is een ERM-type (Eccentric Rotating Mass) die door de DRV2605L wordt aangedreven in ERM-modus. De platte muntvorm laat een lage profielmontage toe tegen de binnenkant van het handvat, zonder dat de buitenmaten beïnvloed worden.

---

## 3. Mechanisch kompas

| Onderdeel | Specificatie | Aantal | Productlink |
|---|---|---|---|
| Mini-servo | VUNIVERSUM MG90S, metalen tandwielen, 25 cm JR-kabel | 1 | https://www.amazon.nl/dp/B07P4WG9D6/ |

De MG90S stuurt het sferisch kompaselement aan. De assenpositie volgt de doelrichting die binnenkomt via de roterende encoder (Wizard-of-Oz) of, in een toekomstige autonome versie, via GPS-routing. Metalen tandwielen zijn gekozen voor langere levensduur onder herhaalde aansturing.

---

## 4. Wizard-of-Oz controller

| Onderdeel | Specificatie | Aantal | Productlink |
|---|---|---|---|
| Roterende encoder | QWORK KY-040, 360° met geïntegreerde drukknop | 1 (uit pakket van 5) | https://www.amazon.nl/dp/B07F26GMSC/ |

De KY-040 maakt het mogelijk om de finale validatie te doen zonder een GPS-systeem te moeten bouwen. De testleider draait de encoder; de XIAO leest CLK/DT/SW en stuurt de MG90S-servo aan. Daarmee voelt de blinde gebruiker een continu, mensgestuurd kompasspoor in de hand ; identiek aan wat een autonoom systeem later zou moeten leveren, maar met de testleider als "GPS-vervanger".

---

## 5. Audio (opt-in fallback)

| Onderdeel | Specificatie | Aantal | Productlink |
|---|---|---|---|
| I2S audio-versterker | AZDelivery MAX98357A I2S Klasse D 3 W [ADA3006-compatible] | 1 | https://www.amazon.nl/dp/B086DL36M5/ |
| Speaker | Weewooday 2 W 8 Ω metalen behuizing, magneet, ronde mini-speaker | 1 (uit pakket van 6) | https://www.amazon.nl/dp/B08RXVXPC3/ |

Standaard staat de audio-output **uit**. Op gebruikersverzoek (zie Develop 3 → Jelle's suggestie) kan een spraak-fallback geactiveerd worden bij vastgelopen routes of onbekende situaties. Hierdoor blijft de "ear-free" positionering intact voor reguliere gebruikers, terwijl een opt-in noodvariant beschikbaar is.

---

## 6. Bedieningselementen

| Onderdeel | Specificatie | Aantal | Productlink |
|---|---|---|---|
| Drukknop | HOTUT IP67 waterdichte momentary drukknop, 12 mm hoge kop, metaal | 1 (uit pakket van 6) | https://www.amazon.nl/dp/B099YJZ8DJ/ |
| Schuifschakelaar | Youmile SS12F44 SPDT 1P2T mini-verticaal, 3-pins, 0.5 A | 1 (uit pakket van 20) | https://www.amazon.nl/dp/B07ZP6BHKT/ |

Eén drukknop = start/stop route + "geef overzicht" (double-press onderscheid). De schuifschakelaar = harde aan/uit voor wanneer het handvat opgeborgen wordt, zodat de XIAO niet in stand-by blijft drainen.

---

## 7. Voeding

| Onderdeel | Specificatie | Aantal | Productlink |
|---|---|---|---|
| Li-Po accu | EEMB 3.7 V 900 mAh, model 603048LC, met JST-connector | 1 | https://www.amazon.nl/dp/B07PNBT6VC/ |
| Laadcircuit | Aideepen TC4056 USB-C 5 V 1 A Li-Ion laadbord met overcharge en over-discharge protectie | 1 (uit pakket van 6) | https://www.amazon.nl/dp/B0BXQ24F7T/ |
| Boost converter | MT3608 step-up DC-DC 2-24 V → 5-28 V verstelbaar | 1 (uit pakket van 3) | https://www.amazon.nl/dp/B07R8C56DK/ |
| USB-C connector | KUOQIY 3 A 4-pins USB-C vrouwelijk, Type-C 4-draads, 150 mm 24 AWG | 1 (uit pakket van 6) | https://www.amazon.nl/dp/B0CRTPQF6K/ |

De Li-Po levert 3.7 V direct aan de XIAO en de coin motor. De MAX98357A audio-versterker heeft 5 V nodig; daarvoor is de MT3608 ingezet die de 3.7 V opwaardeert naar een stabiele 5 V rail (alleen ingeschakeld wanneer audio-fallback actief is, om batterij te sparen). De TP4056 USB-C poort dient voor opladen én voor firmware-flashen via de XIAO USB-data lijnen.

---

## 8. Behuizing en grip

| Onderdeel | Specificatie | Aantal | Toelichting |
|---|---|---|---|
| Handvat-core | 3D-print in PA6 (unfilled) of PETG-fallback | 1 | Draagt de elektronica, het kompasmechanisme en de servo. PA6 voor slag- en slijtvastheid. |
| Overmold-grip | TPE Shore 65A | 1 | Zachte buitenlaag, fijne radiale ribbels voor grip. |
| Kompaselement | Sferisch contactoppervlak, laagste gleufpositie | 1 | Voorkeurconfiguratie uit Develop 2. |
| Aluminium pin | M3 doorgaande as voor kompas-rotatie, gekoppeld aan servo-as | 1 | Vervangbare TPE-tip optioneel (winter / handschoenen). |
| Heatset-insert | M3, messing | 2 | Voor montage op de witte stok. |

CMF-onderbouwing: zie Develop 3 in [README.md](../README.md).

---

## 9. Overige prototyping-materialen

| Onderdeel | Specificatie | Aantal |
|---|---|---|
| JST-PH 2.0 mm connectoren | Mix van 2-pin, 3-pin, 5-pin connectoren met dopjes | Kit |
| Dupont jumper wires | ZDE 10 cm, Female-Female, Male-Female, Male-Male, 120 stuks | Kit |
| Perfboard of mini-PCB | Voor DRV2605L ↔ XIAO bedrading | 1 |
| Krimpkous Ø2 mm | Voor trekontlasting LRA / servo / batterij-bedrading | enkele mm |
| Soldeer + flux | Sn60/Pb40 of loodvrij | naar wens |
| Schroeven | M2 / M3 set | enkele |
| Dubbelzijdige tape of epoxy | Fixatie van motor, servo en batterij tegen handvat-wand | naar wens |

---

## 10. Totale kost (indicatie, finaal eindproduct)

| Categorie | Richtprijs |
|---|---|
| XIAO ESP32-S3 + Adafruit DRV2605L | €25 → €35 |
| Coin vibration motor + speaker + MAX98357A | €10 → €15 |
| MG90S servo + KY-040 encoder | €10 → €15 |
| HOTUT knop + SS12F44 switch + USB-C connector | €10 → €15 |
| TP4056 + MT3608 + Li-Po 900 mAh | €10 → €15 |
| Print-/grondstoffen (PA6 + TPE-filament, ~80 g totaal) | €5 → €10 |
| Hardware (inserts, pin, schroeven, connectoren, jumpers) | €5 → €10 |
| **Totaal eindproduct (één gebouwde unit)** | **€75 → €115** |

---

## 11. Vergelijking met voorgaande iteraties

| Component | Semester 1 | Develop 1 | Develop 2 | Develop 3 → finale integratie |
|---|---|---|---|---|
| Microcontroller | ESP32 DevKit | ESP32 DevKit | XIAO ESP32-S3 | XIAO ESP32-S3 |
| Afstandssensoren | 2× VL53L0X | 2× VL53L0X | geen | geen |
| Mechanisch kompas | geen | mechanisch (handmatig) | sferisch, statisch | sferisch, aangedreven door MG90S servo |
| Trilmotoren | 2× coin vibration | 3× LRA | 1× LRA + DRV2605L | 1× coin vibration + DRV2605L |
| Audio | Speaker + MAX98357A altijd-aan | geen | geen | Opt-in spraak-fallback (default uit) |
| Bediening | 2× drukknop | knop + telefoon (Wizard-of-Oz) | knop + telefoon | 1× drukknop + KY-040 encoder (Wizard-of-Oz) + schuifschakelaar |
| Voeding | 18650 + TP4056 + MT3608 | 18650 + TP4056 | Bench-USB | Interne Li-Po 900 mAh + USB-C oplaad + MT3608 boost voor audio |

De componenten-reductie ten opzichte van semester 1 blijft staan ; wat is teruggekeerd in de finale integratie (audio, MT3608) is doelbewust opt-in en niet altijd-aan, om de "ear-free, minimal-electronics" filosofie te bewaren waar dat kan, en alleen functionaliteit toe te voegen waar gebruikers er expliciet om vroegen.
