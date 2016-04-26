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
#include <memory>

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
		Component(unsigned int e) : entity(e){}
		static std::unique_ptr<Component> createEmptyComponent(unsigned int entity)
		{
			std::unique_ptr<Component> c(new Component(entity));
			return c;
		}
		unsigned int entity;
		std::unordered_map<std::string, int> int_values;
		std::unordered_map<std::string, std::string> string_values;
		std::unordered_map<std::string, float> float_values;
	};

	typedef std::function<std::unique_ptr<Component>(unsigned int)> EmptyComponentFactory;

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

		/*
		void registerComponentType(const ComponentMask mask, EmptyComponentFactory factory);
		void removeComponentType(const ComponentMask mask);
*/
		void addComponentRow(const ComponentMask mask);
		void removeComponentRow(const ComponentMask mask);
	protected:
		sf::RenderWindow& m_window;
		std::unordered_map<unsigned int, System> m_systems;
		std::unordered_map<unsigned int, std::unordered_map<unsigned int,std::unique_ptr<Component>>> m_components;
		std::unordered_map<unsigned int, EmptyComponentFactory> m_registeredComponents;
		std::unordered_map<unsigned int, ComponentMask> m_entities;
		std::queue<unsigned int> m_freeSystemId;
		std::queue<unsigned int> m_freeEntityId;
	};


}
#endif // H_KLAFCORE
