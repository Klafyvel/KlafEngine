#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>

#include <KlafEngine/Core.hpp>


class MyComponent : public klf::Component
{
	public:
		MyComponent(unsigned int entity, int x, int y) : Component(entity) {
			int_values["x"] = x;
			int_values["y"] = y;
		}
		static std::unique_ptr<MyComponent> createEmptyMyComponent(unsigned int e)
		{
			std::cout << "Creating an empty MyComponent for entity " << e << "." << std::endl;
			std::unique_ptr<MyComponent> c(new MyComponent(e, 0,0));
			return c;
		}
};
std::unique_ptr<MyComponent> factory(unsigned int e)
{
	return MyComponent::createEmptyMyComponent(e);
}

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
	klf::Application app(window);

	app.registerComponentType(0, MyComponent::createEmptyMyComponent);

	for(auto i : range(0,100))
	{
		std::cout << "Create entity " << i << "." << std::endl;
		unsigned int entity = app.addEntity();
		app.addMask(entity, 0);
	}
	for(auto i : range(40,60))
	{
		std::cout << "Removing entity " << i << "." << std::endl;
		app.removeEntity(i);
	}
	for(auto i : range(0,60))
	{
		unsigned int e = app.addEntity();
		std::cout << "Creating entity " << e << "." << std::endl;
		app.addMask(e, 0);
	}



	return EXIT_SUCCESS;
}
