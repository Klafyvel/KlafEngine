#ifndef H_KLAFCORE
#define H_KLAFCORE

/**
 * @file Core.hpp
 * @brief KlafEngine's core.
 * @author klafyvel
 */

#include <iostream>
#include <vector>
#include <functional>

#include <SFML/Graphics.hpp>

/**
 * @namespace klf
 *
 * Namespace for the KlafEngine's components.
 */
namespace klf
{
	class State;
	class Component;
	/** @class Application
	* @brief Handles an application.
	*/
	class Application
	{
	public:
		/** @brief Application's constructor.
		* @param firstState The application's first state.
		*/
		Application(State& firstState);

		/** @brief Application's destructor.
		*
		*/
		~Application();

		/** @brief Initialize the application then handle the application's main loop.
		*
		*/
		void onMainLoop();

		/** @brief Handle events for the application.
		*
		* Catch the sf::Event::Closed event or ask the current state what to do.
		*/
		void onEvent(sf::Event e);

		/** @brief Update the application.
		*
		* @return void
		*/
		void onUpdate();

		/** @brief Render the current state.
		* @return void
		*/
		void onRender();

		/** @brief Initialize the application.
		*
		*/
		void onInit();

		/** @brief Change the application's current state.
		*
		*  @param state The new State.
		* @return void
		*/
		void changeState(State& state);

		/** @brief Stop the application's run.
		* @return void
		*/
		void stopRunning();

	protected:
		sf::Clock m_clock; /**Application's internal clock.*/
		sf::RenderWindow m_window; /**Application's window.*/

		bool m_isRunning; /**Application's run state.*/

		State& m_currentState; /**Application's current state.*/

	};

	/** @class Component
	 * @brief A state component.
	 */
	class Component
	{
	public:
		/** @brief Default constructor.
		 */
		Component() {}

		/** @brief Called in order to update the component.
		 */
		virtual void onUpdate()=0;

		/** @brief Handle event.
		 * @param e The event which is to be handled.
		 */
		virtual void onEvent(sf::Event e)=0;
	};

	/** @class State
	 * @brief An application state.
	 */
	class State
	{
	public:
		/** @brief State constructor.
		* This will not initialize the state. You need to call State::onInit().
		*/
		State();

		/** @brief Virtual destructor.
		 */
		virtual ~State();

		/** @brief Init a State.
		*/
		virtual void onInit();

		/** @brief Re-initialize a state.
		* Call State::onCleanup then State::onInit().
		*/
		virtual void reInit();

		/** @brief Handle the given sf::Event.
		*
		* @param e The event which is to be handled.
		* @return void
		*/
		virtual void onEvent(sf::Event e);

		/** @brief Render a state on the given target.
		*
		* @param target The target on which the state is to be rendered.
		* @return void
		*/
		virtual void onRender(sf::RenderTarget& target);

		/** @brief Clean up a State.
		* This will remove every component.
		* @return void
		*/
		virtual void onCleanup();

		/** @brief Update a state.
		* This will also update every owned component.
		* @return void
		*/
		virtual void onUpdate();

		/** @brief Give the next state of a state.
		*
		* @return The next state.
		*/
		State& nextState();

		/** @brief Add a possible next state to a state.
		*
		* @param state A refence to the next state.
		* @return void
		*/
		void addNextState(State& state);

		/** @brief Change a state's next state.
		*
		* @param index Index of the next state.
		* @return void
		*/
		void setNextState(int index);

		/** @brief Add a component to the state.
		*
		* @param component The component which is to be added.
		* @param drawable Has the component to be rendered ?
		*/
		void addComponent(Component& component, bool drawable=false);

	protected:
		std::vector <std::reference_wrapper<Component> > m_components; /** State's components. */
		std::vector <std::reference_wrapper<Component> > m_drawableComponents; /** State's drawable components.*/
		std::vector <std::reference_wrapper<State> > m_nexts; /** The possible next states.*/

		int m_nextState; /** The actual next state (0=self)*/
	};
}

#endif // H_KLAFCORE
