#include <SFML/Graphics.hpp>
#include "Vector.h"

typedef Vector <float> FloatVector2D;
const float pi = 3.141596;

void updatePoint (FloatVector2D &r, FloatVector2D &V, FloatVector2D &F, const float dt, const float mass)
	{
	V += F/mass;
	r += V*dt;
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

int main ()
	{
	// Main window
	sf::RenderWindow window (sf::VideoMode (1600, 900), "");
	
	// Number of bodies
	const int n_bodies = 4;

	// Position radius-vectors
	FloatVector2D r [n_bodies] = 
		{ 
		FloatVector2D (200, 200),
		FloatVector2D (200, 400),
		FloatVector2D (400, 400),
		FloatVector2D (400, 200)
		};
	// Velocity vectors
	FloatVector2D V [n_bodies] = 
		{
		FloatVector2D (30, 0),
		FloatVector2D (0, 0),
		FloatVector2D (0, 0),
		FloatVector2D (0, 0)
		};

	// Masses of the bodies
	const float mass [n_bodies] = 
		{
		10, 
		10, 
		10,
		10
		};
	
	// Springs' variables
	float initial_distance [n_bodies] [n_bodies] = { };
	float k = 5.f;

	for (int i = 0; i < n_bodies; i++)
		for (int j = 0; j < n_bodies; j++)
			initial_distance [i] [j] = (r [i] - r [j]).length ();
			
	// Time step value
	const float dt = 0.016f;
	// Timer that measures delay
	sf::Clock timer;
	float total_delay = 0;

	// Main cycle
	while (window.isOpen ())
		{
		// Delay measurement
		total_delay += timer.getElapsedTime ().asSeconds ()*4.f;
		timer.restart ();

		// Events
		sf::Event event;
		while (window.pollEvent (event))
			if (event.type == sf::Event::Closed)
				window.close ();

		// ------ Physics ------

		// Force vectors
		FloatVector2D F [n_bodies] = { };

		while (total_delay > dt)
			{
			for (int i = 0; i < n_bodies; i++)
				for (int j = i+1; j < n_bodies; j++)
					{
					FloatVector2D current_distance = r [j] - r [i];

					FloatVector2D Force = (current_distance/current_distance.length ()) * (current_distance.length () - initial_distance [j][i]) * k;

					F [i] +=  Force;
					F [j] += -Force;

					}

			for (int i = 0; i < n_bodies; i++)
				updatePoint (r [i], V [i], F [i], dt, mass [i]);

			total_delay -= dt;
			}

		// ------ Graphics ------
		window.clear ();

		for (int i = 0; i < n_bodies; i++)
			drawPoint (r [i], window);

		for (int i = 0; i < n_bodies; i++)
			for (int j = i+1; j < n_bodies; j++)
				drawSpring (r [i], r [j], window);

		window.display ();
		}

	return 0;
	}