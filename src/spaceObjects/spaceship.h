#include <i18n.h>
#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "shipTemplateBasedObject.h"
#include "shipTemplate.h"
#include "spaceStation.h"
#include "spaceshipParts/beamWeapon.h"
#include "spaceshipParts/tractorBeam.h"
#include "spaceshipParts/weaponTube.h"
#include "spaceshipParts/dock.h"

enum EMainScreenSetting
{
    MSS_Front = 0,
    MSS_Back,
    MSS_Left,
    MSS_Right,
    MSS_Target,
    MSS_Tactical,
    MSS_LongRange,
    MSS_FarRange,
    MSS_TargetAnalysis
};
template<> void convert<EMainScreenSetting>::param(lua_State* L, int& idx, EMainScreenSetting& mss);

enum EMainScreenOverlay
{
    MSO_HideComms = 0,
    MSO_ShowComms
};
template<> void convert<EMainScreenOverlay>::param(lua_State* L, int& idx, EMainScreenOverlay& mso);

enum EDockingState
{
    DS_NotDocking = 0,
    DS_Docking,
    DS_Docked
};

class ShipSystem
{
public:
    float health; //1.0-0.0, where 0.0 is fully broken.
    float health_max; //1.0-0.0, where 0.0 is fully broken.
    float power_level; //0.0-3.0, default 1.0
    float power_request;
    float heat_level; //0.0-1.0, system will damage at 1.0
    float coolant_level; //0.0-10.0
    float coolant_request;
    float repair_level; //0.0-10.0
    float repair_request;
    float hacked_level; //0.0-1.0
    float power_user_factor;
    
    float getHeatingDelta()
    {
        return powf(1.7, power_level - 1.0) - (1.01 + coolant_level * 0.1);
    }
    
    float instability_level; //0.0-1.0
    float instability_factor; //0.0-1.0
    int instability_difficulty; //0-4
    float instability_value[4]; //-1.0-1.0
    float instability_target[4]; //-1.0-1.0
    string instability_label[4];
        
    float getInstabilityLevel()
    {
        float instability = 0.0;
        for(int n=0; n<instability_difficulty; n++)
            instability += std::abs(instability_value[n] - instability_target[n]) / 2;
        instability *= hacked_level + 1.0;
        instability *= heat_level + 0.8;
        instability *= power_level;
        
        instability = std::min(1.0f, std::max(0.0f, instability));
        
        return instability;
    }
};

class SpaceShip : public ShipTemplateBasedObject
{
public:
    constexpr static int max_frequency = 20;
    constexpr static float combat_maneuver_charge_time = 20.0f; /*< Amount of time it takes to fully charge the combat maneuver system */
    constexpr static float combat_maneuver_boost_max_time = 3.0f; /*< Amount of time we can boost with a fully charged combat maneuver system */
    constexpr static float combat_maneuver_strafe_max_time = 3.0f; /*< Amount of time we can strafe with a fully charged combat maneuver system */
    constexpr static float warp_charge_time = 4.0f;
    constexpr static float warp_decharge_time = 2.0f;
    constexpr static float jump_drive_charge_time = 90.0;   /*<Total charge time for the jump drive after a max range jump */
    constexpr static float dock_move_time = 15.0f; // It takes this amount of time to move cargo between two docks
    constexpr static float jump_drive_energy_per_km_charge = 4.0f;
    constexpr static float jump_drive_heat_per_jump = 0.35;
    constexpr static float heat_per_combat_maneuver_boost = 0.2;
    constexpr static float heat_per_combat_maneuver_strafe = 0.2;
    constexpr static float heat_per_warp = 0.02;
    constexpr static float unhack_time = 180.0f; //It takes this amount of time to go from 100% hacked to 0% hacked for systems.
    constexpr static int max_target_id = 10; // Number of maximal specific weapons stations


    float energy_level;
    float max_energy_level;
    Dock docks[max_docks_count];
    OxygenZone oxygen_zones[10];

    std::vector<SpaceShip*> targetedBy;

    ShipSystem systems[SYS_COUNT];
    /*!
     *[input] Ship will try to aim to this rotation. (degrees)
     */
    float target_rotation;

    /*!
     *[input] Ship will rotate in this velocity. ([-1,1], overrides target_rotation)
     */
    float turnSpeed;

