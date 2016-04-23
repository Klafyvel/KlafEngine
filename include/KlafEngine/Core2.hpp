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
	};

	class Application;
	class System
	{
	public:
		System(Application &application) : m_application(application){}
	protected:
		void changeComponent(ComponentsMask mask, int entity);

		Application& m_application;

	};

	class Application
	{
	friend class System;
	public:
		Application(sf::RenderWindow &window) : window(window) {}

		void addSystem(System system, int id);
		void removeSystem(int id);

		int addEntity();
		void addMask(int entityId, ComponentsMask mask);
		void removeMask(int entityId, ComponentsMask mask);
		void removeEntity(int id);

		void addComponentType(ComponentsMask mask);
		void removeComponentType(ComponentsMask mask);

	protected:
		std::unordered_map<int, System> m_systems;
		std::unordered_map<int, std::unordered_map<int,Component>> m_components;
		std::unordered_map<int, int> m_entities;


}
