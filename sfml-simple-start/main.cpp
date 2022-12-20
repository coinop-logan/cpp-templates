#include <SFML/Graphics.hpp>

using namespace std;

sf::Font font;

sf::RenderWindow* setupGraphics(bool fullscreen)
{
    // if (!font.loadFromFile("Andale_Mono.ttf"))
    //     throw runtime_error("Can't load main font");

    auto flags =
        fullscreen ? sf::Style::Close | sf::Style::Fullscreen
                   : sf::Style::Close | sf::Style::Titlebar;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(sf::Vector2u(1280, 720), 24), "SFML Start", flags);
    window->setKeyRepeatEnabled(false);

    return window;
}

float x = 50;

void display(sf::RenderWindow* window)
{
    sf::Color backgroundColor(0, 0, 50);
    window->clear(backgroundColor);

    sf::CircleShape circle(10);
    circle.setPosition(sf::Vector2f(x, 20));
    circle.setFillColor(sf::Color::Red);
    window->draw(circle);

    window->display();
}

int main (int argc, char **argv) {
    sf::RenderWindow* window = setupGraphics(false);

    // Your own custom OpenGL setup calls here
    // There's no additional code needed, unless you want to mix SFML drawing and raw OpenGL

    sf::Event e;

    while (window->isOpen()) { // This is the program's main loop

        while (window->pollEvent(e)) { // Event handling
            switch (e.type) {
                case sf::Event::MouseButtonPressed:
                    x = e.mouseButton.x;
                    break;
                case sf::Event::Closed:
                    window->close();
                    break;
                case sf::Event::KeyPressed:
                    x += 20;
                    break;
                default:
                    break;
            }
        }
        
        display(window);
    }

    delete window;
    
    return 0;
}