    /*!
     * [input] Amount of impulse requested from the user (-1.0 to 1.0)
     */
    float impulse_request;

    /*!
     * [output] Amount of actual impulse from the engines (-1.0 to 1.0)
     */
    float current_impulse;

    /*!
     * [config] Speed of rotation, in deg/second
     */
    float turn_speed;

    /*!
     * [config] Max speed of the impulse engines, in m/s
     */
    float impulse_max_speed;

    /*!
     * [config] Impulse engine acceleration, in (m/s)/s
     */
    float impulse_acceleration;

    /*!
     * [config] True if we have a reactor (for energy).
     */
    bool has_reactor;

    /*!
     * [config] True if we have a oxygen generator.
     */
    bool has_oxygen_generator;

    /*!
     * [config] True if we have a warpdrive.
     */
    bool has_warp_drive;

    /*!
     * [input] Level of warp requested, from 0 to 4
     */
    int8_t warp_request;

    /*!
     * [output] Current active warp amount, from 0.0 to 4.0
     */
    float current_warp;

    /*!
     * [output] warp factor due to terrain, from 0.0 to around 10.0
     */
    float warp_layer_factor;

    /*!
     * [config] Amount of speed per warp level, in m/s
     */
    float warp_speed_per_warp_level;

    /*!
     * [output] How much charge there is in the combat maneuvering system (0.0-1.0)
     */
    float combat_maneuver_charge;
    /*!
     * [input] How much boost we want at this moment (0.0-1.0)
     */
    float combat_maneuver_boost_request;
    float combat_maneuver_boost_active;

    float combat_maneuver_strafe_request;
    float combat_maneuver_strafe_active;

    float combat_maneuver_boost_speed; /*< [config] Speed to indicate how fast we will fly forwards with a full boost */
    float combat_maneuver_strafe_speed; /*< [config] Speed to indicate how fast we will fly sideways with a full strafe */

    bool has_jump_drive;      //[config]
    float jump_drive_charge; //[output]
    float jump_distance;     //[output]
    float jump_delay;        //[output]
    float jump_drive_min_distance; //[config]
    float jump_drive_max_distance; //[config]
    float wormhole_alpha;    //Used for displaying the Warp-postprocessor

    int weapon_storage[MW_Count];
    int weapon_storage_max[MW_Count];
    int8_t weapon_tube_count;
    WeaponTube weapon_tube[max_weapon_tubes];

    /*!
     * [output] Frequency of beam weapons
     */
    int beam_frequency;
    ESystem beam_system_target;
    BeamWeapon beam_weapons[max_beam_weapons];
    TractorBeam tractor_beam;
    std::set<SpaceShip*> targetedByTractorBeams;
    int beams_button_station;
    int shields_station;
    int lock_button_station;

    /**
     * Frequency setting of the shields.
     */
    int shield_frequency;
    /**
     * Frequency setting of the warp.
     */
    int warp_frequency;

    /// MultiplayerObjectID of the targeted object, or -1 when no target is selected.
    /// Multi target for specific weapons stations
    int32_t target_id[max_target_id];

    EDockingState docking_state;
    DockStyle docked_style;
    P<SpaceObject> docking_target; //Server only
    sf::Vector2f docking_offset{0, 0}; //Server only
    
    bool docked_and_hidden; // SBW
    string hidden_callsign; // SBW

    SpaceShip(string multiplayerClassName, float multiplayer_significant_range=-1);
    virtual ~SpaceShip();

#if FEATURE_3D_RENDERING
    virtual void draw3D() override;
    virtual void draw3DTransparent() override;
#endif
    /*!
     * Get this ship's radar signature dynamically modified by the state of its
     * systems and current activity.
     */
    virtual RawRadarSignatureInfo getDynamicRadarSignatureInfo();
    float getDynamicRadarSignatureGravity() { return getDynamicRadarSignatureInfo().gravity; }
    float getDynamicRadarSignatureElectrical() { return getDynamicRadarSignatureInfo().electrical; }
    float getDynamicRadarSignatureBiological() { return getDynamicRadarSignatureInfo().biological; }

