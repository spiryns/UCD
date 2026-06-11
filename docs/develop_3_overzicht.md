# SensePath → Develop 3

[← Terug naar hoofdpagina](../README.md)

---

## Develop 3

Develop 3 is de laatste iteratieve fase van het project en bouwt voort op de ergonomische winst uit Develop 2 (versmalde gleuf, voorkeurshoogte van het kompas, sferisch contactoppervlak). Waar Develop 1 de kerninteractie valideerde en Develop 2 de fysieke ergonomie aanscherpte, focust Develop 3 op drie complementaire lagen: de **emotionele en service-laag (UX)**, een **CMF-deepdive** per onderdeel, en een **finale validatie in real-life context** in plaats van de gecontroleerde labosetting van Develop 2.

📄 [Develop 3 → UX & Service Design (uitgebreid document)](develop_3.md)

### UX & Service Design Challenges

De UX-laag van Develop 3 is theoretisch onderbouwd in een afzonderlijk document dat vier ankers behandelt: de **emotionele kern** van het product (kalmte, vertrouwen, autonomie, discretie), **Norman's drie lagen** (visceral, behavioral, reflective), de set **microinteracties** volgens Saffer's trigger / rules / feedback / loops & modes-model, en de **service-context** rond het fysieke product. Drie visualisaties brengen die service-context in kaart en zijn opgenomen als infographics in [develop_3/](develop_3/):

| Visualisatie | Doel | Centraal inzicht |
|---|---|---|
| **Stakeholder map** ([PNG](develop_3/img/stakeholder_map.png)) | Vijf concentrische ringen, van kerngebruiker tot platform-actoren | Ring 3-4 (infrastructuur + institutioneel) levert ~40 % van de value delivery maar heeft nul fysiek contact met de gebruiker. De service moet werken zonder dat de gebruiker die backstage-actoren ooit ontmoet. |
| **Customer Journey Map** ([PNG](develop_3/img/customer_journey.png)) | Vijf fases (oriëntatie, onboarding, eerste gebruik, routine, hergebruik) × vier rijen (touchpoints, acties, emotie-curve, pains/opportunities) | Drie expliciete Moments of Truth: eerste 30 s na unboxing (visceral), eerste fail-safe in publiek (reflective), eerste zelfstandige routeafsluiting zonder hulp (autonomie). |
| **Service Blueprint** ([PNG](develop_3/img/service_blueprint.png)) | Vijf rijen × vier fases met expliciete *line of interaction*, *line of visibility* en *line of internal interaction* | Indoor wayfinding kan niet zonder gebouwbeheerder-POI-data (B2G-afhankelijkheid), schaalbare onboarding hangt af van een mobiliteitstrainer-netwerk, en lange-termijn vertrouwen wordt bepaald door invisible firmware- en mapping-updates. |

<p align="center">
  <img src="develop_3/img/stakeholder_map.png" alt="Stakeholder map SensePath" width="80%"/>
  <br/><em>Stakeholder map → vijf concentrische ringen van kerngebruiker tot platform.</em>
</p>

<p align="center">
  <img src="develop_3/img/customer_journey.png" alt="Customer Journey Map SensePath" width="80%"/>
  <br/><em>Customer Journey Map → vijf fases met emotie-curve en drie Moments of Truth.</em>
</p>

<p align="center">
  <img src="develop_3/img/service_blueprint.png" alt="Service Blueprint SensePath" width="80%"/>
  <br/><em>Service Blueprint → frontstage en backstage interacties van het volledige PSS-systeem.</em>
</p>

### Onderzoeksvragen Develop 3

- Welke set trilpatronen (max. drie tot vier signalen via één trilmotor) is voldoende **onderscheidbaar en intuïtief** om een naderende afslag, een route-afwijking en een statusmelding te communiceren zonder cognitieve overload?
- Op welk **moment vóór een afslag** wenst de gebruiker een voorbereidende trilling (uitgedrukt in stappen, meters of seconden)?
- Wensen gebruikers één neutraal richtings-aankondigingssignaal in combinatie met het kompas, of een **expliciet onderscheid links/rechts** in het patroon zelf?
- Welk **handvatmateriaal** (harde standaardstok, zachter indrukbaar handvat, kurk-element) wordt geprefereerd qua tactiliteit en bruikbaarheid in alle weersomstandigheden?
- Welke **kleurkeuze** voor het handvat sluit aan bij de behoefte aan contrast voor slechtzienden en bij de externe zichtbaarheid in publieke ruimte?
- Verschilt de ervaren **cognitieve belasting en het vertrouwen in real-life context** (verkeer, voetgangers, gidslijnen, niveauverschillen) significant van de labosetting in Develop 2?
- Wensen gebruikers **persoonlijke instelbaarheid** van trilpatronen en aankondigingsafstanden, of volstaat een vaste default?

