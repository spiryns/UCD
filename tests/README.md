# Tests → SensePath

Deze map bevat de testbeschrijvingen en -resultaten van het SensePath project. Voor de uitgebreide protocollen en rapporten: zie [reports and protocols/](../reports%20and%20protocols/).

---

## Test-strategie van het project

SensePath is gevalideerd via **gebruikersonderzoek met echte deelnemers** (in totaal N=15+ over zes test-waves), niet via geautomatiseerde unit- of integratietests op de firmware. De keuze daarvoor is bewust: voor een haptisch interactie-product is de perceptie door de doelgroep de primaire kwaliteitsmaat; firmware-correctheid is een randvoorwaarde maar geen succes-criterium.

| Wave | Fase | N | Type test | Rapport |
|---|---|---|---|---|
| Wave 1 | Definition | 5 | Conceptvalidatie | [Report_define_WAVE1.pdf](../reports%20and%20protocols/Report_define_WAVE1.pdf) |
| Wave 2 | Definition | 5 | Verfijning + MoSCoW | [Report wave 2.pdf](../reports%20and%20protocols/Report%20wave%202.pdf) |
| Develop 1 | Develop | 5 | Functionele tests | [Report_SensePath_Devolop_1.pdf](../reports%20and%20protocols/Report_SensePath_Devolop_1.pdf) |
| Develop 2 | Develop | 5 | Usability + ergonomie | [Rapport_Dev2_PDF.pdf](../reports%20and%20protocols/Rapport_Dev2_PDF.pdf) |
| Develop 3 | Develop | 5 (3 blind + 2 ziend) | Microinteracties + CMF + Wizard-of-Oz | [rapport_sensepath_develop3.pdf](../reports%20and%20protocols/rapport_sensepath_develop3.pdf) |
| Deliver | Deliver | TBD | Autonome wandeling + GPS-validatie | TODO ; gepland |

---

## Firmware-validatie (handmatig)

De firmware in [src/firmware/sensepath_esp32/](../src/firmware/sensepath_esp32/) is getest via:

1. **I2C-scanner sketch** ; bevestigt dat de DRV2605L op adres 0x5A reageert.
2. **Wizard-of-Oz webcontroller** ; elke microinteractie (M1 → M9) handmatig getriggerd via `http://192.168.4.1/`.
3. **Empirische validatie tijdens user tests** ; de drie kernsignalen (M4, M6, M9) werden per gebruiker beoordeeld op herkenbaarheid en cognitieve belasting.

Geen geautomatiseerde unit tests of CI-pipeline. Voor de Deliver-fase staat een trillingsduur- en amplitude-validatie via oscilloscoop op de planning, om de DRV2605L-output objectief te kwantificeren.

---

## Toekomstig werk

Voor wie dit project zou verderzetten:

- **Geautomatiseerde pattern-tests**: een referentie-oscilloscoop + capture-script om de M4/M6/M9 trillingen te verifiëren tegen een golfvorm-spec.
- **Hardware-in-the-loop simulatie**: een mock-DRV2605L op SPI/I2C-bus om de firmware zonder fysieke motor te testen.
- **End-to-end veld-tests**: scripts om GPS-input (mock of echt) door het systeem te leiden en de uitgevoerde microinteracties te loggen, bedoeld voor reproduceerbare regressies.

Deze items vallen buiten de scope van het Develop 3 prototype maar worden hier genoteerd als roadmap.
