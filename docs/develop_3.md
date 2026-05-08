# Develop 3 — UX & Service Design (SensePath)

Dit document legt de concrete UX- en Service Design-beslissingen voor SensePath vast. Alle keuzes verwijzen expliciet naar het huidige prototype uit Develop 2: kunststof handvat met **hypothenar-kompasgleuf (H1–H5)**, één **in-handle vibratiemotor**, **IMU-gestuurde gripkalibratie**, **clip op bestaande witte stok**, gekoppelde **iOS-app**, en een **fail-safe herstart-flow**.

Visuele uitwerkingen:
- [Overkoepelende visuele weergave (HTML)](develop_3.html)
- [Stakeholder map (HTML)](develop_3/stakeholder_map.html)
- [Customer Journey Map (HTML)](develop_3/customer_journey.html)
- [Service Blueprint (HTML)](develop_3/service_blueprint.html)

---

## 1. Emotie-matrix — wat we concreet doen in SensePath

Vier primaire emoties en vier anti-emoties. Per emotie: de concrete ontwerpingreep in het huidige prototype, en de onderbouwing (cursus-theorie + Discovery-quote).

### Primaire emoties

| Emotie | Concrete ingreep in SensePath | Onderbouwing |
|---|---|---|
| **Kalmte** | Default-toestand = *stilte*. Geen "alles-goed"-puls; correcte koers wordt niet bevestigd. Kompas-ticks alleen bij richtingcorrectie. Fade-in van elke trilling over 80 ms (geen abrupte aanzet). | Cursus *Attention* §3.2: aandacht is eindig — elk extra signaal kost cognitieve resources. Discovery-quote: *"in een station wil je niet overprikkeld worden, je bent al aan het zoeken met je oren"*. |
| **Vertrouwen** | **Confidence-puls**: voor elke afslag-crescendo geeft het systeem eerst een *heartbeat-pattern* (2 zachte pulsen @ 150 Hz) dat zegt "ik weet waar je bent". Als IMU-confidence < 70 %, valt de heartbeat weg — de gebruiker voelt meteen dat het systeem twijfelt. | Walter's piramide (*reliable* vóór *pleasurable*). Gulf of Evaluation (Norman): eerlijke status-communicatie > valse geruststelling. |
| **Autonomie** | **Manual-override gesture**: dubbele tap op het handvat ⇒ systeem wacht 5 s en geeft controle terug (gebruiker mag zelf beslissen, systeem niet dominant). Alle app-taal in de tweede persoon, nooit imperatief: *"wil je linksaf?"* i.p.v. *"ga links"*. | Martiniello et al. (2020): *user empowerment* en *symbolic meaning of autonomy* zijn top-2 stigma-verminderaars. Eyal: **self-reward** (mastery) versterkt retention. |
| **Discretie** | Handvat-kleur in **antraciet mat** met één donkergrijs accent (geen "medische wit"). Geen LED's naar buiten zichtbaar. Geen audio-output op het handvat zelf; speech enkel via de telefoon-oortje-koppeling (bone conduction optioneel). Trillingen < 200 Hz en < 80 dB geluidslek. | Martiniello et al.: *visual analogy* (lijkt op mainstream tech) vermindert stigma. Discovery: *"ik wil niet dat mensen me aanstaren"*. |

### Anti-emoties

