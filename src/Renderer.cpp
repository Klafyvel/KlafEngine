#include <KlafEngine/Renderer.hpp>

namespace klf
{
	void Renderer::render(sf::RenderTarget& target)
	{
		std::unordered_map<unsigned int, ComponentMask>& entities = getActiveEntities();
		for(auto entity : entities)
		{
			if((entity.second & SHAPE).any())
			{
				Component& c = getComponent(SHAPE, entity.first);
				std::shared_ptr<Shape> s = std::dynamic_pointer_cast<Shape>(c.value);
				target.draw(*s);
			}
		}
	}
}
