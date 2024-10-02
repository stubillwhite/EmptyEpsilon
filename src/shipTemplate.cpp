#include <i18n.h>
#include "shipTemplate.h"
#include "spaceObjects/spaceObject.h"
#include "mesh.h"

#include "scriptInterface.h"

/// ShipTemplates are created when EmptyEpsilon is started.
/// And used to fill the ship starting statistics, and other information.
REGISTER_SCRIPT_CLASS(ShipTemplate)
{
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setName);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setLocaleName);
    /// Set the class name, and subclass name for the ship. Used to divide ships into different classes.
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setClass);
    /// Set is the ShipTemplate is recorded in the database, true by default
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setRecorded);
    /// Check if the ShipTemplate is recorded in the database
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, getRecorded);
    /// Set the description shown for this ship in the science database.
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setDescription);
    /// Sets the type of template. Defaults to normal ships, so then it does not need to be set.
    /// Example: template:setType("ship"), template:setType("playership"), template:setType("station")
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setType);
    /// Set the default AI behaviour. EE has 3 types of AI coded into the game right now: "default", "fighter", "missilevolley"
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setDefaultAI);
    /// Set the 3D model to be used for this template. The model referers to data set in the model_data.lua file.
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setModel);
    /// Supply a list of ship classes that can be docked to this ship. setDockClasses("Starfighter") will allow all small starfighter type ships to dock with this ship.
    /// (Same as setExternalDockClasses)
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setDockClasses);
    /// Supply a list of ship classes that can be docked to this ship. setExternalDockClasses("Starfighter") will allow all small starfighter type ships to dock with this ship.
    /// External docking will keep the ship attached to the side of this ship.
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setExternalDockClasses);
    /// Supply a list of ship classes that can be docked to this ship. setInternalDockClasses("Starfighter") will allow all small starfighter type ships to dock with this ship.
    /// Internal docking will hide the docked ship inside the other ship.
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setInternalDockClasses);
    /// Set the amount of energy available for this ship. Note that only player ships use energy. So setting this for anything else is useless.
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setEnergyStorage);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setRepairCrewCount);
    /// Setup a beam weapon.
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setBeam);
    /// Setup a beam weapon.
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setBeamWeapon);
    /// Set the tractor beam
    /// Requires the range of the beam and the drag par second
    /// Example : obj:setTractorBeam(2000,100)
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setTractorBeam);
    /// Set a beam weapon's damage type.
    /// Requires an integer index and an integer damage type.
    /// 0 = Energy, 1 = Kinetic,  2 = EMP, 3 = Heat
    /// Example: obj:setBeamWEaponDamageType(0, 2)
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setBeamWeaponDamageType);
    /// Setup a beam's turret.
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setBeamWeaponTurret);
    /// Setup a beam weapon texture
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setBeamTexture);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setBeamWeaponEnergyPerFire);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setBeamWeaponHeatPerFire);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setBeamStation);

    /// Set the amount of missile tubes, limited to a maximum of 16.
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setTubes);
    /// set the amount of docks (launcher, energy)
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setDocks);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setTubeLoadTime);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, weaponTubeAllowMissle);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, weaponTubeDisallowMissle);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setWeaponTubeExclusiveFor);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setTubeDirection);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setTubeSize);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setTubeStation);
    /// add beams button to weapon specific station
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setBeamsButtonStation);
    /// ditto for shields
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setShieldsStation);
    /// ditto for lock button
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setLockButtonStation);

    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setHasReactor);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setHasOxygenGenerator);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setOxygenZone);

    /// Set the amount of starting hull
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setHull);
    /// Set the shield levels, amount of parameters defines the amount of shields. (Up to a maximum of 8 shields)
    /// Example: setShieldData(400) setShieldData(100, 80) setShieldData(100, 50, 50)
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setShields);
    /// Set the impulse speed, rotation speed and impulse acceleration for this ship.
    /// Compare SpaceShip:setImpulseMaxSpeed, :setRotationMaxSpeed, :setAcceleration.
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setSpeed);
    /// Sets the combat maneuver power of this ship.
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setCombatManeuver);
    /// Set the warp speed for warp level 1 for this ship. Setting this will indicate that this ship has a warpdrive. (normal value is 1000)
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setWarpSpeed);
    /// Set if this ship shares energy with docked ships. Example: template:setSharesEnergyWithDocked(false)
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setSharesEnergyWithDocked);
    /// Set if this ship repairs docked ships. Example: template:setRepairDocked(false)
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setRepairDocked);
    /// Set if this ship restocks scan probes on docked ships. Example: template:setRestocksScanProbes(false)
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setRestocksScanProbes);
    /// Set if this ship restores missiles on docked cpuships. Example template:setRestocksMissilesDocked(false)
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setRestocksMissilesDocked);
    /// Set if this ship has a jump drive. Example: template:setJumpDrive(true)
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setJumpDrive);
    /// Set this ship's minimum and maximum jump drive distances.
    /// Example: template:setJumpDrive(5000.0, 50000.0)
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setJumpDriveRange);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setCloaking);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setWeaponStorage);
    /// Add an empty room to a ship template.
    /// Rooms are shown on the engineering and damcon screens.
    /// If a system room isn't accessible via other rooms connected by doors, that system
    /// might not be repairable.
    /// Rooms are placed on an integer x/y grid. The minimum size for a room is 1x1.
    /// Accepts four parameters: the room's x coordinate, y coordinate, width, and height.
    /// Example: template:addRoom(1, 2, 3, 4)
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, addRoom);
    /// Add a room containing a ship system to a ship template.
    /// Rooms are shown on the engineering and damcon screens.
    /// If a system doesn't have a room, or repair crews can't reach a system's room, it
    /// might not be repairable.
    /// Accepts five parameters: the room's x coordinate, y coordinate, width, height, and
    /// the ship system as the string equivalent of an ESystem value.
    /// Example: template:addRoomSystem(1, 2, 3, 4, "Reactor")
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, addRoomSystem);
    /// Add a room containing a title to a ship template.
    /// Rooms are shown on the engineering and damcon screens.
    /// If a system doesn't have a room, or repair crews can't reach a system's room, it
    /// might not be repairable.
    /// Accepts five parameters: the room's x coordinate, y coordinate, width, height, and
    /// the ship system as the string equivalent of an ESystem value.
    /// Example: template:addRoomSystem(1, 2, 3, 4, "Reactor")
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, addRoomTitle);
    /// Add a door between rooms in a ship template.
    /// Rooms are shown on the engineering and damcon screens.
    /// If a system room doesn't have a door connecting it to other rooms, repair crews
    /// might not be able to reach it for repairs.
    /// Accepts three parameters: the door's x coordinate, y coordinate, and a Boolean
    /// value for whether it's horizontal (true) or vertical (false).
    /// Example: template:addDoor(2, 2, false)
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, addDoor);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, addDrones);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setIsShipCargo);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setRadarTrace);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setFarRangeRadarRange);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setLongRangeRadarRange);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setShortRangeRadarRange);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setImpulseSoundFile);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setCanScan);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setCanHack);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setCanDock);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setCanCombatManeuver);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setCanSelfDestruct);
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, setCanLaunchProbe);
    /// Return a new template with the given name, which is an exact copy of this template.
    /// Used to make easy variations of templates.
    REGISTER_SCRIPT_CLASS_FUNCTION(ShipTemplate, copy);
}

