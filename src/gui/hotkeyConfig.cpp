#include <i18n.h>
#include "hotkeyConfig.h"
#include "preferenceManager.h"
#include "shipTemplate.h"

HotkeyConfig hotkeys;

HotkeyConfig::HotkeyConfig()
{  // this list includes all Hotkeys and their standard configuration
    newCategory("GENERAL", "General");
    newKey("NEXT_STATION", std::make_tuple("Switch to next crew station", "Tab"));
    newKey("PREV_STATION", std::make_tuple("Switch to previous crew station", ""));
    newKey("STATION_HELMS", std::make_tuple("Switch to helms station", "F2"));
    newKey("STATION_WEAPONS", std::make_tuple("Switch to weapons station", "F3"));
    newKey("STATION_ENGINEERING", std::make_tuple("Switch to engineering station", "F4"));
    newKey("STATION_SCIENCE", std::make_tuple("Switch to science station", "F5"));
    newKey("STATION_RELAY", std::make_tuple("Switch to relay station", "F6"));

    newCategory("MAIN_SCREEN", "Main Screen");
    newKey("VIEW_FORWARD", std::make_tuple("View forward", "Up"));
    newKey("VIEW_LEFT", std::make_tuple("View left", "Left"));
    newKey("VIEW_RIGHT", std::make_tuple("View right", "Right"));
    newKey("VIEW_BACK", std::make_tuple("View backward", "Down"));
    newKey("VIEW_TARGET", std::make_tuple("Lock view on weapons target", "T"));
    newKey("TACTICAL_RADAR", std::make_tuple("View tactical radar", "Tab"));
    newKey("LONG_RANGE_RADAR", std::make_tuple("View long-range radar", "Q"));
    newKey("FAR_RANGE_RADAR", std::make_tuple("View far-range radar", ""));
    newKey("TARGET_ANALYSIS", std::make_tuple("View target analysis", ""));
    newKey("FIRST_PERSON", std::make_tuple("Toggle first-person view", "F"));

    newCategory("HELMS", "Helms");
    newKey("INC_IMPULSE", std::make_tuple("Increase impulse", "Up"));
    newKey("DEC_IMPULSE", std::make_tuple("Decrease impulse", "Down"));
    newKey("ZERO_IMPULSE", std::make_tuple("Zero impulse", "Space"));
    newKey("MAX_IMPULSE", std::make_tuple("Max impulse", ""));
    newKey("MIN_IMPULSE", std::make_tuple("Max reverse impulse", ""));
    newKey("TURN_LEFT", std::make_tuple("Turn left", "Left"));
    newKey("TURN_RIGHT", std::make_tuple("Turn right", "Right"));
    newKey("WARP_0", std::make_tuple("Warp off", ""));
    newKey("WARP_1", std::make_tuple("Warp 1", ""));
    newKey("WARP_2", std::make_tuple("Warp 2", ""));
    newKey("WARP_3", std::make_tuple("Warp 3", ""));
    newKey("WARP_4", std::make_tuple("Warp 4", ""));
    newKey("DEC_WARP", std::make_tuple("Decrease Warp", ""));
    newKey("INC_WARP", std::make_tuple("Increase Warp", ""));
    newKey("DOCK_ACTION", std::make_tuple("Dock request/abort/undock", "D"));
    newKey("DOCK_REQUEST", std::make_tuple("Initiate docking", ""));
    newKey("DOCK_ABORT", std::make_tuple("Abort docking", ""));
    newKey("UNDOCK", std::make_tuple("Undock", "D"));
    newKey("INC_JUMP", std::make_tuple("Increase jump distance", ""));
    newKey("DEC_JUMP", std::make_tuple("Decrease jump distance", ""));
    newKey("JUMP", std::make_tuple("Initiate jump", ""));
    newKey("COMBAT_LEFT", std::make_tuple("Combat maneuver left", ""));
    newKey("COMBAT_RIGHT", std::make_tuple("Combat maneuver right", ""));
    newKey("COMBAT_BOOST", std::make_tuple("Combat maneuver boost", ""));
    newKey("COMBAT_STOP", std::make_tuple("Combat maneuver stop", ""));

    newCategory("WEAPONS", "Weapons");
    newKey("SELECT_MISSILE_TYPE_HOMING", std::make_tuple("Select homing", "Num1"));
    newKey("SELECT_MISSILE_TYPE_NUKE", std::make_tuple("Select nuke", "Num2"));
    newKey("SELECT_MISSILE_TYPE_MINE", std::make_tuple("Select mine", "Num3"));
    newKey("SELECT_MISSILE_TYPE_EMP", std::make_tuple("Select EMP", "Num4"));
    newKey("SELECT_MISSILE_TYPE_HVLI", std::make_tuple("Select HVLI", "Num5"));
    for(int n=0; n<max_weapon_tubes; n++)
        newKey(std::string("LOAD_TUBE_") + string(n+1), std::make_tuple(std::string("Load tube ") + string(n+1), ""));
    for(int n=0; n<max_weapon_tubes; n++)
        newKey(std::string("UNLOAD_TUBE_") + string(n+1), std::make_tuple(std::string("Unload tube ") + string(n+1), ""));
    for(int n=0; n<max_weapon_tubes; n++)
        newKey(std::string("FIRE_TUBE_") + string(n+1), std::make_tuple(std::string("Fire tube ") + string(n+1), ""));
    newKey("NEXT_ENEMY_TARGET", std::make_tuple("Select next target", ""));
    newKey("NEXT_TARGET", std::make_tuple("Select next target (any)", ""));
    newKey("TOGGLE_SHIELDS", std::make_tuple("Toggle shields", "S"));
    newKey("ENABLE_SHIELDS", std::make_tuple("Enable shields", ""));
    newKey("DISABLE_SHIELDS", std::make_tuple("Disable shields", ""));
    newKey("SHIELD_CAL_INC", std::make_tuple("Increase shield frequency target", ""));
    newKey("SHIELD_CAL_DEC", std::make_tuple("Decrease shield frequency target", ""));
    newKey("SHIELD_CAL_START", std::make_tuple("Start shield calibration", ""));
    newKey("BEAM_SUBSYSTEM_TARGET_NEXT", std::make_tuple("Next beam subsystem target type", ""));
    newKey("BEAM_SUBSYSTEM_TARGET_PREV", std::make_tuple("Previous beam subsystem target type", ""));
    newKey("BEAM_FREQUENCY_INCREASE", std::make_tuple("Increase beam frequency", ""));
    newKey("BEAM_FREQUENCY_DECREASE", std::make_tuple("Decrease beam frequency", ""));
    newKey("TOGGLE_AIM_LOCK", std::make_tuple("Toggle missile aim lock", ""));
    newKey("ENABLE_AIM_LOCK", std::make_tuple("Enable missile aim lock", ""));
    newKey("DISABLE_AIM_LOCK", std::make_tuple("Disable missile aim lock", ""));
    newKey("AIM_MISSILE_LEFT", std::make_tuple("Turn missile aim to the left", ""));
    newKey("AIM_MISSILE_RIGHT", std::make_tuple("Turn missile aim to the right", ""));

    newCategory("SCIENCE", "Science");
    newKey("SCAN_OBJECT", std::make_tuple("Scan object", "S"));
    newKey("NEXT_SCANNABLE_OBJECT", std::make_tuple("Select next scannable object", "C"));
    newKey("ABORD_SCAN", std::make_tuple("Abord scanning", ""));
    newKey("SHOW_DATABASE", std::make_tuple("Show database", ""));
    newKey("SHOW_PROBE", std::make_tuple("Show probe radar", ""));
    newKey("SHOW_RADAR", std::make_tuple("Show main radar", ""));
    newKey("INC_ZOOM", std::make_tuple("Increase zoom level", ""));
    newKey("DEC_ZOOM", std::make_tuple("Decrease zoom level", ""));
    for(int n=0; n<3; n++)
    {
        newKey("SCAN_LEFT_" + string(n+1), std::make_tuple("Scan " + string(n+1) + " left", ""));
        newKey("SCAN_RIGHT_" + string(n+1), std::make_tuple("Scan " + string(n+1) + " right", ""));
    }

    newCategory("ENGINEERING", "Engineering");
    newKey("SELECT_REACTOR", std::make_tuple("Select reactor system", "A"));
    newKey("SELECT_BEAM_WEAPONS", std::make_tuple("Select beam weapon system", "Z"));
    newKey("SELECT_MISSILE_SYSTEM", std::make_tuple("Select missile weapon system", "E"));
    newKey("SELECT_MANEUVER", std::make_tuple("Select maneuvering system", "R"));
    newKey("SELECT_IMPULSE", std::make_tuple("Select impulse system", "Q"));
    newKey("SELECT_WARP", std::make_tuple("Select warp system", "S"));
    newKey("SELECT_JUMP_DRIVE", std::make_tuple("Select jump drive system", "D"));
    newKey("SELECT_FRONT_SHIELDS", std::make_tuple("Select front shields system", "F"));
    newKey("SELECT_REAR_SHIELDS", std::make_tuple("Select rear shields system", "W"));
    newKey("SELECT_DOCKS", std::make_tuple("Select docks system", "X"));
    newKey("SELECT_SCANNER", std::make_tuple("Select scanner system", "C"));
    newKey("SELECT_NEXT_SYSTEM", std::make_tuple("Select next system", "F2"));
    newKey("SELECT_PREVIOUS_SYSTEM", std::make_tuple("Select previous system", "F3"));
    newKey("RESET_SYSTEMS", std::make_tuple("Reset all systems setting", "Space"));
    newKey("SET_POWER_000", std::make_tuple("Set system power to 0%", "Y"));
    newKey("SET_POWER_030", std::make_tuple("Set system power to 30%", ""));
    newKey("SET_POWER_050", std::make_tuple("Set system power to 50%", ""));
    newKey("SET_POWER_100", std::make_tuple("Set system power to 100%", ""));
    newKey("SET_POWER_150", std::make_tuple("Set system power to 150%", ""));
    newKey("SET_POWER_200", std::make_tuple("Set system power to 200%", ""));
    newKey("SET_POWER_250", std::make_tuple("Set system power to 250%", ""));
    newKey("SET_POWER_300", std::make_tuple("Set system power to 300%", "O"));
    newKey("INCREASE_POWER", std::make_tuple("Increase system power", "U"));
    newKey("DECREASE_POWER", std::make_tuple("Decrease system power", "I"));
    newKey("INCREASE_COOLANT", std::make_tuple("Increase system coolant", "K"));
    newKey("DECREASE_COOLANT", std::make_tuple("Decrease system coolant", "J"));
    newKey("COOLANT_MAX", std::make_tuple("Set system coolant to max", "L"));
    newKey("COOLANT_MIN", std::make_tuple("Set system coolant to min", "H"));
    newKey("INCREASE_REPAIR", std::make_tuple("Increase system repair", "SemiColon"));
    newKey("DECREASE_REPAIR", std::make_tuple("Decrease system repair", "Comma"));
    newKey("REPAIR_MAX", std::make_tuple("Set system repair to max", "Equal"));
    newKey("REPAIR_MIN", std::make_tuple("Set system repair to min", "N"));
    newKey("NEXT_REPAIR_CREW", std::make_tuple("Next repair crew", ""));
    newKey("REPAIR_CREW_MOVE_UP", std::make_tuple("Crew move up", ""));
    newKey("REPAIR_CREW_MOVE_DOWN", std::make_tuple("Crew move down", ""));
    newKey("REPAIR_CREW_MOVE_LEFT", std::make_tuple("Crew move left", ""));
    newKey("REPAIR_CREW_MOVE_RIGHT", std::make_tuple("Crew move right", ""));
    newKey("SELF_DESTRUCT_START", std::make_tuple("Start self-destruct", ""));
    newKey("SELF_DESTRUCT_CONFIRM", std::make_tuple("Confirm self-destruct", ""));
    newKey("SELF_DESTRUCT_CANCEL", std::make_tuple("Cancel self-destruct", ""));
    for(int presetId=1; presetId < 10; presetId++) 
    {
        newKey("PRESET_APPLY" + string(presetId), std::make_tuple("Apply engineer preset " + string(presetId), "Numpad" + string(presetId)));
            newKey("PRESET_UPDATE" + string(presetId), std::make_tuple("Update engineer preset " + string(presetId), "[shift]Numpad" + string(presetId)));
    }

    newCategory("RELAY", "Relay");
    newKey("OPEN_COMM", std::make_tuple("Open Comms", "F11"));
    newKey("LINK_SCIENCE", std::make_tuple("Link probe to science station", "F8"));
    newKey("BEGIN_HACK", std::make_tuple("Hack target", "F9"));
    newKey("ADD_WAYPOINT", std::make_tuple("Add waypoint to map", "F4"));
    newKey("DELETE_WAYPOINT", std::make_tuple("Remove the selected waypoint", "F5"));
    newKey("LAUNCH_PROBE", std::make_tuple("Launch probe", "F7"));
    newKey("INC_ZOOM", std::make_tuple("Increase zoom level", "F1"));
    newKey("DEC_ZOOM", std::make_tuple("Decrease zoom level", "F2"));
    newKey("OPEN_LOG", std::make_tuple("Open log", "PageUp"));
    newKey("ALERT_NORMAL", std::make_tuple("Switch to normal alert", "U"));
    newKey("ALERT_YELLOW", std::make_tuple("Switch to yellow alert", "I"));
    newKey("ALERT_RED", std::make_tuple("Switch to red alert", "O"));

    newCategory("INSTABILITY", "Instability");
    newKey("SELECT_REACTOR", std::make_tuple("Select reactor system", "A"));
    newKey("SELECT_BEAM_WEAPONS", std::make_tuple("Select beam weapon system", "Z"));
    newKey("SELECT_MISSILE_SYSTEM", std::make_tuple("Select missile weapon system", "E"));
    newKey("SELECT_MANEUVER", std::make_tuple("Select maneuvering system", "R"));
    newKey("SELECT_IMPULSE", std::make_tuple("Select impulse system", "Q"));
    newKey("SELECT_WARP", std::make_tuple("Select warp system", "S"));
    newKey("SELECT_JUMP_DRIVE", std::make_tuple("Select jump drive system", "D"));
    newKey("SELECT_FRONT_SHIELDS", std::make_tuple("Select front shields system", "F"));
    newKey("SELECT_REAR_SHIELDS", std::make_tuple("Select rear shields system", "W"));
    newKey("SELECT_DOCKS", std::make_tuple("Select docks system", "X"));
    newKey("SELECT_DRONES", std::make_tuple("Select drones system", "C"));
    newKey("INCREASE_SLIDER_1", std::make_tuple("Increase slider 1", "Z"));
    newKey("INCREASE_SLIDER_2", std::make_tuple("Increase slider 2", "S"));
    newKey("INCREASE_SLIDER_3", std::make_tuple("Increase slider 3", "X"));
    newKey("INCREASE_SLIDER_4", std::make_tuple("Increase slider 4", ""));
    newKey("DECREASE_SLIDER_1", std::make_tuple("Decrease slider 1", "A"));
    newKey("DECREASE_SLIDER_2", std::make_tuple("Decrease slider 2", "Q"));
    newKey("DECREASE_SLIDER_3", std::make_tuple("Decrease slider 3", "W"));
    newKey("DECREASE_SLIDER_4", std::make_tuple("Decrease slider 4", ""));
    
    newCategory("RADAR", "Radar");
    newKey("INC_ZOOM", std::make_tuple("Increase zoom level", "Add"));
    newKey("DEC_ZOOM", std::make_tuple("Decrease zoom level", "Subtract"));

}

