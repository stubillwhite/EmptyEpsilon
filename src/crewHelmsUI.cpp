#include "crewHelmsUI.h"

CrewHelmsUI::CrewHelmsUI()
{
    jump_distance = 1.0;
    ghost_delay = 0.0;
}

void CrewHelmsUI::update(float delta)
{
    if (!my_spaceship)
        return;
        
    if (ghost_delay > 0)
    {
        ghost_delay -= delta;
    }else{
        ghost_delay = 5.0;

        foreach(SpaceObject, obj, space_object_list)
        {
            P<SpaceShip> ship = obj;
            if (ship && sf::length(obj->getPosition() - my_spaceship->getPosition()) < 5000.0)
            {
                ghost_dot.push_back(HelmsGhostDot(obj->getPosition()));
            }
        }
    }
    for(unsigned int n=0; n<ghost_dot.size(); n++)
    {
        HelmsGhostDot& ghost = ghost_dot[n];
        ghost.lifetime -= delta;
        if (ghost.lifetime <= 0.0)
        {
            ghost_dot.erase(ghost_dot.begin() + n);
            n--;
        }
    }
    
    CrewUI::update(delta);
}

void CrewHelmsUI::onCrewUI()
{
    sf::Vector2f mouse = InputHandler::getMousePos();
    sf::Vector2f radar_center = getWindowSize() / 2.0f;
    if (InputHandler::mouseIsPressed(sf::Mouse::Left) || InputHandler::mouseIsReleased(sf::Mouse::Left))
    {
        sf::Vector2f diff = mouse - radar_center;
        if (sf::length(diff) < 400)
            my_spaceship->commandTargetRotation(sf::vector2ToAngle(diff));
    }
    
    sf::VertexArray ghost_dots(sf::Points, ghost_dot.size());
    for(unsigned int n=0; n<ghost_dot.size(); n++)
    {
        ghost_dots[n].position = radar_center + (ghost_dot[n].position - my_spaceship->getPosition()) / 5000.0f * 400.0f;
        ghost_dots[n].color = sf::Color(255, 255, 255, 255 * (ghost_dot[n].lifetime / HelmsGhostDot::total_lifetime));
    }
    getRenderTarget()->draw(ghost_dots);

    drawRadar(radar_center, 400, 5000, false, my_spaceship->getTarget());
    if (InputHandler::mouseIsDown(sf::Mouse::Left))
    {
        sf::Vector2f diff = mouse - radar_center;
        if (sf::length(diff) < 400)
        {
            sf::Vector2f text_pos = mouse;
            if (engine->getObject("mouseRenderer"))
                text_pos.y -= 10.0;
            else
                text_pos.y -= 20.0;
            text(sf::FloatRect(text_pos.x, text_pos.y, 0, 0), string(fmodf(sf::vector2ToAngle(diff) + 360.0, 360.0), 1), AlignCenter, 20);
        }
    }

    keyValueDisplay(sf::FloatRect(20, 100, 200, 40), 0.6, "Energy", string(int(my_spaceship->energy_level)), 25);
    keyValueDisplay(sf::FloatRect(20, 140, 200, 40), 0.6, "Heading", string(fmodf(my_spaceship->getRotation() + 360.0, 360.0), 1), 25);

    impulseSlider(sf::FloatRect(20, 400, 50, 300), 20);

    float x = 100;
    if (my_spaceship->hasWarpdrive)
    {
        warpSlider(sf::FloatRect(x, 400, 50, 300), 20);
        x += 80;
    }
    if (my_spaceship->hasJumpdrive)
    {
        jumpSlider(jump_distance, sf::FloatRect(x, 400, 50, 300), 20);
        x += 80;
        jumpButton(jump_distance, sf::FloatRect(20, 750, 280, 50), 30);
    }

    dockingButton(sf::FloatRect(20, 800, 280, 50), 30);
}