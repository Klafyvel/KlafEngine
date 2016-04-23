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

#include <SFML/Graphics.hpp>

#include <KlafEngine/ComponentsMask.hpp>

/**
 * @namespace klf
 *
 * Namespace for the KlafEngine's components.
 */
namespace klf
{
	class Component
	{
	public:
		Component();
	};

	class Application;
	class System
	{
	public:
		System(Application &application) : m_application(application){}
	protected:
		Component& getComponent(ComponentMask mask, int entity);

		Application& m_application;

	};

	class Application
	{
	friend class System;
	public:
		Application(sf::RenderWindow &window) : m_window(window) {}

		void addSystem(System system, int id);
		void removeSystem(int id);

		int addEntity();
		void addMask(int entityId, ComponentMask mask);
		void removeMask(int entityId, ComponentMask mask);
		void removeEntity(int id);

		void addComponentType(ComponentMask mask);
		void removeComponentType(ComponentMask mask);

	protected:
		sf::RenderWindow& m_window;
		std::unordered_map<int, System> m_systems;
		std::unordered_map<int, std::unordered_map<int,Component>> m_components;
		std::unordered_map<int, int> m_entities;
	};


}
#endif // H_KLAFCORE
