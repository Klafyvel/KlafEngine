#ifndef H_KLAFCORE
#define H_KLAFCORE

#include <iostream>
#include <vector>
#include<functional>

#include <SFML/Graphics.hpp>

namespace klf
{
  class State;
  class Component;
  class Application
  {
  public:
    Application(State& firstState);
    ~Application();

    void onMainLoop();
    void onEvent(sf::Event e);
    void onUpdate();
    void onRender();
    void onInit();

    void changeState(State& state);
    void stopRunning();

  protected:

  private:
    sf::Clock m_clock;
    sf::RenderWindow m_window;

    bool m_isRunning;

    State& m_currentState;

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
    std::vector <std::reference_wrapper<Component>> m_components;
    std::vector <std::reference_wrapper<DrawableComponent>> m_drawableComponents;
    std::vector <std::reference_wrapper<State>> m_nexts;

  private:


  };
}

#endif // H_KLAFCORE
