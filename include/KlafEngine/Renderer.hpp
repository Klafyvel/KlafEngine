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
#include <KlafEngine/ComponentsMask.hpp>
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

		void render(sf::RenderTarget& target);
	};
}


#endif // H_KLFRENDERER