std::unordered_map<string, P<ShipTemplate> > ShipTemplate::templateMap;

ShipTemplate::ShipTemplate()
{
    if (game_server) { LOG(ERROR) << "ShipTemplate objects can not be created during a scenario."; destroy(); return; }

    type = Ship;
    class_name = tr("No class");
    sub_class_name = tr("No sub-class");
    recorded = true;
    shares_energy_with_docked = true;
    repair_docked = false;
    restocks_scan_probes = false;
    restocks_missiles_docked = false;
    energy_storage_amount = 1000;
    repair_crew_count = 3;
    weapon_tube_count = 0;
    for(int n=0; n<max_weapon_tubes; n++)
    {
        weapon_tube[n].load_time = 8.0;
        weapon_tube[n].type_allowed_mask = (1 << MW_Count) - 1;
        weapon_tube[n].direction = 0;
        weapon_tube[n].size = MS_Medium;
        weapon_tube[n].station = 0;
    }
    hull = 70;
    shield_count = 0;
    for(int n=0; n<max_shield_count; n++)
        shield_level[n] = 0.0;
    impulse_speed = 500.0;
    impulse_acceleration = 20.0;
    turn_speed = 10.0;
    combat_maneuver_boost_speed = 0.0f;
    combat_maneuver_strafe_speed = 0.0f;
    warp_speed = 0.0;
    has_jump_drive = false;
    jump_drive_min_distance = 5000.0;
    jump_drive_max_distance = 50000.0;
    has_cloaking = false;
    for(int n=0; n<MW_Count; n++)
        weapon_storage[n] = 0;
    radar_trace = "RadarArrow.png";
    impulse_sound_file = "sfx/engine.wav";
    has_reactor = true;
    has_oxygen_generator = false;
    for(int n=0; n<10; n++)
    {
        oxygen_zones[n].label = "";
        oxygen_zones[n].oxygen_level = 0;
        oxygen_zones[n].oxygen_max = 0;
        oxygen_zones[n].recharge_rate_per_second = 0.1f;
        oxygen_zones[n].discharge_rate_per_second = 0.1f;
    }
    launcher_dock_count = 0;
    energy_dock_count = 0;
    weapons_dock_count = 0;
    thermic_dock_count = 0;
    repair_dock_count = 0;
    stock_dock_count = 0;
    isShipCargo = false;
}

