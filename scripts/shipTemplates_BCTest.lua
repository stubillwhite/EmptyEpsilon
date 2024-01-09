--[[                  OLD ship templates
These are older ship templates, going to be replaced soon.
----------------------------------------------------------]]

--[[ Player ships --]]
template = ShipTemplate():setName("Laser Corvette"):setModel("LaserCorvetteBlue"):setType("playership")
template:setRadarTrace("radar_cruiser.png")
--                  Arc, Dir, Range, CycleTime, Dmg
template:setBeam(0, 90, -15, 1000.0, 6.0, 10)
template:setBeam(1, 90,  15, 1000.0, 6.0, 10)
-- Setup 3 missile tubes. 2 forward at a slight angle, and 1 in the rear exclusive for mines.
template:setTubes(3, 8.0) -- Amount of torpedo tubes, and loading time of the tubes.
template:setTubeDirection(0, -5):weaponTubeDisallowMissle(0, "Mine")
template:setTubeDirection(1, 5):weaponTubeDisallowMissle(1, "Mine")
template:setTubeDirection(2, 180):setWeaponTubeExclusiveFor(2, "Mine")
template:setHull(200)
template:setShields(80, 80)
template:setSpeed(90, 10, 20)
template:setWarpSpeed(0)
template:setJumpDrive(true)
template:setCombatManeuver(400, 250)
template:setWeaponStorage("Homing", 12)
template:setWeaponStorage("Nuke", 4)
template:setWeaponStorage("Mine", 8)
template:setWeaponStorage("EMP", 6)

template:addRoomSystem(1, 0, 2, 1, "Maneuver");
template:addRoomSystem(1, 1, 2, 1, "BeamWeapons");
template:addRoom(2, 2, 2, 1);

template:addRoomSystem(0, 3, 1, 2, "RearShield");
template:addRoomSystem(1, 3, 2, 2, "Reactor");
template:addRoomSystem(3, 3, 2, 2, "Warp");
template:addRoomSystem(5, 3, 1, 2, "JumpDrive");
template:addRoom(6, 3, 2, 1);
template:addRoom(6, 4, 2, 1);
template:addRoomSystem(8, 3, 1, 2, "FrontShield");

template:addRoom(2, 5, 2, 1);
template:addRoomSystem(1, 6, 2, 1, "MissileSystem");
template:addRoomSystem(1, 7, 2, 1, "Impulse");

template:addDoor(1, 1, true);
template:addDoor(2, 2, true);
template:addDoor(3, 3, true);
template:addDoor(1, 3, false);
template:addDoor(3, 4, false);
template:addDoor(3, 5, true);
template:addDoor(2, 6, true);
template:addDoor(1, 7, true);
template:addDoor(5, 3, false);
template:addDoor(6, 3, false);
template:addDoor(6, 4, false);
template:addDoor(8, 3, false);
template:addDoor(8, 4, false);
 
 
----------------------Ktlitan ships
template = ShipTemplate():setName("Jump Corporation Frigate"):setModel("LightCorvetteGrey")
template:setRadarTrace("radar_ktlitan_fighter.png")
template:setBeam(0, 60, 0, 1200.0, 4.0, 6)
template:setHull(70)
template:setSpeed(140, 30, 25)
template:setDefaultAI('fighter')	-- set fighter AI, which dives at the enemy, and then flies off, doing attack runs instead of "hanging in your face".

template = ShipTemplate():setName("Jump Corporation Destroyer"):setModel("MultiGunCorvetteGrey")
template:setRadarTrace("radar_ktlitan_breaker.png")
template:setBeam(0, 40, 0, 800.0, 4.0, 6)
template:setBeam(1, 35,-15, 800.0, 4.0, 6)
template:setBeam(2, 35, 15, 800.0, 4.0, 6)
template:setTubes(1, 13.0) -- Amount of torpedo tubes, loading time
template:setWeaponStorage("HVLI", 5) --Only give this ship HVLI's
template:setHull(120)
template:setSpeed(100, 5, 25)

template = ShipTemplate():setName("Jump Corporation Cruiser"):setModel("LaserCorvetteGrey")
template:setRadarTrace("radar_ktlitan_worker.png")
template:setBeam(0, 40, -90, 600.0, 4.0, 6)
template:setBeam(1, 40, 90, 600.0, 4.0, 6)
template:setHull(50)
template:setSpeed(100, 35, 25)

