# CAD exports → STL en STEP

Format-onafhankelijke exports van [../protoype_handvat_trillingmotoren.prt](../protoype_handvat_trillingmotoren.prt) (Develop 3 finaal ontwerp).

## Naming-conventie

- `handvat_dev3_<onderdeel>.<format>`
- Voorbeelden:
  - `handvat_dev3_core.stl` ; buitenwand met gleufpositie
  - `handvat_dev3_kompas.stl` ; sferisch kompaselement
  - `handvat_dev3_cap.stl` ; afsluit-dop met knop-openingen
  - `handvat_dev3_full.step` ; volledige assembly als STEP

## Status

| Bestand | Status |
|---|---|
| handvat_dev3_core.stl | TODO ; export uit NX |
| handvat_dev3_kompas.stl | TODO ; export uit NX |
| handvat_dev3_cap.stl | TODO ; export uit NX |
| handvat_dev3_full.step | TODO ; export uit NX |

## Export-procedure (Siemens NX)

1. Open `protoype_handvat_trillingmotoren.prt` in NX.
2. **STL**: File → Export → STL → kies "Faceted Body" → tolerance 0.05 mm → output naar `handvat_dev3_<onderdeel>.stl`.
3. **STEP**: File → Export → STEP 214 → output naar `handvat_dev3_full.step`.
4. Commit-en-push naar `final-delivery` branch.

> Tot deze exports beschikbaar zijn, kunnen externe bouwers terecht bij het team voor een directe export op aanvraag.