    /*!
     * Draw this ship on the radar.
     */
    virtual void drawOnRadar(sf::RenderTarget& window, sf::Vector2f position, float scale, float rotation, bool long_range) override;
    virtual void drawOnGMRadar(sf::RenderTarget& window, sf::Vector2f position, float scale, float rotation, bool long_range) override;
    void drawBeamOnRadar(sf::RenderTarget& window, sf::Vector2f position, float scale, float rotation, sf::Color color, sf::Vector2f beam_position, float beam_direction, float beam_arc, float beam_range);

    virtual void update(float delta) override;
    virtual float getShieldRechargeRate(int shield_index) override;
    virtual float getZoneRechargeRate(unsigned int zone_index);
    virtual float getShieldDamageFactor(DamageInfo& info, int shield_index) override;
    float getJumpDriveRechargeRate() { return Tween<float>::linear(getSystemEffectiveness(SYS_JumpDrive), 0.0, 1.0, -0.25, 1.0); }

    /*!
     * Check if the ship can be targeted.
     */
    virtual bool canBeTargetedBy(P<SpaceObject> other) override { return true; }

    /*!
     * didAnOffensiveAction is called whenever this ship does something offesive towards an other object
     * this can identify the ship as friend or foe.
     */
    void didAnOffensiveAction();

    /*!
     * Spaceship takes damage directly on hull.
     * This is used when shields are down or by weapons that ignore shields.
     * \param damage_amount Damage to be delt.
     * \param info Information about damage type (usefull for damage reduction, etc)
     */
    virtual void takeHullDamage(float damage_amount, DamageInfo& info) override;

    /*!
     * Spaceship takes heat directly on hull.
     * This is used when shields are down or by weapons that ignore shields.
     * \param damage_amount Damage to be delt.
     * \param info Information about damage type (usefull for damage reduction, etc)
     */
    virtual void takeHeatDamage(float damage_amount, DamageInfo& info) override;

    /*!
     * Spaceship is destroyed by damage.
     * \param info Information about damage type
     */
    virtual void destroyedByDamage(DamageInfo& info) override;

    /*!
     * Jump in current direction
     * \param distance Distance to jump in meters)
     */
    virtual void executeJump(float distance);

    /*!
     * Check if object can dock with this ship.
     * \param object Object that wants to dock.
     */
    virtual DockStyle canBeDockedBy(P<SpaceObject> obj) override;

    virtual void collide(Collisionable* other, float force) override;

    /*!
     * Start the jumping procedure.
     */
    void initializeJump(float distance);

    /*!
     * Request to dock with target.
     */
    void requestDock(P<SpaceObject> target);

    /*!
     * Request undock with current docked object
     */
    void requestUndock();

    /*!
     * Abort the current dock request
     */
    void abortDock();

    /// Dummy virtual function to use energy. Only player ships currently model energy use.
    virtual bool useEnergy(float amount) { return true; }

    /// Dummy virtual function to add heat on a system. The player ship class has an actual implementation of this as only player ships model heat right now.
    virtual void addHeat(ESystem system, float amount) {}

    virtual bool canBeScannedBy(P<SpaceObject> other) override { return getScannedStateFor(other) != SS_FullScan && other->scanning_capability > getScannedStateFor(other); }
    virtual int scanningComplexity(P<SpaceObject> other) override;
    virtual int scanningChannelDepth(P<SpaceObject> other) override;
    virtual void scannedBy(P<SpaceObject> other) override;
    void setScanState(EScannedState scanned);
    void setScanStateByFaction(string faction_name, EScannedState scanned);

    bool isFriendOrFoeIdentified();//[DEPRICATED]
    bool isFullyScanned();//[DEPRICATED]
    bool isFriendOrFoeIdentifiedBy(P<SpaceObject> other);
    bool isFullyScannedBy(P<SpaceObject> other);
    bool isFriendOrFoeIdentifiedByFaction(int faction_id);
    bool isFullyScannedByFaction(int faction_id);

    virtual bool canBeHackedBy(P<SpaceObject> other) override;
    virtual std::vector<std::pair<string, float> > getHackingTargets() override;
    virtual void hackFinished(P<SpaceObject> source, string target, float value) override;

    /*!
     * Check if ship has certain system
     */
    bool hasSystem(ESystem system);

    /*!
     * Check effectiveness of system.
     * If system has more / less power or is damages, this can influence the effectiveness.
     * \return float 0. to 1.
     */
    float getSystemEffectiveness(ESystem system);

    virtual void applyTemplateValues() override;

    P<SpaceObject> getTarget(int station = 0);

