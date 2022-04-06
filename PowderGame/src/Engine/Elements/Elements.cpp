#include <vector>

#include "Elements.h"

#include "UpdateFunctions/UpdateFunctions.h"


std::vector<Element> elements
{
	{ElementType::null, "NULL", {0, 0, 0, 255}, nullptr },
	{ElementType::solid, "SAND", {128, 178, 194, 255}, &update_SolidMovable},
	{ElementType::solid, "STNE", {133, 142, 145, 255}, &update_SolidMovable},
	{ElementType::solid, "SNOW", {50, 224, 192, 255}, &update_SolidMovable},
	{ElementType::solid, "SALT", {253, 250, 243, 255}, &update_SolidMovable},
	{ElementType::solid, "PLUT", {36, 166, 88, 255}, &update_SolidMovable},

	{ElementType::solid, "IRON", {112, 112, 112, 255}, nullptr},
	{ElementType::solid, "WOOD", {64, 160, 192, 255}, nullptr},
	{ElementType::solid, "GOLD", {44, 169, 221, 255}, nullptr}
};