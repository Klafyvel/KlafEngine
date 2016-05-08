#include <iostream>

#include <SFML/Graphics.hpp>

#include <KlafEngine/Core.hpp>
#include <KlafEngine/ComponentMask.hpp>
#include <KlafEngine/Renderer.hpp>
#include <KlafEngine/Shape.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "KlafEngine");
	klf::Application app;

	app.registerComponentType(SHAPE, Shape::shapeFactory);