void ShipTemplate::setTubes(int amount, float load_time)
{
    weapon_tube_count = std::min(max_weapon_tubes, amount);
    for(int n=0; n<max_weapon_tubes; n++)
        weapon_tube[n].load_time = load_time;
}

void ShipTemplate::setTubeLoadTime(int index, float load_time)
{
    if (index < 0 || index >= max_weapon_tubes)
        return;
    weapon_tube[index].load_time = load_time;
}

void ShipTemplate::weaponTubeAllowMissle(int index, EMissileWeapons type)
{
    if (index < 0 || index >= max_weapon_tubes)
        return;
    weapon_tube[index].type_allowed_mask |= (1 << type);
}

void ShipTemplate::weaponTubeDisallowMissle(int index, EMissileWeapons type)
{
    if (index < 0 || index >= max_weapon_tubes)
        return;
    weapon_tube[index].type_allowed_mask &=~(1 << type);
}

void ShipTemplate::setWeaponTubeExclusiveFor(int index, EMissileWeapons type)
{
    if (index < 0 || index >= max_weapon_tubes)
        return;
    weapon_tube[index].type_allowed_mask = (1 << type);
}

void ShipTemplate::setTubeDirection(int index, float direction)
{
    if (index < 0 || index >= max_weapon_tubes)
        return;
    weapon_tube[index].direction = direction;
}

void ShipTemplate::setTubeSize(int index, EMissileSizes size)
{
    if (index < 0 || index >= max_weapon_tubes)
        return;
    weapon_tube[index].size = size;
}

void ShipTemplate::setTubeStation(int index, int station)
{
    LOG(INFO) << "-- NatDebugTubes - setTubeStation(" << index << ", " << station << ")";

    if (index < 0 || index >= 10)
        return;
    weapon_tube[index].station = station;
}
// cloney clone
void ShipTemplate::setBeamsButtonStation(int station)
{
    LOG(INFO) << "-- NatDebug - setBeamsButtonStation(" << station << ")";
    beams_button_station = station;
}

// cloney clone x 2
void ShipTemplate::setShieldsStation(int station)
{
    shields_station = station;
}

// cloney clone x 3
void ShipTemplate::setLockButtonStation(int station)
{
    lock_button_station = station;
}


