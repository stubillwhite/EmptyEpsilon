neutral = FactionInfo():setName("Independent"):setLocaleName(_("Independent"))
ucn = FactionInfo():setName("UCN"):setLocaleName(_("UCN"))
brutal = FactionInfo():setName("Brutal"):setLocaleName(_("Brutal"))
others = FactionInfo():setName("Unknown Synthetic Object"):setLocaleName(_("Unknown Synthetic Object"))
hive = FactionInfo():setName("Unknown Organic Object"):setLocaleName(_("Unknown Organic Object"))
jumpcorp = FactionInfo():setName("Jump Corporation"):setLocaleName(_("Jump Corporation"))
european = FactionInfo():setName("European Federation"):setLocaleName(_("European Federation"))
shanghai = FactionInfo():setName("Shanghai Pact"):setLocaleName(_("Shanghai Pact"))
commonwealth = FactionInfo():setName("Commonwealth"):setLocaleName(_("Commonwealth"))
jasa = FactionInfo():setName("JASA"):setLocaleName(_("JASA"))
corsair = FactionInfo():setName("corsair")

--Colour Blindness Friendly Colours: 
-- Hostile (OpFor): C9005F - Maroon - 201, 0, 95
-- Allied: 1FFF00 - Green - 31, 255, 0
-- Neutral but armed/A threat: C97900 - Amber - 201, 121, 0
-- BluFor: 6060FF - Blue - 96,96,255
-- Unknown F8FF52 - Yellow	- 248, 255, 82

neutral:setGMColor(240, 240, 240)
neutral:setDescription(_([[Despite appearing as a faction, independents are distinguished primarily by having no strong affiliation with any faction at all. Most traders consider themselves independent, though certain voices have started to speak up about creating a merchant faction.]]))


ucn:setGMColor(96,96,255)
ucn:setFriendly(european)
ucn:setFriendly(commonwealth)
ucn:setFriendly(shanghai)
ucn:setFriendly(jasa)
ucn:setEnemy(brutal)
ucn:setEnemy(corsair)
ucn:setDescription(_([[The United Confederation Navy.

The United Confederate Navy (UCN) is the military space-faring arm of the United Confederation of Terran and Circumsolar Nations (UCTUN) - humanity's first attempt at a single unified government system. Just as the UCTCN is made up the varied political governing factions of Earth, so the UCN draws its personel from the various military arms of those old political factions - primarily a mixture of old Commonwealth, European Federation, JASA and Shanghai Pact officers and ratings.  

The technology of the UCN also incorporates the latest and best innovations of those various factions, making the UCN fleet a collection of the finest spacefaring technology humanity has to offer.]]))


brutal:setGMColor(201, 0, 95)
brutal:setEnemy(ucn)
brutal:setDescription(_([[The Brutal.

A hardy race of powerful warriors with a somewhat primitive culture for a spacefaring race - mankind has nicknamed them 'The Brutal'.

From what we can tell, as soon as the Brutal obtained reliable space flight, they immediately set out to conquer and subjugate any other race they might encounter. Their hierarchy is based solely on physical might; a Brutal warrior kills anything it can kill, and owns anything it can take by force. In their own language they call themselves something which roughly translates to 'the apex' which gives you an idea of how they view themselves.

Relatively little is known about the Brutal and their origins, but they are a relatively young spacefaring race who seem to have sprung up from nowhere. They are clustered around the Adamas belt where a significant number of humans lived for many years without encountering them. Their numbers and warlike nature make them an existential threat to humanity. Fortunately they appear to be unaware of our numbers or the location of our homeworld - for now. ]]))


others:setGMColor(248, 255, 82)
others:setDescription(_([[Unknown Synthetic Object.

Where an object is encountered that is obviously constructed (ie not naturally occurring) but it’s origin cannot be determined, the ship will flag it as an “Unknown Synthetic Object”. On many occasions this is simply a large piece of debris with an active system still running, or a vessel with a damaged transponder. However it is possible that such an object could have a genuinely unknown origin – perhaps even something that has been constructed by an as-yet uncontacted race of beings.  ]]))