    virtual std::unordered_map<string, string> getGMInfo() override;

    bool isDocked(P<SpaceObject> target) { return docking_state == DS_Docked && docking_target == target; }
    P<SpaceObject> getDockedWith() { if (docking_state == DS_Docked) return docking_target; return NULL; }
    EDockingState getDockingState() { return docking_state; }
    bool canStartDocking() { return current_warp <= 0.0 && (!has_jump_drive || jump_delay <= 0.0); }
    int getWeaponStorage(EMissileWeapons weapon) { if (weapon == MW_None) return 0; return weapon_storage[weapon]; }
    int getWeaponStorageMax(EMissileWeapons weapon) { if (weapon == MW_None) return 0; return weapon_storage_max[weapon]; }
    void setWeaponStorage(EMissileWeapons weapon, int amount) { if (weapon == MW_None) return; weapon_storage[weapon] = amount; }
    void setWeaponStorageMax(EMissileWeapons weapon, int amount) { if (weapon == MW_None) return; weapon_storage_max[weapon] = amount; weapon_storage[weapon] = std::min(int(weapon_storage[weapon]), amount); }
    float getMaxEnergy() { return max_energy_level; }
    void setMaxEnergy(float amount) { if (amount > 0.0) { max_energy_level = amount;} }
    float getEnergy() { return energy_level; }
    void setEnergy(float amount) { if ( (amount > 0.0) && (amount <= max_energy_level)) { energy_level = amount; } }
    float getSystemHackedLevel(ESystem system) { if (system >= SYS_COUNT) return 0.0; if (system <= SYS_None) return 0.0; return systems[system].hacked_level; }
    void setSystemHackedLevel(ESystem system, float hacked_level) { if (system >= SYS_COUNT) return; if (system <= SYS_None) return; systems[system].hacked_level = std::min(1.0f, std::max(0.0f, hacked_level)); }
    float getSystemHealth(ESystem system) { if (system >= SYS_COUNT) return 0.0; if (system <= SYS_None) return 0.0; return systems[system].health; }
    void setSystemHealth(ESystem system, float health) { if (system >= SYS_COUNT) return; if (system <= SYS_None) return; systems[system].health = std::min(1.0f, std::max(-1.0f, health)); }
    float getSystemHealthMax(ESystem system) { if (system >= SYS_COUNT) return 0.0; if (system <= SYS_None) return 0.0; return systems[system].health_max; }
    void setSystemHealthMax(ESystem system, float health_max) { if (system >= SYS_COUNT) return; if (system <= SYS_None) return; systems[system].health_max = std::min(1.0f, std::max(-1.0f, health_max)); }
    float getSystemHeat(ESystem system) { if (system >= SYS_COUNT) return 0.0; if (system <= SYS_None) return 0.0; return systems[system].heat_level; }
    void setSystemHeat(ESystem system, float heat) { if (system >= SYS_COUNT) return; if (system <= SYS_None) return; systems[system].heat_level = std::min(1.0f, std::max(0.0f, heat)); }
    float getSystemPower(ESystem system) { if (system >= SYS_COUNT) return 0.0; if (system <= SYS_None) return 0.0; return systems[system].power_level; }
    void setSystemPower(ESystem system, float power) { if (system >= SYS_COUNT) return; if (system <= SYS_None) return; systems[system].power_level = std::min(3.0f, std::max(0.0f, power)); }
    float getSystemCoolant(ESystem system) { if (system >= SYS_COUNT) return 0.0; if (system <= SYS_None) return 0.0; return systems[system].coolant_level; }
    void setSystemCoolant(ESystem system, float coolant) { if (system >= SYS_COUNT) return; if (system <= SYS_None) return; systems[system].coolant_level = std::min(1.0f, std::max(0.0f, coolant)); }
    float getSystemRepair(ESystem system) { if (system >= SYS_COUNT) return 0.0; if (system <= SYS_None) return 0.0; return systems[system].repair_level; }
    void setSystemRepair(ESystem system, float repair) { if (system >= SYS_COUNT) return; if (system <= SYS_None) return; systems[system].repair_level = std::min(1.0f, std::max(0.0f, repair)); }
    float getSystemPowerUseFactor(ESystem system) { if (system >= SYS_COUNT) return 0.0; if (system <= SYS_None) return 0.0; return systems[system].power_user_factor; }
    void setSystemPowerUseFactor(ESystem system, float factor) { if (system >= SYS_COUNT) return; if (system <= SYS_None) return; systems[system].power_user_factor = factor; }
    float getSystemInstabilityLevel(ESystem system) { if (system >= SYS_COUNT) return 0.0; if (system <= SYS_None) return 0.0; return systems[system].instability_level; }
    void setSystemInstabilityLevel(ESystem system, float instability) { if (system >= SYS_COUNT) return; if (system <= SYS_None) return; systems[system].instability_level = std::min(1.0f, std::max(0.0f, instability)); }
    float getSystemInstabilityFactor(ESystem system) { if (system >= SYS_COUNT) return 0.0; if (system <= SYS_None) return 0.0; return systems[system].instability_factor; }
    void setSystemInstabilityFactor(ESystem system, float factor) { if (system >= SYS_COUNT) return; if (system <= SYS_None) return; systems[system].instability_factor = std::min(1.0f, std::max(0.0f, factor)); }
    int getSystemInstabilityDifficulty(ESystem system) { if (system >= SYS_COUNT) return 0; if (system <= SYS_None) return 0; return systems[system].instability_difficulty; }
    void setSystemInstabilityDifficulty(ESystem system, int difficulty) { if (system >= SYS_COUNT) return; if (system <= SYS_None) return; systems[system].instability_difficulty = std::min(4, std::max(0, difficulty)); }
    float getSystemInstabilityValue(ESystem system, int slider) { if (system >= SYS_COUNT) return 0; if (system <= SYS_None) return 0; if (slider < 1) return 0; if (slider > 4) return 0; return systems[system].instability_value[slider-1]; }
    void setSystemInstabilityValue(ESystem system, int slider, float value) { if (system >= SYS_COUNT) return; if (system <= SYS_None) return; if (slider < 1) return; if (slider > 4) return; systems[system].instability_value[slider-1] = std::min(1.0f, std::max(-1.0f, value)); }
    string getSystemInstabilityLabel(ESystem system, int slider) { if (system >= SYS_COUNT) return 0; if (system <= SYS_None) return 0; if (slider < 1) return 0; if (slider > 4) return 0; return systems[system].instability_label[slider-1]; }
    void setSystemInstabilityLabel(ESystem system, int slider, string label) { if (system >= SYS_COUNT) return; if (system <= SYS_None) return; if (slider < 1) return; if (slider > 4) return; systems[system].instability_label[slider-1] = label; }
    float getImpulseMaxSpeed() { return impulse_max_speed; }
    void setImpulseMaxSpeed(float speed) { impulse_max_speed = speed; }
    float getRotationMaxSpeed() { return turn_speed; }
    void setRotationMaxSpeed(float speed) { turn_speed = speed; }
    float getAcceleration() { return impulse_acceleration; }
    void setAcceleration(float acceleration) { impulse_acceleration = acceleration; }
    void setCombatManeuver(float boost, float strafe) { combat_maneuver_boost_speed = boost; combat_maneuver_strafe_speed = strafe; }

