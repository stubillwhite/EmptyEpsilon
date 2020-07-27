#ifndef INSTABILITY_H
#define INSTABILITY_H

#include "gui/gui2_overlay.h"
#include "shipTemplate.h"

class GuiPanel;
class GuiSlider;
class GuiProgressbar;
class GuiKeyValueDisplay;

class InstabilityScreen : public GuiOverlay
{
private:
    float previous_time;
    float delta_t;
    ESystem selected_system = SYS_None;

    class SystemRow
    {
    public:
        GuiPanel* box;
        GuiSlider* stability_x_slider;
        GuiSlider* stability_y_slider;
        GuiProgressbar* stability_x_bar;
        GuiProgressbar* stability_y_bar;
        GuiProgressbar* instability_bar;
        float x = 0.0;
        float y = 0.0;
        float x_target = 0.0;
        float y_target = 0.0;
        int x_pos = 1;
        int y_pos = 1; 
    };
    SystemRow systems[SYS_COUNT];
public:
    InstabilityScreen(GuiContainer* owner);
    
    void onDraw(sf::RenderTarget& window) override;

};

#endif//INSTABILITY_H
