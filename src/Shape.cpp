#include <KlafEngine/Shape.hpp>

namespace klf
{
	void ShapesHandler::addPoint(Entity entity, sf::Vector2f p)
	{
		Component& c = getComponent(SHAPE, entity);
		std::shared_ptr<Shape> s = std::dynamic_pointer_cast<Shape>(c.value);
		auto size = s->vertices.getVertexCount();
		if (size <= 0)
		{
			s->vertices.append(sf::Vertex(p, s->color));
			s->vertices.append(s->vertices[0]);
		}
		else
		{
			s->vertices[size - 1] = sf::Vertex(p, s->color);
			s->vertices.append(s->vertices[0]);
		}
		s->sum += Vector2(p);
	}

	void ShapesHandler::removePoint(Entity entity, sf::Vector2f p, float d)
	{
		float d2 = d*d;
		Component& c = getComponent(SHAPE, entity);
		auto s = std::dynamic_pointer_cast<Shape>(c.value);
		sf::VertexArray n(sf::LinesStrip);
		Vector2 sum(0,0);
		for(int i=0;i<s->vertices.getVertexCount();i++)
		{
			float e = pow(s->vertices[i].position.x-p.x, 2) + pow(s->vertices[i].position.y-p.y, 2);
			if(e > d2)
			{
				n.append(s->vertices[i]);
				sum += Vector2(s->vertices[i].position);
			}
		}
		if (n[n.getVertexCount()-1].position != n[0].position)
			n.append(n[0]);
		s->vertices = n;
		s->sum = sum;
	}
	void ShapesHandler::movePoint(Entity entity, sf::Vector2f p, float d)
	{
		float d2 = d*d;
		Component& c = getComponent(SHAPE, entity);
		auto s = std::dynamic_pointer_cast<Shape>(c.value);
		for(int i=0;i<s->vertices.getVertexCount();i++)
		{
			float e = pow(s->vertices[i].position.x-p.x, 2) + pow(s->vertices[i].position.y-p.y, 2);
			if(e < d2)
				s->vertices[i].position = p;
		}
	}

	void ShapesHandler::setVisibleBoundBox(Entity entity, bool state)
	{}

	Entity ShapesHandler::createShape()
	{
		Entity e = m_application.addEntity();
		m_application.makeActive(e);
		m_application.addMask(e, SHAPE);
		return e;
	}

	void ShapesHandler::createShape(Entity e)
	{
		m_application.addMask(e, SHAPE);
	}

	void ShapesHandler::move(Entity e, sf::Vector2f mv)
	{
		Component& c = getComponent(SHAPE, e);
		std::shared_ptr<Shape> s = std::dynamic_pointer_cast<Shape>(c.value);
		s->move(mv);
	}

	bool ShapesHandler::collide(Entity e1, Entity e2)
	{
		ComponentMask mask1 = System::getComponentMask(e1);
		ComponentMask mask2 = System::getComponentMask(e2);
		if ((mask1 & SHAPE)!=0 && (mask2 & SHAPE)!=0) // We can use SAT method
		{
			Shape& s1 = dynamic_cast<Shape&>(System::getComponent(SHAPE, e1).getValue());
			Shape& s2 = dynamic_cast<Shape&>(System::getComponent(SHAPE, e2).getValue());
			return ShapesHandler::collideSAT(s1, s2);
		}
		else
		{
			std::cerr << "Don't know how to test collide..." << std::endl;
		}
	}

	bool ShapesHandler::collideSAT(const Shape& s1, const Shape& s2)
	{
		return false;
	}

}