    void setReactor(bool has_reactor_drive){ has_reactor = has_reactor_drive;}
    bool hasReactor() { return has_reactor; }
    void setOxygenGenerator(bool has_generator){ has_oxygen_generator = has_generator;}
    bool hasOxygenGenerator() { return has_oxygen_generator; }
    void setOxygenZone(int index, string label, float oxygen_level, float oxygen_max, float recharge_rate_per_second, float discharge_rate_per_second);
    string getOxygenZoneLabel(int index) {if (index < 0 || index > 9) return ""; return oxygen_zones[index].label; }
    float getOxygenZoneLevel(int index) {if (index < 0 || index > 9) return 0.0; return oxygen_zones[index].oxygen_level; }
    float getOxygenZoneMax(int index) {if (index < 0 || index > 9) return 0.0; return oxygen_zones[index].oxygen_max; }
    float getOxygenZoneRecharge(int index) {if (index < 0 || index > 9) return 0.0; return oxygen_zones[index].recharge_rate_per_second; }
    float getOxygenZoneDischarge(int index) {if (index < 0 || index > 9) return 0.0; return oxygen_zones[index].discharge_rate_per_second; } 
    bool hasJumpDrive() { return has_jump_drive; }
    void setJumpDrive(bool has_jump) { has_jump_drive = has_jump; }
    void setJumpDriveRange(float min, float max) { jump_drive_min_distance = min; jump_drive_max_distance = max; }
    bool hasWarpDrive() { return has_warp_drive; }
    void setWarpDrive(bool has_warp)
    {
        has_warp_drive = has_warp;
        if (has_warp_drive)
        {
            if (warp_speed_per_warp_level < 100)
                warp_speed_per_warp_level = 1000;
        }else{
            warp_request = 0.0;
            warp_speed_per_warp_level = 0;
        }
    }
    void setWarpSpeed(float speed) { warp_speed_per_warp_level = std::max(0.0f, speed); }
    float getWarpSpeed() {
        if (has_warp_drive) {
            return warp_speed_per_warp_level;
        } else {
            return 0.0f;
        }
    }
    int getWarpFrequency(void){ return warp_frequency; }
    void setWarpFrequency(float freq) { if ((freq > 10) || (freq < 0)) return; warp_frequency = freq;}

