#pragma once
#include <math.h>
#include <SFML/System.hpp>

template <typename dataType> class Vector
	{
	public:
		// Data
		dataType x = 0, y = 0;

		// Constructors and destructors
		Vector ()
			{
			}
		Vector (dataType X, dataType Y)
			{
			x = X;
			y = Y;
			}
		Vector (dataType alpha)
			{
			x = cos (alpha);
			y = sin (alpha);
			}

		// Operators overload
		Vector operator + (Vector const lvec)
			{
			return Vector (lvec.x + x, lvec.y + y);
			};
		Vector operator - (Vector const lvec)
			{
			return Vector (x - lvec.x, y - lvec.y);
			};
		dataType operator * (Vector const lvec)
			{
			return lvec.x*x + lvec.y*y;
			}
		Vector operator * (const dataType factor)
			{
			return Vector (x*factor, y*factor);
			};
        Vector operator - ()
            {
            return Vector (-x, -y);
            };
        Vector operator / (const dataType factor)
            {
            return Vector (x/factor, y/factor);
            };

        Vector& Vector::operator += (const Vector &lvec)
            {
            this->x += lvec.x;
            this->y += lvec.y;
            return *this;
            };
        Vector& Vector::operator -= (const Vector &lvec)
            {
            this->x -= lvec.x;
            this->y -= lvec.y;
            return *this;
            };
        Vector& Vector::operator *= (const dataType factor)
            {
            this->x *= factor;
            this->y *= factor;
            return *this;
            };
        Vector& Vector::operator /= (const dataType factor)
            {
            this->x /= factor;
            this->y /= factor;
            return *this;
            };
		
		// Getters
		dataType length ()
			{
			return sqrt (x*x + y*y);
			}
		Vector dir ()
			{
			return Vector (x/length(), y/length());
			}
		sf::Vector2f toSf ()
			{
			return sf::Vector2f (x, y);
			}

	};