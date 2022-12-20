#include "graphics.h"
#include "myvectors.h"
#include "common.h"
#include "ship.h"

sf::RenderWindow* setupGraphics(bool fullscreen)
{
    // choose a good videomode
    sf::VideoMode chosenMode;
    if (!fullscreen)
    {
        chosenMode = sf::VideoMode(1280, 720, 24);
    }
    else
    {
        bool modeFound(false);

        auto modes = sf::VideoMode::getFullscreenModes();
        for (unsigned int i = 0; i < modes.size(); i++)
        {
            if (modes[i].width == 1920 && modes[i].height == 1080)
            {
                modeFound = true;
                chosenMode = modes[i];
                break;
            }
        }
        if (!modeFound) // gotta lower our standards!
        {
            for (unsigned int i = 0; i < modes.size(); i++)
            {
                if (modes[i].width <= 1920)
                {
                    modeFound = true;
                    chosenMode = modes[i];
                    break;
                }
            }
        }
        if (!modeFound)
        {
            // weird, but okay. Just choose the first mode found.
            modeFound = true;
            chosenMode = modes[0];
        }
        chosenMode.bitsPerPixel = 24;
    }

    // You'll need something like this to later use screen dimensions in your code
    // updateScreenDimensions(vector2i(chosenMode.width, chosenMode.height));

    auto flags =
        fullscreen ? sf::Style::Close | sf::Style::Fullscreen
                   : sf::Style::Close | sf::Style::Titlebar;
    sf::RenderWindow *window = new sf::RenderWindow(chosenMode, "SFML Start", flags);
    window->setKeyRepeatEnabled(false);

    sf::View view = window->getDefaultView();
    // view.setSize(chosenMode.width, chosenMode.height);
    view.setCenter(sf::Vector2f(0,0));
    view.zoom(0.1);
    window->setView(view);

    return window;
}

void display(sf::RenderWindow* window, Ship* ship)
{
    sf::Color backgroundColor(0, 0, 50);
    window->clear(backgroundColor);

    // draw ground
    sf::RectangleShape ground(sf::Vector2f(200, 20));
    ground.setOrigin(100, 10);
    ground.setPosition(sf::Vector2f(0, 10));
    ground.setFillColor(sf::Color::Blue);
    window->draw(ground);

    ship->display(window);

    sf::View view = window->getView();
    vector2fl cameraCenter = ship->getPos();
    cameraCenter.y *= -1;
    view.setCenter(toSFVec(cameraCenter));
    window->setView(view);

    window->display();
}

void Ship::display(sf::RenderWindow* window)
{
    sf::RectangleShape rect(sf::Vector2f(2, 2));
    rect.setOrigin(1, 1);
    vector2fl position = fromB2dVec(body->GetPosition());
    position.y *= -1;
    float rotation = body->GetAngle();
    rect.setPosition(toSFVec(position));
    rect.setRotation(-radToDeg(rotation));
    rect.setFillColor(sf::Color::Red);
    window->draw(rect);
}