| Anti-emotie | Concrete vermijding | Onderbouwing |
|---|---|---|
| **Paniek** | Crescendo voor bocht start **5 m voor keuzepunt** met puls @ 1 Hz, groeit lineair naar 3 Hz op 1 m. Geen exponentiële versnelling, geen volumestijging. Maximale continue intensiteit gecapt op 60 % van motor-peak. | Cursus *Cognition* §3.2 *switching costs*: abrupte alerts dwingen reflective cognitie en verhogen foutkans. |
| **Infantilisering** | Geen "goed gedaan"-toon. App-stem is neutraal-volwassen (lage spraaksnelheid, geen jingles). Succesbevestiging = *warme lange puls* (500 ms fade-out), niet *"perfect!"*. Geen streaks, badges of "bestemmingen deze week"-metrics tenzij expliciet opgevraagd. | Cursus *Behavioral Design*: dark-pattern-risico bij persuasive design. Discovery: *"ik ben geen kind"*. |
| **Medicaliteit** | Materiaal: **glasvezelversterkt PA12** met soft-touch TPU-overmold — geen ABS-glans. Form-taal verwijst naar **outdoor / reizen** (vergelijk fietscomputer, hardloop-clip), niet naar ziekenhuisinstrument. Geen kruis-, plus- of medische pictogrammen. Verpakking in geperst karton, geen blisterverpakking. | Martiniello et al.: *visual analogy* met mainstream tech. Vaes (2014): *perceived stigma* volgt direct uit CMF-signalen. |
| **Faalgevoel** | Bij IMU-verlies heet het **"heroriënteren"**, niet "fout" of "signaal verloren". Fail-safe flow begint met een zachte ademende puls (0,5 Hz, 3 cycli) vóór eender welke instructie — geeft de gebruiker denktijd. App-tekst: *"we pakken dit samen op"*, niet *"er ging iets mis"*. | Cursus *Cognition* §3.1: attribution matters — de user-fout-attributie moet vermeden worden. Cognitive dissonance (Eyal): negatief gelabeld event verlaagt retention sterker dan neutraal event. |

---

## 2. Norman's drie lagen — concreet per laag voor SensePath

### 2.1 Visceral laag (eerste 3 seconden, non-visueel)

Wat de gebruiker voor het eerst voelt/hoort:

| Kanaal | Concrete spec | Waarom zo |
|---|---|---|
| **Gewicht** | 58–62 g (handvat + clip samen). P50-handvolwassene verwacht "telefoon-achtig compact". | Te licht (< 45 g) → *goedkoop gadget*; te zwaar (> 80 g) → belast de stokzwaai, Develop 1-feedback. |
| **Eerste tast-textuur** | Soft-touch TPU-overmold, shore 70A, matige micro-textuur (Ra 3–4 μm). | Cursus *Human Senses* §11.2: matte rubberized grip → "controle/comfort". Hard-glans = "cheap/slippery". |
| **Temperatuur aanvoelen** | Materiaalkeuze PA12 + TPU = lage warmtegeleiding → voelt **warmer** dan metaal bij eerste aanraking. | Koud metaal = "klinisch/instrument"; warm polymeer = "persoonlijk object". |
| **Clip-bevestiging** | Magnetische pre-alignering + mechanische *click* bij vergrendeling, hoorbaar **circa 45–55 dB** met lichte lage resonantie (2 kHz gedempt). | Intentional sound (cursus §11.3). Moet herkenbaar en kort zijn (< 80 ms), bevestigt installatie zonder app-check. |
| **Unbox-ritueel** | Magneetsluiting doos, reliëfletters "SENSEPATH" op deksel, katoenen linnen binnenhoes. Geen plastic folie, geen twist-ties. | Aanraakbaar = leesbaar voor blinde gebruiker. Premium-tactiel ≠ medisch. |

### 2.2 Behavioral laag (tijdens gebruik)

Dit is de Develop 2-laag, nu verfijnd via microinteractions — zie §3.

**Sleutelbeslissing die nu vastligt**: correcte-koers-toestand = **stilte** (niet een continue baseline-puls zoals overwogen in Develop 1). Dit bespaart 40 % motor-duty-cycle (batterij), vermindert habituation, en maakt event-signalen maximaal salient.

### 2.3 Reflective laag (zelfbeeld, verhaal)

