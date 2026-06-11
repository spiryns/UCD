# SensePath → Develop 2

[← Terug naar hoofdpagina](../README.md)

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

<p align="center">
  <img src="../img/NX_anthropometry_ANSUR_II.jpeg" alt="NX Human Hands dialoog met ANSUR II configuratie op P50" width="400"/>
</p>

### Cognitieve & sensorische ergonomie

De cognitieve en sensorische analyse vormt het theoretische hart van Develop 2. Ze koppelt de problemen uit Develop 1 aan drie kaders uit het cursusmateriaal Gebruiksgericht Ontwerpen: **Norman's 7 Stages of Action**, de **Gestalt-wetten**, en het concept van **signifiers**. Elke theoretische vaststelling wordt vertaald naar een concrete ontwerpkeuze.

#### Norman's 7 Stages of Action

In Develop 1 braken drie van Norman's zeven fasen: Perceive, Interpret en Compare.

**Perceive (waarnemen)**: Het probleem was dat twee haptische kanalen (kompas en trilmotoren) tegelijk "gelezen" moesten worden op dezelfde hand. Het probleem was niet dat er te veel informatie was, maar dat de sensorische kanalen elkaar overlapten op dezelfde anatomische zone. Het ontwerpprincipe dat hieruit volgt is **ruimtelijke scheiding van feedbackkanalen**: kompas en trilmotoren moeten op anatomisch gescheiden zones zitten zodat ze niet interfereren. Concreet zijn de finger-mounted vibratiemotoren verwijderd ten gunste van één enkele in-handle motor, en is het kompas verplaatst naar de hypothenar (hiel van de hand).

**Interpret (interpreteren)**: De mentale mapping "balletje naar beneden = rechts draaien" bleek grip-afhankelijk in Develop 1. Verschillende gebruikers hielden het handvat anders vast, waardoor dezelfde beweging tegengestelde betekenissen kreeg. Norman noemt dit een **system image mismatch**: het conceptuele model van de ontwerper klopt niet met het mentale model dat de gebruiker opbouwt op basis van wat het systeem hem laat zien. Het ontwerpprincipe is dat de mapping robuust moet zijn ongeacht gripvariatie. Voor Develop 2 wordt dit opgelost via een **onboarding tutorial** die de oriëntatie kalibreert op de natuurlijke grip van de gebruiker, en een **IMU-gebaseerde fallback** die waarschuwt wanneer de griporiëntatie de mapping breekt.

**Compare (vergelijken)**: De gebruiker wil evalueren "ben ik nog op koers?" maar krijgt daar in Develop 1 onvoldoende bevestiging van. Dit is wat Norman de **Gulf of Evaluation** noemt: de afstand tussen de feedback die het systeem geeft en wat de gebruiker nodig heeft om zijn doel te toetsen. Het ontwerpprincipe is dat het systeem expliciet en eerlijk moet communiceren over zijn eigen status.

#### Gestalt-wetten

De Gestalt-wetten zijn klassiek beschreven voor visuele perceptie, maar gelden evengoed voor tactiele perceptie. Mensen groeperen sensorische input automatisch volgens dezelfde principes.

**Wet van figuur-grond**: Er moet altijd een duidelijk onderscheid zijn tussen wat de "figuur" is (opvallend, belangrijk) en wat de "grond" is (achtergrond, context). In Develop 1 was dit contrast te zwak: het kompas was te subtiel en de vibratie was niet duidelijk genoeg afgebakend van de continue koersfeedback. Het ontwerpprincipe is **versterk het intensiteitscontrast**: vibratie moet kort en krachtig zijn, kompas moet rustig en continu blijven, en beide moeten duidelijk onderscheidbaar zijn.

