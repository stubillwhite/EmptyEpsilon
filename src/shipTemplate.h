#ifndef SHIP_TEMPLATE_H
#define SHIP_TEMPLATE_H

#include <unordered_map>
#include <unordered_set>
#include "engine.h"
#include "modelData.h"

#include "beamTemplate.h"
#include "tractorBeamTemplate.h"
#include "missileWeaponData.h"
constexpr static int max_beam_weapons = 16;
constexpr static int max_weapon_tubes = 16;
constexpr static int max_shield_count = 8;
constexpr static int max_docks_count = 16;

enum ESystem
{
    SYS_None = -1,
    SYS_Reactor = 0,
    SYS_Oxygen,
    SYS_BeamWeapons,
    SYS_MissileSystem,
    SYS_Maneuver,
    SYS_Impulse,
    SYS_Warp,
    SYS_JumpDrive,
    SYS_FrontShield,
    SYS_RearShield,
    SYS_Docks,
    SYS_Scanner,
    SYS_COUNT
};

class OxygenZone
{
public:
    string label;
    float oxygen_level;
    float oxygen_max;
    float recharge_rate_per_second;
    float discharge_rate_per_second;
};

/* Define script conversion function for the ESystem enum. */
template<> void convert<ESystem>::param(lua_State* L, int& idx, ESystem& es);
class DroneTemplate {
    public:
    string template_name;
    int count;
    DroneTemplate(string template_name, int count): template_name(template_name), count(count) {}
};
class ShipRoomTemplate
{
public:
    sf::Vector2i position;
    sf::Vector2i size;
    ESystem system;
    string title;

    ShipRoomTemplate(sf::Vector2i position, sf::Vector2i size, ESystem system, string title) : position(position), size(size), system(system), title(title) {}
};
class ShipDoorTemplate
{
public:
    sf::Vector2i position;
    bool horizontal;

    ShipDoorTemplate(sf::Vector2i position, bool horizontal) : position(position), horizontal(horizontal) {}
};

class SpaceObject;
class ShipTemplate : public PObject
{
public:
    enum TemplateType
    {
        Drone,
        Ship,
        PlayerShip,
        Station
    };
    class TubeTemplate
    {
    public:
        float load_time;
        uint32_t type_allowed_mask;
        float direction;
        EMissileSizes size;
        int station;
    };
private:
    static std::unordered_map<string, P<ShipTemplate> > templateMap;
    string name;
    string locale_name = "";
    string description;
    string class_name;
    string sub_class_name;
    TemplateType type;
    bool recorded;
public:
    string getName();
    string getLocaleName();
    string getDescription();
    string getClass();
    string getSubClass();
    void setType(TemplateType type);
    TemplateType getType();

    void setRecorded(bool value) { recorded = value; }
    bool getRecorded(){ return recorded; }

    P<ModelData> model_data;

    /*!
     * List of ship classes that can dock with this ship. (only used for ship2ship docking)
     */
    std::unordered_set<string> external_dock_classes;
    std::unordered_set<string> internal_dock_classes;
    bool shares_energy_with_docked;
    bool repair_docked;
    bool restocks_scan_probes;
    bool restocks_missiles_docked;
    bool can_scan = true;
    bool can_hack = true;
    bool can_dock = true;
    bool can_combat_maneuver = true;
    bool can_self_destruct = true;
    bool can_launch_probe = true;
    bool has_reactor;
    bool has_oxygen_generator;
    OxygenZone oxygen_zones[10];

    float energy_storage_amount;
    int repair_crew_count;
    string default_ai_name;
    BeamTemplate beams[max_beam_weapons];
    TractorBeamTemplate tractor_beam;
    int weapon_tube_count;
    TubeTemplate weapon_tube[max_weapon_tubes];
    float hull;
    int shield_count;
    float shield_level[max_shield_count];
    float impulse_speed, turn_speed, warp_speed;
    float impulse_acceleration;
    float combat_maneuver_boost_speed;
    float combat_maneuver_strafe_speed;
    bool has_jump_drive, has_cloaking;
    float jump_drive_min_distance;
    float jump_drive_max_distance;
    int weapon_storage[MW_Count];
    int launcher_dock_count;
    int energy_dock_count;
    int weapons_dock_count;
    int thermic_dock_count;
    int repair_dock_count;
    int stock_dock_count;
    bool isShipCargo;
    string radar_trace;
    float far_range_radar_range = 50000.0f;
    float long_range_radar_range = 30000.0f;
    float short_range_radar_range = 5000.0f;
    string impulse_sound_file;
    int beams_button_station;
    int shields_station;
    int lock_button_station;

    std::vector<ShipRoomTemplate> rooms;
    std::vector<ShipDoorTemplate> doors;
    //std::vector<ShipOxygenZoneTemplate> oxygen_zones;
    std::vector<DroneTemplate> drones;

    ShipTemplate();

