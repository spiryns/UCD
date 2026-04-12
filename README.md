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
<p align="center">
  <img src="img/ChatGPT Image 19 feb 2026, 20_31_14.png" alt="User flow SensePath" width="800"/>
</p>

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
  <img src="img/PGGO - SensePath - Morfologische matrix.jpg"
</p>

De morfologische matrix werd gebruikt om per functieblok een afweging te maken tussen wat vandaag het meest geschikt is voor het prototype, wat later het meest geschikt lijkt voor het eindproduct, en welke keuzes in beide fasen overeind blijven.

Volgens de legende betekent:
- **grijs** = keuze voor het prototype
- **lichtgroen** = keuze voor het eindproduct
- **donkergroen** = keuze voor beide

### Interpretatie van de keuzes

De matrix toont dat we voor het **prototype** vooral kozen voor oplossingen die snel testbaar, robuust en technisch haalbaar zijn binnen een iteratief ontwikkelproces. De nadruk ligt daar op het kunnen valideren van de kerninteractie en het betrouwbaar opzetten van experimenten.

Voor het **eindproduct** verschuiven de keuzes meer naar verfijning, compactheid, integratie en gebruikskwaliteit. Hier ligt de focus sterker op comfort, subtiliteit van feedback, toegankelijkheid en een meer afgewerkte gebruikerservaring.

De keuzes die voor **beide** gelden, tonen welke principes voor ons conceptueel fundamenteel zijn. Het gaat daarbij vooral om de basis van de interactie: hoe het systeem geactiveerd wordt, hoe de gebruiker begeleid wordt, hoe feedback wordt gegeven en welke referentiestructuur het systeem gebruikt om richting betekenisvol te maken.

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
## Develop 2

### Doelstellingen

In de Develop 2-fase verschuift de focus van **functionele verfijning** naar **usability en ergonomie**. Het doel is om de drie kernproblemen die uit Develop 1 naar boven kwamen aan te pakken via theoretisch onderbouwde herontwerpkeuzes en die te valideren met een nieuwe gebruikerstest. De drie pijlers zijn: **usability goals** (meetbaar maken van gebruiksvriendelijkheid), **antropometrie** (handvat afstemmen op de doelgroep) en **cognitieve & sensorische ergonomie** (mentale belasting verlagen via theoretische principes uit Norman, Gestalt en signifiers).

Concreet bouwen we voort op vier vaststellingen uit Develop 1: de gecombineerde conditie haalde 97,52% nauwkeurigheid maar slechts 3,00/7 op cognitieve belasting, de mentale mapping van het kompas brak bij andere grippatronen, het kompasbolletje in de handpalm werd nauwelijks gevoeld, en er ontbraken signifiers voor moduswisseling en systeemonzekerheid.

### Onderzoeksvragen

- Op welke hoogte binnen de gleuf van het handvat wordt het kompas het duidelijkst waargenomen?
- Welk contactoppervlak van het kompas (afgerond rechthoekig uitsteeksel, sferisch element, of schuin afgeronde overgangsvorm) brengt richtingsbeweging het duidelijkst over?
- Verlaagt de voorkeursconfiguratie de ervaren cognitieve belasting en verhoogt ze het vertrouwen ten opzichte van Develop 1?
- Blijft de padnauwkeurigheid (SIZ) minstens op het Develop 1-niveau met de nieuwe kompaspositie en aangepaste feedback?

### Usability goals

Voor Develop 2 werden zeven usability goals gedefinieerd volgens de ISO-benadering uit het cursusmateriaal Gebruiksgericht Ontwerpen, waarbij elk doel specifiek en meetbaar is en expliciet vermeld wordt of het om een **observed** (geobserveerde) of **perceived** (waargenomen) meting gaat. De Develop 1-resultaten dienen als kwantitatief referentiepunt.

**Effectiveness**

| ID | Doel | Type |
|---|---|---|
| UG1 | Padnauwkeurigheid: SIZ ≥ Develop 1 niveau (97,52%) op het benchmarkparcours | observed |
| UG2 | Aantal twijfelmomenten ≤ aantal in Develop 1, gemeten via video | observed |