void ShipTemplate::setType(TemplateType type)
{
    if (radar_trace == "RadarArrow.png" && type == Station)
    {
        radar_trace = "RadarBlip.png";
    }
    if (type == Station)
        repair_docked = true;
    if (type == Drone)
        isShipCargo = true;
    this->type = type;
}

void ShipTemplate::setName(string name)
{
    if (templateMap.find(name) != templateMap.end())
    {
        LOG(ERROR) << "Duplicate ship template definition: " << name;
    }

    templateMap[name] = this;
    if (name.startswith("Player "))
        name = name.substr(7);
    this->name = name;
    if (this->locale_name == "")
        this->locale_name = name;
}

void ShipTemplate::setLocaleName(string name)
{
    this->locale_name = name;
}

void ShipTemplate::setClass(string class_name, string sub_class_name)
{
    this->class_name = class_name;
    this->sub_class_name = sub_class_name;
}

void ShipTemplate::setBeam(int index, float arc, float direction, float range, float cycle_time, float damage)
{
    setBeamWeapon(index, arc, direction, range, cycle_time, damage);
}

void ShipTemplate::setBeamWeapon(int index, float arc, float direction, float range, float cycle_time, float damage)
{
    if (index < 0 || index > max_beam_weapons)
        return;
    beams[index].setDirection(direction);
    beams[index].setArc(arc);
    beams[index].setRange(range);
    beams[index].setCycleTime(cycle_time);
    beams[index].setDamage(damage);
}

void ShipTemplate::setTractorBeam(float max_range, float drag_per_second)
{
    tractor_beam.setMaxRange(max_range);
    tractor_beam.setDragPerSecond(drag_per_second);
}

void ShipTemplate::setBeamWeaponDamageType(int index, int damage_type)
{
    if (index < 0 || index > max_beam_weapons)
        return;
    if (damage_type < 0 || damage_type > DT_Count)
        beams[index].setDamageType(0);
    else
        beams[index].setDamageType(damage_type);
}

void ShipTemplate::setBeamWeaponTurret(int index, float arc, float direction, float rotation_rate)
{
    if (index < 0 || index > max_beam_weapons)
        return;
    beams[index].setTurretArc(arc);
    beams[index].setTurretDirection(direction);
    beams[index].setTurretRotationRate(rotation_rate);
}

void ShipTemplate::setBeamTexture(int index, string texture)

{
    if (index >= 0 && index < max_beam_weapons)
    {
        beams[index].setBeamTexture(texture);
    }
}

void ShipTemplate::setBeamStation(int index, int station)
{
    if (index < 0 || index >= 10)
        return;
    beams[index].setStation(station);
}

sf::Vector2i ShipTemplate::interiorSize()
{
    sf::Vector2i min_pos(1000, 1000);
    sf::Vector2i max_pos(0, 0);
    for(unsigned int n=0; n<rooms.size(); n++)
    {
        min_pos.x = std::min(min_pos.x, rooms[n].position.x);
        min_pos.y = std::min(min_pos.y, rooms[n].position.y);
        max_pos.x = std::max(max_pos.x, rooms[n].position.x + rooms[n].size.x);
        max_pos.y = std::max(max_pos.y, rooms[n].position.y + rooms[n].size.y);
    }
    if (min_pos != sf::Vector2i(1, 1))
    {
        sf::Vector2i offset = sf::Vector2i(1, 1) - min_pos;
        for(unsigned int n=0; n<rooms.size(); n++)
            rooms[n].position += offset;
        for(unsigned int n=0; n<doors.size(); n++)
            doors[n].position += offset;
        max_pos += offset;
    }
    max_pos += sf::Vector2i(1, 1);
    return max_pos;
}

ESystem ShipTemplate::getSystemAtRoom(sf::Vector2i position)
{
    for(unsigned int n=0; n<rooms.size(); n++)
    {
        if (rooms[n].position.x <= position.x && rooms[n].position.x + rooms[n].size.x > position.x && rooms[n].position.y <= position.y && rooms[n].position.y + rooms[n].size.y > position.y)
            return rooms[n].system;
    }
    return SYS_None;
}