### Methode & sample

De test combineert drie opeenvolgende blokken in één sessie van ± 75 minuten per deelnemer: een **binnenblok** met CMF-bevraging en haptische leerfase, een **buitenblok** met Wizard-of-Oz wandeling in het Citadelpark, en een **stedelijk blok** vertrekkend vanuit Licht en Liefde naar het station Gent-Sint-Pieters. Tijdens de wandeling stuurt de testleider via een telefoon-app de microcontroller in het handvat, die op zijn beurt het kompas en de trilmotor aanstuurt. Na afloop volgt een aparte evaluatieronde met Likert-scoring en een open reflectiegesprek over instelbaarheid, fallback en algemene indruk.

📄 [Protocol Develop 3](../reports%20and%20protocols/protocol_sensepath_develop3_PDF.pdf) · 📄 [Rapport Develop 3](../reports%20and%20protocols/rapport_sensepath_develop3.pdf)

| Deelnemer | Leeftijd | Profiel | Locatie | Datum |
|---|---|---|---|---|
| Mario | 52 | Verloor zicht op 18-jarige leeftijd | Licht en Liefde | 07/05/2026 |
| Jelle | 22 | Blind van geboorte | Licht en Liefde | 07/05/2026 |
| Herman | 65 | Blind sinds geboorte | Licht en Liefde | 08/05/2026 |
| Milo | 20 | Ziende controle (geblinddoekt) | Thuis | 08/05/2026 |
| Milos | 20 | Ziende controle (geblinddoekt) | Thuis | 08/05/2026 |

### Prototypes

**Handvat met geïntegreerde elektronica.** Het Develop 3 prototype is een 3D-geprint handvat met de uit Develop 2 geselecteerde voorkeurshoogte en sferisch contactoppervlak van het kompas. De gleuf is verkleind zodat het kompas binnen de handpalm blijft draaien in plaats van eruit te wijken. In het handvat zit een **XIAO ESP32-S3 microcontroller** gekoppeld aan een **DRV2605L haptische driver** die de **coin vibratiemotor (ERM)** aanstuurt. De microcontroller maakt een eigen WiFi-acces point ("SensePath") aan, waardoor de testleider via een webpagina op zijn telefoon (`http://192.168.4.1`) de trilpatronen kan aansturen tijdens de Wizard-of-Oz sessie.

<p align="center">
  <img src="../img/test-opstelling-dev3.png" alt="Trilmotor en microcontroller in handvat" width="40%"/>
  <br/><em>Geïntegreerde XIAO ESP32-S3 + DRV2605L + coin vibratiemotor (ERM) in het handvat.</em>
</p>

**Trilpatronen.** Het uitgebreide microinteractie-overzicht in [develop_3.md](develop_3.md) documenteert tien kandidaat-momenten (M1 → M10) verspreid over de hele user journey (route gestart, koers oké, bocht nadert, bocht correct genomen, afwijking, fail-safe, bestemming bereikt, batterij low, clip-bevestiging). Voor de Develop 3 user-test werden de **drie meest kritieke MVP-signalen** geselecteerd, omdat zij de kern van de feedback-taal dragen (twee navigatie-cues plus een statussignaal):

| MVP-signaal | Scenario | Pulslogica getest |
|---|---|---|
| **M4** | Bocht nadert, voorbereidend signaal | Oplopende crescendo (5 pulsen, interval 1000 → 300 ms) |
| **M6** | Route-afwijking, je loopt uit je geplande koers | Ademende pulsreeks (3 cycli @ 0,5 Hz) |
| **M9** | Batterij low (< 15%) | Drie korte hoog-frequente ticks (@ 220 Hz) |

