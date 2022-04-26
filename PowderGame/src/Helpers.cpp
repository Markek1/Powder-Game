#include <iostream>

#include "Helpers.h"


bool catchError(bool result, std::string_view errorMessage)
{
	if (!result)
		std::cout << errorMessage;

	return result;
}


