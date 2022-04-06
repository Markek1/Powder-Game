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


bool catch_error(bool result, std::string_view errorMessage);
