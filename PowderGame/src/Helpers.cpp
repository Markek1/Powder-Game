#include <iostream>

#include "Helpers.h"


bool catch_error(bool result, std::string_view errorMessage)
{
	if (!result)
		std::cout << errorMessage;

	return result;
}
