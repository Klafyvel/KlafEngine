#include <iostream>
#include <KlafEngine/Core.hpp>
#include <KlafEngine/Interface.hpp>

int main()
{
  klf::Button bp(sf::IntRect(1,1,100,60), "Hello World", sf::Color(200,200,200), sf::Color(200,200,200));
  klf::State st;
  st.onInit();

  st.addComponent(bp);

  klf::Application app(st);

  app.onMainLoop();

  return EXIT_SUCCESS;
}