template = ShipTemplate():setName("Jump Corporation Battleship"):setModel("HeavyCorvetteGrey")
template:setRadarTrace("radar_ktlitan_worker.png")
template:setBeam(0, 40, -90, 600.0, 4.0, 6)
template:setBeam(1, 40, 90, 600.0, 4.0, 6)
template:setHull(50)
template:setSpeed(100, 35, 25)

template = ShipTemplate():setName("Jump Corporation Tug"):setModel("MineLayerCorvetteGrey")
template:setRadarTrace("radar_ktlitan_worker.png")
template:setBeam(0, 40, -90, 600.0, 4.0, 6)
template:setBeam(1, 40, 90, 600.0, 4.0, 6)
template:setHull(50)
template:setSpeed(100, 35, 25)

template = ShipTemplate():setName("EF Frigate"):setModel("battleship_destroyer_4_upgraded")
template:setRadarTrace("radar_ktlitan_worker.png")
template:setBeam(0, 40, -90, 600.0, 4.0, 6)
template:setBeam(1, 40, 90, 600.0, 4.0, 6)
template:setHull(50)
template:setSpeed(100, 35, 25)

template = ShipTemplate():setName("EF Destroyer"):setModel("battleship_destroyer_5_upgraded")
template:setRadarTrace("radar_ktlitan_drone.png")
template:setBeam(0, 40, 0, 600.0, 4.0, 6)
template:setHull(30)
template:setSpeed(120, 10, 25)

template = ShipTemplate():setName("EF Cruiser"):setModel("battleship_destroyer_1_upgraded")
template:setRadarTrace("radar_ktlitan_feeder.png")
template:setBeam(0, 20, 0, 800.0, 4.0, 6)
template:setBeam(1, 35,-15, 600.0, 4.0, 6)
template:setBeam(2, 35, 15, 600.0, 4.0, 6)
template:setBeam(3, 20,-25, 600.0, 4.0, 6)
template:setBeam(4, 20, 25, 600.0, 4.0, 6)
template:setHull(150)
template:setSpeed(120, 8, 25)

template = ShipTemplate():setName("EF Battleship"):setModel("battleship_destroyer_3_upgraded")
template:setRadarTrace("radar_ktlitan_scout.png")
template:setBeam(0, 40, 0, 600.0, 4.0, 6)
template:setHull(100)
template:setSpeed(150, 30, 25)

template = ShipTemplate():setName("EF Destroyer Variant"):setModel("battleship_destroyer_2_upgraded")
template:setRadarTrace("radar_ktlitan_destroyer.png")
template:setBeam(0, 90, -15, 1000.0, 6.0, 10)
template:setBeam(1, 90,  15, 1000.0, 6.0, 10)
template:setHull(300)
template:setShields(50, 50, 50)
template:setTubes(3, 15.0) -- Amount of torpedo tubes
template:setSpeed(70, 5, 10)
template:setWeaponStorage("Homing", 25)
template:setDefaultAI('missilevolley')

template = ShipTemplate():setName("Shanghai Pact Frigate"):setModel("small_frigate_3")
template:setRadarTrace("radar_ktlitan_queen.png")
template:setHull(350)
template:setShields(100, 100, 100)
template:setTubes(2, 15.0) -- Amount of torpedo tubes
template:setWeaponStorage("Nuke", 5)
template:setWeaponStorage("EMP", 5)
template:setWeaponStorage("Homing", 5)

template = ShipTemplate():setName("Shanghai Pact Destroyer"):setModel("small_frigate_4")
template:setRadarTrace("radar_ktlitan_queen.png")
template:setHull(350)
template:setShields(100, 100, 100)
template:setTubes(2, 15.0) -- Amount of torpedo tubes
template:setWeaponStorage("Nuke", 5)
template:setWeaponStorage("EMP", 5)
template:setWeaponStorage("Homing", 5)

template = ShipTemplate():setName("Shanghai Pact Cruiser"):setModel("small_frigate_5")
template:setRadarTrace("radar_ktlitan_queen.png")
template:setHull(350)
template:setShields(100, 100, 100)
template:setTubes(2, 15.0) -- Amount of torpedo tubes
template:setWeaponStorage("Nuke", 5)
template:setWeaponStorage("EMP", 5)
template:setWeaponStorage("Homing", 5)

template = ShipTemplate():setName("Shanghai Pact Battleship"):setModel("small_frigate_2")
template:setRadarTrace("radar_ktlitan_queen.png")
template:setHull(350)
template:setShields(100, 100, 100)
template:setTubes(2, 15.0) -- Amount of torpedo tubes
template:setWeaponStorage("Nuke", 5)
template:setWeaponStorage("EMP", 5)
template:setWeaponStorage("Homing", 5)