**Satisfaction**

| ID | Doel | Type |
|---|---|---|
| UG3 | Cognitieve belasting (Likert): ≥ 4,50 (Develop 1 = 3,00) | perceived |
| UG4 | Vertrouwen (Likert): ≥ 5,00 (Develop 1 = 3,00) | perceived |
| UG5 | Bereidheid tot gebruik (Likert): ≥ 5,50 (Develop 1 = 4,33) | perceived |

**Preference ranking**

| ID | Doel | Type |
|---|---|---|
| UG6 | Voorkeursrangschikking gleufpositie over 5 posities | perceived |
| UG7 | Voorkeursrangschikking kompaselement over 5 elementen | perceived |

### Antropometrie

Een van de belangrijkste lessen uit Develop 1 was dat het handvat niet goed paste bij elke handgrootte en grip. De sensorpositie die voor de ene gebruiker comfortabel was, paste voor de andere slecht. Voor Develop 2 werd het handvat daarom antropometrisch onderbouwd via **Siemens NX** met de **ANSUR II-database**.

De ontwerpstrategie volgt de "gemiddelde gebruiker"-aanpak: de handvatdimensies werden gekalibreerd voor het **middelste 50% van de doelgroep** (P25 tot P75), zodat zowel gebruikers met kleinere als grotere handen het handvat comfortabel kunnen vasthouden zonder de grip te moeten forceren. Concreet werd er gewerkt met een mannelijke rechterhand, blote handen en een finger-press posture, met als referentiewaarden lengte 19,3 cm en breedte 8,8 cm (P50).

De diameter van het handvat werd zo bepaald dat de grip natuurlijk blijft over het hele percentielbereik. De lengte van de kompasgleuf werd zo gedimensioneerd dat alle 5 verticale posities binnen de actieve handpalmcontactzone van het middelste 50% vallen. De afstanden tussen de gleufposities werden afgeleid uit het finger-press contact mapping in NX, zodat elke positie effectief verschillend wordt waargenomen door de gebruiker.

De antropometrische output werd rechtstreeks gevoed in de prototype-CAD en empirisch gevalideerd tijdens Test 1 en Test 2 met Mario, Herman en Rory.

<insert afbeelding NX hand model>

### Cognitieve & sensorische ergonomie

De cognitieve en sensorische analyse vormt het theoretische hart van Develop 2. Ze koppelt de problemen uit Develop 1 aan drie kaders uit het cursusmateriaal Gebruiksgericht Ontwerpen: **Norman's 7 Stages of Action**, de **Gestalt-wetten**, en het concept van **signifiers**. Elke theoretische vaststelling wordt vertaald naar een concrete ontwerpkeuze.

#### Norman's 7 Stages of Action

In Develop 1 braken drie van Norman's zeven fasen: Perceive, Interpret en Compare.

**Perceive (waarnemen)** — Het probleem was dat twee haptische kanalen (kompas en trilmotoren) tegelijk "gelezen" moesten worden op dezelfde hand. Het probleem was niet dat er te veel informatie was, maar dat de sensorische kanalen elkaar overlapten op dezelfde anatomische zone. Het ontwerpprincipe dat hieruit volgt is **ruimtelijke scheiding van feedbackkanalen**: kompas en trilmotoren moeten op anatomisch gescheiden zones zitten zodat ze niet interfereren. Concreet zijn de finger-mounted vibratiemotoren verwijderd ten gunste van één enkele in-handle motor, en is het kompas verplaatst naar de hypothenar (hiel van de hand).

**Interpret (interpreteren)** — De mentale mapping "balletje naar beneden = rechts draaien" bleek grip-afhankelijk in Develop 1. Verschillende gebruikers hielden het handvat anders vast, waardoor dezelfde beweging tegengestelde betekenissen kreeg. Norman noemt dit een **system image mismatch**: het conceptuele model van de ontwerper klopt niet met het mentale model dat de gebruiker opbouwt op basis van wat het systeem hem laat zien. Het ontwerpprincipe is dat de mapping robuust moet zijn ongeacht gripvariatie. Voor Develop 2 wordt dit opgelost via een **onboarding tutorial** die de oriëntatie kalibreert op de natuurlijke grip van de gebruiker, en een **IMU-gebaseerde fallback** die waarschuwt wanneer de griporiëntatie de mapping breekt.

