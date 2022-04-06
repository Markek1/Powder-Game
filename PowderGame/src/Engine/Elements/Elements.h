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
	/*Used for checking when other particles try to move into a cell containing this element.*/
	ElementType m_type;

	char m_name[5];
	uint8_t m_color[4];

	bool(*update)(int x, int y, Grid& grid);
};


extern std::vector<Element> elements;