    float getJumpDriveCharge() { return jump_drive_charge; }
    void setJumpDriveCharge(float charge) { jump_drive_charge = charge; }

    float getBeamWeaponArc(int index) { if (index < 0 || index >= max_beam_weapons) return 0.0; return beam_weapons[index].getArc(); }
    float getBeamWeaponDirection(int index) { if (index < 0 || index >= max_beam_weapons) return 0.0; return beam_weapons[index].getDirection(); }
    float getBeamWeaponRange(int index) { if (index < 0 || index >= max_beam_weapons) return 0.0; return beam_weapons[index].getRange(); }

    float getBeamWeaponTurretArc(int index)
    {
        if (index < 0 || index >= max_beam_weapons)
            return 0.0;
        return beam_weapons[index].getTurretArc();
    }

    float getBeamWeaponTurretDirection(int index)
    {
        if (index < 0 || index >= max_beam_weapons)
            return 0.0;
        return beam_weapons[index].getTurretDirection();
    }

    float getBeamWeaponTurretRotationRate(int index)
    {
        if (index < 0 || index >= max_beam_weapons)
            return 0.0;
        return beam_weapons[index].getTurretRotationRate();
    }

    float getBeamWeaponCycleTime(int index) { if (index < 0 || index >= max_beam_weapons) return 0.0; return beam_weapons[index].getCycleTime(); }
    float getBeamWeaponDamage(int index) { if (index < 0 || index >= max_beam_weapons) return 0.0; return beam_weapons[index].getDamage(); }
    EDamageType getBeamWeaponDamageType(int index) { if (index < 0 || index >= max_beam_weapons) return DT_Energy; return beam_weapons[index].getDamageType(); }
    float getBeamWeaponEnergyPerFire(int index) { if (index < 0 || index >= max_beam_weapons) return 0.0; return beam_weapons[index].getEnergyPerFire(); }
    float getBeamWeaponHeatPerFire(int index) { if (index < 0 || index >= max_beam_weapons) return 0.0; return beam_weapons[index].getHeatPerFire(); }
    int getBeamWeaponStation(int index) { if (index < 0 || index >= max_beam_weapons) return 0; return beam_weapons[index].getStation(); }

    int getBeamsButtonStation() { return beams_button_station; }

    int getShieldsStation() {return shields_station; }

    int getLockButtonStation() {return lock_button_station;}
    
    int getShieldsFrequency(void){ return shield_frequency; }
    void setShieldsFrequency(float freq) { if ((freq > SpaceShip::max_frequency) || (freq < 0)) return; shield_frequency = freq;}

    int getBeamFrequency(){ return beam_frequency; }

    void setBeamWeapon(int index, float arc, float direction, float range, float cycle_time, float damage)
    {
        if (index < 0 || index >= max_beam_weapons)
            return;
        beam_weapons[index].setArc(arc);
        beam_weapons[index].setDirection(direction);
        beam_weapons[index].setRange(range);
        beam_weapons[index].setCycleTime(cycle_time);
        beam_weapons[index].setDamage(damage);
    }

    void setBeamWeaponDamageType(int index, int damage_type)
    {
        if (index < 0 || index >= max_beam_weapons)
            return;
        beam_weapons[index].setDamageType(static_cast<EDamageType>(damage_type));
    }

