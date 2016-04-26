#include <KlafEngine/Core.hpp>

namespace klf
{
	Component& System::getComponent(const ComponentMask mask, const unsigned int entity)
	{
		unsigned int component_id = componentMaskToInt(mask);
		return m_application.m_components[component_id][entity];
	}

	void Application::removeSystem(unsigned int id)
	{
		m_systems.erase(id);
		m_freeSystemId.push(id);
	}

	unsigned int Application::addSystem(System system)
	{
		unsigned int i = 0;
		if (m_freeSystemId.empty())
		{
			i = m_systems.size();
			while(m_systems.find(i) != m_systems.end())
			{
				i += 1;
			}
		}
		else
		{
			i = m_freeSystemId.front();
			m_freeSystemId.pop();
		}
		m_systems.emplace(i, system);
		return i;
	}

	unsigned int Application::addEntity()
	{
		unsigned int i = 0;
		if (m_freeEntityId.empty())
		{
			i = m_entities.size();
			while(m_entities.find(i) != m_entities.end())
			{
				i += 1;
			}
		}
		else
		{
			i = m_freeEntityId.front();
			m_freeEntityId.pop();
		}
		m_entities.emplace(i, ComponentMask());
		return i;
	}

	void Application::addMask(const unsigned int entityId, const ComponentMask mask)
	{
		m_entities[entityId] |= mask;
		unsigned int componentId = componentMaskToInt(mask);
		if(m_components.find(componentId) == m_components.end())
		{
			Application::addComponentRow(mask);
		}
		m_components[componentId][entityId] = m_registeredComponents[componentId](entityId);
	}

	void Application::removeMask(const unsigned int entityId, const ComponentMask mask)
	{
		m_entities[entityId] &= ~mask;
		unsigned int componentId = componentMaskToInt(mask);
		m_components[componentId].erase(entityId);
	}

	void Application::removeEntity(const unsigned int id)
	{
		m_entities.erase(id);
		m_freeEntityId.push(id);
	}

	void Application::registerComponentType(const ComponentMask mask, EmptyComponentFactory factory)
	{
		unsigned int componentId = componentMaskToInt(mask);
		m_registeredComponents[componentId] = factory;
	}

	void Application::removeComponentType(const ComponentMask mask)
	{
		Application::removeComponentRow(mask);
		unsigned int componentId = componentMaskToInt(mask);
		m_registeredComponents.erase(componentId);
	}

	void Application::addComponentRow(const ComponentMask mask)
	{
		unsigned int componentId = componentMaskToInt(mask);
		m_components[componentId] = std::unordered_map<unsigned int, Component> ();
	}
	/*
	void Application::addComponentType(const ComponentMask mask)
	{
		unsigned int id = componentMaskToInt(mask);
		std::unordered_map<unsigned int, Component> map();
		m_components.emplace(id, map);
	}
	*/

}
