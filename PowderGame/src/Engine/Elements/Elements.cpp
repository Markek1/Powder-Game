#include <vector>

#include "Elements.h"

#include "UpdateFunctions/UpdateFunctions.h"


std::vector<Element> elements
{
	{ElementType::null, "NULL", {0, 0, 0, 255}, nullptr },

	{ElementType::solid, "SAND", {128, 178, 194, 255}, &update_Powder},
	{ElementType::solid, "STNE", {133, 142, 145, 255}, &update_Powder},
	{ElementType::solid, "SNOW", {255, 224, 192, 255}, &update_Powder},
	{ElementType::solid, "SALT", {253, 250, 243, 255}, &update_Powder},
	{ElementType::solid, "PLUT", {36, 166, 88, 255}, &update_Powder},

	{ElementType::solid, "IRON", {112, 112, 112, 255}, nullptr},
	{ElementType::solid, "WOOD", {64, 160, 192, 255}, nullptr},
	{ElementType::solid, "GOLD", {44, 169, 221, 255}, nullptr},

	{ElementType::liquid, "WATR", {208, 48, 32, 255}, &update_Liquid},
	{ElementType::liquid, "LAVA", {128, 192, 255, 255}, &update_Liquid},
	{ElementType::liquid, "ACID", {255, 163, 255, 255}, &update_Liquid},
};
