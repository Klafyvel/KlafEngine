#ifndef H_PHYSICAL_OBJECT
#define H_PHYSICAL_OBJECT

#include <SFML/Graphics.hpp>

#include <Core.hpp>

namespace klf
{
	class PhysicalObject : public DrawableComponent
	{
	public:
		PhysicalObject(sf::Vector2f pos);
		~PhysicalObject();

		virtual void onUpdate();

	protected:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states);

		sf::Vector2f m_pos;


}


#endif // H_PHYSICAL_OBJECT
