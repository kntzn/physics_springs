#include <SFML/Graphics.hpp>
#include "Vector.h"

typedef Vector <float> FloatVector2D;
#define pi 3.141592653589793238462643383279f

void drawPoint (FloatVector2D r, sf::RenderWindow &window);
void drawSpring (FloatVector2D r1, FloatVector2D r2, sf::RenderWindow &window);

struct MatPoint
    {
    FloatVector2D r, V, F;
    float m = 0;

    MatPoint (FloatVector2D position, float mass)
        {
        r = position;
        m = mass;
        }

    void updatePoint (const float dt);
    };

int main ()
    {
    // Main window
    sf::RenderWindow window (sf::VideoMode (1600, 900), "");

    // Number of bodies
    const int n_bodies = 4;

    // Position radius-vectors
    MatPoint points [n_bodies] =
        {
        MatPoint (FloatVector2D (200, 200), 100.f),
        MatPoint (FloatVector2D (200, 400), 100.f),
        MatPoint (FloatVector2D (400, 400), 100.f),
        MatPoint (FloatVector2D (400, 200), 100.f)
        };

    points [3].V = FloatVector2D (30, 0);

    // Springs' variables
    float initial_distance [n_bodies] [n_bodies] = { };
    float k = 5.f;

    for (int i = 0; i < n_bodies; i++)
        for (int j = 0; j < n_bodies; j++)
            initial_distance [i] [j] = (points [i].r - points [j].r).length ();

    // Time step value
    float dt = 0.0016f;
    // Timer that measures delay
    sf::Clock timer;
    float total_delay = 0;

    // Main cycle
    while (window.isOpen ())
        {
        // Delay measurement

        //timer.restart ();

        // Events
        sf::Event event;
        while (window.pollEvent (event))
            if (event.type == sf::Event::Closed)
                window.close ();

        // ------ Physics ------

        // Force vectors
        for (int i = 0; i < n_bodies; i++)
            for (int j = i+1; j < n_bodies && i != j; j++)
                {
                FloatVector2D current_distance = points [j].r - points [i].r;

                FloatVector2D Force = current_distance.dir () * k *  (current_distance.length () - initial_distance [j] [i]);

                points [i].F += Force;
                points [j].F += -Force;
                }

        for (int i = 0; i < n_bodies; i++)
            points [i].updatePoint (dt);


        // ------ Graphics ------
        window.clear ();

        for (int i = 0; i < n_bodies; i++)
            drawPoint (points [i].r, window);

        for (int i = 0; i < n_bodies; i++)
            for (int j = i+1; j < n_bodies; j++)
                drawSpring (points [i].r, points [j].r, window);

        window.display ();
        }

    return 0;
    }

void MatPoint::updatePoint (const float dt)
    {
    V += F/m;
    r += V*dt;

    // Reseting the force
    F = FloatVector2D (0, 0);
    }

void drawPoint (FloatVector2D r, sf::RenderWindow &window)
    {
    sf::CircleShape circle (30);
    circle.setPosition (r.toSf ());
    circle.setOrigin (circle.getRadius (), circle.getRadius ());

    window.draw (circle);
    }
void drawSpring (FloatVector2D r1, FloatVector2D r2, sf::RenderWindow &window)
    {
    const float rect_length = 100;
    sf::RectangleShape rect (sf::Vector2f (rect_length, 10));
    rect.setOrigin (rect.getSize ()/2.f);
    rect.setPosition ((r1+r2).toSf ()/2.f);
    rect.setFillColor (sf::Color (127, 127, 127));

    // Rotation
    float angle = atan2f (r1.y-r2.y, r1.x-r2.x);
    angle /= pi;
    angle *= 180;
    rect.setRotation (angle);

    // Scaling
    rect.scale ((r1-r2).length ()/rect_length, 1);

    // Drawing
    window.draw (rect);
    }