void ShipTemplate::setCollisionData(P<SpaceObject> object)
{
    model_data->setCollisionData(object);
}

void ShipTemplate::setShields(std::vector<float> values)
{
    shield_count = std::min(max_shield_count, int(values.size()));
    for(int n=0; n<shield_count; n++)
    {
        shield_level[n] = values[n];
    }
}


P<ShipTemplate> ShipTemplate::getTemplate(string name)
{
    if (templateMap.find(name) == templateMap.end())
    {
        LOG(ERROR) << "Failed to find ship template: " << name;
        return nullptr;
    }
    return templateMap[name];
}

std::vector<string> ShipTemplate::getAllTemplateNames()
{
    std::vector<string> ret;
    for(std::unordered_map<string, P<ShipTemplate> >::iterator i = templateMap.begin(); i != templateMap.end(); i++)
        ret.push_back(i->first);
    return ret;
}

std::vector<string> ShipTemplate::getTemplateNameList(TemplateType type)
{
    std::vector<string> ret;
    for(std::unordered_map<string, P<ShipTemplate> >::iterator i = templateMap.begin(); i != templateMap.end(); i++)
        if (i->second->getType() == type)
            ret.push_back(i->first);
    return ret;
}

string getSystemName(ESystem system)
{
    switch(system)
    {
    case SYS_Reactor: return "Reactor";
    case SYS_Oxygen: return "Oxygen";
    case SYS_BeamWeapons: return "Beam Weapons";
    case SYS_MissileSystem: return "Missile System";
    case SYS_Maneuver: return "Maneuvering";
    case SYS_Impulse: return "Impulse Engines";
    case SYS_Warp: return "Warp Drive";
    case SYS_JumpDrive: return "Jump Drive";
    case SYS_FrontShield: return "Front Shield Generator";
    case SYS_RearShield: return "Rear Shield Generator";
    case SYS_Docks: return "Cargo Docks";
    case SYS_Scanner: return "Scanner";
    default:
        return "UNKNOWN";
    }
}

string getLocaleSystemName(ESystem system)
{
    switch(system)
    {
    case SYS_Reactor: return tr("system", "Reactor");
    case SYS_Oxygen: return tr("system", "Oxygen");
    case SYS_BeamWeapons: return tr("system", "Beam Weapons");
    case SYS_MissileSystem: return tr("system", "Missile System");
    case SYS_Maneuver: return tr("system", "Maneuvering");
    case SYS_Impulse: return tr("system", "Impulse Engines");
    case SYS_Warp: return tr("system", "Warp Drive");
    case SYS_JumpDrive: return tr("system", "Jump Drive");
    case SYS_FrontShield: return tr("system", "Front Shield Generator");
    case SYS_RearShield: return tr("system", "Rear Shield Generator");
    case SYS_Docks: return tr("system", "Cargo Docks");
    case SYS_Scanner: return tr("system", "Scanner");
    default:
        return "UNKNOWN";
    }
}

void ShipTemplate::setDescription(string description)
{
    this->description = description;
}

void ShipTemplate::setModel(string model_name)
{
    this->model_data = ModelData::getModel(model_name);
}

void ShipTemplate::setDefaultAI(string default_ai_name)
{
    this->default_ai_name = default_ai_name;
}

void ShipTemplate::setDockClasses(std::vector<string> classes)
{
    external_dock_classes = std::unordered_set<string>(classes.begin(), classes.end());
}

void ShipTemplate::setExternalDockClasses(const std::vector<string> classes)
{
    external_dock_classes = std::unordered_set<string>(classes.begin(), classes.end());
}

void ShipTemplate::setInternalDockClasses(const std::vector<string> classes)
{
    internal_dock_classes = std::unordered_set<string>(classes.begin(), classes.end());
}

void ShipTemplate::setSpeed(float impulse, float turn, float acceleration)
{
    impulse_speed = impulse;
    turn_speed = turn;
    impulse_acceleration = acceleration;
}

