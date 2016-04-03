#ifndef H_KLAFCORE
#define H_KLAFCORE

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

namespace klf
{
  class Application
  {
  public:
    Application(State& firstState);
    ~Application();

    void mainLoop();
    void event(sf::Event e);
    void update();
    void render();
    void changeState(State& state);

  protected:

  private:
    sf::Clock m_clock;
    sf::RenderWindow m_window;

    bool m_isRunning;

    State& m_currentState;

  };

  class Entity
  {
  public:
    Entity() = 0;
    virtual ~Entity() = 0;

  protected:

  private:

  };

  class System
  {
  public:
    System() = 0;
    virtual ~System() = 0;

  protected:

  private:

  };

  class Component
  {
  public:
    Component() = 0;
    virtual ~Component() = 0;

  protected:

  private:

  };

  class State : public System
  {
  public:
    State();
    virtual ~State() = 0;

    virtual void init(){
      if(m_cleanup)
        State::handleCleanup();

    }
    virtual void reInit() = 0;

    virtual void handleEvents(sf::Event theEvent) = 0;
    virtual void handleCleanup()
    {

    }

  protected:

    std::vector <Component> m_components;


  private:


  };
}

#endif // H_KLAFCORE