**Wet van continuïteit**: Mensen volgen liever een doorlopende sensorische stroom dan onderbroken brokstukken. Het kompas geeft continue feedback, vibratie is discreet. Wanneer beide tegelijk actief zijn, "wint" de continue stroom de aandacht en wordt de korte vibratiecue gemist. De ontwerpimplicatie is dat het **kompas kort pauzeert tijdens een vibratiecue**, zodat het korte event-signaal niet verdrinkt in de achtergrondstroom van de koersfeedback.

**Wet van proximity en common region**: Dingen die fysiek dicht bij elkaar zitten of in dezelfde anatomische zone, worden onbewust als één signaal gegroepeerd in plaats van als twee aparte informatiestromen. In Develop 1 zaten kompas en trilmotoren fysiek dicht bij elkaar op dezelfde hand, waardoor ze als één moeilijk te ontleden brij werden waargenomen. Door ze in verschillende anatomische zones te plaatsen creëer je twee aparte "common regions" die elk hun eigen informatie dragen.

#### Signifiers

Norman definieert signifiers als waarneembare aanwijzingen die de gebruiker vertellen wat er kan, gebeurt of fout is. Bij SensePath, een product zonder visuele interface, moeten signifiers volledig tactiel zijn. Uit Develop 1 bleken twee signifiers te ontbreken:

- **Transitiesignaal tussen modi**: Wanneer het systeem schakelt van buiten naar binnen, of van een modus naar een andere, is er geen signifier voor die overgang. De gebruiker merkt de verandering pas wanneer iets onverwachts gebeurt. Voorstel: een uniek kort trilpatroon dat de moduswissel aankondigt.
- **Fout-signifier**: Wanneer het systeem onzeker is over zijn eigen positie of de wizard-timing mist, is er geen feedback dat er iets onverwachts gebeurt. Dit ondergraaft het vertrouwen omdat de gebruiker een fout mental model opbouwt ("ik deed iets fout") terwijl het systeem zelf faalde. Voorstel: een specifiek "heroriënteer"-signaal dat duidelijk verschilt van navigatiecues.

#### Vertaling naar het prototype

De theoretische analyse leidt tot vier concrete ontwerpkeuzes voor Develop 2:

- **Ruimtelijke scheiding van kanalen**: finger-mounted vibratiemotoren verwijderd, één enkele in-handle motor met een beperkte set codes
- **Mental mapping veiliggesteld**: onboarding tutorial die kalibreert op de natuurlijke grip van de gebruiker, IMU-fallback die waarschuwt bij gripverandering
- **Figuur-grond contrast**: vibratie wordt kort en krachtig; kompas pauzeert tijdens een vibratiecue
- **Twee nieuwe signifiers**: uniek patroon voor moduswisseling en eerlijk fout-signaal voor systeemonzekerheid

### Prototypes

Voor Develop 2 werden drie prototypedimensies gevarieerd via **variety prototyping**, een methode die expliciet meerdere fysieke varianten naast elkaar test om confirmation bias te vermijden.

**Handle profile**: Drie verschillende handvatprofielen werden ontwikkeld om de algemene grip-ergonomie te onderzoeken. De vorm bepaalt hoe de hand zich rond het handvat sluit en beïnvloedt onbewust de handoriëntatie.

<p align="center">
  <img src="../img/handle_profile.png" alt="Drie handvatprofielvarianten" width="700"/>
</p>

**Compass groove**: Het handvat werd voorzien van een verticale gleuf met **vijf posities** waarin het kompaselement geplaatst kon worden, van H1 (laagste, dicht bij de pols) tot H5 (hoogste, dicht bij de knokkels). Door dezelfde gleuf te gebruiken kon de positie systematisch gewisseld worden zonder andere variabelen te veranderen.

<p align="center">
  <img src="../img/grooves_prototype.jpeg" alt="Handvat met kompasgleuf en 5 posities" width="300"/>
</p>