Tijdens de leerfase kregen de deelnemers ook een aantal alternatieve patronen uit de bredere set te voelen (Soft Bump, Double Click, Triple Click, Transition Ramp variantes). Vervolgens werd hen gevraagd om per scenario een voorkeurspatroon te kiezen, om te valideren of de drie MVP-koppelingen voor blinde gebruikers ook intuïtief zijn (zie UG10 onder Resultaten).

**Wizard-of-Oz aansturing via telefoon.** Een eenvoudige webpagina op de telefoon van de testleider biedt knoppen om elk patroon real-time te triggeren. De deelnemer ziet of hoort de telefoon niet en interpreteert de trilling als systeem-output, wat de illusie van een werkend GPS-systeem creëert.

**CMF-referentiemonsters voor de bevraging.** Naast het functionele handvat werden twee fysieke referenties meegebracht ter vergelijking: een **padel-racket** als voorbeeld van een zachter indrukbaar handvat met soft-touch overmold, en een **kurk-cilinder** als voorbeeld van een natuurlijk grip-materiaal zoals dat bij hedendaagse fietsstuurlinten wordt gebruikt.

<p align="center">
  <img src="../img/prototype-dev3.png" alt="Handvat-prototype met contactoppervlak" width="50%"/>
  <br/><em>Handvat-prototype met sferisch contactoppervlak, voorkeursconfiguratie uit Develop 2.</em>
</p>

### Resultaten

#### UX-feedback

**Mario** (52, verloor zicht op zijn 18e). De eerste bocht-aankondiging werd te kort en te zwak gevoeld om duidelijk op te merken; de bocht-aankondiging en de route-afwijking werden meermaals verward. Mario verwoordt expliciet de behoefte aan een richtingsindicatie in het patroon zelf: *"Ik ben er nog altijd niet mee akkoord dat je in je pulsen niet aangeeft welke kant je uit moet."* De aankondiging hoeft volgens hem maar twee stappen voor de bocht te komen. De buitencontext is merkbaar zwaarder qua concentratie dan de Develop 2 binnen-test.

**Jelle** (22, blind van geboorte). Bevestigt dat de versmalde gleuf werkt: *"Op deze hoogte heb ik duidelijker contact."* Voor hem zou het contactelement nog 1 mm hoger mogen. Aankondiging op ± 2 meter vooraf is voldoende. Hij heeft geen behoefte aan apart links/rechts in het patroon, het kompas volstaat voor hem. De terugkoppel-logica (terugdraaien naar midden = je staat juist) was niet meteen intuïtief, maar oplosbaar via uitleg. Cognitieve belasting buiten viel hem mee. Hij vraagt expliciet om een audio-fallback voor wanneer haptiek vastloopt.

**Herman** (65, blind sinds geboorte). Het contactelement is volgens hem te klein, met name in winteromstandigheden met handschoenen. Bij langere wandelingen (één uur en meer) maakt hij zich zorgen over tactiele vermoeidheid en aandachtsverlies in de hand. Hij wenst een aankondigingsafstand rond ± 50 m, zoals zijn huidige GPS, en wil de richting al in het patroon zelf herkennen.

#### CMF-feedback

Alle drie de blinde testers reageerden positief op een **zachter, lichtjes indrukbaar handvat** (referentie padel-racket). Het standaard harde handvat van een witte stok wordt niet als ideaal ervaren wanneer er een zachter alternatief naast ligt. **Kurk** werd door Jelle en Herman aanvaard als materiaal, maar enkel onder voorwaarde van duurzaamheid in weer en straatgebruik. Mario was kritisch over slijtage- en vervuilingsrisico van kurk.

Over **kleur** benadrukte Mario expliciet dat het handvat moet contrasteren met de witte stok zodat slechtzienden de stok terugvinden als die ergens ligt: *"Het handvat hier is zwart, gewoon als de stok openligt, dat je het handvat kan zien."* Een wit handvat wordt afgewezen wegens vuilgevoeligheid en gebrek aan contrast. Fluo of rood is bespreekbaar voor externe zichtbaarheid in verkeer en publieke ruimte. Jelle (geboorte-blind) heeft geen kleurvoorkeur, Herman besprak kleur niet expliciet.

#### Subjectieve scores op Likert-schaal (1-7)

