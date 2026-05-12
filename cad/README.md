# CAD → SensePath

Deze map bevat de CAD-bestanden van de SensePath handvat-iteraties. De primaire werkomgeving was **Siemens NX**, dus de bron-bestanden zijn `.prt` en de samengevoegde assemblies zijn als `.zip` bewaard. Voor externe bouwers (zonder NX-licentie) staan exports naar **STL** en **STEP** in [exports/](exports/).

---

## Inhoud

| Bestand | Iteratie | Beschrijving |
|---|---|---|
| [protoype_handvat_trillingmotoren.prt](protoype_handvat_trillingmotoren.prt) | **Develop 3 (finaal)** | Handvat met sferisch kompas-contactoppervlak in laagste gleufpositie. Inclusief uitsparingen voor XIAO ESP32-S3, DRV2605L, LRA en POM-knoppen. |
| [quick&dirty_trillingshandvat.prt](quick&dirty_trillingshandvat.prt) | Develop 1 → 2 | Vroege functionele variant met meervoudige motor-opstelling. Behouden voor traceability. |
| [Bol_mechanisme_motor.zip](Bol_mechanisme_motor.zip) | Develop 2 | Assembly van het kompas-mechanisme met bol op aluminium pin. |
| [Quick en dirty mechanisch bolletje.zip](Quick%20en%20dirty%20mechanisch%20bolletje.zip) | Develop 1 | Eerste mechanische kompas-test. |
| [sensepathsem1final.zip](sensepathsem1final.zip) | Semester 1 (Definition) | Volledige assembly aan het einde van semester 1 ; obsoleet vanaf Develop 1. |

---

## Welke file is het Develop 3 finaal ontwerp?

**`protoype_handvat_trillingmotoren.prt`** is het bestand dat overeenkomt met het prototype beschreven in [../docs/bom.md](../docs/bom.md) en het [Develop 3-hoofdstuk in de README](../README.md#develop-3). Specifiek:

- Sferisch kompas-contactoppervlak (uit Develop 2 selectie)
- Laagste gleufpositie ; kompas binnen handpalm, niet eruit wijkend
- Inwendige uitsparingen voor:
  - XIAO ESP32-S3 microcontroller
  - Adafruit DRV2605L breakout
  - LRA-trilmotor tegen hypothenar-zijde
  - 2× POM-knoppen aan de achterkant

CMF-specs (uit Develop 3 CMF-deepdive):
- Core: **PA6 unfilled** ; slag- en slijtvast voor dragend gedeelte
- Overmold (gepland): **TPE Shore 65A** ; zacht-tactiel comfort
- Grip-textuur: fijne radiale ribbels
- Knoppen: POM (glad, kleurvast)
- Kompas-pin: aluminium met optionele TPE-tip (vervangbaar)

---

## Exports voor externe bouwers

`.prt` bestanden zijn alleen leesbaar in Siemens NX (commerciële licentie). Voor reproduceerbaarheid staan format-onafhankelijke exports in [exports/](exports/):

- `*.stl` ; direct 3D-printbaar (geen editing mogelijk)
- `*.step` ; bewerkbaar in elke CAD-tool (Fusion 360, SolidWorks, FreeCAD)

> Status: STL/STEP-exports worden in de Deliver-fase toegevoegd door het team. Zie [exports/README.md](exports/README.md) voor de naming-conventie en TODO-status.

---

## Volgorde van CAD-iteraties

1. **Semester 1**: `sensepathsem1final.zip` ; volledige slimme stok met ingebouwde elektronica. Verlaten in Develop 1 wegens te complexe productarchitectuur.
2. **Develop 1**: `Quick en dirty mechanisch bolletje.zip` ; eerste validatie van mechanisch kompas-concept.
3. **Develop 1 → 2**: `quick&dirty_trillingshandvat.prt` ; functionele variant met 3 trilmotoren ; verlaten in Develop 2 voor 1-LRA opstelling.
4. **Develop 2**: `Bol_mechanisme_motor.zip` ; assembly met sferisch kompas (uit Develop 2 selectie).
5. **Develop 3 (huidig)**: `protoype_handvat_trillingmotoren.prt` ; gleuf versmald, bedieningselementen geïntegreerd, klaar voor finale validatie in Deliver.