static std::vector<std::pair<string, sf::Keyboard::Key> > sfml_key_names = {
    {"A", sf::Keyboard::A},
    {"B", sf::Keyboard::B},
    {"C", sf::Keyboard::C},
    {"D", sf::Keyboard::D},
    {"E", sf::Keyboard::E},
    {"F", sf::Keyboard::F},
    {"G", sf::Keyboard::G},
    {"H", sf::Keyboard::H},
    {"I", sf::Keyboard::I},
    {"J", sf::Keyboard::J},
    {"K", sf::Keyboard::K},
    {"L", sf::Keyboard::L},
    {"M", sf::Keyboard::M},
    {"N", sf::Keyboard::N},
    {"O", sf::Keyboard::O},
    {"P", sf::Keyboard::P},
    {"Q", sf::Keyboard::Q},
    {"R", sf::Keyboard::R},
    {"S", sf::Keyboard::S},
    {"T", sf::Keyboard::T},
    {"U", sf::Keyboard::U},
    {"V", sf::Keyboard::V},
    {"W", sf::Keyboard::W},
    {"X", sf::Keyboard::X},
    {"Y", sf::Keyboard::Y},
    {"Z", sf::Keyboard::Z},
    {"Num0", sf::Keyboard::Num0},
    {"Num1", sf::Keyboard::Num1},
    {"Num2", sf::Keyboard::Num2},
    {"Num3", sf::Keyboard::Num3},
    {"Num4", sf::Keyboard::Num4},
    {"Num5", sf::Keyboard::Num5},
    {"Num6", sf::Keyboard::Num6},
    {"Num7", sf::Keyboard::Num7},
    {"Num8", sf::Keyboard::Num8},
    {"Num9", sf::Keyboard::Num9},
    {"Escape", sf::Keyboard::Escape},
    {"LControl", sf::Keyboard::LControl},
    {"LShift", sf::Keyboard::LShift},
    {"LAlt", sf::Keyboard::LAlt},
    {"LSystem", sf::Keyboard::LSystem},
    {"RControl", sf::Keyboard::RControl},
    {"RShift", sf::Keyboard::RShift},
    {"RAlt", sf::Keyboard::RAlt},
    {"RSystem", sf::Keyboard::RSystem},
    {"Menu", sf::Keyboard::Menu},
    {"LBracket", sf::Keyboard::LBracket},
    {"RBracket", sf::Keyboard::RBracket},
    {"SemiColon", sf::Keyboard::SemiColon},
    {"Comma", sf::Keyboard::Comma},
    {"Period", sf::Keyboard::Period},
    {"Quote", sf::Keyboard::Quote},
    {"Slash", sf::Keyboard::Slash},
    {"BackSlash", sf::Keyboard::BackSlash},
    {"Tilde", sf::Keyboard::Tilde},
    {"Equal", sf::Keyboard::Equal},
    {"Dash", sf::Keyboard::Dash},
    {"Space", sf::Keyboard::Space},
    {"Return", sf::Keyboard::Return},
    {"BackSpace", sf::Keyboard::BackSpace},
    {"Tab", sf::Keyboard::Tab},
    {"PageUp", sf::Keyboard::PageUp},
    {"PageDown", sf::Keyboard::PageDown},
    {"End", sf::Keyboard::End},
    {"Home", sf::Keyboard::Home},
    {"Insert", sf::Keyboard::Insert},
    {"Delete", sf::Keyboard::Delete},
    {"Add", sf::Keyboard::Add},
    {"Subtract", sf::Keyboard::Subtract},
    {"Multiply", sf::Keyboard::Multiply},
    {"Divide", sf::Keyboard::Divide},
    {"Left", sf::Keyboard::Left},
    {"Right", sf::Keyboard::Right},
    {"Up", sf::Keyboard::Up},
    {"Down", sf::Keyboard::Down},
    {"Numpad0", sf::Keyboard::Numpad0},
    {"Numpad1", sf::Keyboard::Numpad1},
    {"Numpad2", sf::Keyboard::Numpad2},
    {"Numpad3", sf::Keyboard::Numpad3},
    {"Numpad4", sf::Keyboard::Numpad4},
    {"Numpad5", sf::Keyboard::Numpad5},
    {"Numpad6", sf::Keyboard::Numpad6},
    {"Numpad7", sf::Keyboard::Numpad7},
    {"Numpad8", sf::Keyboard::Numpad8},
    {"Numpad9", sf::Keyboard::Numpad9},
    {"F1", sf::Keyboard::F1},
    {"F2", sf::Keyboard::F2},
    {"F3", sf::Keyboard::F3},
    {"F4", sf::Keyboard::F4},
    {"F5", sf::Keyboard::F5},
    {"F6", sf::Keyboard::F6},
    {"F7", sf::Keyboard::F7},
    {"F8", sf::Keyboard::F8},
    {"F9", sf::Keyboard::F9},
    {"F10", sf::Keyboard::F10},
    {"F11", sf::Keyboard::F11},
    {"F12", sf::Keyboard::F12},
    {"F13", sf::Keyboard::F13},
    {"F14", sf::Keyboard::F14},
    {"F15", sf::Keyboard::F15},
    {"Pause", sf::Keyboard::Pause},
};