**Compare (vergelijken)** — De gebruiker wil evalueren "ben ik nog op koers?" maar krijgt daar in Develop 1 onvoldoende bevestiging van. Dit is wat Norman de **Gulf of Evaluation** noemt: de afstand tussen de feedback die het systeem geeft en wat de gebruiker nodig heeft om zijn doel te toetsen. Het ontwerpprincipe is dat het systeem expliciet en eerlijk moet communiceren over zijn eigen status.

#### Gestalt-wetten

De Gestalt-wetten zijn klassiek beschreven voor visuele perceptie, maar gelden evengoed voor tactiele perceptie. Mensen groeperen sensorische input automatisch volgens dezelfde principes.

**Wet van figuur-grond** — Er moet altijd een duidelijk onderscheid zijn tussen wat de "figuur" is (opvallend, belangrijk) en wat de "grond" is (achtergrond, context). In Develop 1 was dit contrast te zwak: het kompas was te subtiel en de vibratie was niet duidelijk genoeg afgebakend van de continue koersfeedback. Het ontwerpprincipe is **versterk het intensiteitscontrast**: vibratie moet kort en krachtig zijn, kompas moet rustig en continu blijven, en beide moeten duidelijk onderscheidbaar zijn.

**Wet van continuïteit** — Mensen volgen liever een doorlopende sensorische stroom dan onderbroken brokstukken. Het kompas geeft continue feedback, vibratie is discreet. Wanneer beide tegelijk actief zijn, "wint" de continue stroom de aandacht en wordt de korte vibratiecue gemist. De ontwerpimplicatie is dat het **kompas kort pauzeert tijdens een vibratiecue**, zodat het korte event-signaal niet verdrinkt in de achtergrondstroom van de koersfeedback.

**Wet van proximity en common region** — Dingen die fysiek dicht bij elkaar zitten of in dezelfde anatomische zone, worden onbewust als één signaal gegroepeerd in plaats van als twee aparte informatiestromen. In Develop 1 zaten kompas en trilmotoren fysiek dicht bij elkaar op dezelfde hand, waardoor ze als één moeilijk te ontleden brij werden waargenomen. Door ze in verschillende anatomische zones te plaatsen creëer je twee aparte "common regions" die elk hun eigen informatie dragen.

#### Signifiers

Norman definieert signifiers als waarneembare aanwijzingen die de gebruiker vertellen wat er kan, gebeurt of fout is. Bij SensePath, een product zonder visuele interface, moeten signifiers volledig tactiel zijn. Uit Develop 1 bleken twee signifiers te ontbreken:

- **Transitiesignaal tussen modi** — Wanneer het systeem schakelt van buiten naar binnen, of van een modus naar een andere, is er geen signifier voor die overgang. De gebruiker merkt de verandering pas wanneer iets onverwachts gebeurt. Voorstel: een uniek kort trilpatroon dat de moduswissel aankondigt.
- **Fout-signifier** — Wanneer het systeem onzeker is over zijn eigen positie of de wizard-timing mist, is er geen feedback dat er iets onverwachts gebeurt. Dit ondergraaft het vertrouwen omdat de gebruiker een fout mental model opbouwt ("ik deed iets fout") terwijl het systeem zelf faalde. Voorstel: een specifiek "heroriënteer"-signaal dat duidelijk verschilt van navigatiecues.

#### Vertaling naar het prototype

De theoretische analyse leidt tot vier concrete ontwerpkeuzes voor Develop 2:

- **Ruimtelijke scheiding van kanalen** — finger-mounted vibratiemotoren verwijderd, één enkele in-handle motor met een beperkte set codes
- **Mental mapping veiliggesteld** — onboarding tutorial die kalibreert op de natuurlijke grip van de gebruiker, IMU-fallback die waarschuwt bij gripverandering
- **Figuur-grond contrast** — vibratie wordt kort en krachtig; kompas pauzeert tijdens een vibratiecue
- **Twee nieuwe signifiers** — uniek patroon voor moduswisseling en eerlijk fout-signaal voor systeemonzekerheid

### Prototypes

Voor Develop 2 werden drie prototypedimensies gevarieerd via **variety prototyping**, een methode die expliciet meerdere fysieke varianten naast elkaar test om confirmation bias te vermijden.

**Handle profile** — Drie verschillende handvatprofielen werden ontwikkeld om de algemene grip-ergonomie te onderzoeken. De vorm bepaalt hoe de hand zich rond het handvat sluit en beïnvloedt onbewust de handoriëntatie.

<insert afbeelding handle profile>

**Compass groove** — Het handvat werd voorzien van een verticale gleuf met **vijf posities** waarin het kompaselement geplaatst kon worden, van H1 (laagste, dicht bij de pols) tot H5 (hoogste, dicht bij de knokkels). Door dezelfde gleuf te gebruiken kon de positie systematisch gewisseld worden zonder andere variabelen te veranderen.

<insert afbeelding compass groove>

**Contact surface** — Vijf verschillende kompaselementen werden ontwikkeld die elk een combinatie zijn van **vorm én uitsteekselhoogte**. Drie afgeronde rechthoekige uitsteeksels op verschillende uitsteekselhoogtes (laag, midden, hoog), één sferisch element, en één schuin afgeronde overgangsvorm. Dat laatste element kwam voort uit een inzicht van Mario tijdens zijn sessie: een geleidelijke overgang van vlak naar verhoog vermindert het scherpe contactgevoel tegen de hand.

<insert afbeelding contact surface>

Belangrijk om te vermelden: deze tests werden uitgevoerd **zonder stok**. De focus lag puur op de ergonomie van het handvat zelf, los van de stok-feedback, om te vermijden dat één variabele de evaluatie van de andere zou vertroebelen. De stok werd parallel uitgewerkt door collega's binnen het maturity-spoor.

### User testing

**Sample (N=5):**

| Naam | Leeftijd | Relevantie | Locatie | Datum |
|---|---|---|---|---|
| Mario | 52 | Verloor zicht op 18-jarige leeftijd | Licht en Liefde | 07/04/2026 |
| Rory | 55 | Ernstig slechtziend | Licht en Liefde | 09/04/2026 |
| Herman | 65 | Blind sinds geboorte | Licht en Liefde | 08/04/2026 |
| Milo | 20 | Ziend (controle) | Thuis | 10/03/2026 |
| Milos | 20 | Ziend (controle) | Thuis | 10/03/2026 |

**Protocol:** Introductie & feedback implementatie → Test 1 (gleufpositie) → Test 2 (kompaselement) → Test 3 (volledig benchmarkparcours) → interview & subjectieve scores → reflectie. De drie tests volgen een **getrapt within-subjects design**: de voorkeur uit Test 1 wordt constant gehouden in Test 2, en de voorkeurscombinatie uit Test 1 en Test 2 wordt meegenomen in Test 3 als benchmarkconfiguratie. Zo wordt confirmation bias vermeden zonder dat alle 25 combinaties getest moeten worden.

<insert afbeelding tijdens de test>

### Test 1: Compass grooves

In Test 1 werd onderzocht op welke gleufpositie het kompaselement het duidelijkst voelbaar is, gegeven de natuurlijke grip van de gebruiker. De vijf posities werden in stilstand gevoeld en daarna kort op een rechte loopstrook getest, met het referentie-element (afgerond rechthoekig uitsteeksel, middelhoge uitsteekselhoogte) constant gehouden over alle posities zodat alleen de gleufpositie varieerde.

> *"Daar voel ik het 't best, helemaal onderaan."*
> *"De bovenste was lastig, mijn vel kwam ertussen."*

**Key findings:**