**Contact surface**: Vijf verschillende kompaselementen werden ontwikkeld die elk een combinatie zijn van **vorm én uitsteekselhoogte**. Drie afgeronde rechthoekige uitsteeksels op verschillende uitsteekselhoogtes (laag, midden, hoog), één sferisch element, en één schuin afgeronde overgangsvorm. Dat laatste element kwam voort uit een inzicht van Mario tijdens zijn sessie: een geleidelijke overgang van vlak naar verhoog vermindert het scherpe contactgevoel tegen de hand.

<p align="center">
  <img src="../img/contact_surface_prototype.png" alt="Vijf kompaselementen met variërende vorm en uitsteekselhoogte" width="700"/>
</p>

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

<p align="center">
  <img src="../img/test_sessions_dev2.png" alt="Testsessies met Mario en Herman in Licht en Liefde" width="700"/>
</p>

### Test 1: Compass grooves

In Test 1 werd onderzocht op welke gleufpositie het kompaselement het duidelijkst voelbaar is, gegeven de natuurlijke grip van de gebruiker. De vijf posities werden in stilstand gevoeld en daarna kort op een rechte loopstrook getest, met het referentie-element (afgerond rechthoekig uitsteeksel, middelhoge uitsteekselhoogte) constant gehouden over alle posities zodat alleen de gleufpositie varieerde.

> *"Daar voel ik het 't best, helemaal onderaan."*
> *"De bovenste was lastig, mijn vel kwam ertussen."*

**Key findings:**

- **Laagste gleufpositie (H1) gewonnen**: Zowel Mario als Herman kozen onafhankelijk de positie het dichtst bij de hiel van de hand.
- **Hypothenar als ankerpunt**: Op de laagste positie rust het element tegen het stevige vlezige deel van de handpalm bij de pols, waar de hand sowieso contact maakt ongeacht hoe ze het handvat vasthouden. Dit lost het Develop 1-probleem van handpalmcentrum (te zwak signaal) op.
- **Hoogste positie problematisch**: Bij de bovenste gleuf raakte de huid bekneld tussen het element en de gleufrand. Dit was een mechanisch probleem dat alleen bij dynamisch grijpen naar boven kwam.
- **Grip-onafhankelijkheid bevestigd**: De laagste gleufpositie werkt over verschillende grippatronen heen omdat het contactvlak anatomisch verankerd is, niet handpositie-afhankelijk. Dit is precies wat de Norman-analyse voorspelde over het belang van een grip-onafhankelijke mapping.

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

- **Middelhoge uitsteekselhoogte gewonnen**: Lage uitsteeksels voelden te subtiel, hoge voelden scherp en oncomfortabel. De middelhoge gaf de beste balans tussen voelbaarheid en comfort.
- **Sferisch element als voorkeursvorm**: Soepele overdracht van richtingsbeweging, geen scherpe randen tegen de huid, comfortabel over verschillende griprotaties. Dit komt rechtstreeks voort uit de Gestalt figuur-grond analyse: het sferische element levert een duidelijker afgebakend tactiel signaal.
- **Schuin afgeronde overgangsvorm (C5) als sterke tweede**: Vooral gewaardeerd voor de geleidelijke overgang van vlak naar verhoog, een idee dat Mario tijdens zijn sessie aanbracht en dat Rory bevestigde.
- **Glove-inzicht van Mario**: Mario merkte op dat in winterse omstandigheden met handschoenen het element nauwelijks voelbaar zou zijn. Dit triggerde het idee van een **uitwisselbare kompasmodule** met een robuustere wintervariant.

### Test 3: Turn via compass feedback

In Test 3 werd de voorkeurscombinatie uit Test 1 en Test 2 (laagste gleufpositie + middelhoge uitsteekselhoogte + sferisch element) gevalideerd op een volledig benchmarkparcours van 60 cm breed, gelijkaardig aan het Develop 1-parcours. De wizard biedt continue kompasfeedback waarbij het kompaselement volledig uitwijkt naar de doelrichting en geleidelijk terugkoppelt naar neutraal naarmate de deelnemer zich oriënteert.

