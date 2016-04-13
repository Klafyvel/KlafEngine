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

  class Component
  {
  public:
    Component() {}
    virtual void onUpdate()=0;
    virtual void onEvent(sf::Event e)=0;
    virtual bool isDrawable() {return false;}

  protected:


  };

  class DrawableComponent : public sf::Drawable, public Component
  {
  public:
    DrawableComponent(sf::Vector2f pos);
    ~DrawableComponent();

    virtual void onUpdate();
    virtual void onEvent(sf::Event e);
    bool isDrawable() {return true;}

  protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states);
    sf::Vector2f m_pos;

  private:

  };

	class State
	{
	public:
		State();
		virtual ~State();

		virtual void onInit();
		virtual void reInit();

		virtual void onEvent(sf::Event e);
		virtual void onRender(sf::RenderTarget& target);
		virtual void onCleanup();
		virtual void onUpdate();

		State& nextState();
		void addNextState(State& state);
		void setNextState(int index);

		void addComponent(Component& component);
		void addComponent(DrawableComponent& component);

	protected:
		std::vector <std::reference_wrapper<Component> > m_components;
		std::vector <std::reference_wrapper<DrawableComponent> > m_drawableComponents;
		std::vector <std::reference_wrapper<State> > m_nexts;

		int m_nextState;

	private:


	};
}

#endif // H_KLAFCORE
