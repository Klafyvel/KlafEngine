#ifndef H_KLFSHAPE
#define H_KLFSHAPE

/**
 * @file Shape.hpp
 * @brief Everything to draw a shape.
 * @author klafyvel
 * It's basically a SFML binding to the ECS.
 */

#include <SFML/Graphics.hpp>

#include <KlafEngine/Core.hpp>

/**
 * @namespace klf
 *
 * Namespace for the KlafEngine's components.
 */
namespace klf
{
	class Shape : public ComponentData, public sf::Transformable, public sf::Drawable
	{
	public:
		Shape(int count) :
			ComponentData(),
			sf::Transformable(),
			sf::Drawable(),
			m_vertices(sf::LinesStrip, count + 1)
		{}
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			states.transform *= getTransform();
			target.draw(m_vertices, states);
		}
		sf::VertexArray m_vertices;

	};

	class ShapesHandler : public System
	{
	public:
		ShapesHandler(Application& app) : System(app) {}
	};
}

#endif // H_KLFSHAPE