template = ShipTemplate():setName("Shanghai Pact Destroyer Variant"):setModel("small_frigate_1")
template:setRadarTrace("radar_ktlitan_queen.png")
template:setHull(350)
template:setShields(100, 100, 100)
template:setTubes(2, 15.0) -- Amount of torpedo tubes
template:setWeaponStorage("Nuke", 5)
template:setWeaponStorage("EMP", 5)
template:setWeaponStorage("Homing", 5)

template = ShipTemplate():setName("Jump Corp Frigate"):setModel("space_tug")
template:setRadarTrace("radar_ktlitan_queen.png")
template:setHull(350)
template:setShields(100, 100, 100)
template:setTubes(2, 15.0) -- Amount of torpedo tubes
template:setWeaponStorage("Nuke", 5)
template:setWeaponStorage("EMP", 5)
template:setWeaponStorage("Homing", 5)

template = ShipTemplate():setName("Jump Corp Cruiser"):setModel("space_cruiser_4")
template:setRadarTrace("radar_ktlitan_queen.png")
template:setHull(350)
template:setShields(100, 100, 100)
template:setTubes(2, 15.0) -- Amount of torpedo tubes
template:setWeaponStorage("Nuke", 5)
template:setWeaponStorage("EMP", 5)
template:setWeaponStorage("Homing", 5)

template = ShipTemplate():setName("JASA Frigate"):setModel("space_frigate_6")
template:setRadarTrace("radar_ktlitan_queen.png")
template:setHull(350)
template:setShields(100, 100, 100)
template:setTubes(2, 15.0) -- Amount of torpedo tubes
template:setWeaponStorage("Nuke", 5)
template:setWeaponStorage("EMP", 5)
template:setWeaponStorage("Homing", 5)

template = ShipTemplate():setName("Rando Cruiser"):setModel("dark_fighter_6")
template:setRadarTrace("radar_ktlitan_queen.png")
template:setHull(350)
template:setShields(100, 100, 100)
template:setTubes(2, 15.0) -- Amount of torpedo tubes
template:setWeaponStorage("Nuke", 5)
template:setWeaponStorage("EMP", 5)
template:setWeaponStorage("Homing", 5)

template = ShipTemplate():setName("Rando Frigate"):setModel("small_fighter_1")
template:setRadarTrace("radar_ktlitan_queen.png")
template:setHull(350)
template:setShields(100, 100, 100)
template:setTubes(2, 15.0) -- Amount of torpedo tubes
template:setWeaponStorage("Nuke", 5)
template:setWeaponStorage("EMP", 5)
template:setWeaponStorage("Homing", 5)

template = ShipTemplate():setName("Commonwealth Frigate"):setModel("WespeScoutBlue")
template:setRadarTrace("radar_ktlitan_queen.png")
template:setHull(350)
template:setShields(100, 100, 100)
template:setTubes(2, 15.0) -- Amount of torpedo tubes
template:setWeaponStorage("Nuke", 5)
template:setWeaponStorage("EMP", 5)
template:setWeaponStorage("Homing", 5)

template = ShipTemplate():setName("Missile Corvette"):setModel("MissileCorvetteBlue")
template:setRadarTrace("radar_ktlitan_queen.png")
template:setHull(350)
template:setShields(100, 100, 100)
template:setTubes(2, 15.0) -- Amount of torpedo tubes
template:setWeaponStorage("Nuke", 5)
template:setWeaponStorage("EMP", 5)
template:setWeaponStorage("Homing", 5)

template = ShipTemplate():setName("Commonwealth Destroyer"):setModel("LindwurmFighterBlue")
template:setRadarTrace("radar_ktlitan_queen.png")
template:setHull(350)
template:setShields(100, 100, 100)
template:setTubes(2, 15.0) -- Amount of torpedo tubes
template:setWeaponStorage("Nuke", 5)
template:setWeaponStorage("EMP", 5)
template:setWeaponStorage("Homing", 5)

template = ShipTemplate():setName("Commonwealth Battleship"):setModel("AtlasHeavyFighterBlue")
template:setRadarTrace("radar_ktlitan_queen.png")
template:setHull(350)
template:setShields(100, 100, 100)
template:setTubes(2, 15.0) -- Amount of torpedo tubes
template:setWeaponStorage("Nuke", 5)
template:setWeaponStorage("EMP", 5)
template:setWeaponStorage("Homing", 5)

