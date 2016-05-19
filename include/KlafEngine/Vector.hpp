#ifndef H_KLFVECTOR
#define H_KLFVECTOR

#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

/**
 * @namespace klf
 *
 * Namespace for the KlafEngine's components.
 */
namespace klf
{
	class Vector2
	{
	public:
		float x;
		float y;

		Vector2(float x, float y) : x(x), y(y) {}
		Vector2(sf::Vector2f v) : x(v.x), y(v.y) {}

		Vector2 norm();
		float mag();
		float ang();

		sf::Vector2f toSFML() const;

		bool operator==(const Vector2& v) const;
		bool operator!=(const Vector2& v) const;

		Vector2 operator%(const float angle) const;
		Vector2& operator%=(const float angle);
		Vector2 operator/(const float f) const;
		Vector2& operator/=(const float f);
		Vector2 operator*(const float f) const;
		float operator*(const Vector2& v) const;
		Vector2& operator*=(const float f);
		Vector2 operator-(const Vector2& v) const;
		Vector2& operator-=(const Vector2& v);
		Vector2 operator+(const Vector2& v) const;
		Vector2& operator+=(const Vector2& v);
	};
	Vector2 operator*(const float f, const Vector2& v);
	std::ostream& operator<<(std::ostream& o, const Vector2& v);

}


#endif //H_KLFVECTOR
