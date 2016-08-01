#ifndef H_PHYSIC_UTILS
#define H_PHYSIC_UTILS

/**
 * @file PhysicUtils.hpp
 * @brief Utility classes for the physic module.
 * @author klafyvel
 */

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

#include <KlafEngine/Core.hpp>
#include <KlafEngine/Vector.hpp>

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
	class MassData : public ComponentData
	{
	public:
		/** @brief MassData constuctor.
		* It calls MassData::setMass and MassData::setInertia .
		* @param mass The mass.
		* @param inertia The inertia.
		*/
		MassData(float mass=0, float inertia=0);

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

		/** @brief MassData Component factory.
		 * @param e entity
		 */
		static std::unique_ptr<klf::Component> factory(unsigned int e);

		float mass; /**Mass value.*/
		float invMass; /**Inverse mass value.*/
		float inertia; /**Inertia value.*/
		float invInertia; /**Inverse inertia value.*/
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
		Material(float density=0, float restitution=0) :
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
