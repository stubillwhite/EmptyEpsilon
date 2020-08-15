#ifndef SYSTEM_SCREEN_H
#define SYSTEM_SCREEN_H

#include "gui/gui2_overlay.h"
#include "shipTemplate.h"
#include "playerInfo.h"

class GuiPanel;
class GuiImage;
class GuiSlider;
class GuiLabel;
class GuiProgressbar;
class GuiKeyValueDisplay;
class GuiAutoLayout;
class GuiSelector;
class GuiElement;

class SystemScreen : public GuiOverlay
{
private:
    GuiOverlay* background_crosses;
    GuiAutoLayout* system_info;
    GuiAutoLayout* instability_info;
    GuiElement* instability_container;
    
    GuiSelector* system_selector;
    
    GuiProgressbar* damage_bar;
    GuiProgressbar* heat_bar;
    GuiProgressbar* power_bar;
    GuiProgressbar* coolant_bar;
    GuiProgressbar* effectiveness_bar;
    
    GuiLabel* system_title;
    GuiLabel* damage_title;
    GuiLabel* damage_label;
    GuiLabel* heat_title;
    GuiLabel* heat_label;
    GuiLabel* power_title;
    GuiLabel* power_label;
    GuiLabel* coolant_title;
    GuiLabel* coolant_label;
    GuiLabel* effectiveness_title;
    GuiLabel* effectiveness_label;
    GuiLabel* instability_label;
    GuiLabel* instability_x_label;
    GuiLabel* instability_y_label;
    
    GuiSlider* instability_x_slider;
    GuiSlider* instability_y_slider;
    
    GuiImage* damage_icon;
    GuiImage* heat_icon;
    GuiImage* power_icon;
    GuiImage* coolant_icon;
    GuiImage* effectiveness_icon;
    
    ESystem selected_system = SYS_None;
    void selectSystem(ESystem system);
    
public:
    SystemScreen(GuiContainer* owner);
    
    void onDraw(sf::RenderTarget& window) override;
    void updateInstability(sf::RenderTarget& window, GuiElement* container);

    virtual void onHotkey(const HotkeyResult& key) override;
};

#endif//SYSTEM_SCREEN_H
