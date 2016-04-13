#ifndef H_PHYSIC_UTILS
#define H_PHYSIC_UTILS

/**
 * @file PhysicUtils.hpp
 * @brief Utility classes for the physic module.
 * @author klafyvel
 */

#include <iostream>
#include <SFML/Graphics.hpp>

/**
 * @namespace klf
 *
 * Namespace for the KlafEngine's components.
 */
namespace klf
{
	/** @class MassData
	 * @brief Used to store mass data.
	 * Value stored : mass, inverse mass, inertia, inverse inertia
	 */
	class MassData
	{
	public:
		/** @brief MassData constuctor.
		* It calls MassData::setMass and MassData::setInertia .
		* @param mass The mass.
		* @param inertia The inertia.
		*/
		MassData(float mass=0, float inertia=0);

		/** @brief MassData's default constructor.
		* Mass and inertia will be set to 0.
		*/
		MassData();

		/** @brief Set the mass value.
		* A null mass will cause the inverse mass to be set at zero.
		* @param mass The new mass value.
		*/
		void setMass(float mass);

		/** @brief Set the inertia value.
		* A null inertia will cause the inverse inertia to be set at zero.
		* @param inertia The new inertia value.
		*/
		void setInertia(float inertia);

		/** @brief Get the mass value.
		* @return mass value.
		*/
		float getMass();

		/** @brief Get the inverse mass value.
		* @return inverse mass value.
		*/
		float getInverseMass();

		/** @brief Get the inertia value.
		* @return inertia value.
		*/
		float getInertia();

		/** @brief Get the inverse inertia value.
		* @return inverse inertia value.
		*/
		float getInverseInertia();

	private:
		float m_mass; /**Mass value.*/
		float m_invMass; /**Inverse mass value.*/
		float m_inertia; /**Inertia value.*/
		float m_invInertia; /**Inverse inertia value.*/
	};

	/** @class Material
	 * @brief Class used in order to describe a material.
	 * It stores density and restitution.
	 */
	class Material
	{
	public:
		/** @brief Constructor
		 * @param density Material's density.
		 * @param restitution Material's resitution.
		 */
		Material(float density, float restitution) :
			density(density), restitution(restitution)
		{}
		const float density; /**Material's density.*/
		const float restitution; /**Material's restitution.*/
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
