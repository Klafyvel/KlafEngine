#include <iostream>

#include <KlafEngine/Vector.hpp>

using namespace klf;

int main()
{
	Vector2 x(1,0);
	Vector2 y(0,1);
	Vector2 v1 = 3*x - y*2;
	Vector2 v2 = v1+3*x;
	Vector2 v3 = 4*v2;
	float s = x*v3;

	std::cout << "x=" << x << std::endl;
	std::cout << "y=" << y << std::endl;
	std::cout << "v1=" << v1 << std::endl;
	std::cout << "v2=" << v2 << std::endl;
	std::cout << "v3=" << v3 << std::endl;
	std::cout << "s=" << s << std::endl;

	return 0;
}
