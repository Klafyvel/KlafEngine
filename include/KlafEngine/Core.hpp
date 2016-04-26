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

	/** @class Component
	 * @brief A component has to store datas.
	 */
	class Component
	{
	public:
		/** @brief Constructor.
		 * @param e The entity which own the component.
		 */
		Component(unsigned int e) : entity(e){}

		/** @brief Dynamically allow a Component for the given entity.
		 * @param entity The entity which own the component.
		 */
		static std::unique_ptr<Component> createEmptyComponent(unsigned int entity)
		{
			std::unique_ptr<Component> c(new Component(entity));
			return c;
		}

		unsigned int entity; /** The component's owner.*/
		std::unordered_map<std::string, int> int_values; /** Every int value stored in the component. */
		std::unordered_map<std::string, std::string> string_values; /** Every std::string value stored in the component. */
		std::unordered_map<std::string, float> float_values; /** Every float value stored in the component. */
	};

	/** @brief Typedef for component factories.
	 */
	typedef std::function<std::unique_ptr<Component>(unsigned int)> EmptyComponentFactory;

	/** @class System
	 * @brief Deal with Component's values.
	 */
	class System
	{
	public:
		/** @brief Constructor.
		 * @param application A reference to the system owner.
		 */
		System(Application &application) : m_application(application){}
	protected:
		/** @brief Access to the entity's component. May not be overrided
		 * @param mask The component's mask.
		 * @param entity The entity.
		 */
		Component& getComponent(const ComponentMask mask, const unsigned int entity);

		Application& m_application;/** System owner.*/
	};

	/** @class Application
	 * @brief Handle every system, components and entities.
	 */
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
		std::unordered_map<unsigned int, std::unordered_map<unsigned int,std::unique_ptr<Component>>> m_components;
	std::unordered_map<unsigned int, EmptyComponentFactory> m_registeredComponents;
		std::unordered_map<unsigned int, ComponentMask> m_entities;
		std::queue<unsigned int> m_freeSystemId;
		std::queue<unsigned int> m_freeEntityId;
	};


}
#endif // H_KLAFCORE