- **Laagste gleufpositie (H1) gewonnen** — Zowel Mario als Herman kozen onafhankelijk de positie het dichtst bij de hiel van de hand.
- **Hypothenar als ankerpunt** — Op de laagste positie rust het element tegen het stevige vlezige deel van de handpalm bij de pols, waar de hand sowieso contact maakt ongeacht hoe ze het handvat vasthouden. Dit lost het Develop 1-probleem van handpalmcentrum (te zwak signaal) op.
- **Hoogste positie problematisch** — Bij de bovenste gleuf raakte de huid bekneld tussen het element en de gleufrand. Dit was een mechanisch probleem dat alleen bij dynamisch grijpen naar boven kwam.
- **Grip-onafhankelijkheid bevestigd** — De laagste gleufpositie werkt over verschillende grippatronen heen omdat het contactvlak anatomisch verankerd is, niet handpositie-afhankelijk. Dit is precies wat de Norman-analyse voorspelde over het belang van een grip-onafhankelijke mapping.

### Test 2: Contact surface

In Test 2 werd op de voorkeursgleufpositie uit Test 1 gezocht naar de combinatie van vorm en uitsteekselhoogte die de richtingsbeweging het duidelijkst en comfortabelst overbrengt. Vijf elementen werden in stilstand gevoeld en daarna kort op een rechte loopstrook getest, gevolgd door een rangschikking door de deelnemer.

**Varianten:**
- C1: Afgerond rechthoekig uitsteeksel, **lage** uitsteekselhoogte
- C2: Afgerond rechthoekig uitsteeksel, **middelhoge** uitsteekselhoogte
- C3: Afgerond rechthoekig uitsteeksel, **hoge** uitsteekselhoogte
- C4: **Sferisch** element
- C5: **Schuin afgeronde** overgangsvorm

> *"Het ronde voelt het zachtste, maar je weet duidelijk waar het naartoe gaat."*
> *"De middelste hoogte is precies goed, niet scherp, wel duidelijk."*

**Key findings:**

- **Middelhoge uitsteekselhoogte gewonnen** — Lage uitsteeksels voelden te subtiel, hoge voelden scherp en oncomfortabel. De middelhoge gaf de beste balans tussen voelbaarheid en comfort.
- **Sferisch element als voorkeursvorm** — Soepele overdracht van richtingsbeweging, geen scherpe randen tegen de huid, comfortabel over verschillende griprotaties. Dit komt rechtstreeks voort uit de Gestalt figuur-grond analyse: het sferische element levert een duidelijker afgebakend tactiel signaal.
- **Schuin afgeronde overgangsvorm (C5) als sterke tweede** — Vooral gewaardeerd voor de geleidelijke overgang van vlak naar verhoog, een idee dat Mario tijdens zijn sessie aanbracht en dat Rory bevestigde.
- **Glove-inzicht van Mario** — Mario merkte op dat in winterse omstandigheden met handschoenen het element nauwelijks voelbaar zou zijn. Dit triggerde het idee van een **uitwisselbare kompasmodule** met een robuustere wintervariant.

### Test 3: Turn via compass feedback

In Test 3 werd de voorkeurscombinatie uit Test 1 en Test 2 (laagste gleufpositie + middelhoge uitsteekselhoogte + sferisch element) gevalideerd op een volledig benchmarkparcours van 60 cm breed, gelijkaardig aan het Develop 1-parcours. De wizard biedt continue kompasfeedback waarbij het kompaselement volledig uitwijkt naar de doelrichting en geleidelijk terugkoppelt naar neutraal naarmate de deelnemer zich oriënteert.

<insert afbeelding path test 3>

> *"Ik ben wel onder de indruk, het is echt beter dan de vorige keer."* — Mario
>
> *"180 graden draaien is eigenlijk niet nodig, het stuurt continu bij."* — Rory
>
> *"Het werkt, maar ik blijf voor mezelf liever met audio werken."* — Herman

**Key findings:**

