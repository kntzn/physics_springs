#include <SFML/Graphics.hpp>
#include "Vector.h"

typedef Vector <float> FloatVector2D;

void updatePoint (FloatVector2D &r, FloatVector2D &V, FloatVector2D &F, const float dt, const float mass)
    {
    V += F/mass;
    r += V*dt;
    }

void drawPoint (FloatVector2D r, sf::RenderWindow &window)
    {
    sf::CircleShape circle (30);
    circle.setPosition (r.toSf ());

    window.draw (circle);
    }

int main ()
    {
    // Main window
    sf::RenderWindow window (sf::VideoMode (1600, 900), "");

    // Position radius-vector
    FloatVector2D r (100, 100);
    // Velocity vector
    FloatVector2D V (10, 10);
    // Force vector
    FloatVector2D F (0, 0);
    // Time step value (1/60 of second)
    const float dt = 0.016f;
    // Mass of the body
    const float mass = 1.f;
    
    while (window.isOpen ())
        {
        window.clear ();

        updatePoint (r, V, F, dt, mass);
        drawPoint (r, window);

        window.display ();
        }
    
    return 0;
    }