Na afloop van de drie testblokken werd elke deelnemer gevraagd om de voorkeursconfiguratie te scoren op een Likert-schaal van 1 (helemaal niet akkoord) tot 7 (helemaal akkoord). De scores worden hieronder vergeleken met de Develop 2 referentie. Develop 3 hanteert eigen usability goals **UG8–UG12**, in aansluiting op UG1–UG7 uit Develop 2.

| Metric | Develop 3 (avg) | Develop 2 (avg) |
|---|---|---|
| Learnability (1-7) | **6,33** | 6,33 |
| Smoothness (1-7) | **5,33** | 5,67 |
| Cognitive load (1-7, hoog = weinig concentratie) | **4,33** | 4,67 |
| Willingness (1-7) | **4,67** | 4,33 |

**UG8 → Cognitieve belasting** daalde licht ten opzichte van Develop 2 (4,33 vs 4,67), volledig toe te schrijven aan Mario's score (3/7) die de buitencontext beduidend zwaarder ervaart dan de gecontroleerde labosetting. Dit valt binnen de protocol-marge "maximaal 1 punt lager", dus UG8 wordt gehaald. Jelle en Herman bleven op het Develop 2 niveau (5/7), wat bevestigt dat de cognitieve belasting voor de kerndoelgroep (audio-vrije navigatoren) hanteerbaar blijft in real-life.

**UG9 → Bereidheid tot gebruik** stijgt van 4,33 (Develop 2) naar 4,67. De gemiddelde stijging is bescheiden door Herman's lage score (3/7), die consistent blijft met zijn Develop 2 willingness van 2/7 en zijn voorkeur voor audio-navigatie. Mario en Jelle scoren 5 en 6, wat een duidelijke stijging is en UG9 (behoud of stijging) bevestigt.

#### Rangschikking trilpatronen (UG10)

Na de leerfase werden de deelnemers gevraagd om per scenario uit de bredere set (M1 → M10) hun top-3 te kiezen. De resultaten bevestigen de drie MVP-koppelingen, maar leggen wel een ontwerpprobleem bloot: de patronen liggen onderling te dicht bij elkaar in waargenomen sterkte.

| Scenario | 1ste keuze | 2de keuze | 3de keuze |
|---|---|---|---|
| Bocht nadert | **M4** (oplopende crescendo) | M1 (zachte dubbele puls) | M5 (dubbele tick) |
| Afwijking van route | **M6** (ademende pulsreeks) | M7 (lange zachte trilling) | M2 (zachte heartbeat) |
| Batterij low | **M9** (drie korte hoog-frequente ticks) | M5 (dubbele tick) | M2 (zachte heartbeat) |

De drie geselecteerde MVP-koppelingen (M4, M6, M9) staan unaniem op de eerste plaats, wat bevestigt dat ze intuïtief aansluiten bij hun scenario. De tweede en derde keuzes komen wel uit de bredere kandidatenset, wat aantoont dat alternatieve patronen voor verschillende deelnemers ook denkbaar zijn. Mario en Jelle gaven echter beide aan dat het verschil in sterkte tussen de patronen onderling te klein is, waardoor de bocht-aankondiging en de route-afwijking in twijfelgevallen verwisseld werden. Dit onderbouwt de design implicatie "scherper differentiëren in lengte of ritme".

#### Rangschikking handvatmateriaal (UG11)

De deelnemers rangschikten drie tactiele referenties van beste naar slechtste op tactiliteit en draagcomfort.

| Plaats | Materiaal (consensus) |
|---|---|
| 1ste | Zachter handvat (padelracket-textuur) |
| 2de | Eigen huidige stok (harde standaard) |
| 3de | Kurk |

Twee van de drie deelnemers (Mario, Jelle) plaatsen het zachter handvat op de eerste plek, met hun eigen stok als tweede en kurk als derde. Herman wijkt af door zijn eigen stok bovenaan te plaatsen, omdat die voor hem de tactiele tikfeedback het zuiverste doorgeeft, maar zet het zachter alternatief eveneens op de tweede plek. Kurk wordt door alle drie als minst geschikt beoordeeld omwille van duurzaamheid en onderhoud. Dit bevestigt UG11 en de design implicatie om TPE Shore 65A overmold als hoofdmateriaal te kiezen, met de huidige harde stok-textuur als optie voor de eindgebruikers die dat verkiezen.