void HotkeyConfig::load()
{
    for(HotkeyConfigCategory& cat : categories)
    {
        for(HotkeyConfigItem& item : cat.hotkeys)
        {
            string key_config = PreferencesManager::get(std::string("HOTKEY.") + cat.key + "." + item.key, std::get<1>(item.value));
            item.load(key_config);
        }
    }
}

std::vector<HotkeyResult> HotkeyConfig::getHotkey(sf::Event::KeyEvent key)
{
    std::vector<HotkeyResult> results;
    for(HotkeyConfigCategory& cat : categories)
    {
        for(HotkeyConfigItem& item : cat.hotkeys)
        {
            if (item.hotkey.code == key.code && item.hotkey.alt == key.alt && item.hotkey.control == key.control && item.hotkey.shift == key.shift && item.hotkey.system == key.system)
            {
                results.emplace_back(cat.key, item.key);
            }
        }
    }
    return results;
}

void HotkeyConfig::newCategory(string key, string name)
{
    categories.emplace_back();
    categories.back().key = key;
    categories.back().name = name;
}

void HotkeyConfig::newKey(string key, std::tuple<string, string> value)
{
    categories.back().hotkeys.emplace_back(key, value);
}

std::vector<string> HotkeyConfig::getCategories()
{
    // Initialize return value.
    std::vector<string> ret;

    // Add each category to the return value.
    for(HotkeyConfigCategory& cat : categories)
    {
        ret.push_back(cat.name);
    }

    return ret;
}

