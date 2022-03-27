#include <iostream>
#include <vector>

#include "Engine.h"
#include "MovementSystem.h"

#include "../Helpers.h"


bool Grid::Initialize(Vector2<uint32_t> size_)
{
	size.x = size_.x;
	size.y = size_.y;

	grid.resize(size.x * size.y * sizeof(Cell));

	return true;
}


bool Engine::Initialize(Vector2<uint32_t> size_)
{
	if (error(!grid.Initialize(size_), "Grid initialization failed. Aborting...\n"))
		return false;

	return true;
}


void Engine::Update()
{
	int32_t startX, endX, incrementX, startY, endY, incrementY;
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
	for (int32_t y = startY; y != endY + incrementY; y += incrementY)
	{
		for (int32_t x = startX; x != endX + incrementX; x += incrementX)
		{
			switch (grid.grid[y * grid.size.x + x].type)
			{
			case SolidMovable:
				if (grid.grid[y * grid.size.x + x].processed || y == grid.size.y - 1)
					break;

				grid.grid[y * grid.size.x + x].processed = true;

				if (MovementSystem::SolidMovableMovement::TryMoveDown(x, y, grid))
					break;

				if (balanceCounter % 2 == 0)
					MovementSystem::SolidMovableMovement::TryMoveDownLeft(x, y, grid) ||
					MovementSystem::SolidMovableMovement::TryMoveDownRight(x, y, grid);
				else
					MovementSystem::SolidMovableMovement::TryMoveDownRight(x, y, grid) ||
					MovementSystem::SolidMovableMovement::TryMoveDownLeft(x, y, grid);

				break;
			}
		}
	}

	for (uint32_t y = 0; y < grid.size.y; y++)
		for (uint32_t x = 0; x < grid.size.x; x++)
			grid.grid[y * grid.size.x + x].processed = false;
}
