#pragma once

#include <iostream>


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


// If result is equal to 0, prints out errorMessage
int32_t error(int32_t result, std::string errorMessage);


//Marsaglia's xorshf generator (Fast Random Function)
static uint32_t s_randX = 123456789;
static uint32_t s_randY = 362436069;
static uint32_t s_randZ = 521288629;
uint32_t FastRand(void);
