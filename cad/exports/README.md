# CAD exports → STL

3D-print-klare STL-exports van het Develop 3 finale ontwerp. De NX-bronbestanden (`.prt` + zips) staan in [../](../).

## Bestanden

| Bestand | Onderdeel |
|---|---|
| `behuizingstok_3Dprint.stl` | Hoofdbehuizing van het tech-handvat (stok-zijde) |
| `opzetstukbehuizing_3Dprint.stl` | Opzetstuk-behuizing bovenaan het handvat |
| `servobehuizing_3Dprint.stl` | Behuizing voor de MG90S servo (kompas-aandrijving) |
| `Kompas_3Dprint.stl` | Sferisch kompaselement, koppelt op de servo-as |
| `elektronica_3Dprint.stl` | Houder/frame voor de elektronica in het handvat |
| `boxhold_3Dprint.stl` | Behuizing van de Wizard-of-Oz controller-module |

Aanbevolen print-instellingen (laagdikte, infill, oriëntatie, materiaal) staan in de [build guide](../../docs/build_guide.md) → Sectie 1.

## Opnieuw exporteren (Siemens NX)

1. Open het betreffende bronbestand in [../](../) in NX.
2. File → Export → STL → kies "Faceted Body" → tolerance 0.05 mm → output naar `<onderdeel>_3Dprint.stl`.
