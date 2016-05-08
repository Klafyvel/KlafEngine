#include <iostream>

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

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		r.render(window);
		window.display();
	}

	return EXIT_SUCCESS;
}




