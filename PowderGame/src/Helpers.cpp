#include <iostream>

#include "Helpers.h"


int32_t error(int32_t result, std::string errorMessage)
{
	if (result)
	{
		std::cout << errorMessage;
	}

	return result;
}


uint32_t FastRand(void)
{
	uint32_t t;

	s_randX ^= s_randX << 16;
	s_randX ^= s_randX >> 5;
	s_randX ^= s_randX << 1;

	t = s_randX;
	s_randX = s_randY;
	s_randY = s_randZ;
	s_randZ = t ^ s_randX ^ s_randY;

	return s_randZ;
}
