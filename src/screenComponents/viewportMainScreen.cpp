#include "viewportMainScreen.h"
#include "playerInfo.h"
#include "preferenceManager.h"
#include "spaceObjects/playerSpaceship.h"

GuiViewportMainScreen::GuiViewportMainScreen(GuiContainer* owner, string id)
: GuiViewport3D(owner, id)
{
    uint8_t flags = PreferencesManager::get("ship_mainscreen_flags","0").toInt();

    LOG(INFO) << "SBW: flags: " << flags;

    if (flags & flag_callsigns)
        showCallsigns();
    if (flags & flag_headings)
        showHeadings();
    if (flags & flag_spacedust)
        showSpacedust();

    first_person = PreferencesManager::get("first_person") == "1";
}

void GuiViewportMainScreen::onDraw(sf::RenderTarget& window)
{
    if (my_spaceship)
    {
        P<SpaceObject> target_ship = my_spaceship->getTarget();
        float target_camera_yaw = my_spaceship->getRotation();
        switch(my_spaceship->main_screen_setting)
        {
        case MSS_Back: target_camera_yaw += 180; break;
        case MSS_Left: target_camera_yaw -= 90; break;
        case MSS_Right: target_camera_yaw += 90; break;
        case MSS_Target:
            if (target_ship)
            {
                sf::Vector2f target_camera_diff = my_spaceship->getPosition() - target_ship->getPosition();
                target_camera_yaw = sf::vector2ToAngle(target_camera_diff) + 180;
            }
            break;
        default: break;
        }
        camera_pitch = 30.0f;

        float camera_ship_distance = 420.0f;
        float camera_ship_height = 420.0f + my_spaceship->getPositionZ();
        if (first_person)
        {
            camera_ship_distance = -my_spaceship->getRadius();
            // camera_ship_height = my_spaceship->getRadius() / 10.f + my_spaceship->getPositionZ();
            camera_ship_height = 15.0f;
            camera_pitch = 0;
        }
        sf::Vector2f cameraPosition2D = my_spaceship->getPosition() + sf::vector2FromAngle(target_camera_yaw) * -camera_ship_distance;
        sf::Vector3f targetCameraPosition(cameraPosition2D.x, cameraPosition2D.y, camera_ship_height);
//#ifdef DEBUG
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            targetCameraPosition.x = my_spaceship->getPosition().x;
            targetCameraPosition.y = my_spaceship->getPosition().y;
            targetCameraPosition.z = 3000.0;
            camera_pitch = 90.0f;
        }
//#endif

        if (first_person)
        {
            camera_position = targetCameraPosition;
            camera_yaw = target_camera_yaw;
        }
        else
        {
            camera_position = camera_position * 0.9f + targetCameraPosition * 0.1f;
            camera_yaw += sf::angleDifference(camera_yaw, target_camera_yaw) * 0.1f;
        }

        // LOG(INFO)
        //     << "SBW: " << my_spaceship->getCallSign() << "-" << first_person
        //     << ", my_spaceship->getPosition() [" << my_spaceship->getPosition().x << ", " << my_spaceship->getPosition().y << ", " << my_spaceship->getPositionZ() << "]"
        //     << ", camera_position [" << camera_position.x << ", " << camera_position.y << ", " << camera_position.z << "]"
        //     << ", target_camera_position [" << targetCameraPosition.x << ", " << targetCameraPosition.y << ", " << targetCameraPosition.z << "]"
        //     << ", camera_ship_distance " << camera_ship_distance
        //     << ", camera_ship_height " << camera_ship_height
        //     // << ", camera_yaw " << camera_yaw
        //     // << ", dx " << (my_spaceship->getPosition().x - camera_position.x)
        //     // << ", camera_pitch " << camera_pitch
        //     ;
    }
    GuiViewport3D::onDraw(window);
}
