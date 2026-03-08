# SensePath
### Ear-free, intuitive navigation indoors

🛠️ Built by **Sam Piryns**, **Titus Impens**, **Han Deburchgraeve**  
🔥 Supervised by `prof. dr. Bas Baccarne`, `Yannick Christiaens` & `Wouter Devriese`  
🌱 Grown at `Ghent University` 🏛️ `Industrial Design Engineering` ([project overview](https://github.com/basbaccarne/human-centered-design))

*19/01/2026*

---

## Introductie

Mensen die blind of slechtziend zijn navigeren buitenshuis relatief goed met GPS, maar in grote publieke gebouwen (stations, ziekenhuizen, campussen) valt die ondersteuning weg. Vooral op kruispunten, splitsingen en bij tijdelijke omleidingen leidt dit tot twijfel, extra mentale belasting en afhankelijkheid van hulp van anderen.

We onderzochten dit via deskresearch en benchmarking van bestaande (indoor) navigatieoplossingen, en via user interviews en feedbackmomenten met gebruikers en organisaties uit de blinden- en mobiliteitswereld. Daaruit kwamen duidelijke noden naar voren: betrouwbare "decision support" op keuzemomenten, zo weinig mogelijk telefoongebruik tijdens het stappen, en discrete feedback die ook in publieke context bruikbaar is.

Onze oplossing is **SensePath**: een slimme handgreep die op een bestaande lange witte stok wordt bevestigd en gekoppeld is aan een eenvoudige app-workflow. SensePath vertaalt route-informatie naar haptische begeleiding op het juiste moment (bv. bij keuzes en bochten), zodat de gebruiker "hands-free, heads-up" kan blijven bewegen met de stok als primair hulpmiddel. Optioneel biedt het systeem een fail-safe flow om te herstarten of hulp te vragen bij afwijkingen of blokkades. Zo maakt SensePath indoor navigatie zelfstandiger, rustiger en betrouwbaarder.

<p align="center">
  <img src="img/WhatsApp Image 2026-01-07 at 20.23.09.jpeg" alt="Hero render SensePath" width="600"/>
</p>

---

## Inhoudstafel

1. [Methodologie](#methodologie)
2. [Discovery](#discovery)
3. [Definition](#definition)
4. [Design Requirements](#design-requirements)
5. [Develop 1](#develop-1)
   - [Prototypes & User Testing](#user-testing)
   - [Develop 1 conclusies](#develop-1-conclusies)
6. [Kritische reflectie](#kritische-reflectie)
7. [Noot inzake het gebruik van AI](#noot-inzake-het-gebruik-van-ai)
8. [Bijlagen](#bijlagen)
9. [Bronnen](#bronnen)

---

## Methodologie

Dit project volgt de **Double Diamond** aanpak (Discover, Define, Develop, Deliver), met nadruk op gebruikersgericht ontwerpen en iteratieve validatie.

### Discovery (problem space)

In de discoveryfase werd de probleemruimte verkend via:

- **User interviews** — fricties, routines, copingstrategieën en contextfactoren identificeren (drukte, tijdelijke werken, knooppunten).
- **Deskresearch en benchmarking** — bestaande navigatie- en mobiliteitsoplossingen in kaart brengen en analyseren op feedbackmodaliteit, infrastructuurbehoefte, betrouwbaarheid en schaalbaarheid.

De resultaten werden samengebracht tot een probleemdefinitie, een eerste set **design requirements** en een initiële **PRD**.

### Definition (solution space)

In de definitionfase werd het concept getoetst en aangescherpt via **iteratief prototypen en testen** in twee waves:

- **Wave 1** — Vroege conceptvalidatie met low- tot mid-fidelity prototypes en Wizard-of-Oz scenario's. Focus op begrijpelijkheid, wenselijkheid en aanvaardbaarheid van de conceptrichting.
- **Wave 2** — Verfijning van interactie en feedback met nadruk op minimale smartphone-interactie, haptische feedback als primaire modaliteit, en een fail-safe workflow. Inclusief MoSCoW-prioritering en obstakeldetectie-observatietest.

### Develop (semester 2)

Technische uitwerking, interaction design, prototyping met oplopende fideliteit en usability testing in iteraties.

### Deliver (semester 2)

Finale validatie in realistische omgevingen, afronding prototype en documentatie.

📄 [Volledige methodologie](docs/methodologie.md)

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
| User interviews | Semigestructureerde diepte-interviews (15–20 min) | 3 | 18/10 – 25/10/2025 | Contextuele inzichten over routines, frustraties en voorkeuren |
| Benchmarking | Systematische vergelijking bestaande oplossingen | 11 | — | Sterktes → best practices, zwaktes → design opportuniteiten |

### Resultaten

#### User interviews — key findings

> *"Je volgt een lijn... probleem is dat je niet weet naar waar."*

- **Thuis vs. publiek** — Thuis is oriëntatie automatisme. In publieke gebouwen ontstaat onzekerheid, vooral aan knooppunten waar beslissingsinformatie ontbreekt.
- **Geleidelijnen: love-hate** — Ze helpen vooruit, maar op kruispunten ontbreekt informatie over richting.
- **Real world messiness** — Bezette geleidelijnen, slecht onderhoud, en vooral werken/omleidingen veroorzaken onzekerheid en tijdverlies.
- **Feedbackvoorkeur is contextgebonden** — In publieke context duidelijke voorkeur om gehoor vrij te houden → haptische feedback aantrekkelijk.

> *"Plots werken op het pad... niemand in de buurt, dan zoek je lang."*

**Korte conclusie:** De grootste pijn zit niet in "vooruit geraken", maar in keuzes maken aan knooppunten en omgaan met onbetrouwbare context.

#### Benchmarking — key findings

- Veel systemen steunen op **audio** (turn-by-turn), maar dat botst met de nood om het gehoor vrij te houden.
- **Infrastructuurgebaseerde oplossingen** (beacons/codes) zijn bewezen, maar vragen inzet van gebouwbeheerders en zijn minder schaalbaar.
- **Infra-vrije smartphone-only oplossingen** zijn schaalbaar, maar hebben trade-offs (mapping, kalibratie).
- **Haptische feedback** is discreet en laat oren vrij, maar vraagt een duidelijke "taal". Combinatie haptiek + korte spraak is meest robuust.
- **Form factor is cruciaal** — integratie in bestaande mobiliteitshulpmiddelen verlaagt drempel.

**Korte conclusie:** Duidelijke opportuniteit voor een hybride aanpak: haptisch eerst, handsfree, schaalbaar met minimale infrastructuur, doelgericht tot exacte bestemming.

### How Might We

> Hoe kunnen we blinde en ernstig slechtziende gebruikers in complexe publieke gebouwen betrouwbaar naar hun exacte doel leiden, met focus op knooppunten, minimale frictie en contextgevoelige feedback (haptisch en indien nodig korte spraak), zodat het ook werkt wanneer geleidelijnen bezet, onduidelijk of inconsistent zijn?

📄 [Volledig discovery-rapport](docs/discovery.md)

---

## Definition

### Doelstellingen

- Inzicht krijgen in hoe gebruikers zich vandaag verplaatsen en welke rol technologie hierin mag spelen.
- Verschillende haptische en fysieke concepten uittesten en vergelijken.
- Bepalen welke functies en feedbackvormen als logisch, betrouwbaar en aanvaardbaar worden ervaren.
- De belangrijkste design requirements definiëren.

### Wave 1 — Vroege conceptvalidatie

**Doel:** Nagaan of de conceptrichting (slimme handgreep op bestaande witte stok met discrete feedback) begrijpelijk, wenselijk en geloofwaardig aanvoelt.

**Aanpak:** Low-fidelity prototypes met verschillende haptische principes (mechanisch, vibratie, beweging, tactiel) werden getest via Wizard-of-Oz met ervaren stokgebruikers (N=5).

<p align="center">
  <img src="img/WhatsApp Image 2025-12-28 at 19.39.51.jpeg" width="180"/>
  <img src="img/WhatsApp Image 2026-01-19 at 16.18.37 (1).jpeg" width="180"/>
  <img src="img/WhatsApp Image 2026-01-19 at 16.18.38 (2).jpeg" width="180"/>
  <img src="img/WhatsApp Image 2026-01-19 at 16.18.38 (3).jpeg" width="180"/>
</p>

**Key findings:**

- Alle respondenten wezen een **volledige slimme stok** af. Een **afneembaar handvat** werd unaniem aanvaard.
- **Auditieve feedback** werd als storend ervaren — gehoor is cruciaal tijdens navigatie.
- **Mechanische en bewegingsgebaseerde feedback** werd spontaan en correct geïnterpreteerd.
- Abstracte/symbolische patronen werden als te complex ervaren tijdens het stappen.
- **Vertrouwen** is cruciaal: zelfs kleine vormen van instabiliteit leiden tot onmiddellijke afwijzing.

### Wave 2 — Verfijning en prioritering

**Doel:** Feedbackwijze optimaliseren, fysieke integratie evalueren, en design requirements prioriteren via MoSCoW-analyse.

**Aanpak:** Fitting-prototypes met klemmechanismes + verfijnde haptische varianten, getest met dezelfde respondenten (N=5). Inclusief obstakeldetectie-observatietest.

<p align="center">
  <img src="img/WhatsApp Image 2025-12-28 at 19.39.19.jpeg" width="180"/>
  <img src="img/WhatsApp Image 2025-12-28 at 19.39.52.jpeg" width="180"/>
  <img src="img/WhatsApp Image 2025-12-28 at 19.39.51 (1).jpeg" width="180"/>
  <img src="img/WhatsApp Image 2025-12-28 at 19.39.50.jpeg" width="180"/>
</p>

**Key findings:**

- **Stabiliteit en "één geheel"-gevoel** zijn essentieel — zelfs kleine speling leidde tot afwijzing.
- **Continue, rustige bewegingsfeedback** werd als geruststellend en betrouwbaar ervaren.
- **Vibratie** werd enkel aanvaard als aanvullende feedback (bevestiging), niet continu.
- Bij obstakeldetectie: **graduele toename** van het signaal werd als ondersteunend ervaren. Te snelle/dwingende waarschuwingen verhoogden stress.
- Technologie moet ondersteunen op beslismomenten, maar **nooit de controle overnemen**.

### Conclusies

SensePath heeft het meeste potentieel als:

- Een **afneembaar, modulair handvat** compatibel met meerdere witte stokken.
- Een hulpmiddel met **haptische feedback als primaire informatiedrager**.
- Een systeem met **rustige, intuïtieve bewegingsfeedback** in plaats van complexe signalen.
- Een oplossing die **bestaande routines respecteert** en minimale extra handelingen vereist.

Gebruikers verwachten eerst en vooral **betrouwbaarheid, controle en mentale rust**.

📄 [Volledig definition-rapport](docs/definition.md)

---

## Design Requirements

> [!IMPORTANT]
> **Fysiek ontwerp**
>
> | ID | Requirement |
> |---|---|
> | D1.1 | SensePath wordt ontworpen als **volledige slimme stok** (geen universeel afneembaar handvat) |
> | D1.2 | De stok moet beschikbaar zijn in **meerdere lengtes** |
> | D1.3 | De gebruiker moet **kunnen switchen tussen lengtes** (modulair systeem) |
> | D1.4 | De lengte-verbinding(en) moeten **mechanisch stabiel** zijn (geen speling/rotatie) |

> [!IMPORTANT]
> **Feedback & detectie**
>
> | ID | Requirement |
> |---|---|
> | D2.1 | Haptische feedback moet de **primaire informatiedrager** zijn (boven audio) |
> | D2.2 | Richtinginformatie moet **intuïtief** zijn (geen codes/patronen die je moet aanleren) |
> | D2.3 | Bewegingsgebaseerde haptiek moet **duidelijk en consistent** aanvoelen |
> | D2.4 | Vibratie mag enkel dienen als **secundaire feedback** (bevestiging/waarschuwing), niet continu |
> | D2.5 | Het systeem moet **obstakeldetectie op hoofdhoogte** ondersteunen |
> | D2.6 | Het systeem moet **obstakeldetectie voor putten en niveauverschillen** ondersteunen |

> [!IMPORTANT]
> **Interactie & controle**
>
> | ID | Requirement |
> |---|---|
> | D3.1 | De gebruiker moet **controle behouden** (duidelijk start/stop; geen onverwachte automatische acties) |
> | D3.2 | Interactie tijdens het stappen moet **minimaal** blijven |
> | D3.3 | De smartphone mag enkel een **ondersteunende rol** hebben (instellen/starten) |
> | D3.4 | De gebruiker moet op een bewust gekozen moment een **volledig overzicht** kunnen opvragen |
> | D3.5 | Overzichtsinformatie mag **niet continu aanwezig** zijn, maar enkel op vraag |

> [!IMPORTANT]
> **Betrouwbaarheid & compatibiliteit**
>
> | ID | Requirement |
> |---|---|
> | D4.1 | Het systeem mag het **normale stokgebruik niet verstoren** (gewicht, balans, grip) |
> | D4.2 | Het systeem moet **betrouwbaar en voorspelbaar** aanvoelen in dagelijks gebruik |
> | D5.1 | Het navigatiesysteem moet zowel **indoor als outdoor** gebruikt kunnen worden, met automatische overgang |

📄 [Volledige design requirements](docs/design_requirements.md)

---

## Develop 1

### Doelstellingen

In de Develop 1-fase verschuift de focus van conceptvalidatie naar **functionele verfijning**. Het doel is om van concept naar een onderbouwde functionele architectuur te evolueren: onzekerheden wegnemen via gerichte onderzoeksvragen, het product ontleden in deelaspecten, en prototypevarianten bouwen en testen.

### Onderzoeksvragen

- Kan de gebruiker via een trilsignaal in het handvat correct en tijdig een afslag herkennen en uitvoeren (links, rechts, schuin)?
- Kan de gebruiker via continue kompasfeedback in het handvat een bocht volgen en op koers blijven?
- Hoe effectief is de combinatie van trilsignaal (event-cue) en kompasfeedback (continue koerscorrectie) bij een gecombineerd parcours?
- Hoe verhoudt de nauwkeurigheid (out-of-area proportion) zich tot vergelijkbare systemen in de literatuur, specifiek het Tactile Compass (Liu et al., CHI 2021)?
- Wat is de subjectieve ervaring (workload, vertrouwen, leerbaarheid) van de gebruiker bij elke conditie?

### Scenario & user flow (Norman's 7 stages of action)

Het kernscenario is: **van punt A naar punt B (bv. station → lokaal) wandelen met SensePath, zonder dat aandacht (auditief/mentaal) overbelast raakt.**

### Storyboard

<!-- TODO: storyboard afbeelding toevoegen als img/storyboard.jpg -->

De user flow werd geanalyseerd via Norman's 7 stages of action:

| Fase | Wat de gebruiker doet | Fricties & aandachtspunten |
|---|---|---|
| **Goal** | Veilig en zelfstandig aankomen, met rust/vertrouwen | Doel is breder dan "navigeren": ook veiligheid, vertrouwen, stress |
| **Plan** | Beslissen: SensePath gebruiken? Smartphone nodig? Haptiek-only of audio? | Te veel opties = keuzestress → overchoice-effect. Mental model mismatch: user verwacht "stok blijft stok" |
| **Specify** | "SensePath ON", route starten naar bestemming, mode kiezen | Onduidelijke signifiers: waar/hoe start ik? (knop, lang indrukken, dubbelklik) |
| **Perform** | Wandelen met stok + haptische richtingscue + evt. waarschuwing/confirmatie | Interactie mag niet "extra handelingen" vragen. Recall i.p.v. recognition = hogere load |
| **Perceive** | Haptiek voelen (primair), evt. audio horen, stokfeedback voelen | In echte context (wind, handschoenen, stress) kan haptiek minder onderscheidbaar zijn |
| **Interpret** | Cue → betekenis → actie (mentale mapping) | Ambiguïteit tussen soorten feedback. Mental model mismatch door verkeerde systeemimage |
| **Compare** | "Ben ik nog op koers? Voel ik me veiliger?" | Resultaat niet eenduidig te linken aan systeem. Emotie en stress domineren de evaluatie |

### User flow

<p align="center">
  <img src="img/PGGO - SensePath - User flow.jpg" alt="User flow SensePath" width="800"/>
</p>

### Functionele breakdown

Het product werd ontleed in 8 functionele deelgebieden:

**1) Locatie instellen + vertrekken**
Persoon krijgt afspraakgegevens, zet bestemming in app (spraak/typ), bevestigt routekeuze, pakt handvat van oplaadstation, klikt/lockt op stok, handvat gaat aan (auto-on), app koppelt (BT) en geeft "klaar om te vertrekken" (korte haptische ping).

**2) Buiten wandelen: "kompas"-feedback (draaiend bolletje in handpalm)**
Systeem bepaalt startpositie + richting (GPS/kompas/IMU), handvat geeft startsignaal, bolletje draait naar "juiste looprichting", persoon voelt bol-oriëntatie in handpalm en corrigeert lichaam/looplijn. Bij GPS drift/urban canyon → systeem schakelt naar "lage zekerheid" patroon.

**3) Kruispunt: links/rechts instructie via trillmotoren (duim/middelvinger)**
Systeem herkent aankomend kruispunt (route-data + positie), handvat "waarschuwt vooraf", persoon vertraagt/zoekt veilig punt. Afslaaninstructie: trilling duim = rechts, trilling middelvinger = links. Persoon bevestigt (optioneel): knop/knijp/voice "ok".

**4) Obstakel: detectie + audiofeedback**
Sensoren scannen vooruit (hoogte/afstand), systeem detecteert obstakel, classificatie "urgentie": ver weg → zachte waarschuwing, dichtbij/snel → dringende waarschuwing. Audiofeedback start (via telefoon of speaker/bone conduction). Zodra obstakel voorbij: audio stopt + korte haptische "clear".

**5) Gebouw binnen: overgang outdoor → indoor**
Systeem merkt "GPS weg / signaalpatroon verandert" of detecteert ingang (geo-fence), handvat geeft transitie-signaal, app schakelt naar indoor positioning (BLE/Wi-Fi/UWB/QR-kaart). Kalibratie: "sta 1 seconde stil" (haptische vraag) om heading/IMU te resetten.

**6) Binnen: preciezere navigatie door het gebouw**
Systeem bepaalt indoor startpunt (ingang node), route door gebouw wordt gekozen (corridors, deuren, obstakels, toegankelijkheid). Persoon wandelt rechtuit: bolletje haptiek voor koers (subtwieler dan buiten). Turn-instructie via duim/middelvinger (zoals kruispunt, maar korter).

**7) Trappen en liften: verticale navigatie**
Systeem detecteert "verticale keuze punt" (trap/lift in route), handvat geeft speciaal patroon. Trap = ritmisch oploppend patroon, lift = lang-kort-lang. Persoon nadert trap/lift en stopt op veilige positie. Systeem geeft keuze/advies (toegankelijkheid). Trap-flow: waarschuwing → tempo-haptiek voor op/af → "einde trap" signaal.

**8) Aankomst op locatie**
Systeem herkent "bestemming bereikt", handvat geeft duidelijk eindsignaal (uniek patroon), systeem geeft "precise cue": exacte deur/desk. Persoon verifieert bestemming (tast naambordje, vraagt hulp, luistert). Navigatie stopt automatisch of na bevestiging ("stop"). Handvat gaat naar idle (energie besparen).

### Productarchitectuur (I/O)

<p align="center">
  <img src="img/PGGO - SensePath - HPI - Productarchitectuur (I_O).jpg" alt="Productarchitectuur I/O diagram" width="800"/>
</p>

De technische architectuur is opgebouwd rond drie lagen:

**Voor gebruik (initiatie + interactie):**
- Input: movement input (presence sensor) + push input (push button)
- Processing: microcontroller (Arduino/ESP32) met BLE of WiFi Direct pairing stok ↔ app
- Output: bestemmingselectie via app

**Tijdens gebruik:**
- Montage op stok → behuizing → obstakeldfeedback (pulsfrequentie/intensiteit stijgt)
- Vibratie (vibratiemotor) + audio (speaker) als outputmodaliteiten
- Gevaarsdetectie via lasersensor + ultrasoon sensor → afstandsmeting → obstakel → microcontroller
- Koersfeedback via draaiend element (servo/stepper/brushless motor → motor driver)
- Afslagcue via trilmotor omhulsel (vibratiemotor)

**Energiemanagement:**
- Batterij: lithium (cilindrisch/plat) of AAA oplaadbaar
- Opladen: USB-C / draadloos / magnetisch
- Low battery detectie → batterij feedback (korte toon / piezo buzzer)

### MVP-definitie

De MVP wordt gedefinieerd als de minimale set functies die moet werken om de kernwaarde van het concept aan te tonen: dat een gebruiker via haptische feedback binnenshuis van A naar B begeleid kan worden, met minimale smartphone-interactie tijdens het stappen.

**Essentieel voor proof of interaction:**
1. Start/stop van guidance
2. Continue haptische koersfeedback (recht lopen)
3. Turn cue op beslissingspunten (links/rechts) met duidelijke mapping
4. Aankomst/stop signaal (afscheidsritueel) zodat het systeem "sluit"
5. Basis statuszekerheid (minimaal: "guidance is aan")

**Niet essentieel voor proof of interaction:**
- Automatische herberekening
- Obstakeldetectie (los van navigatie)
- Uitgebreide contextbeschrijvingen
- Geavanceerde personalisatie in real time

**MVP-gate: speaker ja of nee**
Speaker wordt als experimentele variant binnen de MVP-test behandeld:
- Variant A: haptiek-only (baseline)
- Variant B: haptiek + minimale audio (alleen status of arrival, niet continu)
- Variant C: audio-first benchmark (zoals veel bestaande systemen)

### Morfologische matrix

<p align="center">
  <img src="img/PGGO - SensePath - Morfologische matrix.jpg" alt="Morfologische matrix SensePath" width="800"/>
</p>


### Interactieblokken & informatiehiërarchie

De MVP-interacties zijn opgedeeld in 5 blokken met oplopende pressure:

**A. Voor vertrek** (low pressure, smartphone toegestaan): route/bestemming selecteren, handle bevestigen, grip checken.

**B. Start guidance**: actie via fysieke input of gesture (knop duidelijk en robuust, gesture vereist filtering tegen accidental triggers).

**C. Tijdens wandelen** (high pressure, geen smartphone): continue koersfeedback voelen (background), omgeving scannen met stok (parallelle primaire taak), micro-correcties uitvoeren.

**D. Beslissingspunten**: turn cue detecteren en interpreteren (event), actie uitvoeren (links/rechts), korte bevestiging na turn (optioneel).

**E. Stop of aankomst**: arrival/stop cue (closure), guidance stopt en wordt stil.

**Informatiehiërarchie:**
- Background info: koersfeedback (mag niet opdringerig zijn)
- Event info: turn cue (hoog belang, korte duidelijke cue)
- Fail/status info: alleen wanneer nodig (bv. guidance aan/uit)

### Prototypes

Er werden twee prototypevarianten gebouwd op basis van de morfologische matrix:

**Prototype 1: Vibratie (afslagcue)**
3D-geprint handvat met drie trilmotoren (duim, wijsvinger, middelvinger) aangestuurd via ESP32 en een Wizard-of-Oz controller-app. De wizard triggert op het juiste moment links/rechts/rechtdoor signalen.

**Prototype 2: Kompas (koersfeedback)**
3D-geprint handvat met een draaiend bolletje in de handpalm dat continue richtingsfeedback geeft. De wizard stuurt de kompasrichting aan op basis van de gewenste looprichting.

<p align="center">
  <img src="img/WhatsApp Image 2026-03-08 at 19.57.35 (1).jpeg" width="200"/>
  <img src="img/WhatsApp Image 2026-03-08 at 19.57.35.jpeg" width="200"/>
  <img src="img/WhatsApp Image 2026-03-08 at 19.57.34 (1).jpeg" width="200"/>
  <img src="img/WhatsApp Image 2026-03-08 at 19.57.34.jpeg" width="200"/>
</p>

### User testing

**Sample (N=5):**

| Naam | Leeftijd | Relevantie | Locatie | Datum |
|---|---|---|---|---|
| Mario | 52 | Verloor zicht op 18-jarige leeftijd | Licht en Liefde | 04/03/2026 |
| Rory | 55 | Ernstig slechtziend | Licht en Liefde | 04/03/2026 |
| Herman | 65 | Blind sinds geboorte | Licht en Liefde | 06/03/2026 |
| Milo | 20 | Ziend (controle) | Thuis | 08/03/2026 |
| Milos | 20 | Ziend (controle) | Thuis | 08/03/2026 |

**Protocol:** Introductie & leerfase → Test 1 (kompas) → Interview & subjectieve scores → Test 2 (vibratie) → Interview & subjectieve scores → Test 3 (gecombineerd) → Reflectie. Alle tests via Wizard-of-Oz op een afgetaped parcours (60cm breedte).

### Test 1: Bocht via kompasfeedback

De wizard biedt continue feedback via het draaiende kompasbolletje in het handvat.

> *"Ik denk dat het zelfs zou lukken om niet buiten het pad te gaan."*

**Key findings:**
- **Grip bepaalt interpretatie** — Verschillende grip = links/rechts omgekeerd. Handoriëntatie is cruciaal.
- **Palmsensatie is zwak** — Meerdere deelnemers voelden het bolletje nauwelijks.
- **Ergonomie onvoldoende** — Handvat past niet bij elke hand. Bolletje is verkeerd gepositioneerd.
- **Rechtdoor lopen werkt** — Goede resultaten bij rechtdoor; bochten zijn moeilijker.
- **Winter = probleem** — Handschoenen en dikke jassen blokkeren de sensatie.

**Benchmark vergelijking Test 1:**

| Metric | Tactile Compass (Liu et al.) | SensePath |
|---|---|---|
| SIZ (% stappen in zone) | 92,6% | 83,78% |
| Leerbaarheid (1–7) | 6,67 | 5,67 |
| Soepelheid (1–7) | 6,06 | 5,50 |
| Cognitieve belasting (1–7) | 5,22 | 3,67 |
| Bereidheid (1–7) | 6,39 | 5,33 |
| Vertrouwen (1–7) | n.v.t. | 5,33 |

### Test 2: Afslag via trilsignaal

De wizard stuurt trilsignalen op het juiste moment via de controller-app.

> *"Die trilmotoren, dat ging wel goed."*
> *"Het voelde beter, minder concentreren dan het balletje."*

**Key findings:**
- **Vingertoppen voelen het best** — "Daar zitten de voelers."
- **Afslaan werkt goed** — Richtingssignalen worden snel begrepen en aangeleerd.
- **Rechtdoor is moeilijker** — Zonder continu signaal drijven gebruikers af.
- **Bevestigingssignaal nodig** — Gebruikers willen feedback dat ze rechtdoor lopen.
- **Niet te veel signalen** — "Begin niet met zevenhonderdachtendertig verschillende signalen."
- **Sensorpositie problematisch** — Links past goed = rechts past slecht, en omgekeerd. Handgrootte speelt een rol.

**Benchmark vergelijking Test 2:**

| Metric | Tactile Compass (Liu et al.) | SensePath |
|---|---|---|
| SIZ (% stappen in zone) | 92,6% | 79,85% |
| Leerbaarheid (1–7) | 6,67 | 6,50 |
| Soepelheid (1–7) | 6,06 | 6,33 |
| Cognitieve belasting (1–7) | 5,22 | 4,67 |
| Bereidheid (1–7) | 6,39 | 6,33 |
| Vertrouwen (1–7) | n.v.t. | 6,00 |

### Test 3: Gecombineerd parcours

Kompas (continue koersfeedback) + vibratie (afslagcue) samen op hetzelfde parcours.

> *"Ik ben wel onder indruk van deze keer."*
> *"Het was beter dan ik had verwacht."*

**Key findings:**
- **Vibratie interfereert met kompas** — Twee systemen tegelijk aflezen op één hand is moeilijk.
- **Ergonomie is de bottleneck** — Huidig prototype laat geen eerlijke evaluatie toe.
- **Concept heeft potentieel** — Vibratie als aankondiging + kompas voor koerscorrectie is logisch.
- **Hogere cognitieve belasting** — Scores dalen vergeleken met individuele tests.
- **Herpositionering bolletje** — Suggestie: naar de knokkels of hiel van de hand i.p.v. de palm.
- **Audio als back-up** — Speaker/bluetooth voor wanneer vibraties niet waarneembaar zijn.

**Benchmark vergelijking Test 3:**

| Metric | Tactile Compass (Liu et al.) | SensePath |
|---|---|---|
| SIZ (% stappen in zone) | 92,6% | **97,52%** |
| Leerbaarheid (1–7) | 6,67 | 6,00 |
| Soepelheid (1–7) | 6,06 | 4,67 |
| Cognitieve belasting (1–7) | 5,22 | 3,00 |
| Bereidheid (1–7) | 6,39 | 4,33 |
| Vertrouwen (1–7) | n.v.t. | 3,00 |

### Develop 1 conclusies

- **Vibratie is intuïtiever** dan kompas voor discrete navigatie-events (afslagen).
- **Kompas biedt superieure koersbewaking** maar lijdt onder perceptuele ambiguïteit.
- De **gecombineerde conditie scoorde het hoogst op nauwkeurigheid** (97,52% SIZ) maar het laagst op subjectieve ervaring.
- **Ergonomie is geen bijzaak** — het is de primaire confound in de data.
- SensePath houdt stand tegen de **Tactile Compass benchmark** onder moeilijkere condities (met stok, video-observatie i.p.v. OptiTrack, Wizard-of-Oz i.p.v. automatisch).
- **90% van alle fouten** is te wijten aan wizard-timing — bij automatisering worden minder fouten verwacht.
- Gebruikers memoriseren onbewust het pad over de drie tests heen, wat een confound vormt voor de SIZ-scores.

---

## Kritische reflectie

Uit de vergelijking tussen test 1 en test 2 blijkt dat gebruikers fouten sneller corrigeren. Dat wijst erop dat ze het pad beter begrijpen naarmate ze er vaker mee in contact komen en dat hun reactie op fouten met de tijd efficiënter wordt. 

Daarnaast toont de evolutie over test 1, test 2 en test 3 dat gebruikers het pad onbewust beginnen te onthouden. Door herhaling ontstaat er dus een vorm van path learning, waardoor de uitvoering vlotter en waarschijnlijk ook consistenter verloopt. 

Een belangrijk inzicht is dat 90% van alle fouten te wijten is aan de timing van de wizard. Dat betekent dat een groot deel van de fouten niet noodzakelijk door de gebruiker zelf veroorzaakt wordt, maar eerder samenhangt met het moment waarop de begeleiding of tussenkomst plaatsvindt. Op basis daarvan kan verondersteld worden dat een geautomatiseerde aanpak minder fouten zou opleveren. 

Ten slotte wijst de vergelijking tussen omgeving en cognitieve belasting erop dat de context waarin de test plaatsvindt een invloed kan hebben op de prestaties van de gebruiker. Een complexere of minder geschikte omgeving kan de cognitieve load verhogen, wat op zijn beurt het aantal fouten of de moeilijkheidsgraad van de taak kan beïnvloeden. 

---

## Noot inzake het gebruik van AI

Binnen dit project werden meerdere AI-tools ingezet als ondersteunend hulpmiddel:

- **Tekst en rapportage** — Claude (Anthropic) werd gebruikt om ruwe notities en onderzoeksdata te structureren tot leesbare paragrafen en om teksten taalkundig te verfijnen. De inhoudelijke keuzes, analyses en conclusies zijn steeds door het team zelf gemaakt.
- **Benchmarking en analyse** — AI werd ingezet om publiek beschikbare informatie samen te vatten, vergelijkingscriteria te structureren en eerste analyses te genereren. Alle bevindingen werden handmatig geverifieerd.
- **Storyboard** — Het script werd geschreven met Claude Code, image direction via ChatGPT (GPT-4o), en de uiteindelijke beeldgeneratie via NanoBanana (Gemini 3 Pro Image).
- **Codering** — Claude en Gemini werden gebruikt voor ondersteuning bij de ESP32-firmware en de Wizard-of-Oz controller-app.

AI werd **niet** ingezet voor het uitvoeren of analyseren van user interviews, het nemen van ontwerpbeslissingen, of het formuleren van design requirements. Deze zijn volledig gebaseerd op eigen gebruikersonderzoek en teamreflectie.

> *"All content in this document has been reviewed and approved by the author. AI tools were used solely to support text processing, coding, and image editing, not for generating research data or conclusions."*

---

## Bijlagen

### Discovery

| Document | Link |
|---|---|
| Interview protocol | [Interview - protocol - SensePath.docx](reports%20and%20protocols/Interview%20-%20protocol%20-%20SensePath.docx) |
| Onderzoeksrapport interviews | [Onderzoeksrapport_user_interviews_SensePath.docx](reports%20and%20protocols/Onderzoeksrapport_user_interviews_SensePath.docx) |
| Benchmarking protocol | [Benchmarkingprotocol_SensePath.docx](reports%20and%20protocols/Benchmarkingprotocol_SensePath.docx) |
| Benchmarking rapport | [Benchmarkingrapport_SensePath.docx](reports%20and%20protocols/Benchmarkingrapport_SensePath.docx) |

### Definition

| Document | Link |
|---|---|
| Wave 1 — Protocol | [Protocol](reports%20and%20protocols/) |
| Wave 1 — Rapport | [Rapport](reports%20and%20protocols/) |
| Wave 2 — Protocol | [Protocol](reports%20and%20protocols/) |
| Wave 2 — Rapport | [Rapport](reports%20and%20protocols/) |

### Overige documenten

- [Methodologie](docs/methodologie.md)
- [Discovery](docs/discovery.md)
- [Definition](docs/definition.md)
- [Design Requirements](docs/design_requirements.md)
- [Bill of Materials](docs/bom.md)

---

## Bronnen

- Liu, G., Yu, T., Yu, C., Xu, H., Xu, S., Yang, C., Wang, F., Mi, H., & Shi, Y. (2021). Tactile Compass: Enabling visually impaired people to follow a path with continuous directional feedback. *Proceedings of the 2021 CHI Conference on Human Factors in Computing Systems*. ACM. https://doi.org/10.1145/3411764.3445644
- Guerreiro, J., Ahmetovic, D., Sato, D., Kitani, K., & Asakawa, C. (2019). Airport accessibility and navigation assistance for people with visual impairments. *Proceedings of the 2019 CHI Conference on Human Factors in Computing Systems*, 1–14.
- Slade, P., Tambe, A., & Kochenderfer, M. J. (2021). Multimodal sensing and intuitive steering assistance improve navigation and mobility for people with impaired vision. *Science Robotics, 6*(59), eabg6594.
- Norman, D. A. (2013). *The Design of Everyday Things: Revised and Expanded Edition.* Basic Books.
- World Health Organization. (2023). *Blindness and vision impairment.* Geraadpleegd van https://www.who.int/news-room/fact-sheets/detail/blindness-and-visual-impairment
- Design Council. (2005). *The Double Diamond: A universally accepted depiction of the design process.* Geraadpleegd van https://www.designcouncil.org.uk/double-diamond
- Anthropic. (2025). Claude (Claude Opus 4.6) [Groot taalmodel]. https://claude.ai
- OpenAI. (2025). ChatGPT (GPT-4o) [Groot taalmodel]. https://chat.openai.com
- Google DeepMind. (2025). Nano Banana Pro (Gemini 3 Pro Image) [AI-beeldgeneratiemodel].

---

## Licentie

This repository contains both software and design materials created as part of an industrial design engineering project at Ghent University.

- **Software and code:** [MIT License](LICENSE-MIT)
- **Design, documentation, CAD, and media:** [CC BY 4.0 License](LICENSE)

You are free to reuse and build upon this work, both commercially and non-commercially, as long as proper attribution is given to the original authors.