    void setName(string name);
    void setLocaleName(string name);
    void setClass(string class_name, string sub_class_name);
    void setDescription(string description);
    void setModel(string model_name);
    void setDefaultAI(string default_ai_name);
    void setDockClasses(std::vector<string> classes);
    void setExternalDockClasses(const std::vector<string> classes);
    void setInternalDockClasses(const std::vector<string> classes);
    void setSharesEnergyWithDocked(bool enabled);
    void setRepairDocked(bool enabled);
    void setRestocksScanProbes(bool enabled);
    void setRestocksMissilesDocked(bool enabled);
    void setCanScan(bool enabled) { can_scan = enabled; }
    void setCanHack(bool enabled) { can_hack = enabled; }
    void setCanDock(bool enabled) { can_dock = enabled; }
    void setCanCombatManeuver(bool enabled) { can_combat_maneuver = enabled; }
    void setCanSelfDestruct(bool enabled) { can_self_destruct = enabled; }
    void setCanLaunchProbe(bool enabled) { can_launch_probe = enabled; }
    void setHasReactor(bool hasReactor);
    void setHasOxygenGenerator(bool hasOxygen);
    void setIsShipCargo(bool enabled) { isShipCargo = enabled; }
    void setMesh(string model, string color_texture, string specular_texture, string illumination_texture);
    void setEnergyStorage(float energy_amount);
    void setRepairCrewCount(int amount);

    void setBeam(int index, float arc, float direction, float range, float cycle_time, float damage);
    void setBeamWeapon(int index, float arc, float direction, float range, float cycle_time, float damage);
    void setBeamWeaponDamageType(int index, int damage_type);
    void setBeamWeaponTurret(int index, float arc, float direction, float rotation_rate);
    void setBeamStation(int index, int station);
    void setTractorBeam(float max_range, float drag_per_second);
    // add beams button station
    void setBeamsButtonStation(int station);
    void setShieldsStation(int station);
    void setLockButtonStation(int station);
    /**
     * Convenience function to set the texture of a beam by index.
     */
    void setBeamTexture(int index, string texture);
    void setBeamWeaponEnergyPerFire(int index, float energy) { if (index < 0 || index >= max_beam_weapons) return; return beams[index].setEnergyPerFire(energy); }
    void setBeamWeaponHeatPerFire(int index, float heat) { if (index < 0 || index >= max_beam_weapons) return; return beams[index].setHeatPerFire(heat); }

    void setTubes(int amount, float load_time);
    void setTubeLoadTime(int index, float load_time);
    void weaponTubeAllowMissle(int index, EMissileWeapons type);
    void weaponTubeDisallowMissle(int index, EMissileWeapons type);
    void setWeaponTubeExclusiveFor(int index, EMissileWeapons type);
    void setTubeSize(int index, EMissileSizes size);
    void setTubeStation(int index, int station);
    void setTubeDirection(int index, float direction);
    void setHull(float amount) { hull = amount; }
    void setShields(std::vector<float> values);
    void setSpeed(float impulse, float turn, float acceleration);
    void setCombatManeuver(float boost, float strafe);
    void setWarpSpeed(float warp);
    void setJumpDrive(bool enabled);
    void setJumpDriveRange(float min, float max) { jump_drive_min_distance = min; jump_drive_max_distance = max; }
    void setCloaking(bool enabled);
    void setWeaponStorage(EMissileWeapons weapon, int amount);
    void addRoom(sf::Vector2i position, sf::Vector2i size);
    void addRoomSystem(sf::Vector2i position, sf::Vector2i size, ESystem system);
    void addRoomTitle(sf::Vector2i position, sf::Vector2i size, string title);
    void addDoor(sf::Vector2i position, bool horizontal);
    void setOxygenZone(int index, string label, float oxygen_max, float recharge_rate_per_second, float discharge_rate_per_second);
    void addDrones(string template_name, int count);
    void setDocks(int launchers, int energy, int weapons, int thermic, int repair, int stock);
    void setRadarTrace(string trace);
    void setFarRangeRadarRange(float range);
    void setLongRangeRadarRange(float range);
    void setShortRangeRadarRange(float range);
    void setImpulseSoundFile(string sound);

    P<ShipTemplate> copy(string new_name);

    sf::Vector2i interiorSize();
    ESystem getSystemAtRoom(sf::Vector2i position);

    void setCollisionData(P<SpaceObject> object);
public:
    static P<ShipTemplate> getTemplate(string name);
    static std::vector<string> getAllTemplateNames();
    static std::vector<string> getTemplateNameList(TemplateType type);
};
string getSystemName(ESystem system);
string getLocaleSystemName(ESystem system);
REGISTER_MULTIPLAYER_ENUM(ESystem);

/* Define script conversion function for the ShipTemplate::TemplateType enum. */
template<> void convert<ShipTemplate::TemplateType>::param(lua_State* L, int& idx, ShipTemplate::TemplateType& tt);

#ifdef _MSC_VER
// MFC: GCC does proper external template instantiation, VC++ doesn't.
#include "shipTemplate.hpp"
#endif /* _MSC_VER */

#endif//SHIP_TEMPLATE_H
