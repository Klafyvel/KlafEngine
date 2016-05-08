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

	klf::ShapesHandler s(app);
	klf::Renderer r(app);
	klf::Entity e = s.createShape();

	sf::Clock clock;
    float lastTime = 0;

	unsigned int n_iter = 0;
	float sum = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			else if (event.type == sf::Event::MouseButtonReleased)
			{
				if(event.mouseButton.button == sf::Mouse::Right)
					s.removePoint(e, sf::Vector2f(event.mouseButton.x, event.mouseButton.y), 30);
				else
					s.addPoint(e, sf::Vector2f(event.mouseButton.x, event.mouseButton.y));
			}
		}
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