void ShipTemplate::setCombatManeuver(float boost, float strafe)
{
    combat_maneuver_boost_speed = boost;
    combat_maneuver_strafe_speed = strafe;
}

void ShipTemplate::setWarpSpeed(float warp)
{
    warp_speed = warp;
}

void ShipTemplate::setSharesEnergyWithDocked(bool enabled)
{
    shares_energy_with_docked = enabled;
}

void ShipTemplate::setRepairDocked(bool enabled)
{
    repair_docked = enabled;
}

void ShipTemplate::setRestocksScanProbes(bool enabled)
{
    restocks_scan_probes = enabled;
}

void ShipTemplate::setHasReactor(bool hasReactor)
{
    has_reactor = hasReactor;
}

void ShipTemplate::setHasOxygenGenerator(bool hasOxygen)
{
    has_oxygen_generator = hasOxygen;
}

void ShipTemplate::setOxygenZone(int index, string label, float oxygen_max, float recharge_rate_per_second, float discharge_rate_per_second)
{
    if (index < 0 || index > 9)
        return;
    oxygen_zones[index].label = label;
    oxygen_zones[index].oxygen_level = oxygen_max;
    oxygen_zones[index].oxygen_max = oxygen_max;
    oxygen_zones[index].recharge_rate_per_second = recharge_rate_per_second;
    oxygen_zones[index].discharge_rate_per_second = discharge_rate_per_second;
}

void ShipTemplate::setRestocksMissilesDocked(bool enabled)
{
    restocks_missiles_docked = enabled;
}

void ShipTemplate::setJumpDrive(bool enabled)
{
    has_jump_drive = enabled;
}

void ShipTemplate::setCloaking(bool enabled)
{
    has_cloaking = enabled;
}

void ShipTemplate::setWeaponStorage(EMissileWeapons weapon, int amount)
{
    if (weapon != MW_None)
        weapon_storage[weapon] = amount;
}

void ShipTemplate::addRoom(sf::Vector2i position, sf::Vector2i size)
{
    rooms.push_back(ShipRoomTemplate(position, size, SYS_None, ""));
}

void ShipTemplate::addRoomSystem(sf::Vector2i position, sf::Vector2i size, ESystem system)
{
    rooms.push_back(ShipRoomTemplate(position, size, system, ""));
}

void ShipTemplate::addRoomTitle(sf::Vector2i position, sf::Vector2i size, string title)
{
    rooms.push_back(ShipRoomTemplate(position, size, SYS_None, title));
}

void ShipTemplate::addDoor(sf::Vector2i position, bool horizontal)
{
    doors.push_back(ShipDoorTemplate(position, horizontal));
}

void ShipTemplate::addDrones(string template_name, int count)
{
    drones.push_back(DroneTemplate(template_name, count));
}

void ShipTemplate::setDocks(int launchers, int energy, int weapons, int thermic, int repair, int stock){
    launcher_dock_count = launchers;
    energy_dock_count = energy;
    weapons_dock_count = weapons;
    thermic_dock_count = thermic;
    repair_dock_count = repair;
    stock_dock_count = stock;
}

void ShipTemplate::setRadarTrace(string trace)
{
    radar_trace = trace;
}

void ShipTemplate::setFarRangeRadarRange(float range)
{
    range = std::max(range, 100.0f);
    far_range_radar_range = range;
    long_range_radar_range = std::min(long_range_radar_range, range);
    short_range_radar_range = std::min(short_range_radar_range, range);
}

void ShipTemplate::setLongRangeRadarRange(float range)
{
    range = std::max(range, 100.0f);
    long_range_radar_range = range;
    short_range_radar_range = std::min(short_range_radar_range, range);
}

void ShipTemplate::setShortRangeRadarRange(float range)
{
    range = std::max(range, 100.0f);
    short_range_radar_range = range;
    long_range_radar_range = std::max(long_range_radar_range, range);
}

void ShipTemplate::setImpulseSoundFile(string sound)
{
    impulse_sound_file = sound;
}

