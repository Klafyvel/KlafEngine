#ifndef H_KLAFINTERFACE
#define H_KLAFINTERFACE

#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../Core/Core.h"

namespace klf
{
  template <class T>
  class Widget : public DrawableComponent
  {
  public:
    Widget(sf::IntRect rect, T value) : DrawableComponent(sf::Vector2f(rect.left, rect.top)), m_rect(rect), m_value(value){};
    virtual ~Widget(){};

    virtual T getValue() = 0;
    virtual void setValue(T value) = 0;

  protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
    sf::IntRect m_rect;
    T m_value;

  };


  typedef Widget <int> IntWidget;
  typedef Widget <float> FloatWidget;
  typedef Widget <sf::String> StringWidget;
  typedef Widget <bool> BoolWidget;

  class Button : public BoolWidget
  {
  public:
    Button(sf::IntRect rect, sf::String text, sf::Color bg=sf::Color(0,0,0,0), sf::Color textColor=sf::Color(255,255,255,255));

    void setValue(bool value) {m_value = value;}
    bool getValue() {return m_value;}

    void onEvent(sf::Event e);

  protected:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

    sf::IntRect m_rect;
    sf::String m_text;
    sf::Color m_bg;
    sf::Color m_textColor;

    bool m_pressing;
    bool m_value;
  };
}

#endif // H_KLAFINTERFACE
