#include <KlafEngine/PhysicUtils.hpp>

namespace klf
{
	/** @brief MassData constuctor.
	 * It calls MassData::setMass and MassData::setInertia .
	 * @param mass The mass.
	 * @param inertia The inertia.
	 */
	MassData::MassData(float mass, float inertia)
	{
		MassData::setMass(mass);
		MassData::setInertia(inertia);
	}

	/** @brief MassData's default constructor.
	 * Mass and inertia will be set to 0.
	 */
	MassData::MassData()
	{
		MassData::setMass(0);
		MassData::setInertia(0);
	}

	/** @brief Set the mass value.
	 * A null mass will cause the inverse mass to be set at zero.
	 * @param mass The new mass value.
	 */
	void MassData::setMass(float mass)
	{
		m_mass = mass;
		if(mass==0)
			m_invMass = 0;
		else
			m_invMass = 1.0 / mass;
	}

	/** @brief Set the inertia value.
	 * A null inertia will cause the inverse inertia to be set at zero.
	 * @param inertia The new inertia value.
	 */
	void MassData::setInertia(float inertia)
	{
		m_inertia = inertia;
		if(inertia == 0)
			m_invInertia = 0;
		else
			m_invInertia = 1.0 / inertia;
	}

	/** @brief Get the mass value.
	 * @return mass value.
	 */
	float MassData::getMass()
	{
		return m_mass;
	}

	/** @brief Get the inverse mass value.
	 * @return inverse mass value.
	 */
	float MassData::getInverseMass()
	{
		return m_invMass;
	}

	/** @brief Get the inertia value.
	 * @return inertia value.
	 */
	float MassData::getInertia()
	{
		return m_inertia;
	}

	/** @brief Get the inverse inertia value.
	 * @return inverse inertia value.
	 */
	float MassData::getInverseInertia()
	{
		return m_invInertia;
	}
}
