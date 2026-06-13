# SensePath Develop 3, concrete implementatielijst

Drie sporen: **App**, **Elektronica** en **Hardware**. Per item een kolom "Bron" die zegt uit welk idee, welke theorie of welke emotie/microinteraction de keuze komt. Geen uitleg, geen visuals, enkel wat gebouwd wordt.

---

## 1. App (iOS, VoiceOver-compatibel)

| # | Implementatie | Bron |
|---|---|---|
| A1 | Audio-onboarding die de gebruiker door de grip-kalibratie leidt | Norman behavioral + grip-dependency uit Dev 1 |
| A2 | Grip-kalibratie-routine: gebruiker houdt handvat 10 s vast, IMU registreert natuurlijke oriëntatie | Dev 2 conclusie over mental mapping safeguard |
| A3 | Neutraal-volwassen TTS-stem, lage spraaksnelheid, geen jingles | Anti-emotie "infantilisering" |
| A4 | App-teksten in tweede persoon ("wil je linksaf?"), nooit imperatief | Primaire emotie "autonomie" |
| A5 | Fail-safe UI heet "heroriënteren", niet "fout" of "signaal verloren" | Anti-emotie "faalgevoel" |
| A6 | Instelling om feedback-intensiteit (laag/medium/hoog) aan te passen | Martiniello stigma factor "customization" |
| A7 | Instelling om audio-modus aan te zetten als secundaire laag (Rory: "audio still works better") | Dev 2 Test 3 feedback |
| A8 | Route starten met één bevestigingsknop, grote hit-area | Fitts' law |
| A9 | Dubbele-tap op handvat triggert 5 s "override"-modus waarin app wacht | Primaire emotie "autonomie" + micro-interactie manual override |
| A10 | Maandelijks tekstueel routerapport (opt-in, geen badges/streaks) | Anti-emotie "infantilisering" |
| A11 | 1-op-1 route-deling met trainer of familielid (geen publieke feed) | Reflective laag, waardigheid |
| A12 | Firmware-updates uitsluitend opt-in, nooit forced | Reflective laag "ik hou de controle" |
| A13 | Route-data standaard lokaal opgeslagen, cloud-sync opt-in (GDPR) | Reflective laag + GDPR |
| A14 | Bluetooth-link-indicator en IMU-kalibratie-leeftijd zichtbaar | Microinteractie M1 trigger rule |
| A15 | Confidence-waarde uit routing-engine leesbaar voor haptische laag | Microinteractie M2 heartbeat |
| A16 | Batterij-drempel-notificatie (via BLE characteristic) | Microinteractie M9 |
| A17 | POI-melding via dubbele app-tap ("lift defect", "werken") | Customer journey fase D |

---

## 2. Elektronica & firmware

| # | Implementatie | Bron |
|---|---|---|
| E1 | Eén LRA-motor (170 tot 230 Hz) in de handle | Dev 2 D6.10 + D6.6 |
| E2 | IMU (accelerometer + gyroscoop + magnetometer) voor griporiëntatie | Dev 2 D6.9 |
| E3 | BLE 5.x module voor koppeling met iOS-app | Dev 2 prototype-flow |
| E4 | Li-ion cell, USB-C laadpoort, vervangbare module | Customer journey fase E (graceful degradation) |
| E5 | Microcontroller met vibratie-patroonbibliotheek voor M1 tot M10 | Microinteractions-tabel |
| E6 | PWM-duty-cycle control voor intensiteit per patroon (25% tot 70%) | Microinteractions-tabel |
| E7 | Fade-in 80 ms op elke trilling, fade-out waar gespecificeerd | Primaire emotie "kalmte" |
| E8 | Confidence-heartbeat-loop (M2): elke 45 s, 2 pulsen, auto-stop als confidence < 70% | Microinteractie M2 |
| E9 | Crescendo-generator (M4): 5 pulsen, 1 Hz naar 3 Hz, 35% naar 60% intensiteit | Microinteractie M4 |
| E10 | Hysterese op off-path detection (4 s aanhouden voor M6) | Anti-emotie "paniek" + M6 |
| E11 | Fail-safe override (M7): onderbreekt alle andere patronen | Microinteractie M7 |
| E12 | IMU-drift-detectie, triggert grip-fallback-signifier | Dev 2 signifier 3 |
| E13 | Outside/inside detectie (licht of druk of RSSI-gebaseerd), triggert transitie-signifier | Dev 2 signifier 2 |
| E14 | Tap-detectie via IMU voor dubbele-tap override-gesture | App A9 |
| E15 | Capacitieve of mechanische aan/uit-knop op handle | Algemene hardware-logica |
| E16 | Audio-passthrough via BLE naar telefoon-oortje (geen speaker op handle) | Primaire emotie "discretie" |
| E17 | Batterij-voltage-read, low-threshold trigger voor M9 | Microinteractie M9 |
| E18 | Sensor-module pauzeert kompas tijdens vibratiecue (D6.5) | Dev 2 figure-ground contrast |
| E19 | Max continue motor-intensiteit softwarematig gecapt op 60% | Anti-emotie "paniek" |
| E20 | Servo of stappenmotor voor fysieke kompasdeflectie (volle rotatie + gradual return) | Dev 2 D6.4 |

