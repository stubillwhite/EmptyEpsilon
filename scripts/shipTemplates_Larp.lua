template = ShipTemplate():setName("Battle docker"):setLocaleName(_("Battle docker")):setClass(_("Corvette"), _("Destroyer")):setModel("battleship_destroyer_1_upgraded"):setType("playership")
template:setDescription(_([[The battle Docker can send drones to explore , fight and support a war field.]]))
template:setDockClasses("Drone")
template:setRadarTrace("radar_dread.png")
template:setHull(100)
template:setCombatManeuver(400, 250)
template:setShields(200, 200, 200, 200)
template:setSpeed(90, 10, 20)
template:setJumpDrive(true)
--                  Arc, Dir, Range, CycleTime, Dmg
template:setBeam(0,100, -20, 1500.0, 6.0, 8)
template:setBeam(1,100,  20, 1500.0, 6.0, 8)
template:setBeam(2,100, 180, 1500.0, 6.0, 8)
variation:setTubes(5, 8.0) -- Amount of torpedo tubes, and loading time of the tubes.
variation:weaponTubeDisallowMissle(0, "Mine"):weaponTubeDisallowMissle(1, "Mine")
variation:weaponTubeDisallowMissle(2, "Mine"):weaponTubeDisallowMissle(3, "Mine")
variation:setTubeDirection(4, 180):setWeaponTubeExclusiveFor(4, "Mine")
variation:setWeaponStorage("Homing", 12)
variation:setWeaponStorage("Nuke", 4)
variation:setWeaponStorage("Mine", 8)
variation:setWeaponStorage("EMP", 6)
template:setTubeDirection(0, -90)
template:setTubeDirection(1, -90)
template:setTubeDirection(2,  90)
template:setTubeDirection(3,  90)
template:setDocks(2, 1, 1, 1, 1, 1)
template:addDrones("L3 Mouse", 1)
template:addDrones("L3 Cat", 1)
template:addDrones("H9 Owl", 1)
template:addDrones("M19 Rino", 1)
template:setTractorBeam(2000, 100)

template:addRoomSystem(1, 0, 2, 1, "Maneuver");
template:addRoomSystem(1, 1, 2, 1, "BeamWeapons");
template:addRoomSystem(2, 2, 2, 1, "Drones");
template:addRoomSystem(0, 3, 1, 2, "RearShield");
template:addRoomSystem(1, 3, 2, 2, "Reactor");
template:addRoomSystem(3, 3, 2, 2, "Warp");
template:addRoomSystem(5, 3, 1, 2, "JumpDrive");
template:addRoom(6, 3, 2, 1);
template:addRoomSystem(6, 4, 2, 1, "Docks");
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
 

