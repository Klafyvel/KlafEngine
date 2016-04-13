#ifndef H_PHYSIC_UTILS
#define H_PHYSIC_UTILS

#include <iostream>
#include <SFML/Graphics.hpp>

namespace klf
{
	class MassData
	{
	public:
		MassData(float mass=0, float inertia=0);
		MassData();

		void setMass(float mass);
		void setInertia(float inertia);

		float getMass();
		float getInverseMass();
		float getInertia();
		float getInverseInertia();

	private:
		float m_mass;
		float m_invMass;
		float m_inertia;
		float m_invInertia;
	};

	class Material
	{
	public:
		Material(float density, float restitution) :
			density(density), restitution(restitution)
		{}
		const float density;
		const float restitution;
	};
	const Material Rock(0.6, 0.1);
	const Material Wood(0.3, 0.2);
	const Material Metal(1.2, 0.05);
	const Material BouncyBall(0.3, 0.8);
	const Material SuperBall(0.3, 0.95);
	const Material Pillow(0.1, 0.2);
	const Material Static(0.0, 0.4);

}

#endif // H_PHYSIC_UTILS
