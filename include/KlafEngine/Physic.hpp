#ifndef H_PHYSIC
#define H_PHYSIC

/**
 * @file Physic.hpp
 * @brief Physic components and systems.
 * @author klafyvel
 */

#include <iostream>
#include <KlafEngine/Core.hpp>
#include <KlafEngine/PhysicUtils.hpp>
#include <KlafEngine/Vector.hpp>
#include <KlafEngine/Shape.hpp>

namespace klf
{
	/** @class PhysicData
	 * @brief This is a physic component.
	 */
	class PhysicData : public ComponentData
	{
	public:
		/** @brief PhysicData constructor.
		 */
		PhysicData();

		MassData mass;
		Material material;
		Vector2 pos;
		Shape shape;
	};

}

#endif // H_PHYSIC