---

## 3. Hardware prototype

| # | Implementatie | Bron |
|---|---|---|
| H1 | Handvat-behuizing, glasvezelversterkt PA12 | Anti-emotie "medicaliteit" |
| H2 | Soft-touch TPU-overmold, shore 70A, micro-textuur Ra 3 tot 4 µm | Visceral laag "tast-textuur" |
| H3 | Olijfgroen (olive green) mat als hoofdkleur | Primaire emotie "discretie" |
| H4 | Handvat-dimensies binnen P25 tot P75 ANSUR II (middle 50%) | Dev 2 D6.8 |
| H5 | Kompasgleuf met compass-element op positie H1 (hypothenar) | Dev 2 D6.1 |
| H6 | Sferisch kompaselement, medium protrusiehoogte | Dev 2 D6.2 + D6.3 |
| H7 | Verwisselbare compass module (default + winter-variant voor handschoenen) | Dev 2 D6.7 |
| H8 | Geen vibratiemotoren op individuele vingerposities | Dev 2 D6.10 |
| H9 | Schroefverbinding naar bestaande witte stok (compatibel met meerdere stokmodellen) | README + hero-render |
| H10 | Geen externe LED's of visuele indicatoren op de handle | Primaire emotie "discretie" |
| H11 | Geen audio-speaker op de handle | Primaire emotie "discretie" |
| H12 | Totaalgewicht handvat + clip-module binnen 58 tot 62 g | Visceral laag "gewicht" |
| H13 | Vervangbare batterijmodule, toegankelijk zonder speciaal gereedschap | Customer journey fase E (graceful degradation) |
| H14 | USB-C laadpoort standaard, geen propriëtaire dock | Fogg ability-laag (reduce physical effort) |
| H15 | Aan/uit-knop taktiel onderscheidbaar (ander oppervlak dan omringend handvat) | Signifier-principe |
| H16 | Geen kruis-, plus-, of medische pictogrammen op behuizing of verpakking | Anti-emotie "medicaliteit" |
| H17 | Verpakking in geperst karton, geen blister of plastic folie | Anti-emotie "medicaliteit" + unbox-ritueel |
| H18 | Reliëfletters "SENSEPATH" op doos-deksel, tastbaar | Visceral laag "unbox-ritueel" |

---

## Legenda van bronnen

- **Dev 1 / Dev 2**: resultaten en design requirements uit `reports and protocols/Report_SensePath_Devolop_1.pdf` en `Rapport_Dev2_PDF.pdf`.
- **Primaire emotie**: kalmte, vertrouwen, autonomie, discretie (zie develop_3.md §1).
- **Anti-emotie**: paniek, infantilisering, medicaliteit, faalgevoel.
- **Microinteractie Mx**: zie develop_3.md §3, Saffer-tabel.
- **Norman laag**: visceral, behavioral, reflective (develop_3.md §2).
- **Martiniello (2020)**: stigma en aesthetics van AT voor visueel beperkten.
- **Fogg / Eyal / Walter**: behavioral design, hook-model, pyramid of needs.