    void setBeamWeaponTurret(int index, float arc, float direction, float rotation_rate)
    {
        if (index < 0 || index >= max_beam_weapons)
            return;
        beam_weapons[index].setTurretArc(arc);
        beam_weapons[index].setTurretDirection(direction);
        beam_weapons[index].setTurretRotationRate(rotation_rate);
    }

    void setBeamWeaponTexture(int index, string texture)
    {
        if (index < 0 || index >= max_beam_weapons)
            return;
        beam_weapons[index].setBeamTexture(texture);
    }

    void setBeamWeaponEnergyPerFire(int index, float energy) { if (index < 0 || index >= max_beam_weapons) return; return beam_weapons[index].setEnergyPerFire(energy); }
    void setBeamWeaponHeatPerFire(int index, float heat) { if (index < 0 || index >= max_beam_weapons) return; return beam_weapons[index].setHeatPerFire(heat); }
    void setBeamWeaponStation(int index, int station) { if (index < 0 || index >= max_beam_weapons) return; return beam_weapons[index].setStation(station); }

    void setTractorBeam(ETractorBeamMode mode, float arc, float direction, float range, float max_area, float drag_per_second)
    {
        tractor_beam.setMode(mode);
        tractor_beam.setArc(arc);
        tractor_beam.setDirection(direction);
        tractor_beam.setRange(range);
        tractor_beam.setMaxArea(max_area);
        tractor_beam.setDragPerSecond(drag_per_second);
    }
    
    void setTractorBeamMax(float max_range, float drag_per_second)
    {
        tractor_beam.setMaxRange(max_range);
        tractor_beam.setDragPerSecond(drag_per_second);
    }

    void addAsTractorBeamTargeter(SpaceShip* targeter);
    void removeAsTractorBeamTargeter(SpaceShip* targeter);
    
    void setWeaponTubeCount(int amount);
    int getWeaponTubeCount();
    EMissileWeapons getWeaponTubeLoadType(int index);
    EMissileSizes getWeaponTubeSize(int index);
    int getWeaponTubeStation(int index);

    void weaponTubeAllowMissle(int index, EMissileWeapons type);
    void weaponTubeDisallowMissle(int index, EMissileWeapons type);
    void setWeaponTubeExclusiveFor(int index, EMissileWeapons type);
    void setWeaponTubeDirection(int index, float direction);
    void setWeaponTubeSize(int index, EMissileSizes size);
    void setTubeSize(int index, EMissileSizes size);
    EMissileSizes getTubeSize(int index);
    void setWeaponTubeStation(int index, int station);
    void setTubeLoadTime(int index, float time);
    float getTubeLoadTime(int index);

    void setRadarTrace(string trace) { radar_trace = trace; }

    void addBroadcast(int threshold, string message);

    // Return a string that can be appended to an object create function in the lua scripting.
    // This function is used in getScriptExport calls to adjust for tweaks done in the GM screen.
    string getScriptExportModificationsOnTemplate();
    void addDrone(string drone);
    bool tryDockDrone(SpaceShip* other);
    float getDronesControlRange();
};

float frequencyVsFrequencyDamageFactor(int beam_frequency, int shield_frequency);

string getMissileWeaponName(EMissileWeapons missile);
string getLocaleMissileWeaponName(EMissileWeapons missile);
REGISTER_MULTIPLAYER_ENUM(EMissileWeapons);
REGISTER_MULTIPLAYER_ENUM(EWeaponTubeState);
REGISTER_MULTIPLAYER_ENUM(EMainScreenSetting);
REGISTER_MULTIPLAYER_ENUM(EMainScreenOverlay);
REGISTER_MULTIPLAYER_ENUM(EDockingState);
REGISTER_MULTIPLAYER_ENUM(DockStyle);
REGISTER_MULTIPLAYER_ENUM(EScannedState);
REGISTER_MULTIPLAYER_ENUM(EDockType);
REGISTER_MULTIPLAYER_ENUM(EDockState);
REGISTER_MULTIPLAYER_ENUM(ETractorBeamMode);
REGISTER_MULTIPLAYER_ENUM(EDamageType);


string frequencyToString(int frequency);

#ifdef _MSC_VER
// MFC: GCC does proper external template instantiation, VC++ doesn't.
#include "spaceship.hpp"
#endif

#endif//SPACESHIP_H