#### Kleurkeuze en contrast (UG12)

Zoals in de CMF-feedback hierboven beschreven, wijst UG12 in dezelfde richting: contrast tussen handvat en de witte stok is leidend, niet één specifieke kleur. Zwart of rood worden door Mario expliciet aanvaard, wit wordt afgewezen wegens vuilgevoeligheid en gebrek aan contrast.

### CMF-Deepdive

Het handvat is in Develop 3 ontleed in vijf functionele componenten, elk afzonderlijk geanalyseerd op CMF-relevante criteria. De volledige weegtabellen, materiaalvergelijkingen en literatuur-onderbouwingen staan in het [Rapport Develop 3](../reports%20and%20protocols/rapport_sensepath_develop3.pdf). De geselecteerde combinaties zijn:

| Component | Geselecteerd materiaal | Onderbouwing |
|---|---|---|
| **Structural core** | PA6 unfilled | Beste totaalscore (49/60) op rigiditeit, TPE-overmold-adhesie en productiekost. Ondersteunt de elektronica en draagt het schroefdraad voor stokmontage. |
| **Soft-touch overmold** | TPE Shore 65A | Beste totaalscore (62/75) op tactiel comfort, 2K-overmold-compatibiliteit en productiekost. Recyclebaar en thermisch warm bij eerste aanraking, in lijn met de visceral-laag uit het UX-document. |
| **Grip texture** | Fijne radiale ribbels (pitch 0,8 mm) | Beste totaalscore (63/70). Boven tactiele drempel voor blinde gebruikers (Alary 2008), leesbaar voor oudere handen (Skedung 2018), goede grip in natte omstandigheden, lage vuilophoping. |
| **Buttons (cap)** | POM (Delrin) + TPE 50A overlay | Beste totaalscore (57/65). Click feel blijft consistent na 10.000 cycli, tactiel onderscheidbaar van de grip (Norman 2011). |
| **Pin tip / kompas-indicator** | TPE 50A op aluminium kern | Beste totaalscore (64/75). Thermisch comfort op koude ochtenden, hoge tactiele leesbaarheid van de richtings-uitwijking, premium-gevoel. Uitwisselbaar zodat winterhandschoen-versie mogelijk is. |

De **stok zelf** volgt de standaard ISO 9999:2016 (code 12 39 03 Tactile sticks): aluminium of fiberglass shaft, ±12 mm diameter, lengte op basis van gebruikerslengte (122-152 cm), nylon of TPU tip 2-3 cm, wettelijk wit gekleurd met rode onderzone, minstens 2 jaar levensduur (WHO APS24).

### Design implicaties

**UX**

