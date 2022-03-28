#include <iostream>

#include "MovementSystem.h"
#include "Particle.h"


bool MovementSystem::SolidMovableMovement::TryMoveDown(uint32_t x, uint32_t y, Grid& grid)
{
	uint32_t sourcePos = y * grid.size.x + x;
	uint32_t targetPos = (y + 1) * grid.size.x + x;

	uint8_t id = grid.grid[targetPos].id;

	if (particleArr[id].type != ParticleType::SolidMovable &&
		particleArr[id].type != ParticleType::SolidImmovable)
	{
		grid.grid[targetPos] = grid.grid[sourcePos];
		grid.grid[sourcePos] = emptyCell;
		return true;
	}
	return false;
}


bool MovementSystem::SolidMovableMovement::TryMoveDownLeft(uint32_t x, uint32_t y, Grid& grid)
{
	uint32_t sourcePos = y * grid.size.x + x;
	uint32_t targetPos = (y + 1) * grid.size.x + x - 1;

	uint8_t id = grid.grid[targetPos].id;

	if (particleArr[id].type != ParticleType::SolidMovable &&
		particleArr[id].type != ParticleType::SolidImmovable &&
		x > 0)
	{
		grid.grid[targetPos] = grid.grid[sourcePos];
		grid.grid[sourcePos] = emptyCell;
		return true;
	}
	return false;
}


bool MovementSystem::SolidMovableMovement::TryMoveDownRight(uint32_t x, uint32_t y, Grid& grid)
{
	uint32_t sourcePos = y * grid.size.x + x;
	uint32_t targetPos = (y + 1) * grid.size.x + x + 1;

	uint8_t id = grid.grid[targetPos].id;

	if (particleArr[id].type != ParticleType::SolidMovable &&
		particleArr[id].type != ParticleType::SolidImmovable &&
		x + 1 < grid.size.x)
	{
		grid.grid[targetPos] = grid.grid[sourcePos];
		grid.grid[sourcePos] = emptyCell;
		return true;
	}
	return false;
}