hive:setGMColor(248, 255, 82)
--hive:setEnemy(neutral)
--hive:setEnemy(ucn)
--hive:setEnemy(brutal)
--hive:setEnemy(jumpcorp)
--hive:setEnemy(european)
--hive:setEnemy(commonwealth)
--hive:setEnemy(shanghai)
--hive:setEnemy(jasa)
hive:setDescription(_([[Unknown Organic Object.

Where an object is encountered that is primarily organic, but it’s nature cannot be determined, the ship will flag it as an “Unknown Organic Object”. Contacts such as this are extremely rare. It could be a deceased being that has been ejected from an airlock, or an organic waste product, or significant quantity of organic matter left over from the destruction of a vessel. In most of these situations, the organic matter would usually be too small to register on radar. It is theoretically possible that an as-yet uncontacted race of beings may employ organic matter in the construction of space-faring vessels, but the UCN has not found anything like this to date.]]))


jumpcorp:setGMColor(201, 0, 95)
jumpcorp:setEnemy(ucn)
jumpcorp:setEnemy(neutral)
jumpcorp:setEnemy(commonwealth)
jumpcorp:setEnemy(shanghai)
jumpcorp:setEnemy(european)
jumpcorp:setEnemy(jasa)
jumpcorp:setEnemy(hive)
jumpcorp:setDescription(_([[The Jump Corporation.

Jump was one of the five human factions to leave earth during the Exodus, and the only one of those factions to be a private-interest corporation rather than a trans-national government body. Jump offered the opportunity for anyone to buy their way onto an Ark ship leaving earth, but at a very steep price. An individual could either contribute to the funding of the expedition by becoming a shareholder at the cost of billions, or could indenture themselves to the corporation for the rest of their own life and the lives of their children for two further generations.

Jump were the only one of the Exodus factions to elect not to return to Earth following the discovery of the technology required to fix Earth's climate. Instead, the entire faction disappeared into the void with the intention of founding a breakaway civilisation.

No Jump vessel has been sighted since the remaining four factions returned to earth and began a process of co-operation which resulted in the formation of the UCTCN. Given the difficult circumstances under which Jump parted company with the rest of humanity, no attempt has been made to contact them since.]]))



european:setGMColor(31, 255, 0)
european:setFriendly(ucn)
european:setFriendly(commonwealth)
european:setFriendly(shanghai)
european:setFriendly(jasa)
european:setEnemy(brutal)
european:setDescription(_([[The European Federation.

The European Federation was the second major faction on Earth to start it's voyage to find a new and habitable world. The European space program was staggeringly well funded, and consequently their ships were remarkably well equipped and armed.

However, the quality of their crews sometimes left a lot to be desired. The European Federation prioritised useful skills for rebuilding civilisation in its lottery, believing that its advanced technology would be enough to deter the other factions from aggression.

On returning to Earth, the European Federation led the way in restoring civilisation in its former territories. Always a vociferous proponent of unification, the EF was highly successful in bringing its former territory to compliance, and the UCTCN headquarters in Geneva sits within former EF territory.

UCN officers drawn from EF territories can generally be assumed to have a strong political alignment with the UCTCN and its aims and objectives.]]))

shanghai:setGMColor(31, 255, 0)
shanghai:setFriendly(ucn)
shanghai:setFriendly(european)
shanghai:setFriendly(commonwealth)
shanghai:setFriendly(jasa)
shanghai:setEnemy(brutal)
shanghai:setDescription(_([[The Shanghai Pact.

The Shanghai Pact was the first major faction to leave Earth during the Exodus - a move that took all the other nations and factions by surprise. The Pact was dominated by The People's Republic of China and the Russian Federation whose somewhat uneasy alliance ensured both civilisation's survival. They were joined by a smattering of other countries, many of whom with a dubious human rights record.

Of the exodus factions, the Pact was the most secretive and insular, trading only where necessary and communicating very little. They were also the most authoritarian - in many ways totalitarian – exodus faction which put significant obstacles in the way of co-operating with the other factions in making the return to earth.

The former territories of the Pact saw some of the worst environmental problems and the most sustained resistance to the returning exodus fleets. Bringing the former Pact territories to compliance has been a difficult and painful task, requiring significant support from the other factions – particularly the Commonwealth. It has only been a decade since the subdual of the Mongolian tyranny allowing for the full compliance of all former Pact territories. 

Since the formation of the UCTCN, the Shanghai Pact has dialled back its authoritarian policies significantly. However, the adoption by the UCTCN of some of the underlying technologies of the Pact’s old Social Credit system to underpin compliance across the globe has caused some controversy – particularly in more rural areas.]]))

