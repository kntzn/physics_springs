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
	
	// Position radius-vectors
	FloatVector2D r1 (300, 300);
	FloatVector2D r2 (400, 400);
	FloatVector2D r3 (500, 500);
	// Velocity vectors
	FloatVector2D V1 (20, 0);
	FloatVector2D V2 (-10, 0);
	FloatVector2D V3 (-10, 0);
	// Force vectors
	FloatVector2D F1 (0, 0);
	FloatVector2D F2 (0, 0);
	FloatVector2D F3 (0, 0);
	// Masses of the bodies
	const float mass1 = 100.f;
	const float mass2 = 100.f;
	const float mass3 = 100.f;
	
	// Spring's variables
	float initial_distance_2_3 = (r2-r3).length ();
	float initial_distance_2_1 = (r2-r1).length ();
	float initial_distance_3_1 = (r3-r1).length ();
	float k = 0.05f;

	// Time step value
	const float dt = 0.016f;
	// Timer that measures delay
	sf::Clock timer;
	float total_delay = 0;

	// Main cycle
	while (window.isOpen ())
		{
		// Delay measurement
		total_delay += timer.getElapsedTime ().asSeconds ()*2.f;
		timer.restart ();

		// Events
		sf::Event event;
		while (window.pollEvent (event))
			if (event.type == sf::Event::Closed)
				window.close ();

		// ------ Physics ------
		while (total_delay > dt)
			{
			FloatVector2D current_distance_2_1 = r2-r1;
			FloatVector2D current_distance_2_3 = r2-r3;
			FloatVector2D current_distance_3_1 = r3-r1;

			//            Force     = (                      direction                    )   (                         dx                          ) * k
			FloatVector2D Force_2_1 = (current_distance_2_1/current_distance_2_1.length ()) * (current_distance_2_1.length () - initial_distance_2_1) * k;
			FloatVector2D Force_2_3 = (current_distance_2_3/current_distance_2_3.length ()) * (current_distance_2_3.length () - initial_distance_2_3) * k;
			FloatVector2D Force_3_1 = (current_distance_3_1/current_distance_3_1.length ()) * (current_distance_3_1.length () - initial_distance_3_1) * k;

			// According to 3rd Newton's law
			F1 =  Force_2_1 + Force_3_1;
			F2 = -Force_2_1 - Force_2_3;
			F3 =  Force_2_3 - Force_3_1;

			updatePoint (r1, V1, F1, dt, mass1);
			updatePoint (r2, V2, F2, dt, mass2);
			updatePoint (r3, V3, F3, dt, mass3);

			total_delay -= dt;
			}

		// ------ Graphics ------
		window.clear ();

		drawPoint (r1, window);
		drawPoint (r2, window);
		drawPoint (r3, window);
		drawSpring (r1, r2, window);
		drawSpring (r3, r2, window);
		drawSpring (r3, r1, window);
		
		window.display ();
		}

	return 0;
	}