std::vector<std::pair<string, string>> HotkeyConfig::listHotkeysByCategory(string hotkey_category)
{
    std::vector<std::pair<string, string>> ret;

    for(HotkeyConfigCategory& cat : categories)
    {
        if (cat.name == hotkey_category)
        {
            for(HotkeyConfigItem& item : cat.hotkeys)
            {
                for(auto key_name : sfml_key_names)
                {
                    if (key_name.second == item.hotkey.code)
                    {
                        string keyModifier = "";
                        if (item.hotkey.shift) {
                            keyModifier = "Shift+";
                        } else if (item.hotkey.control) {
                            keyModifier = "Ctrl+";
                        } else if (item.hotkey.alt){
                            keyModifier = "Alt+";
                        }
                        ret.push_back({std::get<0>(item.value), keyModifier + key_name.first});
                    }
                }
            }
        }
    }

    return ret;
}

HotkeyConfigItem::HotkeyConfigItem(string key, std::tuple<string, string> value)
{
    this->key = key;
    this->value = value;
    hotkey.code = sf::Keyboard::KeyCount;
    hotkey.alt = false;
    hotkey.control = false;
    hotkey.shift = false;
    hotkey.system = false;
}

void HotkeyConfigItem::load(string key_config)
{
    for(const string& config : key_config.split(";"))
    {
        if (config == "[alt]")
            hotkey.alt = true;
        else if (config == "[control]")
            hotkey.control = true;
        else if (config == "[shift]")
            hotkey.shift = true;
        else if (config == "[system]")
            hotkey.system = true;
        else
        {
            for(auto key_name : sfml_key_names)
            {
                if (key_name.first == config)
                {
                    hotkey.code = key_name.second;
                    break;
                }
            }
        }
    }
}
