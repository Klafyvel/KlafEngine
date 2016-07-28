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
		PhysicData() {}

		/** @brief PhysicData Component factory
		 * @param e entity
		 */
		static std::unique_ptr<Component> factory(Entity e);

		MassData mass; /** Object's mass */
		Material material; /** Object's composition. */
		Vector2 pos; /** Object's position in the physics coordinate system. */
		Shape shape; /** Object's shape (used fo collision). */
	};

	class PhysicHandler : public System
	{
	public:
		PhysicHandler(Application& application, unsigned int id, float dt=0.0) ;
		void attachShapeHandler(unsigned int id);
		void update();
	private:
		unsigned int m_shapeHandlerId;
		bool m_fixedTime;
		float m_dt;
		sf::Clock m_clock;
	};

}

#endif // H_PHYSIC
