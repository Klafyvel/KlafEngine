#ifndef H_KLFRENDERER
#define H_KLFRENDERER

/**
 * @file Renderer.hpp
 * @brief KlafEngine's rendering system.
 * @author klafyvel
 */

#include <unordered_map>
#include <memory>

#include <SFML/Graphics.hpp>

#include <KlafEngine/Core.hpp>
#include <KlafEngine/ComponentMask.hpp>
#include <KlafEngine/Shape.hpp>


/**
 * @namespace klf
 *
 * Namespace for the KlafEngine's components.
 */
namespace klf
{
	// const std::bitset<MASK_SIZE> DRAWABLE = FIXEDSPRITE | SPRITE | SHAPE | TEXT_OUTPUT;

	class Renderer : public System
	{
	public:
		Renderer(Application& app): System(app) {}

		void render(sf::RenderTarget& target)
		{
			std::unordered_map<unsigned int, ComponentMask>& entities = getActiveEntities();
			for(auto entity : entities)
			{
				if(entities.second&SHAPE)
				{
					Component& c = getComponent(SHAPE, entity.first);
					std::shared_ptr<Shape> s = std::dynamic_pointer_cast<Shape>(c.value);
					target.draw(s);
				}
			}
		}
	};


#endif // H_KLFRENDERER
