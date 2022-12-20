#include <SFML/Graphics.hpp>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <cmath>

const float PLAYER_SPEED = 0.1;

using namespace std;

void glEnable2D() {
    GLint iViewport[4];

    //get a copy of the viewport
    glGetIntegerv(GL_VIEWPORT, iViewport);

    //save a copy of the projection matrix so we can restore it
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    //load identity projection matrix
    glLoadIdentity();

    //set up orthographic projection
    glOrtho(iViewport[0], iViewport[0]+iViewport[2], iViewport[1]+iViewport[3], iViewport[1], -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    //ensure lighting and depth testing are disabled
    glPushAttrib(GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
}

void glDisable2D() {
    glPopAttrib();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

const float DEG2RAD = 3.14159/180;

void drawCircle(float radius) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i=0; i<360; i++) {
        float rad = i*DEG2RAD;
        glVertex2f(cos(rad)*radius, sin(rad)*radius);
    }
    glEnd();
}

float getVecMagnitude(sf::Vector2f v) {
    return (sqrt(v.x*v.x + v.y*v.y));
}

// I'm just leaving this CORRECTED code here, and not bothering to get it working with the rest of the code.
// The following three functions is what I ended up with to continue on, last time I was here.

vector2fl scaleAndFilterJoystickVector(vector2fl inputVec)
{
    inputVec = inputVec / 100.f;

    if (inputVec.getMagnitude() < 0.15) {
        return vector2fl();
    }
    else {
        return inputVec;
    }
}

vector2fl getFilteredLeftStickVector()
{
    return scaleAndFilterJoystickVector(
        vector2fl(sf::Joystick::getAxisPosition(0, sf::Joystick::X),
                  sf::Joystick::getAxisPosition(0, sf::Joystick::Y)
                )
    );
}

vector2fl getFilteredRightStickVector()
{
    return scaleAndFilterJoystickVector(
        vector2fl(sf::Joystick::getAxisPosition(0, sf::Joystick::U),
                  sf::Joystick::getAxisPosition(0, sf::Joystick::V)
                )
    );
}

class Player {
public:
    sf::Vector2f pos;

    Player() {
        pos = sf::Vector2f(100,100);
    }

    void go() {
        handleInput();
    }

    void handleInput() {
        sf::Vector2f input = joystickAxisToFilterdVector(0, 0);
        
        pos += input * PLAYER_SPEED;
    }
} player;

void go() {
    player.go();
}

void display(sf::RenderWindow &window) {
    window.clear(); // Clear the buffer

            glClearColor(0,0,0,0);
            glClear(GL_COLOR_BUFFER_BIT);
            glColor3f(0,1,0);

            glEnable2D();
            glPushMatrix();
            glTranslatef(player.pos.x, player.pos.y, 0);
            drawCircle(5);
            glPopMatrix();
            glDisable2D();

    window.display(); // Update window contents
}

int main (int argc, char **argv) {
    sf::RenderWindow window(sf::VideoMode(640, 480), "OpenGL Test", sf::Style::Close | sf::Style::Titlebar);

    // Your own custom OpenGL setup calls here
    // There's no additional code needed, unless you want to mix SFML drawing and raw OpenGL

    sf::Event e;

    while (window.isOpen()) { // This is the program's main loop

        while (window.pollEvent(e)) { // Event handling
            switch (e.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                default:
                    break;
            }
        }

        go();

        display(window);
    }
    return 0;
}
