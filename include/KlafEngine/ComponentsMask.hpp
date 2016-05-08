#ifndef H_KLFCOMPONENTSMASK
#define H_KLFCOMPONENTSMASK

/**
 * @file ComponentsMask.hpp
 * @brief Contain every component bit mask.
 * @author klafyvel
 */

#include <bitset>
#include <cmath>

/**
 * @namespace klf
 *
 * Namespace for the KlafEngine's components.
 */
namespace klf {
	/** The component's mask size. */
	const size_t MASK_SIZE = 50;

	typedef std::bitset<MASK_SIZE> ComponentMask;

	unsigned int componentMaskToInt(ComponentMask mask);

	/** Render Components */

	const int COMPONENTS_FIRST_BIT = 0;

	const std::bitset<MASK_SIZE> POSITION		(1<<(0+COMPONENTS_FIRST_BIT));
	const std::bitset<MASK_SIZE> TRANSFORM		(1<<(1+COMPONENTS_FIRST_BIT));
	const std::bitset<MASK_SIZE> FIXEDSPRITE	(1<<(2+COMPONENTS_FIRST_BIT));
	const std::bitset<MASK_SIZE> SPRITE			(1<<(3+COMPONENTS_FIRST_BIT));
	const std::bitset<MASK_SIZE> ANIMATION		(1<<(4+COMPONENTS_FIRST_BIT));
	const std::bitset<MASK_SIZE> SHAPE			(1<<(5+COMPONENTS_FIRST_BIT));
	const std::bitset<MASK_SIZE> BOUND_BOX		(1<<(6+COMPONENTS_FIRST_BIT));
	const std::bitset<MASK_SIZE> TEXT_OUTPUT	(1<<(7+COMPONENTS_FIRST_BIT));

	/** Physics Components */

	const int PHYSICS_FIRST_BIT = COMPONENTS_FIRST_BIT + 8;

	const std::bitset<MASK_SIZE> MASS			(1<<(0+PHYSICS_FIRST_BIT));
	const std::bitset<MASK_SIZE> VELOCITY		(1<<(1+PHYSICS_FIRST_BIT));
	const std::bitset<MASK_SIZE> PHYSIC_POS		(1<<(2+PHYSICS_FIRST_BIT));
	const std::bitset<MASK_SIZE> MATERIAL		(1<<(3+PHYSICS_FIRST_BIT));
	const std::bitset<MASK_SIZE> PHYS_TRANSFORM	(1<<(4+PHYSICS_FIRST_BIT));
	const std::bitset<MASK_SIZE> COLLIDABLE		(1<<(5+PHYSICS_FIRST_BIT));
	const std::bitset<MASK_SIZE> PHYSIC			(1<<(6+PHYSICS_FIRST_BIT));

	/** Interface Components */

	const int INTERFACE_FIRST_BIT = PHYSICS_FIRST_BIT + 7;

	const std::bitset<MASK_SIZE> CLICKABLE		(1<<(0+INTERFACE_FIRST_BIT));
	const std::bitset<MASK_SIZE> KEYBOARD_INPUT	(1<<(1+INTERFACE_FIRST_BIT));
	const std::bitset<MASK_SIZE> KEY_BIND		(1<<(2+INTERFACE_FIRST_BIT));

	/** Logic Components */

	const int LOGIC_FIRST_BIT = INTERFACE_FIRST_BIT + 3;

	const std::bitset<MASK_SIZE> TRIGGERS		(1<<(0+LOGIC_FIRST_BIT));
	const std::bitset<MASK_SIZE> TRIGGERED		(1<<(1+LOGIC_FIRST_BIT));

	/** Character Components */

	const int CHARACTER_FIRST_BIT = LOGIC_FIRST_BIT + 2;

	const std::bitset<MASK_SIZE> LEFT			(1<<(0+CHARACTER_FIRST_BIT));
	const std::bitset<MASK_SIZE> TOP			(1<<(1+CHARACTER_FIRST_BIT));
	const std::bitset<MASK_SIZE> DOWN			(1<<(2+CHARACTER_FIRST_BIT));
	const std::bitset<MASK_SIZE> JUMP			(1<<(3+CHARACTER_FIRST_BIT));
	const std::bitset<MASK_SIZE> ACT_1			(1<<(4+CHARACTER_FIRST_BIT));
	const std::bitset<MASK_SIZE> ACT_2			(1<<(5+CHARACTER_FIRST_BIT));
	const std::bitset<MASK_SIZE> ACT_3			(1<<(6+CHARACTER_FIRST_BIT));
	const std::bitset<MASK_SIZE> CHARACTER		(1<<(7+CHARACTER_FIRST_BIT));

	const int FIRST_FREE_BIT = 1+7+CHARACTER_FIRST_BIT;
}

#endif // H_KLFCOMPONENTSMASK
