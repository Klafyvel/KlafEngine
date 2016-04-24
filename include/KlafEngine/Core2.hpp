#ifndef H_KLAFCORE
#define H_KLAFCORE

/**
 * @file Core.hpp
 * @brief KlafEngine's core.
 * @author klafyvel
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <bitset>
#include <queue>
#include <functional>

#include <SFML/Graphics.hpp>

#include <KlafEngine/ComponentsMask.hpp>

/**
 * @namespace klf
 *
 * Namespace for the KlafEngine's components.
 */
namespace klf
{
	class Application;
	class System;

	class Component
	{
	public:
		Component();
		static Component createEmptyComponent(unsigned int entity)
		{
			Component c = Component();
			c.entity = entity;
			return c;
		}

		unsigned int entity;
	};
	typedef std::function<Component(unsigned int)> EmptyComponentFactory;

	class System
	{
	public:
		System(Application &application) : m_application(application){}
	protected:
		Component& getComponent(const ComponentMask mask, const unsigned int entity);

		Application& m_application;
	};

	class Application
	{
	friend class System;
	public:
		Application(sf::RenderWindow &window) : m_window(window) {}

		unsigned int addSystem(System system);
		void removeSystem(unsigned int id);

		unsigned int addEntity();
		void addMask(const unsigned int entityId, const ComponentMask mask);
		void removeMask(const unsigned int entityId, const ComponentMask mask);
		void removeEntity(const unsigned int id);

		void registerComponentType(const ComponentMask mask, EmptyComponentFactory factory);
		void removeComponentType(const ComponentMask mask);

		void addComponentRow(const ComponentMask mask);
		void removeComponentRow(const ComponentMask mask);

	protected:
		sf::RenderWindow& m_window;
		std::unordered_map<unsigned int, System> m_systems;
		std::unordered_map<unsigned int, std::unordered_map<unsigned int,Component>> m_components;
		std::unordered_map<unsigned int, EmptyComponentFactory> m_registeredComponents;
		std::unordered_map<unsigned int, ComponentMask> m_entities;
		std::queue<unsigned int> m_freeSystemId;
		std::queue<unsigned int> m_freeEntityId;
	};


}
#endif // H_KLAFCORE