| Reflectief doel | Concrete ingreep |
|---|---|
| "Ik ben iemand die moderne tools gebruikt voor mijn autonomie" | App noemt het product *"SensePath"*, niet *"navigatie-hulpmiddel"*. Mutualiteit-documentatie gebruikt de term **"mobility enhancer"**. |
| "Dit is gift-worthy" | Doos + handleiding in 3 talen, premium karton, QR-code-activatie via blindenvereniging geeft 6 maanden POI-premium — maakt het gift-ready zonder stigma. |
| "Ik deel dit met anderen zoals ik" | **Opt-in route-deling** met trainer of peer (via app). Geen publieke feed, geen likes — enkel 1-op-1 deling, waardig. |
| "Ik hou de controle" | Firmware-updates zijn **opt-in**, niet forced. Ruwe routedata staat lokaal, niet standaard in de cloud (GDPR + symbolische autonomie). |

---

## 3. Microinteractions — concrete specs (Saffer: trigger / rules / feedback / loops & modes)

Alle patronen gebruiken de **in-handle LRA-motor** (lineaire resonantie-actuator, 170–230 Hz) en het **IMU-gestuurde kompaselement** in de H1–H5 gleuf. Intensiteit uitgedrukt als percentage van motor-peak (PWM-duty).

### 3.1 Tabel microinteractions

| # | Moment | Trigger | Regels | Feedback (wat de gebruiker voelt/hoort) | Loops & modes |
|---|---|---|---|---|---|
| M1 | **Route gestart** | App "Start route" bevestigd | Alleen als Bluetooth-link stabiel én IMU-kalibratie < 2 min geleden | 2 zachte pulsen LRA @ 180 Hz, 120 ms, 40 % int., interval 200 ms. Fade-in 80 ms. | Eén keer; geen loop. |
| M2 | **Confidence-heartbeat** (nieuw) | IMU + routepositie-confidence > 70 % | Elke 45 s in correcte-koers-toestand | 2 pulsen @ 150 Hz, 60 ms, 25 % int., interval 250 ms | Loop elke 45 s; stopt zodra confidence < 70 %. Mode: *ambient reassurance*. |
| M3 | **Correcte koers** | Default | Geen actieve feedback buiten M2 | **Stilte** (behalve heartbeat M2) | N/A. |
| M4 | **Bocht nadert** | Afstand tot keuzepunt = 5 m | Alleen 1× per keuzepunt | Crescendo: 5 pulsen @ 180 Hz, 100 ms elk, interval lineair van 1000 ms → 300 ms. Int. van 35 % → 60 %. Kompas tegelijk activeert richting (links/rechts) op hypothenar. | Start op 5 m, eindigt op 1 m. |
| M5 | **Bocht correct genomen** | IMU detecteert rotatie binnen 15° van verwacht pad binnen 3 s na M4 | Alleen na succesvolle M4 | Dubbele "tick": 2 pulsen @ 200 Hz, 40 ms, 50 % int., interval 80 ms | Eenmalig. Mode: *succesbevestiging* (zelfde patroon ook bij bestemming, kortere variant). |
| M6 | **Afwijking van route** | Off-path > 2 m gedurende > 4 s | Hysterese: moet 4 s aanhouden voor trigger | Ademende puls: 3 cycli @ 0,5 Hz, int. swing 15 % → 40 %. Kompas wijst naar dichtstbijzijnde ankerpunt. | Loop tot gebruiker terug < 1 m. |
| M7 | **Fail-safe actief** (IMU-verlies / GPS-gat / confidence < 40 %) | Systeem-onzekerheid | Onmiddellijk; overschrijft M2–M6 | Lange zachte trilling 800 ms @ 120 Hz, 30 % int., gevolgd door 1,5 s stilte. Optioneel (app-setting) korte spraak via oortje: *"heroriënteer, hou je stok stil"*. | Loop tot IMU-heroriëntatie bevestigd. Mode: *pause* — geen andere cues. |
| M8 | **Bestemming bereikt** | GPS/beacon-match + user-geometrie stabiel 3 s | Alleen op routeafsluiting | Warme lange puls: 1 puls @ 160 Hz, 600 ms, fade-in 200 ms, peak 70 %, fade-out 300 ms | Eenmalig. Zelfde patroon wordt "brand signature". |
| M9 | **Batterij low** (< 15 %) | Interval-contingent | Elke 10 min tot opgeladen | Drie korte ticks @ 220 Hz, 30 ms, 20 % int., interval 300 ms. Afwijkend hoog-frequent patroon ⇒ herkenbaar als "systeem-status", niet "route". | Loop elke 10 min. |
| M10 | **Clip-bevestiging op stok** | Mechanisch contact + IMU detecteert stok-orientatie | Bij fysieke installatie | Geen motor-feedback; enkel de mechanische *click* (intentional sound). App geeft audio-bevestiging *"klaar om te starten"*. | Eenmalig per sessie. |