- **Single focus point is een echte verlichting** — Gebruikers hoeven enkel op het kompas te letten, geen restrictie meer op handpositie om finger-mounted vibratiemotoren te voelen. De grip mag natuurlijk blijven, wat het belangrijkste ergonomische pluspunt is van de Develop 2 herontwerpkeuze.
- **180° uitwijking is in de praktijk overbodig** — Mario merkte tijdens het lopen op dat het systeem nooit zo veel rotatie nodig heeft omdat het continu corrigeert, zelfs voor hij de hoek bereikte. Dit is een bevinding die alleen tijdens het werkelijk lopen aan het licht kwam.
- **Hand-aandacht-bottleneck zichtbaar onder realistische condities** — Herman erkende dat het prototype in deze setting werkt, maar waarschuwde dat met een echte stok die de grond aftikt, een stoeprand die gevolgd wordt en omgevingsgeluiden waarop hij vertrouwt, de constante hand-aandacht zou concurreren met al die andere taken. Dit is geen kritiek op het prototype zelf maar een belangrijke nuance voor de doelgroepafbakening.

**Benchmark vergelijking Develop 1 vs Develop 2:**

| Metric | Develop 2 | Develop 1 |
|---|---|---|
| Walking zone width | 60 cm | 60 cm |
| SIZ (% Steps in zone) | **100%** | 97,52% |
| Apprenticeship | Av. 4 min | Av. 4 min |
| Learnability (1–7) | 6,33 | 6,00 |
| Smoothness (1–7) | 5,67 | 4,67 |
| Cognitive load (1–7) | **4,67** | 3,00 |
| Willingness (1–7) | 4,33 | 4,33 |
| Trust (1–7) | n.v.t. | n.v.t. |
| Positioning system | Video + observation | Video + observation |
| Stick used? | No (loose handle) | Yes |
| Context | Interior space Licht en Liefde | Interior space Licht en Liefde |

### Develop 2 design requirements

| ID | Requirement |
|---|---|
| D6.1 | Het kompaselement wordt geplaatst op de laagste gleufpositie (dichtbij de hypothenar) voor optimale tactiele waarneming |
| D6.2 | Het kompaselement gebruikt een sferisch contactoppervlak als standaardgeometrie |
| D6.3 | Het kompaselement heeft een middelhoge uitsteekselhoogte: hoog genoeg om duidelijk voelbaar te zijn, laag genoeg om huidbeknelling of scherpe druk te vermijden |
| D6.4 | Het kompas gedraagt zich met volledige uitwijking naar de doelrichting en koppelt geleidelijk terug naar neutraal naarmate de gebruiker zich oriënteert |
| D6.5 | Het kompas pauzeert kort tijdens een vibratiecue om de figuur-grond scheiding tussen de twee haptische kanalen te bewaren |
| D6.6 | De vibratieset blijft beperkt tot een klein aantal korte, krachtige codes (richtingsaankondiging, buiten-naar-binnen transitie, fallback) |
| D6.7 | De kompasmodule is uitwisselbaar zodat gebruikers kunnen wisselen naar een robuustere variant voor handschoengebruik in koude omstandigheden |
| D6.8 | De handvatdimensies accommoderen het middelste 50% van de doelgroep (ANSUR II, P25–P75) zoals gevalideerd in NX |
| D6.9 | Het systeem voorziet een IMU-gebaseerd fallbacksignaal wanneer de griporiëntatie van de gebruiker de kompas-mapping breekt, gecommuniceerd via een onderscheidend trilpatroon |
| D6.10 | Er worden geen vibratiemotoren geplaatst op individuele vingerposities, om afhankelijkheid van gripvariatie weg te nemen |

### Develop 2 conclusies

