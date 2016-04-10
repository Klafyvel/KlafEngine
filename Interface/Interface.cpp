#include "Interface.h"

namespace klf
{
  /** @brief Draws the button.
    *
    */
  void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
  {
    sf::Vector2f pos(m_rect.left, m_rect.top);
    sf::Vector2f rectSize(m_rect.width, m_rect.height);

    sf::RectangleShape rect(rectSize);
    rect.setPosition(pos);
    rect.setFillColor(m_bg);

    target.draw(rect, states);

    //std::cout << m_rect.left << " " << m_rect.top << " " << m_rect.width << " " << m_rect.height << std::endl;

  }

  /** @brief (one liner)
    *
    * (documentation goes here)
    */
   Button::Button(sf::IntRect rect, sf::String text, sf::Color bg, sf::Color textColor) :
     Widget<bool>::Widget(rect, false), m_rect(rect), m_text(text), m_bg(bg), m_textColor(textColor)
  {
    std::cout << rect.left << " " << rect.top << " " << rect.width << " " << rect.height << std::endl;
  }


  /** @brief (one liner)
    *
    * (documentation goes here)
    */
  void Button::onEvent(sf::Event e)
  {
    if (e.type == sf::Event::MouseButtonPressed)
      m_pressing = true;
    else if (e.type == sf::Event::MouseButtonReleased)
    {
      m_pressing = false;
      m_value = true;
      std::cout << "Released" << std::endl;
    }
  }

}