<p align="center">
  <img src="../img/path_test_3_dev2.png" alt="Afgetaped benchmarkparcours Test 3" width="400"/>
</p>

> *"Ik ben wel onder de indruk, het is echt beter dan de vorige keer."* (Mario)
>
> *"180 graden draaien is eigenlijk niet nodig, het stuurt continu bij."* (Rory)
>
> *"Het werkt, maar ik blijf voor mezelf liever met audio werken."* (Herman)

**Key findings:**

- **Single focus point bevestigt de keuze voor 1 LRA**: het loslaten van finger-mounted vibratiemotoren bevrijdt de gebruiker van een kunstmatige greep-restrictie. Design-implicatie: voor het Develop 3 ontwerp is dit een vergrendelende keuze ; geen terugkeer naar meerkanaals haptiek tenzij een nieuwe pijn dat afdwingt.
- **180° kompas-uitwijking is overdimensionering**: Mario's observatie dat het systeem continu corrigeert vóór de gebruiker de extreme hoek bereikt, weerlegt onze initiële aanname dat volledig richtingbereik nodig is. Design-implicatie: in de finale firmware kan de uitwijking begrensd worden tot de werkelijke gebruiksrange, wat de mechaniek vereenvoudigt en motorbelasting verlaagt.
- **Hand-aandacht is een bottleneck onder real-life parallelle taken**: Herman's waarschuwing dat stok-tikken, randvolging en omgevingsgeluid samen om aandacht concurreren, is geen kritiek op het prototype maar een doelgroep-afbakening. Design-implicatie: het systeem mag niet uitgaan van permanente hand-aandacht; het ontwerp moet werken op periodieke check-ins, niet op continue monitoring. Dit voedt de keuze voor scherp gelokaliseerde event-cues (M4/M6/M9) boven continue richtingsruis.

**Benchmark vergelijking Develop 1 vs Develop 2:**

| Metric | Develop 2 | Develop 1 |
|---|---|---|
| Walking zone width | 60 cm | 60 cm |
| SIZ (% Steps in zone) | **100%** | 97,52% |
| Apprenticeship | Av. 4 min | Av. 4 min |
| Learnability (1-7) | 6,33 | 6,00 |
| Smoothness (1-7) | 5,67 | 4,67 |
| Cognitive load (1-7) | **4,67** | 3,00 |
| Willingness (1-7) | 4,33 | 4,33 |
| Trust (1-7) | n.v.t. | n.v.t. |
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
| D6.8 | De handvatdimensies accommoderen het middelste 50% van de doelgroep (ANSUR II, P25-P75) zoals gevalideerd in NX |
| D6.9 | Het systeem voorziet een IMU-gebaseerd fallbacksignaal wanneer de griporiëntatie van de gebruiker de kompas-mapping breekt, gecommuniceerd via een onderscheidend trilpatroon |
| D6.10 | Er worden geen vibratiemotoren geplaatst op individuele vingerposities, om afhankelijkheid van gripvariatie weg te nemen |

### Develop 2 conclusies

