#include <KlafEngine/PhysicUtils.hpp>

namespace klf
{
	MassData::MassData(float mass, float inertia)
	{
		MassData::setMass(mass);
		MassData::setInertia(inertia);
	}

	void MassData::setMass(float mass)
	{
		this->mass = mass;
		if(mass==0)
			this->invMass = 0;
		else
			this->invMass = 1.0 / mass;
	}

	void MassData::setInertia(float inertia)
	{
		this->inertia = inertia;
		if(inertia == 0)
			this->invInertia = 0;
		else
			this->invInertia = 1.0 / inertia;
	}

	std::unique_ptr<klf::Component> MassData::factory(unsigned int e)
	{
		std::unique_ptr<klf::Component> c = klf::Component::createEmptyComponent(e);
		c->value = std::shared_ptr<klf::ComponentData>(new MassData());
		return c;
	}
}