commonwealth:setGMColor(31, 255, 0)
commonwealth:setFriendly(ucn)
commonwealth:setEnemy(brutal)
commonwealth:setFriendly(ucn)
commonwealth:setFriendly(european)
commonwealth:setFriendly(shanghai)
commonwealth:setFriendly(jasa)
commonwealth:setDescription(_([[The Commonwealth.

The Commonwealth was one of the major factions that managed to escape Earth in the exodus. It was largely made up of the countries of the old British Commonwealth, although India had long since been the senior partner within the participating countries due to its size and influence.

On returning to earth, the Commonwealth territories proved challenging to bring to full compliance, partly due to their wide distribution across the globe. At its height, Commonwealth territory covered around a third of the surface of the Earth, but its far flung nature made it difficult to govern under the best of circumstances. After the exodus, the political structure than remained on Earth collapsed almost entirely, devolving into a mixture of localised systems which later gave way to civil disruption and unrest and the rise of local warlords. 

The Commonwealth is now largely restored as a founding signatory and major member of the UCTCN, and Commonwealth leadership is strongly supportive of unification, but large parts of the Commonwealth’s far-flung territories are sadly very suspicious of what the UCTCN means for the future of humanity. Re-education campaigns are ongoing. It is for this reason that the UCN recruited a very limited number of officers from the former Commonwealth Stellar Navy in the first instance, even though many CSN ships were retained within the USN due to their superb construction and impressive histories. ]]))


jasa:setGMColor(31, 255, 0)
jasa:setFriendly(ucn)
jasa:setFriendly(european)
jasa:setFriendly(shanghai)
jasa:setFriendly(commonwealth)
jasa:setEnemy(brutal)
jasa:setDescription(_([[JASA.

The Japanese-American Space Alliance was born out of necessity as two formerly titanic economies struggled to come to terms with their inevitable decline. While most other factions were leaving the Earth behind, JASA was still struggling to get its warp drive technology to function fully as intended. Unlike the other factions, JASA itself was not a political or governmental body, merely a colonist fleet with attendant protective vessels.

JASA lagged behind the other factions at every stage, largely due to behind-the-scenes political infighting from its parent nations that dogged the launching of their exodus attempt. This, combined with a substantial brain-drain to the Jump Corporation put JASA on the back foot in humanity's race towards the stars. For most of the outbound journey of the exodus, JASA was out of contact with the other exodus fleets, finally catching up with the others as the technology to revert the climate disaster on Earth was discovered. 

JASA’s fleet was severely depleted on its outbound journey, and returned with only a fraction of the ships and colonists that it set out with. Much of the records of their expedition were also lost. On returning to Earth, JASA found that the political structures of its parent nations had completely collapsed. With help from the other returning factions the former American and Japanese territories were brought to full compliance, and a new governmental structure was created – the Pan-Pacific Alliance – drawing together the former Japanese and American territories along with some former Commonwealth nations and other independent groups that had sprung up since the Exodus. 

The PPA is an enthusiastic member and founder signatory of the UCTCN, and have provided a significant number of recruits to the UCN officer academy.]]))

corsair:setGMColor(201, 0, 95)
corsair:setEnemy(ucn)
corsair:setDescription([[Pirates and Corsairs.

Over time, through mutiny theft and hijacking, a substantial number of vessels have taken to a form of piracy. A lot of these have their origin within the Jump Corporation where desperate men and women facing a life of slavery may choose to risk everything in a dangerous mutiny, but every faction has seen deserters and many of these have banded together into ad-hoc mini-factions resorting to piracy to stay alive.]])