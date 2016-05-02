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

	/** @class ComponentData
	 * @brief Base class for component data.
	 */
	class ComponentData
	{
	public:
		/** @brief Constructor */
		ComponentData() {}

		/** @brief Virtual destructor. */
		virtual ~ComponentData() {};
	};

	/** @class Component
	 * @brief A component has to store datas.
	 */
	class Component
	{
	public:
		/** @brief Constructor.
		 * @param e The entity which own the component.
		 */
		Component(unsigned int e) : entity(e)
		{}

		/** @brief Dynamically allow a Component for the given entity.
		 * @param entity The entity which own the component.
		 * @return A std::unique_ptr on the component.
		 */
		static std::unique_ptr<Component> createEmptyComponent(unsigned int entity)
		{
			std::unique_ptr<Component> comp(new Component(entity));
			return comp;
		}

		unsigned int entity; /** The component's owner.*/
		std::shared_ptr<ComponentData> value; /** Use value to store your data struct. */
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

		/** @brief Update the system.
		 */
		virtual void onUpdate() = 0;

		Application& m_application;/** System owner.*/
	};

	/** @brief Typedef for system factories.
	 */
	typedef std::function<std::unique_ptr<System>(void)> SystemFactory;

	/** @class Application
	 * @brief Handle every system, components and entities.
	 */
	class Application
	{
	friend class System;
	public:
		/** @brief Constructor
		 */
		Application() : {}

		/** @brief Add a system to the application
		 * @param systemFactory A SystemFactory to build the system.
		 * @return The system id.
		 */
		unsigned int addSystem(SystemFactory systemFactory);
		/** @brief Remove a system from the application by id.
		 * @param id System id.
		 */
		void removeSystem(unsigned int id);

		/** @brief Add an entity to the system.
		 * @return The entity id.
		 */
		unsigned int addEntity();
		/** @brief Add a mask on the given entity.
		 * @param entityId The entity id.
		 * @param mask The mask which is to be applied.
		 */
		void addMask(const unsigned int entityId, const ComponentMask mask);
		/** @brief Remove the mask on the given entity.
		 * @param entityId The entity id.
		 * @param mask The mask which is to be applied.
		 */
		void removeMask(const unsigned int entityId, const ComponentMask mask);
		/** @brief Remove the entity from the application.
		 * @param id The entity which is to be removed.
		 */
		void removeEntity(const unsigned int id);

		/** @brief Register a component type.
		 * @param mask The mask of the new component.
		 * @param factory The component factory.
		 */
		void registerComponentType(const ComponentMask mask, EmptyComponentFactory factory);
		/** @brief Remove a component type.
		 * @param mask The mask of the component which is to be removed.
		 */
		void removeComponentType(const ComponentMask mask);
		/** @brief Add a component row from the application.
		 * @param mask The component mask to be added.
		 */
		void addComponentRow(const ComponentMask mask);
		/** @brief Remove the component row of the mask.
		 * @param mask The component mask.
		 */
		void removeComponentRow(const ComponentMask mask);
	protected:
		std::unordered_map<unsigned int, System> m_systems; /** Every system of the application.*/
		std::unordered_map<unsigned int, std::unordered_map<unsigned int,std::unique_ptr<Component>>> m_components; /** Every component rows.*/
	std::unordered_map<unsigned int, EmptyComponentFactory> m_registeredComponents; /** Registered component (i.e. the factories to build them) */
		std::unordered_map<unsigned int, ComponentMask> m_entities; /** Every application's entity. */
		std::queue<unsigned int> m_freeSystemId; /** Free systems ids. */
		std::queue<unsigned int> m_freeEntityId; /** Free entities id. */
	};


}
#endif // H_KLAFCORE
