#include <iostream>
#include <KlafEngine/Core.h>
#include <KlafEngine/Interface.h>

int main()
{
  klf::Button bp(sf::IntRect(1,1,100,60), "Hello World", sf::Color(200,200,200), sf::Color(200,200,200));
  klf::State st;

  st.addComponent(bp);

  klf::Application app(st);

  app.onMainLoop();

  return EXIT_SUCCESS;
}
