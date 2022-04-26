#include <iostream>
#include <vector>

#include "Engine.h"

#include "Elements/Element.h"

#include "../Helpers.h"


bool Grid::initialize(Vector2<int> size_)
{
	size.x = size_.x;
	size.y = size_.y;

	grid.resize(size.x * size.y * sizeof(Cell));

	return true;
}


bool Engine::initialize(Vector2<int> size_)
{
	initializeElements();

	if (!catchError(grid.initialize(size_), "Grid initialization failed. Aborting...\n"))
		return false;

	return true;
}


void Engine::update()
{
	int startX, endX, incrementX, startY, endY, incrementY;
	switch (balanceCounter % 2)
	{
	case 0:
		startX = 0;
		endX = grid.size.x - 1;
		incrementX = 1;
		startY = grid.size.y - 1;
		endY = 0;
		incrementY = -1;

		break;

	case 1:
		startX = grid.size.x - 1;
		endX = 0;
		incrementX = -1;
		startY = grid.size.y - 1;
		endY = 0;
		incrementY = -1;

		break;
	}
	balanceCounter++;

	// Adding the increment to the endpoint so that it's -1 when 0 is the end point and max + 1 when max is the endpoint
	for (int y = startY; y != endY + incrementY; y += incrementY)
	{
		for (int x = startX; x != endX + incrementX; x += incrementX)
		{
			Cell& cell = grid.grid[y * grid.size.x + x];

			if (cell.processed)
				continue;

			bool (*updateFunc)(int x, int y, Grid& grid) = elements[cell.elementId].update;
			if (updateFunc)
				updateFunc(x, y, grid);
		}
	}

	for (int y = 0; y < grid.size.y; y++)
		for (int x = 0; x < grid.size.x; x++)
			grid.grid[y * grid.size.x + x].processed = false;
}
