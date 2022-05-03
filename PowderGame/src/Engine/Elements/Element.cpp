#include <vector>

#include "Element.h"

#include "UpdateFunctions/UpdateFunctions.h"

// might work with YAML files at some point
void initializeElements()
{
	elements.resize(ElementId::NUM_ITEMS);

	elements[ElementId::NONE] =
	{
	.type = ElementType::null,
	.name = "NONE",
	.color = {0, 0, 0, 255}
	};

	elements[ElementId::SAND] =
	{
	.type = ElementType::solid,
	.name = "SAND",
	.color = { 128, 178, 194, 255 },
	.update = &update_Powder
	};

	elements[ElementId::STNE] =
	{
	.type = ElementType::solid,
	.name = "STNE",
	.color = {133, 142, 145, 255},
	.update = &update_Powder
	};

	elements[ElementId::SNOW] =
	{
	.type = ElementType::solid,
	.name = "SNOW",
	.color = {255, 224, 192, 255},
	.update = &update_Powder
	};

	elements[ElementId::SALT] =
	{
	.type = ElementType::solid,
	.name = "SALT",
	.color = {253, 250, 243, 255},
	.update = &update_Powder
	};

	elements[ElementId::PLUT] =
	{
	.type = ElementType::solid,
	.name = "PLUT",
	.color = {36,  166, 88,  255},
	.update = &update_Powder
	};

	elements[ElementId::IRON] =
	{
	.type = ElementType::solid,
	.name = "IRON",
	.color = {112, 112, 112, 255},
	.update = nullptr
	};

	elements[ElementId::WOOD] =
	{
	.type = ElementType::solid,
	.name = "WOOD",
	.color = {64,  160, 192, 255},
	.update = nullptr,
	.flammability = 0.005
	};

	elements[ElementId::GOLD] =
	{
	.type = ElementType::solid,
	.name = "GOLD",
	.color = {44,  169, 221, 255},
	.update = nullptr
	};

	elements[ElementId::OBSD] =
	{
	.type = ElementType::solid,
	.name = "OBSD",
	.color = {120,  49, 80, 255},
	.update = nullptr
	};

	elements[ElementId::WATR] =
	{
	.type = ElementType::liquid,
	.name = "WATR",
	.color = {208,   48, 32, 255},
	.update = &update_Liquid,
	.spreadFactor = 8
	};

	elements[ElementId::LAVA] =
	{
	.type = ElementType::liquid,
	.name = "LAVA",
	.color = {23,  112, 255, 255},
	.update = &update_Liquid,
	.spreadFactor = 2
	};

	elements[ElementId::ACID] =
	{
	.type = ElementType::liquid,
	.name = "ACID",
	.color = {255, 163, 255, 255},
	.update = &update_Liquid,
	.spreadFactor = 8
	};

	elements[ElementId::OXYG] =
	{
	.type = ElementType::gas,
	.name = "OXYG",
	.color = {255, 160, 128, 255},
	.update = &update_Gas,
	.flammability = 0.3
	};

	elements[ElementId::SMKE] =
	{
	.type = ElementType::gas,
	.name = "SMKE",
	.color = {100, 100, 100, 255},
	.update = &update_Gas,
	};

	elements[ElementId::WTRV] =
	{
	.type = ElementType::gas,
	.name = "WTRV",
	.color = { 255, 160, 160, 255 },
	.update = &update_Gas,
	};

	elements[ElementId::FIRE] =
	{
	.type = ElementType::gas,
	.name = "FIRE",
	.color = { 20, 110, 255, 255 },
	.update = &update_Fire,
	};
}
