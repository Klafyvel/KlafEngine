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

	void ShapesHandler::move(Entity e, Vector2 mv)
	{
		Component& c = getComponent(SHAPE, e);
		std::shared_ptr<Shape> s = std::dynamic_pointer_cast<Shape>(c.value);
		for (int i : range(0,s->vertices.getVertexCount()))
			s->vertices[i].position += mv.toSFML();
	}

	Vector2 ShapesHandler::collide(Entity e1, Entity e2)
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
		return Vector2(0,0);
	}

	Vector2 ShapesHandler::collideSAT(const Shape& s1, const Shape& s2)
	{
		int sizeS1 = s1.vertices.getVertexCount();
		int sizeS2 = s2.vertices.getVertexCount();
		if(sizeS1 <= 1 || sizeS2 <= 1)
			return Vector2(0,0);
		Vector2 minV(0,0);
		float minMag = 0;
		bool colliding = true;
		for (int i : range(0,sizeS1))
		{
			if (!colliding)
				break;
			Vector2 axis = (Vector2(s1.vertices[(i+1)%sizeS1].position) \
				- Vector2(s1.vertices[i].position)).orthogonal();
			Vector2 p1 = ShapesHandler::projectOrthogonally(s1,axis);
			Vector2 p2 = ShapesHandler::projectOrthogonally(s2,axis);
			float inter = intersect(p1.x,p1.y, p2.x, p2.y);
			if(i==0 || (colliding && inter > 0 && inter < minMag))
			{
				minV = axis.norm() * inter;
				minMag = inter;
			}
			else if (inter <= 0)
			{
				colliding = false;
				minV = Vector2(0,0);
				minMag = 0;
			}
		}
		for (int i : range(0,sizeS2))
		{
			if (!colliding)
				break;
			Vector2 axis = (Vector2(s2.vertices[(i+1)%sizeS2].position) \
				- Vector2(s2.vertices[i].position)).orthogonal();
			Vector2 p1 = ShapesHandler::projectOrthogonally(s1,axis);
			Vector2 p2 = ShapesHandler::projectOrthogonally(s2,axis);
			float inter = intersect(p1.x,p1.y, p2.x, p2.y);
			if(colliding && inter > 0 && inter < minMag)
			{
				minV = axis.norm() * inter;
				minMag = inter;
			}
			else if (inter <= 0)
			{
				colliding = false;
				minV = Vector2(0,0);
				minMag = 0;
			}
		}
		return minV;
	}
	Vector2 ShapesHandler::collideBoundBox(const Shape& s1, const Shape& s2) const
	{
		sf::FloatRect b1 = s1.vertices.getBounds();
		sf::FloatRect b2 = s2.vertices.getBounds();
		return Vector2( \
				intersect(b1.left,b1.left+b1.width, b2.left, b2.left+b2.width),\
				intersect(b1.top, b1.top+b1.height, b2.top, b2.top+b2.height));
	}
	Vector2 ShapesHandler::projectOrthogonally(const Shape& s, Vector2 axis)
	{
		Vector2 dir = axis.norm();
		int size = s.vertices.getVertexCount();
		Vector2 ret;
		for(int i : range(0,size))
		{
			Vector2 p(s.vertices[i].position);
			float v = p*dir;
			if (i==0)
				ret = Vector2(v,v);
			else
				ret = Vector2(std::min(ret.x,v), std::max(ret.y,v));
		}
		return ret;
	}

}
