#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include <KlafEngine/Core.hpp>

class MyCompData : public klf::ComponentData
{
public:
	MyCompData() : x(0), y(0) {}
	int x;
	int y;
};

std::unique_ptr<klf::Component> factory(unsigned int e)
{
	std::unique_ptr<klf::Component> c = klf::Component::createEmptyComponent(e);
	c->value = std::shared_ptr<klf::ComponentData>(new MyCompData());
	return c;
}

class MySystem : public klf::System
{
public:
	MySystem(klf::Application& app) : klf::System(app) {}
	void onUpdate()
	{
		std::cout << "Update ! " << std::endl;
		klf::Component& c = getComponent(0, 0);
		std::shared_ptr<MyCompData> d = std::dynamic_pointer_cast<MyCompData>(c.value);
		std::cout << "Entity : " << c.entity << " " << d->x << " " << d->y << std::endl;
		d->x += 20;
	}
};

class range {
 public:
   class iterator {
      friend class range;
    public:
      long int operator *() const { return i_; }
      const iterator &operator ++() { ++i_; return *this; }
      iterator operator ++(int) { iterator copy(*this); ++i_; return copy; }

      bool operator ==(const iterator &other) const { return i_ == other.i_; }
      bool operator !=(const iterator &other) const { return i_ != other.i_; }

    protected:
      iterator(long int start) : i_ (start) { }

    private:
      unsigned long i_;
   };

   iterator begin() const { return begin_; }
   iterator end() const { return end_; }
   range(long int  begin, long int end) : begin_(begin), end_(end) {}
private:
   iterator begin_;
   iterator end_;
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "KlafEngine");
	klf::Application app;

	app.registerComponentType(0, factory);

	std::cout << "Let's create 100 entites with our MyCompData as component." << std::endl;
	for(auto i : range(0,100))
	{
		unsigned int entity = app.addEntity();
		app.addMask(entity, 0);
	}
	std::cout << "Done." << std::endl;
	std::cout << "Let's remove entites 40 to 59 ." << std::endl;
	for(auto i : range(40,60))
	{
		app.removeEntity(i);
	}
	std::cout << "Done." << std::endl;
	std::cout << "Let's create 60 entites with our MyCompData as component." << std::endl;
	for(auto i : range(0,60))
	{
		unsigned int e = app.addEntity();
		app.addMask(e, 0);
	}


	std::cout << "Let's create a system and update it !" << std::endl;

	MySystem s(app);
	s.onUpdate();
	s.onUpdate();

	return EXIT_SUCCESS;
}
