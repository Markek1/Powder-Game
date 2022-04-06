#pragma once

#include <iostream>
#include <vector>

#include "../Helpers.h"


struct Cell
{
public:
	uint8_t elementId{0};
	bool processed{false};
};


class Grid
{
public:
	Vector2<int> size{};
	std::vector<Cell> grid;

	bool initialize(Vector2<int> size_);
};


class Engine
{
public:
	Grid grid;

	// exists to be incremented each update and used to make particles prefer left or rightzz
	int balanceCounter{ 0 };

	bool initialize(Vector2<int> size_);
	void update();
};
