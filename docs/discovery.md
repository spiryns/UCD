Discovery
========

Doelstellingen
--------------
- Een scherp beeld krijgen van waar blinde en ernstig slechtziende gebruikers vandaag vastlopen bij indoor navigatie in complexe publieke gebouwen (bv. gemeentehuis, station, museum).
- Begrijpen waarom knooppunten (junctions) de grootste frictie veroorzaken en welke situaties daar het vaakst mislopen (geleidelijnen, drukte, werken, omleidingen).
- Onderzoeken welke bestaande indoor wayfinding oplossingen al bestaan en waar ze tekortschieten (feedback, infrastructuur, betrouwbaarheid, schaalbaarheid).
- Eindigen met een heldere "How Might We" en eerste design requirements als basis voor Definition.

Onderzoeksvragen
----------------
- Welke ervaringen hebben personen met een visuele beperking bij het navigeren in publieke gebouwen, en waar ontstaat onzekerheid tijdens taken, beslismomenten en obstakels?
- Welke indoor wayfinding technologieen leveren aantoonbare meerwaarde, en waar liggen marktopportuniteiten voor differentiatie?

Doelgroep
---------
Primair
- Volledig blinde volwassenen die autonoom publieke gebouwen willen kunnen bezoeken.
- Vertrouwd met iPhone (VoiceOver) en gebruiken witte stok (soms ook geleidehond).

Secundair en stakeholders
- Partner/begeleiders, balie medewerkers, gebouwbeheerders, lokale overheid.

Materiaal en methoden
---------------------

User interviews (N = 3)
- Type: semigestructureerde diepte interviews (15-20 min).
- Periode: 18/10/2025 - 25/10/2025.
- Locatie: BrailleTech (18/10/2025).
- Doel: rijke, contextuele inzichten verzamelen over routines, frustraties, veiligheid en voorkeuren (audio vs haptiek).

Links
- Protocol: Interview - protocol - SensePath.docx
- Rapport: Onderzoeksrapport_user_interviews_SensePath.docx

Benchmarking / technology scouting (N = 11)
- Type: systematische vergelijking van bestaande (indoor) navigatie oplossingen.
- Doel: sterktes vertalen naar best practices, zwaktes vertalen naar design opportuniteiten.
- Criteria (o.a.): lokalisatiemethode, benodigde infrastructuur, nauwkeurigheid en robuustheid, feedbackmodaliteit, schaalbaarheid en beheer, rijpheid (TRL).

Links
- Protocol: Benchmarkingprotocol_SensePath.docx
- Rapport: Benchmarkingrapport _SensePath.docx

Resultaten
----------

User interviews (N = 3)
Key findings
- Thuis is orientatie grotendeels automatisme, maar in publieke gebouwen ontstaat onzekerheid, vooral aan knooppunten.
  - "Binnen in huis doe ik eigenlijk alles op de tast... dat wordt een automatisme."
  - "In uw thuisomgeving weet je alles te staan... na een week zit dat erin."
- Geleidelijnen zijn "love-hate": ze helpen vooruit, maar op kruispunten ontbreekt beslissingsinformatie.
  - "Je volgt een lijn... probleem is dat je niet weet naar waar."
  - "In stations goed uitgewerkt, maar aan kruispunten weet niet naar welke kant."
- Real world messiness is een probleem: bezette geleidelijnen, slechte opvolging/onderhoud, en vooral werken/omleidingen veroorzaken onzekerheid en tijdverlies.
  - "Plots werken op het pad... niemand in de buurt, dan zoek je lang."
- Feedbackvoorkeur is contextgebonden: in publieke context is er duidelijke voorkeur om het gehoor vrij te houden, waardoor haptische feedback aantrekkelijk is.

Korte conclusie
De grootste pijn zit niet in "vooruit geraken", maar in keuzes maken aan knooppunten en omgaan met onbetrouwbare context (drukte, bezette lijnen, tijdelijke veranderingen). Een oplossing moet dus vooral junction ambiguity wegnemen met korte, zekere en contextgevoelige aanwijzingen.

Benchmarking / technology scouting (N = 11)
Key findings
- Veel systemen steunen sterk op audio (turn-by-turn), maar dat botst met de nood om het gehoor vrij te houden in publieke ruimtes.
- Infrastructuur gebaseerde oplossingen (beacons/codes) zijn bewezen, maar vragen inzet van gebouwbeheerders en zijn minder schaalbaar zonder uitrol.
- Infra vrije smartphone only oplossingen zijn schaalbaar, maar hebben trade offs:
  - afhankelijk van mapping/kaartwerk en updates
  - gevoelig voor kalibratie of cameracondities
- Haptische feedback is discreet en laat oren vrij, maar vraagt een duidelijke "taal" en leercurve. Combinaties van haptiek en korte spraak lijken vaak het meest robuust.
- Form factor is cruciaal: integratie in bestaande mobiliteitshulpmiddelen (bv. stokhandvat) of handsfree dragers verlaagt drempel en verhoogt bruikbaarheid.

Korte conclusie
Er is een duidelijke opportuniteit voor een hybride aanpak: haptisch eerst, handsfree waar mogelijk, schaalbaar met minimale infrastructuur, en doelgericht tot een exacte bestemming. De kern is betrouwbaarheid aan beslismomenten.

Conclusies en implicaties
-------------------------
Kernproblematiek
- Junction ambiguity in publieke gebouwen: geleidelijnen en bestaande oplossingen geven te weinig zekerheid op beslismomenten, zeker wanneer de omgeving afwijkt door drukte, bezette lijnen, werken of omleidingen.

Design implicaties
- Feedback moet primair haptisch zijn zodat het gehoor vrij blijft; audio kan optioneel als korte fallback.
- Het systeem moet expliciet ontworpen zijn rond decision points (knooppunten) in plaats van alleen algemene turn-by-turn begeleiding.
- De oplossing moet werken in realistische omstandigheden (bezette/inconsistente geleidelijnen, tijdelijke obstakels, omleidingen).
- De gebruiker moet eenvoudig een exacte bestemming kunnen kiezen en daarna frictieloos begeleid worden.

How Might We
------------
Hoe kunnen we blinde en ernstig slechtziende gebruikers in complexe publieke gebouwen betrouwbaar naar hun exacte doel leiden, met focus op knooppunten, minimale frictie en contextgevoelige feedback (haptisch en indien nodig korte spraak), zodat het ook werkt wanneer geleidelijnen bezet, onduidelijk of inconsistent zijn?

Design requirements (eerste versie)
-----------------------------------
- D1.1 Het systeem leidt de gebruiker in publieke gebouwen doelgericht naar een exacte bestemming (bv. balie, toilet, perron, uitgang).
- D1.2 Het systeem vermindert onzekerheid op knooppunten door ondubbelzinnige guidance op beslismomenten.
- D1.3 De primaire feedback is haptisch zodat het gehoor vrij blijft; audio is optioneel en kort (fallback).
- D1.4 De oplossing blijft bruikbaar wanneer geleidelijnen bezet, onduidelijk of inconsistent zijn en houdt rekening met tijdelijke obstakels/omleidingen.
- D2.1 De bestemming kiezen is toegankelijk en low friction (VoiceOver compatibel) en vereist minimale handelingen.
- D2.2 De oplossing is schaalbaar: minimale infrastructuur en haalbaar qua kost en beheer.
