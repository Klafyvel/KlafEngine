#include <KlafEngine/Physic.hpp>

namespace klf
{
	std::unique_ptr<Component> PhysicData::factory(Entity e)
	{
		std::unique_ptr<Component> c = klf::Component::createEmptyComponent(e);
		c->value = std::shared_ptr<ComponentData>(new PhysicData());
		return c;
	}

	PhysicHandler::PhysicHandler(Application& application, unsigned int id, float dt) : System(application, id)
	{
		m_fixedTime = dt != 0.0;
		m_clock.restart();
		m_dt = dt;
		m_shapeHandlerId = 0;
	}

	void PhysicHandler::attachShapeHandler(unsigned int id)
	{
		m_shapeHandlerId = id;
	}


}