template = ShipTemplate():setName("Commonwealth Cruiser"):setModel("AdlerLongRangeScoutBlue")
template:setRadarTrace("radar_ktlitan_queen.png")
template:setHull(350)
template:setShields(100, 100, 100)
template:setTubes(2, 15.0) -- Amount of torpedo tubes
template:setWeaponStorage("Nuke", 5)
template:setWeaponStorage("EMP", 5)
template:setWeaponStorage("Homing", 5)

template = ShipTemplate():setName("AdlerLongRangeScoutRed"):setModel("AdlerLongRangeScoutRed")
template:setRadarTrace("radar_ktlitan_queen.png")
template:setHull(350)
template:setShields(100, 100, 100)
template:setTubes(2, 15.0) -- Amount of torpedo tubes
template:setWeaponStorage("Nuke", 5)
template:setWeaponStorage("EMP", 5)
template:setWeaponStorage("Homing", 5)

template = ShipTemplate():setName("AdlerLongRangeScoutGrey"):setModel("AdlerLongRangeScoutGrey")
template:setRadarTrace("radar_ktlitan_queen.png")
template:setHull(350)
template:setShields(100, 100, 100)
template:setTubes(2, 15.0) -- Amount of torpedo tubes
template:setWeaponStorage("Nuke", 5)
template:setWeaponStorage("EMP", 5)
template:setWeaponStorage("Homing", 5)

template = ShipTemplate():setName("AdlerLongRangeScoutGreen"):setModel("AdlerLongRangeScoutGreen")
template:setRadarTrace("radar_ktlitan_queen.png")
template:setHull(350)
template:setShields(100, 100, 100)
template:setTubes(2, 15.0) -- Amount of torpedo tubes
template:setWeaponStorage("Nuke", 5)
template:setWeaponStorage("EMP", 5)
template:setWeaponStorage("Homing", 5)

template = ShipTemplate():setName("AdlerLongRangeScoutWhite"):setModel("AdlerLongRangeScoutWhite")
template:setRadarTrace("radar_ktlitan_queen.png")
template:setHull(350)
template:setShields(100, 100, 100)
template:setTubes(2, 15.0) -- Amount of torpedo tubes
template:setWeaponStorage("Nuke", 5)
template:setWeaponStorage("EMP", 5)
template:setWeaponStorage("Homing", 5)

template = ShipTemplate():setName("AdlerLongRangeScoutYellow"):setModel("AdlerLongRangeScoutYellow")
template:setRadarTrace("radar_ktlitan_queen.png")
template:setHull(350)
template:setShields(100, 100, 100)
template:setTubes(2, 15.0) -- Amount of torpedo tubes
template:setWeaponStorage("Nuke", 5)
template:setWeaponStorage("EMP", 5)
template:setWeaponStorage("Homing", 5)

template = ShipTemplate():setName("Sensor Buoy Mk1"):setModel("SensorBuoyMKI")
template:setRadarTrace("radar_ktlitan_queen.png")
template:setHull(350)
template:setShields(100, 100, 100)
template:setTubes(2, 15.0) -- Amount of torpedo tubes
template:setWeaponStorage("Nuke", 5)
template:setWeaponStorage("EMP", 5)
template:setWeaponStorage("Homing", 5)

template = ShipTemplate():setName("Sensor Buoy Mk2"):setModel("SensorBuoyMKII")
template:setRadarTrace("radar_ktlitan_queen.png")
template:setHull(350)
template:setShields(100, 100, 100)
template:setTubes(2, 15.0) -- Amount of torpedo tubes
template:setWeaponStorage("Nuke", 5)
template:setWeaponStorage("EMP", 5)
template:setWeaponStorage("Homing", 5)


template = ShipTemplate():setName("Sensor Buoy Mk3"):setModel("SensorBuoyMKIII")
template:setRadarTrace("radar_ktlitan_queen.png")
template:setHull(350)
template:setShields(100, 100, 100)
template:setTubes(2, 15.0) -- Amount of torpedo tubes
template:setWeaponStorage("Nuke", 5)
template:setWeaponStorage("EMP", 5)
template:setWeaponStorage("Homing", 5)




for type=1,5 do
    for cnt=1,5 do
        template = ShipTemplate():setName("Transport" .. type .. "x" .. cnt):setModel("transport_" .. type .. "_" .. cnt)
        template:setHull(100)
        template:setShields(50, 50)
        template:setSpeed(60 - 5 * cnt, 6, 10)
        template:setRadarTrace("radar_transport.png")
    end
end
