# SensePath
Ear free, intuitive navigation indoors

🛠️ Built by Sam Piryns, Titus Impens, Han Deburchgraeve 
🔥 Supervised by ``prof. dr. Bas Baccarne``, ``Yannick Christiaens`` & ``Wouter Devriese``    
🌱 Grown at ``Ghent University`` 🏛️ ``Industrial Design Engineering`` ([project overview](https://github.com/basbaccarne/human-centered-design))       

*Dag/Maand/Jaar van de laatste update*   

Mensen die blind of slechtziend zijn kunnen buiten relatief goed navigeren met GPS, maar in grote publieke gebouwen (stations, ziekenhuizen, campussen) valt die ondersteuning vaak weg. Vooral op kruispunten, splitsingen en bij tijdelijke omleidingen leidt dit tot twijfel, extra mentale belasting en afhankelijkheid van hulp van anderen.

We onderzochten dit via deskresearch en benchmarking van bestaande (indoor) navigatieoplossingen, en via user interviews en feedbackmomenten met gebruikers en organisaties uit de blinden- en mobiliteitswereld. Daaruit kwamen duidelijke noden naar voren: betrouwbare “decision support” op keuzemomenten, zo weinig mogelijk telefoongebruik tijdens het stappen, en discrete feedback die ook in publieke context bruikbaar is.

Onze oplossing is SensePath: een slimme handgreep die op een bestaande lange witte stok wordt bevestigd en gekoppeld is aan een eenvoudige app-workflow. SensePath vertaalt route-informatie naar haptische begeleiding op het juiste moment (bv. bij keuzes en bochten), zodat de gebruiker “hands-free, heads-up” kan blijven bewegen met de stok als primair hulpmiddel. Optioneel biedt het systeem een fail-safe flow om te herstarten of hulp te vragen bij afwijkingen of blokkades. Zo maakt SensePath indoor navigatie zelfstandiger, rustiger en betrouwbaarder.
- Hero sketch/render/image, vb.
<p align="center">
  <img src="img/hero_example.png" width="100%">
</p>

## Introductie
Navigeren is voor blinde en slechtziende personen niet enkel “de weg vinden”, maar ook continu beslissingen nemen op basis van beperkte informatie: waar is de ingang, welke gang is juist, waar bevindt de lift, en wanneer moet je handelen aan een kruispunt. In grote publieke gebouwen wordt dit extra moeilijk omdat herkenningspunten minder consistent zijn, routes vaak veranderen door tijdelijke werken en omdat klassieke GPS-navigatie binnenshuis onvoldoende betrouwbaar is. In onze interviews benoemden gebruikers vooral onzekerheid op keuzemomenten en de mentale belasting van voortdurend moeten verifiëren of men nog “goed zit”, vaak met afhankelijkheid van hulp van anderen als gevolg (User Interviews, 2025).

Het doel van dit project is het ontwikkelen van een onderbouwd concept: een slimme handgreep die op een bestaande lange witte stok wordt geplaatst en indoor begeleiding mogelijk maakt via discrete feedback, met de witte stok als primair mobiliteitshulpmiddel. Om dit concept te definiëren combineren we deskresearch en benchmarking van bestaande navigatie- en mobiliteitsoplossingen met gebruikersonderzoek (interviews en iteratieve concepttesten), zodat ontwerpkeuzes expliciet voortkomen uit gebruikersnoden en realistische contexten (Benchmarking, 2025; User Interviews, 2025).

Binnen het eerste semester ligt de focus op concept testing en op het doorlopen van sequentiële iteraties waarin prototypes worden getest, inzichten geanalyseerd en vertaald naar design requirements en een bijgewerkte PRD. Boundary conditions voor deze fase zijn: (1) de oplossing moet compact blijven (geen bulky wearables), (2) zo weinig mogelijk actieve smartphone-interactie tijdens het stappen, (3) toepasbaarheid op 2D-navigatie per verdieping, en (4) een duidelijke fail-safe workflow voor afwijkingen of blokkades (Benchmarking, 2025; User Interviews, 2025).

## Inhoudstafel

1. [Methodologie](./docs/methodologie.md)
2. [Discovery](./docs/discovery.md)
3. [Defintion](./docs/definition.md)
4. [Design Requirements](./docs/design_requirements.md)
5. [Bill of materials](./docs/bom.md)
## Discovery
## Definition
### Doelstellingen
Het doel van de definition-fase is om een diepgaand inzicht te krijgen in de noden, verwachtingen en mentale modellen van blinde en slechtziende gebruikers tijdens navigatie, en deze inzichten te vertalen naar een onderbouwd concept voor SensePath.

Concreet wil deze fase:

- inzicht krijgen in hoe gebruikers zich vandaag verplaatsen en welke rol technologie hierin mag spelen;

- verschillende haptische en fysieke concepten uittesten en onderling vergelijken;

- bepalen welke functies en feedbackvormen als logisch, betrouwbaar en aanvaardbaar worden ervaren;

- de belangrijkste design requirements definiëren die richting geven aan verdere ontwikkeling.

### Materiaal & methoden
#### Wave 1 – Concept testing in een gecontroleerde omgeving

In Wave 1 werd vertrokken vanuit een eerste conceptueel kader voor SensePath: een slimme, afneembare handgreep voor de witte stok die via haptische feedback ondersteuning biedt bij navigatie.

De sessies vonden plaats in een gecontroleerde omgeving en hadden een exploratief karakter. Het doel was niet om oplossingen te valideren, maar om mogelijke richtingen te openen.

Vanuit dit kader werden volgende onderzoeksvragen geformuleerd:

- Welke rol mag technologie spelen tijdens het stappen?

- Welke vormen van haptische feedback worden spontaan begrepen?

- In welke mate mag een hulpmiddel afwijken van bestaande stokgebruik-routines?

- Welke conceptuele drager (handvat vs. volledige stok) wordt aanvaard?

Om deze vragen te onderzoeken, werden low-fidelity prototypes ontwikkeld die verschillende haptische principes representeerden:

- mechanische feedback;

- vibratie;

- bewegingsgebaseerde feedback;

- tactiele patronen.

Deze prototypes werden manueel aangestuurd (Wizard-of-Oz) zodat gebruikers de ervaring konden beoordelen zonder technische beperkingen.

👉 Hier een foto plaatsen van de haptische prototypes uit Wave 1

De prototypes werden getest via semigestructureerde interviews en think-aloud tests met ervaren gebruikers van de witte stok (n = 5). De focus lag op interpretatie, comfort, vertrouwen en mentale belasting.

De inzichten uit deze sessies vormden de basis voor een eerste set richtinggevende design requirements.

#### Wave 2 – Gerichte prototype-testing (verdieping)

In Wave 2 werd voortgebouwd op de inzichten uit Wave 1. Op basis van duidelijke voorkeuren en afwijzingen werd het aantal concepten bewust beperkt.

De focus van Wave 2 lag op:

- verfijning van geselecteerde haptische principes;

- evaluatie van de fysieke integratie van technologie in relatie tot de witte stok;

- het testen van stabiliteit, ergonomie en vertrouwen.

De onderzoeksvragen voor deze fase waren onder andere:

- Hoe ervaren gebruikers de fysieke bevestiging van een extra component op hun stok?

- Welke haptische feedback blijft begrijpelijk en comfortabel tijdens langere interactie?

- Wanneer voelt een oplossing aan als een logisch onderdeel van de stok, en wanneer als storend?

Voor deze fase werden nieuwe prototypes ontwikkeld:

- fitting-prototypes met verschillende klemmechanismes;

- haptische prototypes met verfijnde bewegings- en vibratiefeedback.

👉 Hier een foto plaatsen van de fitting-prototypes (Wave 2)
👉 Hier een foto plaatsen van de haptische prototypes (Wave 2)

Dezelfde respondenten als in Wave 1 (n = 5) namen deel aan deze fase, zodat evoluties in mening en voorkeur konden worden opgevolgd. De sessies combineerden unguided interactie, guided simulatie en reflectie.

### Resultaten
#### Wave 1

Uit de eerste testfase kwamen een aantal duidelijke patronen naar voren.

Alle respondenten gaven aan sterk gehecht te zijn aan hun bestaande witte stok. Het idee van een volledige slimme stok werd vrijwel unaniem afgewezen. Een afneembaar handvat werd daarentegen als een realistische en aanvaardbare oplossing gezien.

Auditieve feedback werd door de meeste gebruikers als storend ervaren, aangezien gehoor cruciaal is tijdens navigatie. Haptische feedback werd consequent verkozen als primaire informatiedrager.

Niet alle haptiek werd echter gelijk beoordeeld. Mechanische en bewegingsgebaseerde feedback werd spontaan en correct geïnterpreteerd, terwijl meer abstracte of symbolische vormen (zoals patronen of braille-achtige signalen) als te complex werden ervaren tijdens het stappen.

Daarnaast bleek vertrouwen een cruciale factor: zelfs kleine vormen van instabiliteit of onduidelijkheid leiden tot onmiddellijke afwijzing van een concept.

#### Wave 2

In Wave 2 konden gebruikers explicieter vergelijken en verdiepen.

Wat betreft de fitting-prototypes werd duidelijk dat stabiliteit en het gevoel van “één geheel” met de stok essentieel zijn. Oplossingen die eenvoudig te monteren waren maar enige speling vertoonden, werden negatief beoordeeld. Gebruikers gaven aan liever iets meer moeite te doen bij montage dan onzekerheid te ervaren tijdens gebruik.

Bij de haptische prototypes werd opnieuw bevestigd dat beweging een zeer sterke informatiedrager is. Continue, rustige bewegingsfeedback werd als geruststellend en betrouwbaar ervaren. Vibratie werd enkel aanvaard als aanvullende feedback, bijvoorbeeld ter bevestiging.

Gebruikers benadrukten dat technologie hen moet ondersteunen op beslissingsmomenten, maar nooit de controle mag overnemen.

### Conclusies & implicaties

Op basis van Wave 1 en Wave 2 kan worden geconcludeerd dat SensePath het meeste potentieel heeft als:

- een afneembaar, modulair handvat dat compatibel is met meerdere witte stokken;

- een hulpmiddel dat haptische feedback als primaire informatiedrager gebruikt;

- een systeem dat inzet op rustige, intuïtieve beweging in plaats van complexe signalen;

- een oplossing die bestaande routines respecteert en minimale extra handelingen vereist.

Gebruikers verwachten eerst en vooral betrouwbaarheid, controle en mentale rust. Extra functies zijn enkel waardevol wanneer ze deze basis versterken.

Deze conclusies vormen de basis voor verdere ontwikkeling in volgende fases, waarin de focus zal verschuiven naar verfijning, realistischere contexten en mogelijke technische implementatie.
> [!IMPORTANT]
> Design Requirements:
> - D1.1 SensePath wordt ontworpen als **volledige slimme stok** (geen universeel afneembaar handvat)
> - D1.2 De stok moet beschikbaar zijn in **meerdere lengtes**
> - D1.3 De gebruiker moet **kunnen switchen tussen lengtes** (modulair systeem)
> - D1.4 De lengte-verbinding(en) moeten **mechanisch stabiel** zijn (geen speling/rotatie)
> - D2.1 Haptische feedback moet de **primaire informatiedrager** zijn (boven audio)
> - D2.2 Richtinginformatie moet **intuïtief** zijn (geen codes/patronen die je moet aanleren)
> - D2.3 Bewegingsgebaseerde haptiek (links/rechts, voor/achter) moet **duidelijk en consistent** aanvoelen
> - D2.4 Vibratie mag enkel dienen als **secundaire feedback** (bevestiging/waarschuwing), niet continu
> - D3.1 De gebruiker moet **controle behouden** (duidelijk start/stop; geen onverwachte automatische acties)
> - D3.2 Interactie tijdens het stappen moet **minimaal** blijven
> - D3.3 De smartphone mag enkel een **ondersteunende rol** hebben (instellen/starten), niet als constante interface
> - D4.1 Het systeem mag het **normale stokgebruik niet verstoren** (gewicht, balans, grip)
> - D4.2 Het systeem moet **betrouwbaar en voorspelbaar** aanvoelen in dagelijks gebruik

## Kritische reflectie
Max. 500 woorden

## Noot inzake het gebruik van AI
Licht toe op welke manier je AI gebruikte in dit project.

## Bijlagen
### Discovery
* Literatuuronderzoek (N=x)
  * [Protocol](url)
  * [Rapport](url)
* Interviews (N=x)
  * [Protocol](url)
  * [Rapport](url)
    
### Definition
* User testing wave 1 (N=x)
  * [Protocol](url)
  * [Rapport](url)
* User testing wave 2 (N=x)
  * [Protocol](url)
  * [Rapport](url)

## Licentie
> :warning: voeg jullie namen toe in de documenten hieronder en delete dan dit lijntje   

This repository contains both software and design materials created as part of an industrial design energineering project at Ghent University.

- **Software and code:** [MIT License](./LICENSE-MIT)  
- **Design, documentation, CAD, and media:** [CC BY 4.0 License](./LICENSE)
  
You are free to reuse and build upon this work, both commercially and non-commercially, as long as proper attribution is given to the original authors.

## Bronnen
 [^1]: Thomas, T., & Ritter, A. (2022). Wandering & sundowning in dementia. _Practical Neurology, 21_(3), 36–44.
