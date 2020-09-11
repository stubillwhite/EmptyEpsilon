-- Name: Larp Test
-- Description: Empty scenario, no enemies, no friendlies. Just to show larp edition of Empty Epsilon
-- Type: Basic

require("ee.lua")

function init()
    
    player = PlayerSpaceship():setFaction("Human Navy"):setTemplate("Ship_Test_Larp"):setPosition(-10000, 0)
    
    -----------------------------------
    ------------ In Progress ----------
    -----------------------------------
    
    -- Personalize name of ship's rooms
    -- During template configuration, can use addRoomTitle to create a zone with a label. This label will be shown in the center of the room. RP only.
    -- See shipTemplate_Larp.lua for an example
    
    -- Change Power Use Factor
    -- Each system use a fixed amount of energy, affected by the power and the efficiency of the system. Here is the default values
    -- SYS_Reactor     -25.0 * 0.08,   (Negative factor seems Reactor produces energy)
    -- SYS_Oxygen        3.0 * 0.08,
    -- SYS_BeamWeapons   3.0 * 0.08,
    -- SYS_MissileSystem 1.0 * 0.08,
    -- SYS_Maneuver      2.0 * 0.08,
    -- SYS_Impulse       4.0 * 0.08,
    -- SYS_Warp          5.0 * 0.08,
    -- SYS_JumpDrive     5.0 * 0.08,
    -- SYS_FrontShield   5.0 * 0.08,
    -- SYS_RearShield    5.0 * 0.08,
    -- SYS_Docks         1.0 * 0.08,
    -- SYS_Drones        3.0 * 0.08,
    -- Factor can be changed by script (example : oxygen don't use energy)
    player:setSystemPowerUseFactor(SYS_OXYGEN, 0.0)

    -- Oxygen system
    -- Ship can have up to 10 oxygen zones (0 to 9), with a level and a max of oxygen (100 by default). You could also choose the discharge_rate_per_second, aka the number of oxygen decrease by second (0.1 by default) independently of another setting. And the recharge_rate_per_second parameter, aka the number of oxygen increase by second (0.1 by default) affected by the efficiency of oxygen system.
    -- Each zone must be set in the template file or in the script file, and can after be changed by tweak.
    player:setOxygenZone(0, "Zone 1", 200.0, 500.0, 0.5, 0.5)
    -- You also need a oxygen generator to access to the oxygen system (false by default)
    player:setOxygenGenerator(true)
    
    -- New main screen radar
    -- Add a far range radar (aka relay screen)
    player:commandMainScreenSetting("farRange")

    -- Template recorded or not in the database
    -- Into the templates configuration files, you can choose to avoid a template from the database. It allow you to configure multiple ship template from a same base (for example with different texture color). Only the base is recorded and the rest is removed from the database.
    
    -- Station and drone recorded in the database
    -- Nothing to do here, just to inform you that stations and drones template are now recorded in the database. Name of the button has changed (ships -> Templates) to keep consistency. This can be changed by translation.
    
    -- Dynamic Factions and Personality
    -- setPersonalityId can modify personality of object and behaviour with another object
    -- 0: Normal (with faction behaviour)
    -- 1: Pacifist (don't attack anyone)
    -- 2: Hostile (attack everybody with another faction)
    -- 3: Solo (attack everybody, except another solo object)
    CpuShip():setFaction("Kraylor"):setTemplate("Adv. Gunship"):setPosition(-10000, 4000):setPersonalityId(1):orderRoaming()
    -- Factions behaviour between themselves can be changed by GM during the game 
    
    -- Logs by station
    -- Logs can now append on several stations. You activate this feature in options.ini with the parameter server_config_logs_by_station. If enabled, logs are only visible in a station if at least one log entry exist for the considered station. Ship logs screen shown all the logs with an indication of the station.
    player:addToShipLog("Start of helm log","white","helms")
    player:addToShipLog("Start of weapons log","white","weapons")
    player:addToShipLog("Start of engineering log","white","engineering")
    player:addToShipLog("Start of science log","white","science")
    player:addToShipLog("Start of relay log","white","relay")

    -----------------------------------
    -- ### EE LARP release 1.3-beta ---
    -----------------------------------
    
    -- Instability for systems
    -- You can active a instability processus for one or many systems. If Instability factor is more than 0, instability is active. Instability Factor must be between 0.0 and 1.0 (float) and is the probability of change of sliders for instability control
    -- Instability Difficulty must be between 0 and 4 (integer), and is the number of slider to control the instability (like the scanning dialog)
    player:setSystemInstabilityFactor("oxygen",0.10):setSystemInstabilityDifficulty("oxygen",3)
    player:setSystemInstabilityFactor("reactor",0.20):setSystemInstabilityDifficulty("reactor",2)
    -- You can personalize label of each slider
    player:setSystemInstabilityLabel("oxygen",1,"thermal expansion")
    player:setSystemInstabilityLabel("oxygen",2,"boiler water")
    player:setSystemInstabilityLabel("oxygen",3,"neutrons")
    
    -- Nano repair system
    -- You can avoid using repair crew into room systems and use instead nano repair crew. nano repair crew works as coolant.
    -- You need to activate in options.ini with server_use_nano_repair_crew
    -- You change the amount of nano repair crew with the same function
    player:setRepairCrewCount(8)
    -- You can change the maximum amount of repair by system with this function (the same for each system)
    player:setMaxRepairPerSystem(4)
    -- It is also possible to active automatic repair
    -- player:commandSetAutoRepair(true):setAutoCoolant(true)
    
    -----------------------------------
    -- ### EE LARP release 1.2-beta ---
    -----------------------------------
    
    -- Position Z for all object to simulate space
    
    -- player:setPositionZ(-500)
    
    station_z = SpaceStation():setPosition(5000, 0):setTemplate('Huge Station'):setFaction("Human Navy"):setPositionZ(500)

    for n=1,20 do
        CpuShip():setFaction("Human Navy"):setTemplate("Adv. Gunship"):setPosition(random(0,10000), random(-10000,10000)):setPositionZ(random(-500,500)):orderRoaming()
        CpuShip():setFaction("Kraylor"):setTemplate("Adv. Gunship"):setPosition(random(0,10000), random(-10000,10000)):setPositionZ(random(-500,500)):orderRoaming()
    end
    
    Nebula():setPosition(5000, 5000):setPositionZ(500)
    Nebula():setPosition(5000, -5000):setPositionZ(-500)
    
    -- Capacity to Change font
    -- You need to change the parameters font_main and font_bold in options.ini
    
    -- Color by faction (in server only)
    -- You need to change the parameter server_config_color_by_faction in options.ini
    -- Once done, ship and station icon will be colored by faction's color (once scanned)
    
    -- Complexity of radar signatures
    -- You need to change the parameter server_config_use_complex_radar_signatures in options.ini
    -- Once done to 0, radar signatures will be easier to understand : Gravity affect red bar, biologic affect green bar, electric affect blue bar
    
    -- Configurable beam damage (0:energy, 1:kinetic, 2:emp or 3:heat)
    -- Create a heat beam
    -- setBeamWeapon (int index, float arc, float direction, float range, float cycle_time, float damage)
    player:setBeamWeapon(0,90, 0  , 1500, 4, 3):setBeamWeaponDamageType(0, 0)
    player:setBeamWeapon(1,90, 90 , 1500, 4, 3):setBeamWeaponDamageType(1, 1)
    player:setBeamWeapon(2,90, 180, 1500, 4, 3):setBeamWeaponDamageType(2, 2)
    player:setBeamWeapon(3,90, 270, 1500, 4, 3):setBeamWeaponDamageType(3, 1)
    -- Color of beams arc can be changed with colors.ini
        
    -----------------------------------
    -- ### EE LARP release 1.1-beta ---
    -----------------------------------
    
    ----
    -- weapons tube and beams specific by station
    ----
    
    -- the Battle docker have 3 beams and 5 tubes weapons. Example here : Beams are used only in station 1, the 2 first tubes are used only in station 2, the last 3 tubes are used only in station 3
    -- If there is noting in options.ini, weapons stations have all beams and tubes. You need to change options.ini to allow this feature.
    player:setBeamWeaponStation(0,1):setBeamWeaponStation(1,1):setBeamWeaponStation(2,1)
    --player:setWeaponTubeStation(0,2):setWeaponTubeStation(1,2)
    --player:setWeaponTubeStation(2,3):setWeaponTubeStation(3,3):setWeaponTubeStation(4,3)
    
    ----
    -- enable waypoints by route
    ----
    
    -- Example of waypoints for many routes
    player:commandAddWaypoint(20000,20000,1):commandAddWaypoint(-20000,-20000,2)
    
    ----
    -- dynamic texture files and texture color by player
    ----
    
    -- Change rgba color of the texture, example here for a dynamic background
    color_r = 1
    color_g = 1
    color_b = 1
    color_a = 1
    player:setTextureColor(color_r, color_g, color_b, color_a)
    
    -- Set the cubebox background (here not necessary, use the default string)
    player:setTexture("StarsFront", "StarsBack", "StarsLeft", "StarsRight", "StarsTop", "StarsBottom")

    ----------------------------------
    -- ### EE LARP release 1.0-beta --
    ----------------------------------
    
    ----
    -- GM access allowed from clients
    ----
    
    -- GM is available from client, with a password
    -- From now, only work with numbers
    setGMControlCode("123456")
    
    ----
    -- Advanced sector system
    ----
    player:setFarRangeRadarRange(100000000)
    addLocalName("0/0","Alpha.sec")
    addLocalName("0/0 1.1","Beta.sec")
    addLocalName("0/0 1.1 C2","Zeta.sec")

    ----
    -- Drones, fighters and docks system
    ----
    
    -- Example of adding a drone
    player:addDrone("L3 Mouse")
    
    -- Tractor Beam
    -- Initial configuration can be into ship template
    -- Can be changed into script
    player:setTractorBeamMax(5000, 100)
    
end

function update(delta)
    --No victory condition
    
    -- dynamic texture files and texture color by player
    color_r = color_r + random(-10, 10) / 100
    color_g = color_g + random(-10, 10) / 100
    color_b = color_b + random(-10, 10) / 100
    color_a = color_a + random(-10, 10) / 100
    player:setTextureColor(color_r, color_g, color_b, color_a)
    
    -- Position Z for all object to simulate space
    -- station_z:setPositionZ(station_z:getPositionZ() + random(-1, 1) )
    
end