### 3.2 Signature moments (de "herinnerbare" interacties)

Twee patronen zijn doelbewust uniek om *brand recognition* op te bouwen:
- **M8 — warme lange puls bij aankomst**: enige 600 ms-puls in het hele systeem.
- **M4 — crescendo voor bocht**: enige crescendo-patroon; alle andere events zijn statisch of pulserend.

### 3.3 Mapping emoties ⇄ microinteractions

- Kalmte → M3 (stilte) + M6 (ademend, laag-frequent).
- Vertrouwen → M2 (heartbeat) + M7 (eerlijk fail-safe).
- Autonomie → ontbreken van "push"-patroon buiten keuzepunten + dubbele-tap-override.
- Discretie → max 60 % intensiteit, geen audio uit handvat, LRA < 230 Hz (minder hoorbaar lek).

---

## 4. Stakeholder map

Vijf concentrische ringen, van kerngebruiker naar platform. Zie [develop_3/stakeholder_map.html](develop_3/stakeholder_map.html) voor de interactieve versie.

**Sleutelinzicht**: ring 3–4 (infrastructuur + institutioneel) levert ~40 % van de *value delivery* maar heeft nul fysiek contact met de gebruiker. Dit is de harde PSS-test: de service moet werken zonder dat de gebruiker die backstage-actoren ooit ontmoet.

---

## 5. Customer Journey Map

Vijf fases × vier rijen (touchpoints, actions, emotie-curve, pains/opportunities). Drie expliciete Moments of Truth gemarkeerd. Zie [develop_3/customer_journey.html](develop_3/customer_journey.html).

**Moments of Truth voor SensePath:**
- **MoT-1**: eerste 30 s na unboxing — visceral laag beslist over doorzetten of terugsturen.
- **MoT-2**: eerste fail-safe in publieke context — reflective laag beslist over vertrouwen op lange termijn.
- **MoT-3**: eerste keer zelfstandig routeafsluiting zonder hulp — autonomie-emotie wordt bevestigd of ondermijnd.

---

## 6. Service Blueprint

Vijf rijen × vier fases, met expliciete *line of interaction*, *line of visibility* en *line of internal interaction*. Zie [develop_3/service_blueprint.html](develop_3/service_blueprint.html).

**Kritieke afhankelijkheden die zichtbaar worden:**
- Zonder gebouwbeheerder-POI-data (backstage) werkt indoor wayfinding niet → noodzaak van B2G-model.
- Zonder mobiliteitstrainer-netwerk (frontstage) geen schaalbare onboarding → partnership met revalidatiecentra.
- Firmware- en mapping-updates zijn invisible maar bepalen lange-termijn vertrouwen.

---

## 7. Bronnen

Cursus: [IxD/Usability/UX](../Project%20theorie/SV_GO_IxD_Usability_UX_DesignPrinciples.md) · [Cognition](../Project%20theorie/SV_GO_Cognition.md) · [Human Senses & Interfaces](../Project%20theorie/SV_GO_HumanSenses&Interfaces.md) · [Social Interaction & Behaviour](../Project%20theorie/SV_GO_SocialInteraction&Behaviour.md) · [Evaluation Methods](../Project%20theorie/SV_GO_EvaluationMethods.md).

Extern: Norman *Emotional Design* (2004); Saffer *Microinteractions* (2013); Shostack (1984) *Service Blueprint*; Martiniello et al. (2020) *Aesthetics and perceived stigma of AT for visual impairment*; Eyal *Hooked* (2014); Fogg *Behavior Model*.
