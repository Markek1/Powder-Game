#pragma once

#include <vector>

#include "../Engine.h"


enum class ElementType
{
	null, gas, liquid, solid
};


class Element
{
public:
	// Used for checking when other particles try to move into a cell containing this element.
	ElementType type{ ElementType::null };

	char name[5] {"DFLT"};
	uint8_t color[4]{ 255, 0, 255, 255 };

	// Called once every engine update
	bool(*update)(int x, int y, Grid& grid) { nullptr };

	// How many times a particle should try to move per update
	int spreadFactor{ 1 };
};


extern std::vector<Element> elements;
