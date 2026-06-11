# SensePath → Discovery

[← Terug naar hoofdpagina](../README.md)

---

## Discovery

### Doelstellingen

- Scherp beeld krijgen van waar blinde en ernstig slechtziende gebruikers vastlopen bij indoor navigatie in complexe publieke gebouwen.
- Begrijpen waarom knooppunten (junctions) de grootste frictie veroorzaken.
- Onderzoeken welke bestaande indoor wayfinding oplossingen bestaan en waar ze tekortschieten.
- Eindigen met een heldere "How Might We" en eerste design requirements.

### Onderzoeksvragen

- Welke ervaringen hebben personen met een visuele beperking bij het navigeren in publieke gebouwen, en waar ontstaat onzekerheid?
- Welke indoor wayfinding technologieën leveren aantoonbare meerwaarde, en waar liggen marktopportuniteiten?

### Doelgroep

**Primair:** Blinde en zeer slechtziende volwassenen die autonoom publieke gebouwen willen bezoeken. Vertrouwd met iPhone (VoiceOver) en gebruiken witte stok.

**Secundair:** Partner/begeleiders, baliemedewerkers, gebouwbeheerders, lokale overheid.

### Materiaal en methoden

| Methode | Type | N | Periode | Doel |
|---|---|---|---|---|
| User interviews | Semigestructureerde diepte-interviews (15-20 min) | 3 | 18/10 - 25/10/2025 | Contextuele inzichten over routines, frustraties en voorkeuren |
| Benchmarking | Systematische vergelijking bestaande oplossingen | 11 | n.v.t. | Sterktes → best practices, zwaktes → design opportuniteiten |

### Resultaten

#### User interviews: key findings

> *"Je volgt een lijn... probleem is dat je niet weet naar waar."*

- **Thuis vs. publiek**: Thuis is oriëntatie automatisme. In publieke gebouwen ontstaat onzekerheid, vooral aan knooppunten waar beslissingsinformatie ontbreekt.
- **Geleidelijnen: love-hate**: Ze helpen vooruit, maar op kruispunten ontbreekt informatie over richting.
- **Real world messiness**: Bezette geleidelijnen, slecht onderhoud, en vooral werken/omleidingen veroorzaken onzekerheid en tijdverlies.
- **Feedbackvoorkeur is contextgebonden**: In publieke context duidelijke voorkeur om gehoor vrij te houden → haptische feedback aantrekkelijk.

> *"Plots werken op het pad... niemand in de buurt, dan zoek je lang."*

**Korte conclusie:** De grootste pijn zit niet in "vooruit geraken", maar in keuzes maken aan knooppunten en omgaan met onbetrouwbare context.

#### Benchmarking: key findings

- Veel systemen steunen op **audio** (turn-by-turn), maar dat botst met de nood om het gehoor vrij te houden.
- **Infrastructuurgebaseerde oplossingen** (beacons/codes) zijn bewezen, maar vragen inzet van gebouwbeheerders en zijn minder schaalbaar.
- **Infra-vrije smartphone-only oplossingen** zijn schaalbaar, maar hebben trade-offs (mapping, kalibratie).
- **Haptische feedback** is discreet en laat oren vrij, maar vraagt een duidelijke "taal". Combinatie haptiek + korte spraak is meest robuust.
- **Form factor is cruciaal**: integratie in bestaande mobiliteitshulpmiddelen verlaagt drempel.

**Korte conclusie:** Duidelijke opportuniteit voor een hybride aanpak: haptisch eerst, handsfree, schaalbaar met minimale infrastructuur, doelgericht tot exacte bestemming.

### Conclusies en implicaties

**Kernproblematiek** → *junction ambiguity* in publieke gebouwen: geleidelijnen en bestaande oplossingen geven te weinig zekerheid op beslismomenten, zeker wanneer de omgeving afwijkt door drukte, bezette lijnen, werken of omleidingen.

**Design implicaties:**

- Feedback moet primair haptisch zijn zodat het gehoor vrij blijft; audio kan optioneel als korte fallback.
- Het systeem moet expliciet ontworpen zijn rond decision points (knooppunten) in plaats van alleen algemene turn-by-turn begeleiding.
- De oplossing moet werken in realistische omstandigheden (bezette/inconsistente geleidelijnen, tijdelijke obstakels, omleidingen).
- De gebruiker moet eenvoudig een exacte bestemming kunnen kiezen en daarna frictieloos begeleid worden.

### How Might We

> Hoe kunnen we blinde en ernstig slechtziende gebruikers in complexe publieke gebouwen betrouwbaar naar hun exacte doel leiden, met focus op knooppunten, minimale frictie en contextgevoelige feedback (haptisch en indien nodig korte spraak), zodat het ook werkt wanneer geleidelijnen bezet, onduidelijk of inconsistent zijn?

### Bronnen & protocollen

- Interview protocol → [Interview - protocol - SensePath.docx](../reports%20and%20protocols/Interview%20-%20protocol%20-%20SensePath.docx)
- Onderzoeksrapport interviews → [Onderzoeksrapport_user_interviews_SensePath.docx](../reports%20and%20protocols/Onderzoeksrapport_user_interviews_SensePath.docx)
- Benchmarking protocol → [Benchmarkingprotocol_SensePath.docx](../reports%20and%20protocols/Benchmarkingprotocol_SensePath.docx)
- Benchmarking rapport → [Benchmarkingrapport_SensePath.docx](../reports%20and%20protocols/Benchmarkingrapport%20_SensePath.docx)

---

[← Terug naar hoofdpagina](../README.md) · [Volgende fase → Definition](definition.md)
