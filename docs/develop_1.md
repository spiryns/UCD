# SensePath → Develop 1

[← Terug naar hoofdpagina](../README.md)

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
  <img src="../img/ChatGPT Image 19 feb 2026, 20_31_14.png" alt="User flow SensePath" width="800"/>
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
  <img src="../img/PGGO - SensePath - User flow.jpg" alt="User flow SensePath" width="800"/>
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
  <img src="../img/PGGO - SensePath - HPI - Productarchitectuur (I_O).jpg" alt="Productarchitectuur I/O diagram" width="800"/>
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
  <img src="../img/PGGO - SensePath - Morfologische matrix.jpg" alt="Morfologische matrix met functionele deelaspecten en oplossingsvarianten" width="800"/>
  <br/><em>Morfologische matrix → de deelfuncties (input, feedback, montage, voeding) en hun varianten waaruit het Develop 1 ontwerp gecombineerd is.</em>
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
  <img src="../img/WhatsApp Image 2026-03-08 at 19.57.35 (1).jpeg" alt="Develop 1 prototype: trilmotor-handvat (afslagcue)" width="200"/>
  <img src="../img/WhatsApp Image 2026-03-08 at 19.57.35.jpeg" alt="Develop 1 prototype: kompas-handvat met draaiend bolletje" width="200"/>
  <img src="../img/WhatsApp Image 2026-03-08 at 19.57.34 (1).jpeg" alt="Develop 1 prototype: ESP32-controller en bedrading van trilmotoren" width="200"/>
  <img src="../img/WhatsApp Image 2026-03-08 at 19.57.34.jpeg" alt="Develop 1 prototype: testopstelling met handvat aan witte stok" width="200"/>
  <br/><em>Develop 1 prototypes (N=5) → Prototype 1 (vibratie-afslagcue) en Prototype 2 (continu kompas). Beide via Wizard-of-Oz aangestuurd.</em>
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
- **Grip bepaalt interpretatie**: Verschillende grip = links/rechts omgekeerd. Handoriëntatie is cruciaal.
- **Palmsensatie is zwak**: Meerdere deelnemers voelden het bolletje nauwelijks.
- **Ergonomie onvoldoende**: Handvat past niet bij elke hand. Bolletje is verkeerd gepositioneerd.
- **Rechtdoor lopen werkt**: Goede resultaten bij rechtdoor; bochten zijn moeilijker.
- **Winter = probleem**: Handschoenen en dikke jassen blokkeren de sensatie.

**Benchmark vergelijking Test 1:**

| Metric | Tactile Compass (Liu et al.) | SensePath |
|---|---|---|
| SIZ (% stappen in zone) | 92,6% | 83,78% |
| Leerbaarheid (1-7) | 6,67 | 5,67 |
| Soepelheid (1-7) | 6,06 | 5,50 |
| Cognitieve belasting (1-7) | 5,22 | 3,67 |
| Bereidheid (1-7) | 6,39 | 5,33 |
| Vertrouwen (1-7) | n.v.t. | 5,33 |

### Test 2: Afslag via trilsignaal

De wizard stuurt trilsignalen op het juiste moment via de controller-app.

> *"Die trilmotoren, dat ging wel goed."*
> *"Het voelde beter, minder concentreren dan het balletje."*

**Key findings:**
- **Vingertoppen voelen het best**: "Daar zitten de voelers."
- **Afslaan werkt goed**: Richtingssignalen worden snel begrepen en aangeleerd.
- **Rechtdoor is moeilijker**: Zonder continu signaal drijven gebruikers af.
- **Bevestigingssignaal nodig**: Gebruikers willen feedback dat ze rechtdoor lopen.
- **Niet te veel signalen**: "Begin niet met zevenhonderdachtendertig verschillende signalen."
- **Sensorpositie problematisch**: Links past goed = rechts past slecht, en omgekeerd. Handgrootte speelt een rol.

**Benchmark vergelijking Test 2:**

| Metric | Tactile Compass (Liu et al.) | SensePath |
|---|---|---|
| SIZ (% stappen in zone) | 92,6% | 79,85% |
| Leerbaarheid (1-7) | 6,67 | 6,50 |
| Soepelheid (1-7) | 6,06 | 6,33 |
| Cognitieve belasting (1-7) | 5,22 | 4,67 |
| Bereidheid (1-7) | 6,39 | 6,33 |
| Vertrouwen (1-7) | n.v.t. | 6,00 |

