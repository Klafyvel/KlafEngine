#include <KlafEngine/Vector.hpp>

namespace klf
{
	Vector2 Vector2::norm()
	{
		return *this / mag();
	}

	float Vector2::mag()
	{
		return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
	}

	float Vector2::ang()
	{
		return atan2(x, y);
	}

	sf::Vector2f Vector2::toSFML() const
	{
		return sf::Vector2f(x, y);
	}

	bool Vector2::operator==(const Vector2& v) const
	{
		return (v.x == x) && (v.y == y);
	}

	bool Vector2::operator!=(const Vector2& v) const
	{
		return !(*this == v);
	}

	Vector2 Vector2::operator%(const float angle) const
	{
		float c = cos(angle);
		float s = sin(angle);
		return Vector2(x*c - y*s, x*s + y*c);
	}

	Vector2& Vector2::operator%=(const float angle)
	{
		*this = *this % angle;
		return *this;
	}

	Vector2 Vector2::operator/(const float f) const
	{
		return Vector2(x/f, y/f);
	}

	Vector2& Vector2::operator/=(const float f)
	{
		*this = *this / f;
		return *this;
	}

	Vector2 Vector2::operator*(const float f) const
	{
		return Vector2(x*f, y*f);
	}
	Vector2 operator*(const float f, const Vector2& v)
	{
		return v*f;
	}

	float Vector2::operator*(const Vector2& v) const
	{
		return x*v.x + y*v.y;
	}

	Vector2& Vector2::operator*=(const float f)
	{
		*this = *this * f;
		return *this;
	}

	Vector2 Vector2::operator-(const Vector2& v) const
	{
		return Vector2(x-v.x, y-v.y);
	}

	Vector2& Vector2::operator-=(const Vector2& v)
	{
		*this = *this - v;
		return *this;
	}

	Vector2 Vector2::operator+(const Vector2& v) const
	{
		return Vector2(x+v.x, y+v.y);
	}

	Vector2& Vector2::operator+=(const Vector2& v)
	{
		*this = *this + v;
		return *this;
	}

	std::ostream& operator<<(std::ostream& o, const Vector2& v)
	{
		o << '(' << v.x << ',' << v.y << ')';
		return o;
	}

};
