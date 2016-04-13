#include <KlafEngine/PhysicUtils.hpp>

namespace klf
{
	MassData::MassData(float mass, float inertia)
	{
		MassData::setMass(mass);
		MassData::setInertia(inertia);
	}

	MassData::MassData()
	{
		MassData::setMass(0);
		MassData::setInertia(0);
	}

	void MassData::setMass(float mass)
	{
		m_mass = mass;
		if(mass==0)
			m_invMass = 0;
		else
			m_invMass = 1.0 / mass;
	}

	void MassData::setInertia(float inertia)
	{
		m_inertia = inertia;
		if(inertia == 0)
			m_invInertia = 0;
		else
			m_invInertia = 1.0 / inertia;
	}

	float MassData::getMass()
	{
		return m_mass;
	}

	float MassData::getInverseMass()
	{
		return m_invMass;
	}

	float MassData::getInertia()
	{
		return m_inertia;
	}

	float MassData::getInverseInertia()
	{
		return m_invInertia;
	}
}
