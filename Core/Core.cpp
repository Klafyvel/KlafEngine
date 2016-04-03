#include "Core.h"

namespace klf
{
  //////////////
  // APPLICATION
  ///////////////////////////////

  /** @brief Stops the application's run.
    * @return void
    */
  void Application::stopRunning()
  {
    m_isRunning = false;
  }

  /** @brief (one liner)
    * @return void
    */
  void Application::changeState(State& state)
  {
    m_currentState = state;
  }

  /** @brief Initializes the application.
    *
    */
  void Application::onInit()
  {
    m_window.create(sf::VideoMode(800, 600), "KlafEngine");
  }

  /** @brief Renders the current state.
    * @return void
    */
  void Application::onRender()
  {
    m_window.clear();
    m_currentState.onRender(m_window);
  }

  /** @brief (one liner)
    *
    * (documentation goes here)
    */
  void Application::onUpdate()
  {

    m_currentState = m_currentState.nextState();
  }

  /** @brief Handles events for the application.
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

  /** @brief Initializes the application then handles the application's main loop.
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
  /** @brief Draws a component.
    *
    */
  void Component::draw(sf::RenderTarget& target, sf::RenderStates states)
  {

  }

  /** @brief (one liner)
    *
    * (documentation goes here)
    */
   Component::~Component()
  {

  }

  /** @brief (one liner)
    *
    * (documentation goes here)
    */
   Component::Component(sf::Vector2f pos):
     m_pos(pos)
  {

  }

  //////////////
  // STATE
  ///////////////////////////////
  /** @brief (one liner)
    *
    * (documentation goes here)
    */
  void State::setNextState(int index)
  {

  }

  /** @brief (one liner)
    *
    * (documentation goes here)
    */
  void State::addNextState(State& state)
  {

  }

  /** @brief (one liner)
    *
    * (documentation goes here)
    */
  State& State::nextState()
  {
    return (*this);
  }

  /** @brief (one liner)
    *
    * (documentation goes here)
    */
  void State::onUpdate()
  {

  }

  /** @brief (one liner)
    *
    * (documentation goes here)
    */
  void State::onCleanup()
  {

  }

  /** @brief (one liner)
    *
    * (documentation goes here)
    */
  void State::onRender(sf::RenderTarget& target)
  {

  }

  /** @brief (one liner)
    *
    * (documentation goes here)
    */
  void State::onEvent(sf::Event e)
  {

  }

  /** @brief (one liner)
    *
    * (documentation goes here)
    */
  void State::reInit()
  {

  }

  /** @brief (one liner)
    *
    * (documentation goes here)
    */
  void State::onInit()
  {

  }

  /** @brief (one liner)
    *
    * (documentation goes here)
    */
   State::~State()
  {

  }

  /** @brief (one liner)
    *
    * (documentation goes here)
    */
   State::State()
  {

  }


}