P<ShipTemplate> ShipTemplate::copy(string new_name)
{
    P<ShipTemplate> result = new ShipTemplate();
    result->setName(new_name);

    result->description = description;
    result->class_name = class_name;
    result->sub_class_name = sub_class_name;
    result->type = type;
    result->model_data = model_data;

    result->external_dock_classes = external_dock_classes;
    result->internal_dock_classes = internal_dock_classes;
    result->energy_storage_amount = energy_storage_amount;
    result->repair_crew_count = repair_crew_count;

    result->can_scan = can_scan;
    result->can_hack = can_hack;
    result->can_dock = can_dock;
    result->can_combat_maneuver = can_combat_maneuver;
    result->can_self_destruct = can_self_destruct;
    result->can_launch_probe = can_launch_probe;

    result->default_ai_name = default_ai_name;
    for(int n=0; n<max_beam_weapons; n++)
        result->beams[n] = beams[n];
    result->weapon_tube_count = weapon_tube_count;
    for(int n=0; n<max_weapon_tubes; n++)
        result->weapon_tube[n] = weapon_tube[n];
    result->hull = hull;
    result->shield_count = shield_count;
    for(int n=0; n<max_shield_count; n++)
        result->shield_level[n] = shield_level[n];
    result->impulse_speed = impulse_speed;
    result->turn_speed = turn_speed;
    result->warp_speed = warp_speed;
    result->impulse_acceleration = impulse_acceleration;
    result->combat_maneuver_boost_speed = combat_maneuver_boost_speed;
    result->combat_maneuver_strafe_speed = combat_maneuver_strafe_speed;
    result->shares_energy_with_docked = shares_energy_with_docked;
    result->repair_docked = repair_docked;
    result->restocks_scan_probes = restocks_scan_probes;
    result->restocks_missiles_docked = restocks_missiles_docked;
    result->has_reactor = has_reactor;
    result->has_jump_drive = has_jump_drive;
    result->has_oxygen_generator = has_oxygen_generator;
    result->has_cloaking = has_cloaking;
    for(int n=0; n<MW_Count; n++)
        result->weapon_storage[n] = weapon_storage[n];
    result->radar_trace = radar_trace;

    result->rooms = rooms;
    result->doors = doors;
    for(int n=0; n<10; n++)
    {
        result->oxygen_zones[n].label = oxygen_zones[n].label;
        result->oxygen_zones[n].oxygen_level = oxygen_zones[n].oxygen_level;
        result->oxygen_zones[n].oxygen_max = oxygen_zones[n].oxygen_max;
        result->oxygen_zones[n].recharge_rate_per_second = oxygen_zones[n].recharge_rate_per_second;
        result->oxygen_zones[n].discharge_rate_per_second = oxygen_zones[n].discharge_rate_per_second;
    }
    result->drones = drones;
    result->launcher_dock_count = launcher_dock_count;
    result->energy_dock_count = energy_dock_count;
    result->weapons_dock_count = weapons_dock_count;
    result->thermic_dock_count = thermic_dock_count;
    result->repair_dock_count = repair_dock_count;
    result->stock_dock_count = stock_dock_count;
    result->tractor_beam = tractor_beam;
    result->isShipCargo = isShipCargo;

    return result;
}

void ShipTemplate::setEnergyStorage(float energy_amount)
{
    this->energy_storage_amount = energy_amount;
}

void ShipTemplate::setRepairCrewCount(int amount)
{
    this->repair_crew_count = amount;
}

string ShipTemplate::getName()
{
    return this->name;
}

string ShipTemplate::getLocaleName()
{
    return this->locale_name;
}

string ShipTemplate::getDescription()
{
    return this->description;
}

string ShipTemplate::getClass()
{
    return this->class_name;
}

string ShipTemplate::getSubClass()
{
    return this->sub_class_name;
}

ShipTemplate::TemplateType ShipTemplate::getType()
{
    return type;
}

#ifndef _MSC_VER
#include "shipTemplate.hpp"
#endif /* _MSC_VER */
