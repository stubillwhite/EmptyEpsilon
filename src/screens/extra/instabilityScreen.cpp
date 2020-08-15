#include "instabilityScreen.h"

#include "playerInfo.h"
#include "spaceObjects/playerSpaceship.h"
#include "screenComponents/customShipFunctions.h"

#include "gui/gui2_autolayout.h"
#include "gui/gui2_panel.h"
#include "gui/gui2_label.h"
#include "gui/gui2_slider.h"
#include "gui/gui2_progressbar.h"
#include "gui/gui2_keyvaluedisplay.h"

InstabilityScreen::InstabilityScreen(GuiContainer* owner)
: GuiOverlay(owner, "INSTABILITY_SCREEN", colorConfig.background)
{
    selected_system = SYS_None;

    GuiAutoLayout* layout = new GuiAutoLayout(this, "", GuiAutoLayout::LayoutHorizontalLeftToRight);
    layout->setPosition(20, 60, ATopLeft)->setSize(GuiElement::GuiSizeMax, 400);
    for(int n=0; n<SYS_COUNT; n++)
    {
        if (n == 4)
        {
            //Start the 2nd row after 4 elements.
            layout = new GuiAutoLayout(this, "", GuiAutoLayout::LayoutHorizontalLeftToRight);
            layout->setPosition(20, 450, ATopLeft)->setSize(GuiElement::GuiSizeMax, 400);
        }

        GuiPanel* box = new GuiPanel(layout, "");
        systems[n].box = box;
        box->setSize(290, 400);

        (new GuiLabel(box, "", getLocaleSystemName(ESystem(n)), 30))->addBackground()->setAlignment(ACenter)->setPosition(0, 0, ATopLeft)->setSize(290, 50);
        (new GuiLabel(box, "", "Stability_x", 30))->setVertical()->setAlignment(ACenterLeft)->setPosition(20, 50, ATopLeft)->setSize(30, 340);
        (new GuiLabel(box, "", "Stability_y", 30))->setVertical()->setAlignment(ACenterLeft)->setPosition(100, 50, ATopLeft)->setSize(30, 340);
        (new GuiLabel(box, "", "Instability", 30))->setVertical()->setAlignment(ACenterLeft)->setPosition(180, 50, ATopLeft)->setSize(30, 340);

        systems[n].stability_x_slider = new GuiSlider(box, "", -1.0, 1.0, 0.0, [this, n](float value) {
            if (my_spaceship) my_spaceship->systems[n].instability_x_value = value;
        });        
        systems[n].stability_x_slider->setPosition(50, 50, ATopLeft)->setSize(55, 340);

        systems[n].stability_y_slider = new GuiSlider(box, "", -1.0, 1.0, 0.0, [this, n](float value) {
            if (my_spaceship) my_spaceship->systems[n].instability_y_value = value;
        });
        systems[n].stability_y_slider->setPosition(130, 50, ATopLeft)->setSize(55, 340);

        systems[n].instability_bar = new GuiProgressbar(box, "", 0.0, 1.0, 0.0);
        systems[n].instability_bar->setPosition(210, 60, ATopLeft)->setSize(50, 320);
    }

    (new GuiCustomShipFunctions(this, powerManagement, ""))->setPosition(-20, 120, ATopRight)->setSize(250, GuiElement::GuiSizeMax);

    previous_time = 0.0;
    delta_t = 0.0;

    // TODO: Hotkey help overlay
}

void InstabilityScreen::onDraw(sf::RenderTarget& window)
{
    GuiOverlay::onDraw(window);

    for(int n=0; n<SYS_COUNT; n++)
    {
	systems[n].box->setVisible(my_spaceship->hasSystem(ESystem(n)));
	float instability = my_spaceship->getSystemInstabilityLevel(ESystem(n));
        systems[n].instability_bar->setValue(instability)->setColor(sf::Color(128, 128 * (1.0 - instability), 0));
        systems[n].stability_x_slider->setValue(my_spaceship->systems[n].instability_x_value);
        systems[n].stability_y_slider->setValue(my_spaceship->systems[n].instability_y_value);
    }
}
