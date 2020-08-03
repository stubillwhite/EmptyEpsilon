-- Name: Larp Test
-- Description: Empty scenario, no enemies, no friendlies. Just to show larp edition of Empty Epsilon
-- Type: Basic

function init()
    
    player = PlayerSpaceship():setFaction("Human Navy"):setTemplate("Battle docker"):setPosition(-10000, 0)
    
    -----------------------------------
    -- ### EE LARP release 1.2-beta ---
    -----------------------------------
    
    -- Position Z for all object to simulate space
    
    -- player:setPositionZ(-500)
    
    station_z = SpaceStation():setPosition(5000, 0):setTemplate('Huge Station'):setFaction("Human Navy"):setPositionZ(500)

    --for n=1,20 do
    --    CpuShip():setFaction("Human Navy"):setTemplate("Adv. Gunship"):setPosition(random(0,10000), random(-10000,10000)):setPositionZ(random(-500,500)):orderRoaming()
    --    CpuShip():setFaction("Kraylor"):setTemplate("Adv. Gunship"):setPosition(random(0,10000), random(-10000,10000)):setPositionZ(random(-500,500)):orderRoaming()
    --end
    
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
