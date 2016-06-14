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
	/** @class Shape
	 * @brief A shape which can be drawn.
	 */
	class Shape : public ComponentData, public sf::Transformable, public sf::Drawable
	{
	public:
		/** @brief Constructor.
		 * @param count Count of vertices.
		 */
		Shape(int count) :
			ComponentData(),
			sf::Transformable(),
			sf::Drawable(),
			vertices(sf::LinesStrip, count),
			sum(0,0),
			color(sf::Color::White)
		{}
		/** @brief SFML binding to draw the shape.
		 * @param target The target.
		 * @param states States (transformations and so on.)
		 */
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			states.transform *= getTransform();
			target.draw(vertices, states);
		}
		/** @brief Dynamically allow a shape.
		 * @param e The shape's entity.
		 * @return std::unique_ptr on the shape.
		 */
		static std::unique_ptr<Component> shapeFactory(Entity e)
		{
			std::unique_ptr<klf::Component> c = klf::Component::createEmptyComponent(e);
			c->value = std::shared_ptr<Shape>(new Shape(0));
			return c;
		}
		sf::VertexArray vertices; /** Shape's vertices. */
		Vector2 sum; /** Sum of the Shape's vertices. */
		sf::Color color; /** Shape's color. */

	};

	/** @class ShapesHandler
	 * @brief Perform basics operations on shapes, such as moving their vertices or test their collisions.
	 */
	class ShapesHandler : public System
	{
	public:
		/** @brief Constructor.
		 * @param app The System's app.
		 * @param id Its id.
		 */
		ShapesHandler(Application& app, unsigned int id) : System(app, id) {}
		/** @brief Add a vertex to the entity's shape.
		 * @param entity The entity.
		 * @param p The point which is to be added.
		 */
		void addPoint(Entity entity, sf::Vector2f p);
		/** @brief Remove the points at a given distance of an other one.
		 * @param entity The entity.
		 * @param p The point.
		 * @param d The max distance.
		 */
		void removePoint(Entity entity, sf::Vector2f p, float d);
		void movePoint(Entity entity, sf::Vector2f p, float d);
		void setVisibleBoundBox(Entity entity, bool state);
		Vector2 collide(Entity e1, Entity e2);
		Vector2 collideSAT(const Shape& s1, const Shape& s2);
		Vector2 collideBoundBox(const Shape& s1, const Shape& s2) const;
		Entity createShape();
		void createShape(Entity e);
		void move(Entity e, sf::Vector2f mv);
	};
}

#endif // H_KLFSHAPE