- **Eén in-handle vibratiemotor met beperkte codeset** verwijdert de grip-afhankelijkheid die finger-mounted vibratie in Develop 1 brak.
- **Laagste gleufpositie (hypothenar contact)** is de optimale locatie voor het kompaselement, onafhankelijk gevalideerd door alle drie de blinde/slechtziende deelnemers.
- **Sferisch contactoppervlak met middelhoge uitsteekselhoogte** levert de duidelijkste richtingsperceptie zonder oncomfortabel of scherp aan te voelen.
- **Cognitieve belasting daalt met 1,67 punten** op een 7-puntsschaal (van 3,00 naar 4,67), het sterkste bewijs dat ergonomische herontwerpkeuzes direct de mentale belasting verlagen. UG3 (≥4,50) is hiermee gehaald.
- **Continue closed-loop kompasfeedback** (volledige uitwijking naar de doelrichting, geleidelijke terugkoppeling naar neutraal) sluit de Gulf of Evaluation die in Develop 1 de Compare-fase brak.
- **Antropometrische verankering in NX (ANSUR II, P25–P75)** zorgt dat het handvat past bij het middelste 50% van de doelgroep en niet meer afhangt van individuele handgrootte.
- **Bereidheid blijft het open vraagstuk** — Develop 2 bevestigt dat sommige gebruikers (audio-eerst navigators zoals Herman) buiten de kerndoelgroep van SensePath vallen, wat de gebruikerssegmentatie scherper maakt voor Develop 3.
- **Een uitwisselbare kompasmodule** is de logische volgende stap, met ruimte voor persoonlijke voorkeur en een robuuste wintervariant voor handschoengebruik.

### Kritische reflectie Develop 2

De Develop 2-resultaten zijn op zich positief, maar er moeten een aantal eerlijke nuances bij geplaatst worden.

Ten eerste was de **sample beperkt**. Met N=3 blinde/slechtziende deelnemers (Mario, Herman, Rory) en N=2 ziende controles is de statistische zeggingskracht klein. De convergentie tussen Mario en Herman op de voorkeursgleufpositie en het voorkeurselement is op zich sterk, maar moet in Develop 3 met een grotere groep bevestigd worden.

Ten tweede is de **stok bewust weggelaten** in deze testopzet. De focus lag puur op de ergonomie van het handvat zelf, om te vermijden dat de stok-feedback de evaluatie van het handvat zou vertroebelen. Dit is methodisch verdedigbaar voor deze fase, maar betekent ook dat de gecombineerde belasting van stok + handvat + omgevingsperceptie pas in Develop 3 echt getest kan worden. Herman wees daar zelf op tijdens het interview, en die opmerking weegt zwaar omdat zij precies aangeeft waar de praktijksituatie afwijkt van de testomgeving.

Ten derde werd de **elektronica niet empirisch gevalideerd**. De drie nieuwe ontwerpelementen die uit de cognitieve ergonomie-analyse kwamen (de twee signifiers voor moduswisseling en systeemonzekerheid, en de IMU-fallback voor gripverandering) konden niet gedemonstreerd worden omdat het handvat in deze fase nog geen geïntegreerde elektronica had. Deze zaken werden verbaal aan de deelnemers voorgelegd en positief ontvangen, maar dat is geen empirische validatie. Develop 3 zal deze concepten met geïntegreerde hardware moeten testen.

Ten vierde was **Test 2 minder gestructureerd dan oorspronkelijk gepland**. De vijf varianten van het kompaselement werden niet allemaal in dezelfde volgorde aan elke deelnemer voorgelegd, en de schuin afgeronde overgangsvorm (C5) ontstond pas tijdens de eerste sessie met Mario en werd daarna meegenomen bij Herman. Dit is enerzijds een teken van iteratief ontwerpen in actie, maar anderzijds een methodische zwakte voor de directe vergelijkbaarheid tussen deelnemers.

Ten vijfde verdient **Herman's lage willingness-score (2/7)** een aparte kanttekening. Zijn lage score komt niet voort uit een tekortkoming van het prototype, maar uit zijn persoonlijke voorkeur voor audio-navigatie en zijn jarenlange ervaring met echolocalisatie. Dit zegt iets over de doelgroepafbakening van SensePath, niet over de kwaliteit van de huidige iteratie. Voor Develop 3 betekent dit dat de kerngebruiker scherper gedefinieerd moet worden: SensePath richt zich op gebruikers die haptische feedback prefereren boven audio en die hun gehoor willen vrijhouden voor omgevingswaarneming.

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
