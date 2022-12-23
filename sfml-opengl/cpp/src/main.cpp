#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

int main()
{
    float cameraX = 0;
    // Create the window
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "3D Triangle");

    // Set the clear color to blue
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    // Set the viewport and projection matrix
    glViewport(0, 0, window.getSize().x, window.getSize().y);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat aspect = (GLfloat)window.getSize().x / (GLfloat)window.getSize().y;
    gluPerspective(45.0f, aspect, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

    // Run the main loop
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type== sf::Event::KeyPressed){
                cameraX += 1;
            }
        }

        // Clear the window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set the camera position
        glLoadIdentity();
        gluLookAt(cameraX, 0.0f, 3.0f,  // Eye position
                  0.0f, 0.0f, 0.0f,  // Look at position
                  0.0f, 1.0f, 0.0f); // Up vector

        // Render the triangle
        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f);
        glColor3f(0.0f, 1.0f, 0.0f);
        glVertex3f(1.0f, -1.0f, 0.0f);
        glColor3f(0.0f, 0.0f, 1.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
        glEnd();

        // Display the window
        window.display();
    }

    return 0;
}
