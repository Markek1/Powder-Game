#pragma once

#include <iostream>
#include <string_view>


template <typename T>
struct Vector2
{
public:
	T x;
	T y;
};


template <typename T>
struct Vector3
{
public:
	T x;
	T y;
	T z;
};


template <typename T>
struct Vector4
{
public:
	T x;
	T y;
	T z;
	T w;
};


bool catchError(bool result, std::string_view errorMessage);

static unsigned long x = 123456789, y = 362436069, z = 521288629;
inline unsigned long fastRand()
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