- **Bocht-aankondiging vs route-afwijking scherper differentiëren** in lengte of ritme. Mario's verwarring is een early warning die in een drukke straatcontext zal breken.
- **Richtingsinformatie (links/rechts) in het trilpatroon zelf** integreren als default, mét mogelijkheid om dit via app uit te schakelen voor power-users zoals Jelle die het kompas voldoende vinden.
- **Aankondigingsafstand parametriseren** in software. De spread tussen 2 stappen (Mario), 2 meter (Jelle) en 50 meter (Herman) toont dat één universele default onhaalbaar is.
- **Stille default**: het systeem mag niet ingrijpen bij elke micro-correctie, alleen bij echte gebeurtenissen. Dit is consistent met het *kalmte*-principe uit het UX-document.
- **Onboarding-flow** als verplicht productonderdeel. Alle drie de testers benoemden onafhankelijk dat de kompas-terugkoppellogica niet self-evident is bij eerste gebruik. Korte training via Licht en Liefde of via app is noodzakelijk.
- **Audio-fallback** via gekoppelde app voor situaties waar haptiek vastloopt of bij overgang naar onbekende contexten (Jelle's expliciete vraag).

**CMF**

- **Zachter handvatmateriaal** (TPE Shore 65A overmold) als hoofdkeuze. Afwijken van het standaard harde stokhandvat is gerechtvaardigd door de unanieme positieve reactie op de padelracket-referentie.
- **Kurk hoogstens als grip-accent**, niet als hoofdmateriaal. Duurzaamheid in weer en straatgebruik weegt zwaarder dan tactiele appeal.
- **Kleurregel**: contrasterend met de witte stok (zwart of rood handvat). Wit uitgesloten wegens vuilgevoeligheid en gebrek aan contrast.
- **De stok blijft wit** conform wettelijke vereisten in de meeste landen (ISO 9999, nationale verkeerswetten).
- **Vervangbare pin** is randvoorwaarde, niet een latere optimalisatie. Herman's winter-zorg combineert met Jelle's millimeter-finetuning tot één gedeelde noodzaak.

### Develop 3 conclusies

- **De versmalde gleuf werkt** → expliciete bevestiging door Jelle dat het kompas op de juiste plek zit, geen heropening van die ontwerpkeuze nodig.
- **De drie trilpatronen zijn principieel onderscheidbaar** maar de ruimte tussen de bocht-aankondiging en de route-afwijking is op de grens en moet aangescherpt worden voor de eindversie.
- **Twee van de drie testers willen richtingsinformatie in het patroon zelf** → de Develop 1 hypothese dat het kompas alleen volstaat is door de meerderheid weerlegd.
- **De optimale aankondigingsafstand bestaat niet als universele waarde** → personalisering via settings is geen luxe-extra maar een design requirement.
- **Real-life cognitieve belasting blijft hanteerbaar** voor de kerndoelgroep (audio-vrije navigatoren), de Develop 2 winst houdt stand in een complexere context.
- **Zachter handvatmateriaal wint unaniem** → Develop 3 levert een eenduidige CMF-richting op voor het overmold (TPE Shore 65A), de grip-textuur (fijne radiale ribbels), de buttons (POM + TPE) en de pin-tip (TPE op aluminium).
- **Kleur-keuze volgt een regel, geen voorkeur**: contrast met de witte stok is leidend (zwart of rood), niet esthetiek.
- **Vervangbare pin** is noodzakelijk om winterse handschoen-condities te dekken en individuele tactiele drempels te accommoderen.

### Kritische reflectie Develop 3

De Develop 3 resultaten zijn richtinggevend, maar verdienen een aantal eerlijke nuances.

Ten eerste blijft de **sample beperkt** met N=3 blinde of slechtziende deelnemers en N=2 ziende controles (geblinddoekt). De convergentie tussen Mario en Herman op de behoefte aan richting-in-patroon is sterk genoeg om een design-implicatie te trekken, maar Jelle's tegengestelde voorkeur toont dat de doelgroep intern heterogeen is. Een grotere sample zou de instelbaarheids-vraag verder kunnen kwantificeren.

Ten tweede was de **trilmotor in deze sessie nog niet op de finale plek** in het handvat geïntegreerd. Deelnemers voelden de patronen wel, maar in het eindproduct zal de motorpositie tegen de hypothenar liggen waar de demping minder is. Dit kan de perceptiekwaliteit beïnvloeden ten goede of ten kwade, en moet in een laatste validatie-iteratie hertest worden.

Ten derde was de **stok in deze sessie nog steeds niet permanent op het handvat bevestigd**. De focus lag op het handvat zelf en op de signalen, maar dat betekent dat de gecombineerde belasting van stok-tikken + handvat-vibratie + omgevingsperceptie nog niet integraal getest is. Mario en Herman wezen er beide expliciet op tijdens de sessies dat de stok-feedback in de praktijk parallel doorloopt en dat het systeem moet samenwerken met die bestaande tactiele input.

Ten vierde is de **CMF-deepdive grotendeels analytisch en literatuurgedreven**, niet empirisch via prototyping. De geselecteerde materialen (TPE Shore 65A, PA6 unfilled, fijne radiale ribbels) scoren hoog op de weegtabellen, maar zijn nog niet als gecombineerd prototype getest met eindgebruikers. Een 1-op-1 fysieke variant testen zou de finale CMF-keuzes verder kunnen valideren.

Ten vijfde blijft **stations-navigatie als gerichte use-case** een open strategische vraag. Alle drie de blinde testers wezen spontaan op stations als de plek waar haptische navigatie het meeste verschil zou maken. Dit suggereert dat een toekomstige product-go-to-market gerichter zou kunnen zijn dan de algemene "indoor wayfinding"-positionering, maar deze pivot ligt buiten de scope van Develop 3.

---

[← Terug naar hoofdpagina](../README.md) · [Volgende fase → Deliver](deliver.md)
