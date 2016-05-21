#ifndef H_KLFSHAPE
#define H_KLFSHAPE

/**
 * @file Shape.hpp
 * @brief Everything to draw a shape.
 * @author klafyvel
 * It's basically a SFML binding to the ECS.
 */

#include <memory>

#include <SFML/Graphics.hpp>

#include <KlafEngine/Core.hpp>
#include <KlafEngine/ComponentsMask.hpp>

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
			vertices(sf::LinesStrip, count),
			color(sf::Color::White)
		{}
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			states.transform *= getTransform();
			target.draw(vertices, states);
		}
		static std::unique_ptr<Component> shapeFactory(Entity e)
		{
			std::unique_ptr<klf::Component> c = klf::Component::createEmptyComponent(e);
			c->value = std::shared_ptr<Shape>(new Shape(0));
			return c;
		}
		sf::VertexArray vertices;
		sf::Color color;

	};

	class ShapesHandler : public System
	{
	public:
		ShapesHandler(Application& app) : System(app) {}
		void addPoint(Entity entity, sf::Vector2f p);
		void removePoint(Entity entity, sf::Vector2f p, float d);
		void setVisibleBoundBox(Entity entity, bool state);
		Entity createShape();
		void createShape(Entity e);
	};
}

#endif // H_KLFSHAPE
