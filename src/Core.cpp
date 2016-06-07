#include <KlafEngine/Core.hpp>

/**
 * @file Core.cpp
 * @brief KlafEngine's core.
 * @author klafyvel
 */
namespace klf
{
	Component& System::getComponent(const ComponentMask mask, const Entity entity) const
	{
		unsigned int component_id = componentMaskToInt(mask);
		return *(m_application.m_components[component_id][entity]);
	}
	ComponentMask System::getComponentMask(const Entity entity) const
	{
		return m_application.m_entities[entity];
	}
	std::unordered_map<unsigned int, ComponentMask>& System::getActiveEntities() const
	{
		return m_application.m_activeEntities;
	}

	void Application::removeSystem(unsigned int id)
	{
		m_systems.erase(id);
		m_freeSystemId.push(id);
	}

	unsigned int Application::addSystem(SystemFactory systemFactory)
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

		m_systems.emplace(i, systemFactory());
		return i;
	}

	unsigned int Application::addEntity()
	{
		unsigned int i = 0;
		if (m_freeEntityId.empty())
		{
			i = m_greaterEntity;
			m_greaterEntity ++;
		}
		else
		{
			i = m_freeEntityId.front();
			m_freeEntityId.pop();
		}
		m_entities.emplace(i, ComponentMask());
		return i;
	}

	void Application::makeActive(unsigned int entity)
	{
		m_activeEntities[entity] = m_entities[entity];
	}

	void Application::makeUnactive(unsigned int entity)
	{
		m_entities[entity] = m_activeEntities[entity];
		m_activeEntities.erase(entity);
	}

	void Application::addMask(const unsigned int entityId, const ComponentMask mask)
	{
		m_activeEntities[entityId] |= mask;
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
		m_activeEntities[entityId] &= ~mask;
		unsigned int componentId = componentMaskToInt(mask);
		m_components[componentId].erase(entityId);
	}

	void Application::removeEntity(const unsigned int id)
	{
		makeUnactive(id);
		m_entities.erase(id);
		if (id == m_greaterEntity-1)
			m_greaterEntity = id;
		else
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
		m_components[componentId] = std::unordered_map<unsigned int, std::unique_ptr<Component>> ();
	}

	void Application::removeComponentRow(const ComponentMask mask)
	{
		unsigned int componentId = componentMaskToInt(mask);
		m_components[componentId].clear();
		m_components.erase(componentId);
	}

	void Application::update()
	{
		for(auto s : m_systemProcessing)
			m_systems[s]->update();
		m_systemProcessing.clear();
	}
	void Application::pushUpdate(unsigned int id)
	{
		m_systemProcessing.push_back(id);
	}
}
