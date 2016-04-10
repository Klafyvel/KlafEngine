#include <KlafEngine/Core.hpp>

namespace klf
{
  //////////////
  // APPLICATION
  ///////////////////////////////

  /** @brief Stop the application's run.
    * @return void
    */
  void Application::stopRunning()
  {
    m_isRunning = false;
  }

  /** @brief Change the application's current state.
   *
   *  @param state The new State.
    * @return void
    */
  void Application::changeState(State& state)
  {
    m_currentState = state;
  }

  /** @brief Initialize the application.
    *
    */
  void Application::onInit()
  {
    m_window.create(sf::VideoMode(800, 600), "KlafEngine");
    m_window.setFramerateLimit(60);
  }

  /** @brief Render the current state.
    * @return void
    */
  void Application::onRender()
  {
    m_window.clear();
    m_currentState.onRender(m_window);
  }

  /** @brief Update the application.
    *
    * @return void
    */
  void Application::onUpdate()
  {

    m_currentState = m_currentState.nextState();
	m_currentState.onUpdate();
  }

  /** @brief Handle events for the application.
    *
    * Catch the sf::Event::Closed event or ask the current state what to do.
    */
  void Application::onEvent(sf::Event e)
  {
    if(e.type == sf::Event::Closed)
      m_isRunning = false;
    else
      m_currentState.onEvent(e);
  }

  /** @brief Initialize the application then handle the application's main loop.
    *
    */
  void Application::onMainLoop()
  {
    Application::onInit();

    m_isRunning = true;
    m_clock.restart();
    sf::Event event;

    while(m_isRunning && m_window.isOpen())
    {
      // Handles events
      while(m_window.pollEvent(event))
        Application::onEvent(event);

      Application::onUpdate();

      Application::onRender();

      m_window.display();
    }
  }

  /** @brief Application's destructor.
    *
    */
   Application::~Application()
  {
    m_window.close();
  }

  /** @brief Application's constructor.
    *
    */
   Application::Application(State& firstState):
     m_clock(),
     m_window(),
     m_isRunning(false),
     m_currentState(firstState)
  {
  }

  //////////////
  // COMPONENT
  ///////////////////////////////

  /** @brief Draw a component.
    *
	* @return void
    */
  void DrawableComponent::draw(sf::RenderTarget& target, sf::RenderStates states)
  {

  }

  /** @brief DrawableComponent's destructor.
    *
    */
   DrawableComponent::~DrawableComponent()
  {

  }

  /** @brief DrawableComponent's constructor.
    *
    * @param pos The component's position.
    */
   DrawableComponent::DrawableComponent(sf::Vector2f pos):
     m_pos(pos)
  {

  }

  /** @brief Update a DrawableComponent.
    *
	* @return void
    */
  void DrawableComponent::onUpdate()
  {

  }

  /** @brief Handle an event.
    *
	* @param e The event which is to be handled.
	* @return void
    */
  void DrawableComponent::onEvent(sf::Event e)
  {

  }



  //////////////
  // STATE
  ///////////////////////////////
  /** @brief Change a state's next state.
    *
    * @param index Index of the next state.
	* @return void
    */
	void State::setNextState(int index)
	{
		m_nextState = index;
	}

	/** @brief Add a possible next state to a state.
	*
	* @param state A refence to the next state.
	* @return void
	*/
	void State::addNextState(State& state)
	{
		m_nexts.push_back(std::reference_wrapper<State>(state));
	}

	/** @brief Give the next state of a state.
	*
	* @return The next state.
	*/
	State& State::nextState()
	{
		return m_nexts[m_nextState].get();
	}

	/** @brief Update a state.
	* This will also update every owned component.
	* @return void
	*/
	void State::onUpdate()
	{
		for(unsigned int i=0; i < m_components.size(); i++)
			m_components[i].get().onUpdate();
	}

	/** @brief Clean up a State.
	* This will remove every component.
	* @return void
	*/
	void State::onCleanup()
	{

	}

	/** @brief Render a state on the given target.
	*
	* @param target The target on which the state is to be rendered.
	* @return void
	*/
	void State::onRender(sf::RenderTarget& target)
	{
	for(unsigned int i=0; i<m_drawableComponents.size(); i++)
		target.draw(m_drawableComponents[i].get());

	}

	/** @brief Handle the given sf::Event.
	*
	* @param e The event which is to be handled.
	* @return void
	*/
	void State::onEvent(sf::Event e)
	{
	for(unsigned int i=0; i < m_components.size(); i++)
		m_components[i].get().onEvent(e);
	}

	/** @brief Re-initialize a state.
	*
	* @return void
	*/
	void State::reInit()
	{
		State::onCleanup();
		State::onInit();
	}

	/** @brief Init a State.
	*
	* @return void
	*/
	void State::onInit()
	{
		m_nextState = 0;
		m_nexts.push_back(std::reference_wrapper<State>(*this));

	}

	/** @brief State destructor.
	*/
	State::~State()
	{}

	/** @brief State constructor.
	* This will not initialize the state. You need to call State::onInit().
	*/
	State::State()
	{
	}

	/** @brief Add a drawable component to a state.
	*
	* @param component
	* @return void
	*/
	void State::addComponent(DrawableComponent& component)
	{
		m_drawableComponents.push_back(std::reference_wrapper<DrawableComponent>(component));
		m_components.push_back(std::reference_wrapper<Component>(component));
	}

	/** @brief Add a component to the state.
	*
	* @param component
	* @return void
	*/
	void State::addComponent(Component& component)
	{
		m_components.push_back(std::reference_wrapper<Component>(component));
	}
}
