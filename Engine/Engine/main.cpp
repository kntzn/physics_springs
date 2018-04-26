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
	
	// Position radius-vectors
	FloatVector2D r1 (100, 100);
	FloatVector2D r2 (100, 200);
	// Velocity vectors
	FloatVector2D V1 (10, 0);
	FloatVector2D V2 (-10, 0);
	// Force vectors
	FloatVector2D F1 (0, 0);
	FloatVector2D F2 (0, 0);
	// Masses of the bodies
	const float mass1 = 100.f;
	const float mass2 = 100.f;

	// Time step value (1/60 of second)
	const float dt = 0.016f;

	// Spring's variables
	float initial_distance = (r2-r1).length ();
	float k = 0.05f;

	// Main cycle
	while (window.isOpen ())
		{
		// ------ Physics ------
		FloatVector2D current_distance = (r2-r1);

		//            Force = (                  direction               )   (                     dx                     ) * k
		FloatVector2D Force = (current_distance/current_distance.length()) * (current_distance.length() - initial_distance) * k;
		
		// According to 3rd Newton's law
		F1 = Force;
		F2 = -Force;

		updatePoint (r1, V1, F1, dt, mass1);
		updatePoint (r2, V2, F2, dt, mass2);

		// ------ Graphics ------
		window.clear ();
		drawPoint (r1, window);
		drawPoint (r2, window);
		window.display ();
		}

	return 0;
	}