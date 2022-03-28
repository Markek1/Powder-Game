#pragma once

#include <iostream>
#include <vector>

#include "Particle.h"

#include "../Helpers.h"


struct Cell
{
public:
	uint8_t id;
	bool processed;
};
static Cell emptyCell = { 0, false};


class Grid
{
public:
	Vector2<uint32_t> size = {};
	std::vector<Cell> grid;

	bool Initialize(Vector2<uint32_t> size_);
};


class Engine
{
public:
	Grid grid;

	// exists to be incremented each update and used to make particles prefer left or right
	uint32_t balanceCounter = 0;

	bool Initialize(Vector2<uint32_t> size_);
	void Update();
};
