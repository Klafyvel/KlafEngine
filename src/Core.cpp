#include <KlafEngine/Core.hpp>

namespace klf
{
	//////////////
	// APPLICATION
	///////////////////////////////

	void Application::stopRunning()
	{
		m_isRunning = false;
	}

	void Application::changeState(State& state)
	{
		m_currentState = state;
	}

	void Application::onInit()
	{
		m_window.create(sf::VideoMode(800, 600), "KlafEngine");
		m_window.setFramerateLimit(60);
	}

	void Application::onRender()
	{
		m_window.clear();
		m_currentState.onRender(m_window);
	}

	void Application::onUpdate()
	{
		m_currentState = m_currentState.nextState();
		m_currentState.onUpdate();
	}

	void Application::onEvent(sf::Event e)
	{
		if(e.type == sf::Event::Closed)
			m_isRunning = false;
		else
			m_currentState.onEvent(e);
	}

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

	Application::~Application()
	{
		m_window.close();
	}

	Application::Application(State& firstState):
		m_clock(),
		m_window(),
		m_isRunning(false),
		m_currentState(firstState)
	{
	}

  //////////////
  // STATE
  ///////////////////////////////
	void State::setNextState(int index)
	{
		m_nextState = index;
	}

	void State::addNextState(State& state)
	{
		m_nexts.push_back(std::reference_wrapper<State>(state));
	}

	State& State::nextState()
	{
		return m_nexts[m_nextState].get();
	}

	void State::onUpdate()
	{
		for(unsigned int i=0; i < m_components.size(); i++)
			m_components[i].get().onUpdate();
	}

	void State::onCleanup()
	{

	}

	void State::onRender(sf::RenderTarget& target)
	{
	for(unsigned int i=0; i<m_drawableComponents.size(); i++)
		target.draw(m_drawableComponents[i].get());

	}

	void State::onEvent(sf::Event e)
	{
	for(unsigned int i=0; i < m_components.size(); i++)
		m_components[i].get().onEvent(e);
	}

	void State::reInit()
	{
		State::onCleanup();
		State::onInit();
	}

	void State::onInit()
	{
		m_nextState = 0;
		m_nexts.push_back(std::reference_wrapper<State>(*this));

	}

	State::~State()
	{}

	State::State()
	{
	}

	void State::addComponent(Component& component, bool drawable)
	{
		if(drawable)
			m_drawableComponents.push_back(std::reference_wrapper<Component>(component));
		m_components.push_back(std::reference_wrapper<Component>(component));
	}
}
