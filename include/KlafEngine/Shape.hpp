#ifndef H_KLFSHAPE
#define H_KLFSHAPE

/**
 * @file Shape.hpp
 * @brief Everything to draw a shape.
 * @author klafyvel
 */

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include <KlafEngine/Core.hpp>
#include <KlafEngine/ComponentsMask.hpp>
#include <KlafEngine/Vector.hpp>
#include <KlafEngine/Utils.hpp>

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
			sum(0,0),
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
		Vector2 sum;
		sf::Color color;

	};

	class ShapesHandler : public System
	{
	public:
		ShapesHandler(Application& app, unsigned int id) : System(app, id) {}
		void addPoint(Entity entity, sf::Vector2f p);
		void removePoint(Entity entity, sf::Vector2f p, float d);
		void movePoint(Entity entity, sf::Vector2f p, float d);
		void setVisibleBoundBox(Entity entity, bool state);
		bool collide(Entity e1, Entity e2);
		bool collideSAT(const Shape& s1, const Shape& s2);
		Entity createShape();
		void createShape(Entity e);
		void move(Entity e, sf::Vector2f mv);
	};
}

#endif // H_KLFSHAPE
