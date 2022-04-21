#include <vector>

#include "Element.h"

#include "UpdateFunctions/UpdateFunctions.h"


std::vector<Element> elements
{
	{
	.type = ElementType::null,
	.name = "NULL",
	.color = {0, 0, 0, 255}
	},

	{
	.type = ElementType::solid,
	.name = "SAND",
	.color = { 128, 178, 194, 255 },
	.update = &update_Powder
	},

	{
	.type = ElementType::solid,
	.name = "STNE",
	.color = {133, 142, 145, 255},
	.update = &update_Powder
	},

	{
	.type = ElementType::solid,
	.name = "SNOW",
	.color = {255, 224, 192, 255},
	.update = &update_Powder
	},

	{
	.type = ElementType::solid,
	.name = "SALT",
	.color = {253, 250, 243, 255},
	.update = &update_Powder
	},

	{
	.type = ElementType::solid,
	.name = "PLUT",
	.color = {36,  166, 88,  255},
	.update = &update_Powder
	},

	{
	.type = ElementType::solid,
	.name = "IRON",
	.color = {112, 112, 112, 255},
	.update = nullptr
	},

	{
	.type = ElementType::solid,
	.name = "WOOD",
	.color = {64,  160, 192, 255},
	.update = nullptr
	},

	{
	.type = ElementType::solid,
	.name = "GOLD",
	.color = {44,  169, 221, 255},
	.update = nullptr
	},

	{
	.type = ElementType::liquid,
	.name = "WATR",
	.color = {208,   48, 32, 255},
	.update = &update_Liquid,
	.spreadFactor = 8
	},

	{
	.type = ElementType::liquid,
	.name = "LAVA",
	.color = {23,  112, 255, 255},
	.update = &update_Liquid,
	.spreadFactor = 2
	},

	{
	.type = ElementType::liquid,
	.name = "ACID",
	.color = {255, 163, 255, 255},
	.update = &update_Liquid,
	.spreadFactor = 8
	},

	{
	.type = ElementType::gas,
	.name = "OXYG",
	.color = {255, 160, 128, 255},
	.update = &update_Gas,
	},

	{
	.type = ElementType::gas,
	.name = "SMKE",
	.color = {100, 100, 100, 255},
	.update = &update_Gas,
	},

	{
	.type = ElementType::gas,
	.name = "WTRV",
	.color = {255, 160, 160, 255},
	.update = &update_Gas,
	},
};
