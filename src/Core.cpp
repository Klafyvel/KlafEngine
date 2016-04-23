#include <KlafEngine/Core2.hpp>

namespace klf
{
	Component& System::getComponent(ComponentMask mask, int entity)
	{
		int component_id = componentMaskToInt(mask);
		return m_application.m_components[component_id][entity];
	}
}
