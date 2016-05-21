#ifndef H_KLFVECTOR
#define H_KLFVECTOR

#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

#include <KlafEngine/Core.hpp>

/**
 * @namespace klf
 *
 * Namespace for the KlafEngine's components.
 */
namespace klf
{
	/** @class Vector2
	 * @brief 2D Vector.
	 */
	class Vector2 : public ComponentData
	{
	public:
		float x; /** X component */
		float y; /** Y component */

		/** @brief Constructor
		 * @param x x value
		 * @param y y value
		 */
		Vector2(float x, float y) : x(x), y(y) {}
		/** Copy constructor
		 * @param v Vector to be copied.
		 */
		Vector2(sf::Vector2f v) : x(v.x), y(v.y) {}

		/** @brief Compute the normalized vector.
		 * @return Normalized vector.
		 */
		Vector2 norm();
		/** @brief Compute vector's magnitude.
		 * @return Magnitude.
		 */
		float mag();
		/** @brief Compute angle between vector and (1,0).
		 * @return angle
		 */
		float ang();
		/** @brief Compute an orthogonal vector.
		 * This is more precise than rotating M_PI*2.
		 * @return orthogonal vector.
		 */
		Vector2 orthogonal();

		/** Convert Vector2 to SFML Vector2f.
		 * @return SFML Vector2f
		 */
		sf::Vector2f toSFML() const;

		/** Compare two Vector2.*/
		bool operator==(const Vector2& v) const;
		/** Compare two Vector2.*/
		bool operator!=(const Vector2& v) const;

		/** @brief Rotate the Vector2 by the given angle.
		 *	@param angle The angle the vector is to be rotated.
		 *	@return A Vector2.
		 */
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