### Test 3: Gecombineerd parcours

Kompas (continue koersfeedback) + vibratie (afslagcue) samen op hetzelfde parcours.

> *"Ik ben wel onder indruk van deze keer."*
> *"Het was beter dan ik had verwacht."*

**Key findings:**
- **Vibratie interfereert met kompas**: Twee systemen tegelijk aflezen op één hand is moeilijk.
- **Ergonomie is de bottleneck**: Huidig prototype laat geen eerlijke evaluatie toe.
- **Concept heeft potentieel**: Vibratie als aankondiging + kompas voor koerscorrectie is logisch.
- **Hogere cognitieve belasting**: Scores dalen vergeleken met individuele tests.
- **Herpositionering bolletje**: Suggestie: naar de knokkels of hiel van de hand i.p.v. de palm.
- **Audio als back-up**: Speaker/bluetooth voor wanneer vibraties niet waarneembaar zijn.

**Benchmark vergelijking Test 3:**

| Metric | Tactile Compass (Liu et al.) | SensePath |
|---|---|---|
| SIZ (% stappen in zone) | 92,6% | **97,52%** |
| Leerbaarheid (1-7) | 6,67 | 6,00 |
| Soepelheid (1-7) | 6,06 | 4,67 |
| Cognitieve belasting (1-7) | 5,22 | 3,00 |
| Bereidheid (1-7) | 6,39 | 4,33 |
| Vertrouwen (1-7) | n.v.t. | 3,00 |

### Develop 1 conclusies

- **Vibratie is intuïtiever** dan kompas voor discrete navigatie-events (afslagen).
- **Kompas biedt superieure koersbewaking** maar lijdt onder perceptuele ambiguïteit.
- De **gecombineerde conditie scoorde het hoogst op nauwkeurigheid** (97,52% SIZ) maar het laagst op subjectieve ervaring.
- **Ergonomie is geen bijzaak**; het is de primaire confound in de data.
- SensePath houdt stand tegen de **Tactile Compass benchmark** onder moeilijkere condities (met stok, video-observatie i.p.v. OptiTrack, Wizard-of-Oz i.p.v. automatisch).
- **90% van alle fouten** is te wijten aan wizard-timing; bij automatisering worden minder fouten verwacht.
- Gebruikers memoriseren onbewust het pad over de drie tests heen, wat een confound vormt voor de SIZ-scores.

### Kritische reflectie Develop 1

De drie test-runs leverden zowel signaal als ruis op, en de scheidslijn ertussen bepaalt welke conclusies dragend zijn voor het verdere ontwerp.

Het sterkste signaal is de **convergentie tussen test 1 en test 2 op snellere foutcorrectie**: dat patroon bevestigt onze hypothese dat de gebruiker via herhaalde blootstelling een mentaal model opbouwt van de feedbacktaal. Implicatie voor Develop 2: de leerfase moet expliciet in de UX zitten (oefenmodus, kalibratie), niet impliciet via gebruik.

De **convergentie over test 1, 2 en 3 op path learning** is daarentegen een confound dat onze meetstrategie ondermijnt: deelnemers onthouden het parcours onbewust, waardoor SIZ-scores na test 2 niet meer de feedback meten maar het geheugen. Implicatie: Develop 2 en 3 moeten ofwel met verschillende parcours werken, ofwel het leereffect expliciet rapporteren.

Het meest design-kritische inzicht is dat **90% van de fouten herleidbaar is tot wizard-timing**, niet tot gebruikersgedrag. Dat betekent dat het huidige fout-percentage geen ondergrens is van wat het systeem kan, maar een bovengrens van wat Wizard-of-Oz kan meten. Implicatie: voor de finale validatie hebben we een geautomatiseerd systeem nodig dat dezelfde test reproduceerbaar uitvoert ; deze open vraag draagt door naar de [Deliver](deliver.md)-fase.

Tot slot beïnvloedt **de testomgeving de cognitieve belasting** in een mate die we niet vooraf controleerden. Implicatie voor Develop 2: omgevingscontext meenemen als variabele in de test-opzet, niet als ruis.

---

[← Terug naar hoofdpagina](../README.md) · [Volgende fase → Develop 2](develop_2.md)
