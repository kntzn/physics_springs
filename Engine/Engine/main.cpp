#include <SFML/Graphics.hpp>
#include "Vector.h"

typedef Vector <float> FloatVector2D;

void updatePoint (FloatVector2D r, FloatVector2D V)
	{
	r += V;
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
	// Time step value (1/60 of second)
	const float dt = 0.016f;

	return 0;
	}