#include <iostream>
#include <sstream>
#include <string>

#include <SFML/Graphics.hpp>

#include <KlafEngine/Core.hpp>
#include <KlafEngine/ComponentsMask.hpp>
#include <KlafEngine/Renderer.hpp>
#include <KlafEngine/Shape.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "KlafEngine");
	klf::Application app;

	app.registerComponentType(klf::SHAPE, klf::Shape::shapeFactory);

	klf::ShapesHandler s(app, 0);
	klf::Renderer r(app, 1);
	klf::Entity e1 = s.createShape();
	klf::Entity e2 = s.createShape();

	s.collide(e1, e2);

	sf::Clock clock;
    float lastTime = 0;

	unsigned int n_iter = 0;
	float sum = 0;

	bool moving = false;

	bool currentShapeIs1 = true;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				if(!moving && event.mouseButton.button == sf::Mouse::Right)
					s.removePoint(e1, sf::Vector2f(event.mouseButton.x, event.mouseButton.y), 30);
				else
					s.addPoint(e1, sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			sf::Vector2i i = sf::Mouse::getPosition(window);
			sf::Vector2f p(i.x,i.y);
			s.movePoint(e1, p, 20);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			s.move(e1, sf::Vector2f(-1,0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			s.move(e1, sf::Vector2f(1,0));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			s.move(e1, sf::Vector2f(0,-1));
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			s.move(e1, sf::Vector2f(0,1));


		sum += 1.f / clock.getElapsedTime().asSeconds();
		n_iter += 1;
		clock.restart();
		std::ostringstream ss;
		ss << sum / n_iter;
		window.setTitle("FPS : " + ss.str());

		if(n_iter > 1000)
		{
			n_iter = 0;
			sum = 0.f;
		}

		window.clear();
		r.render(window);
		window.display();
	}

	return EXIT_SUCCESS;
}