- **Eén in-handle vibratiemotor met beperkte codeset** verwijdert de grip-afhankelijkheid die finger-mounted vibratie in Develop 1 brak.
- **Laagste gleufpositie (hypothenar contact)** is de optimale locatie voor het kompaselement, onafhankelijk gevalideerd door alle drie de blinde/slechtziende deelnemers.
- **Sferisch contactoppervlak met middelhoge uitsteekselhoogte** levert de duidelijkste richtingsperceptie zonder oncomfortabel of scherp aan te voelen.
- **Cognitieve belasting daalt met 1,67 punten** op een 7-puntsschaal (van 3,00 naar 4,67), het sterkste bewijs dat ergonomische herontwerpkeuzes direct de mentale belasting verlagen. UG3 (≥4,50) is hiermee gehaald.
- **Continue closed-loop kompasfeedback** (volledige uitwijking naar de doelrichting, geleidelijke terugkoppeling naar neutraal) sluit de Gulf of Evaluation die in Develop 1 de Compare-fase brak.
- **Antropometrische verankering in NX (ANSUR II, P25-P75)** zorgt dat het handvat past bij het middelste 50% van de doelgroep en niet meer afhangt van individuele handgrootte.
- **Bereidheid blijft het open vraagstuk**: Develop 2 bevestigt dat sommige gebruikers (audio-eerst navigators zoals Herman) buiten de kerndoelgroep van SensePath vallen, wat de gebruikerssegmentatie scherper maakt voor Develop 3.
- **Een uitwisselbare kompasmodule** is de logische volgende stap, met ruimte voor persoonlijke voorkeur en een robuuste wintervariant voor handschoengebruik.

### Kritische reflectie Develop 2

De Develop 2-resultaten zijn op zich positief, maar er moeten een aantal eerlijke nuances bij geplaatst worden.

Ten eerste was de **sample beperkt**. Met N=3 blinde/slechtziende deelnemers (Mario, Herman, Rory) en N=2 ziende controles is de statistische zeggingskracht klein. De convergentie tussen Mario en Herman op de voorkeursgleufpositie en het voorkeurselement is op zich sterk, maar moet in Develop 3 met een grotere groep bevestigd worden.

Ten tweede is de **stok bewust weggelaten** in deze testopzet. De focus lag puur op de ergonomie van het handvat zelf, om te vermijden dat de stok-feedback de evaluatie van het handvat zou vertroebelen. Dit is methodisch verdedigbaar voor deze fase, maar betekent ook dat de gecombineerde belasting van stok + handvat + omgevingsperceptie pas in Develop 3 echt getest kan worden. Herman wees daar zelf op tijdens het interview, en die opmerking weegt zwaar omdat zij precies aangeeft waar de praktijksituatie afwijkt van de testomgeving.

Ten derde werd de **elektronica niet empirisch gevalideerd**. De drie nieuwe ontwerpelementen die uit de cognitieve ergonomie-analyse kwamen (de twee signifiers voor moduswisseling en systeemonzekerheid, en de IMU-fallback voor gripverandering) konden niet gedemonstreerd worden omdat het handvat in deze fase nog geen geïntegreerde elektronica had. Deze zaken werden verbaal aan de deelnemers voorgelegd en positief ontvangen, maar dat is geen empirische validatie. Develop 3 zal deze concepten met geïntegreerde hardware moeten testen.

Ten vierde was **Test 2 minder gestructureerd dan oorspronkelijk gepland**. De vijf varianten van het kompaselement werden niet allemaal in dezelfde volgorde aan elke deelnemer voorgelegd, en de schuin afgeronde overgangsvorm (C5) ontstond pas tijdens de eerste sessie met Mario en werd daarna meegenomen bij Herman. Dit is enerzijds een teken van iteratief ontwerpen in actie, maar anderzijds een methodische zwakte voor de directe vergelijkbaarheid tussen deelnemers.

Ten vijfde verdient **Herman's lage willingness-score (2/7)** een aparte kanttekening. Zijn lage score komt niet voort uit een tekortkoming van het prototype, maar uit zijn persoonlijke voorkeur voor audio-navigatie en zijn jarenlange ervaring met echolocalisatie. Dit zegt iets over de doelgroepafbakening van SensePath, niet over de kwaliteit van de huidige iteratie. Voor Develop 3 betekent dit dat de kerngebruiker scherper gedefinieerd moet worden: SensePath richt zich op gebruikers die haptische feedback prefereren boven audio en die hun gehoor willen vrijhouden voor omgevingswaarneming.

---

[← Terug naar hoofdpagina](../README.md) · [Volgende fase → Develop 3](develop_3_overzicht.md)
