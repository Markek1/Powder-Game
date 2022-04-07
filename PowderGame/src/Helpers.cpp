#include <iostream>

#include "Helpers.h"


bool catch_error(bool result, std::string_view errorMessage)
{
	if (!result)
		std::cout << errorMessage;

	return result;
}


static unsigned long x = 123456789, y = 362436069, z = 521288629;

unsigned long fastRand()
{
	unsigned long t;
	x ^= x << 16;
	x ^= x >> 5;
	x ^= x << 1;

	t = x;
	x = y;
	y = z;
	z = t ^ x ^ y;

	return z;
}