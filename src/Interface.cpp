#include <KlafEngine/Interface.hpp>

namespace klf
{
	//////////////
	// FUNCTIONS
	///////////////////////////////

	/** @brief Check if a point is in a rect.
	 * @param p The point which is to be checked.
	 * @param rect The rectangle.
	 * @return A boolean (true if the point is inside, false if it is not.)
	 */
	bool pointInRect(sf::Vector2f p, sf::IntRect rect)
	{
		bool x = rect.left < p.x && p.x < rect.left+rect.width;
		bool y = rect.top < p.y && p.y < rect.top+rect.height;
		return x & y;
	}


	//////////////
	// BUTTON
	///////////////////////////////
	/** @brief Draws the button.
	* @param target The target on which the button is to be rendered.
	* @return void
	*/
	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		sf::Vector2f pos(m_rect.left, m_rect.top);
		sf::Vector2f rectSize(m_rect.width, m_rect.height);

		sf::Color bg(m_bg);
		if(m_pressing)
		{
			bg.r = (int)(0.5*bg.r);
			bg.g = (int)(0.5*bg.g);
			bg.b = (int)(0.5*bg.b);
		}

		sf::RectangleShape rect(rectSize);
		rect.setPosition(pos);
		rect.setFillColor(bg);

		target.draw(rect, states);
	}

	/** @brief Button's constructor.
	*
	* @param rect A rectangle that represents the button.
	* @param text Text of the button.
	* @param bg Background color.
	* @param textColor Text color.
	*/
	Button::Button(sf::IntRect rect, sf::String text, sf::Color bg, sf::Color textColor) :
		 Widget<bool>::Widget(rect, false), m_rect(rect), m_text(text), m_bg(bg), m_textColor(textColor), m_pressing(false), m_value(false)
	{
	}

	/** @brief Handle an event.
	*
	* @param e The event which is to be handled.
	* @return void
	*/
	void Button::onEvent(sf::Event e)
	{
		if (e.type == sf::Event::MouseButtonPressed)
		{
			sf::Vector2f p(e.mouseButton.x, e.mouseButton.y);
			m_pressing = pointInRect(p, m_rect);
			m_value = m_pressing;
		}
		else if (e.type == sf::Event::MouseButtonReleased)
		{
			m_pressing = false;
		}
	}

}
