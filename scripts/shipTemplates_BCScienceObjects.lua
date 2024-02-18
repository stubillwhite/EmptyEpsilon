--[[                  New Models
These are Nat's new models
----------------------------------------------------------]]
template = ShipTemplate():setName("Sensor Buoy MKI"):setLocaleName(_("Sensor Buoy MK1")):setModel("sensor-buoy")
template:setRadarTrace("radar_buoy.png")
template:setDescription(_([[Sensor Bouy MKI]]))
template:setHull(70)
template:setShields(40)
template:setHasReactor(false)
template:setShortRangeRadarRange(300)
template:setCanDock(true)
template:setDockClasses("Destroyer")
template:setRecorded(false)

template = ShipTemplate():setName ("Shield Generator"):setLocaleName(_("Shield Generator")):setModel("shield_generator")
template:setRadarTrace("radar_shield.png")
template:setHull(50)
template:setHasReactor(false)
template:setShortRangeRadarRange(300)
template:setCanDock(true)

template = ShipTemplate():setName("Sphere"):setModel("sphere_1"):setType("station")
template:setRadarTrace("radar_turret.png")
template:setHull(90)
template:setSharesEnergyWithDocked(false)
template:setRecorded(false)

template = ShipTemplate():setName("Turret"):setLocaleName(_("Turret")):setModel("artifact3")
template:setRadarTrace("radar_sphere.png")
template:setHull(100)
template:setShields(50)
template:setHasReactor(false)
template:setSpeed(0.0, 0.0, 0.0)
template:setBeamWeapon(0, 360, -15, 800, 2, 10)
template:setRecorded(false)

template = ShipTemplate():setName("Comms Hub"):setLocaleName(_("Comms Hub")):setModel("comm-hub"):setType("station")
template:setRadarTrace("radartrace_smallstation.png")
template:setHull(90)
template:setSharesEnergyWithDocked(false)

template = ShipTemplate():setName("Derelict Station"):setModel("derelict"):setType("station")
template:setRadarTrace("radartrace_smallstation.png")
template:setHull(40)
template:setSharesEnergyWithDocked(false)
template:setRecorded(false)

template = ShipTemplate():setName("Gravitational Anomaly"):setModel("heresy-g"):setType("station")
template:setRadarTrace("radartrace_sphere.png")
template:setHull(500)
template:setSharesEnergyWithDocked(false)
template:setRecorded(false)

template = ShipTemplate():setName("Commonwealth Mining Rig"):setLocaleName(_("EFS Mining Rig")):setModel("kono"):setType("station")
template:setRadarTrace("radartrace_mediumstation.png")
template:setHull(300)
template:setShields(800, 800, 800, 800)
template:setRecorded(false)

template = ShipTemplate():setName("Science Lab"):setLocaleName(_("Science Lab")):setModel("serenity"):setType("station")
template:setRadarTrace("radartrace_smallstation.png")
template:setHull(200)
template:setShields(500, 500, 500, 500)
template:setRecorded(false)

--- WRECKS
--template = ShipTemplate():setName("Cassard Wreck"):setLocaleName("Cassard Wreck"):setModel("wreck-cassard"):setRecorded(false)	--Yellow, Green, Blue, White, Red
--template:setDescription([[The Cassard class Frigate fires salvos of missiles from forward facing tubes but is poorly shielded and under-armoured. It is something of a glass cannon.]])
--template:setRadarTrace("radar_cruiser.png")
--template:setHull(10)
--template:setShields(0, 0)
--template:setSpeed(0, 0, 0)