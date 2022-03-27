#include <iostream>

#include "MovementSystem.h"
#include "Particle.h"


bool MovementSystem::SolidMovableMovement::TryMoveDown(uint32_t x, uint32_t y, Grid& grid)
{
	if (grid.grid[(y + 1) * grid.size.x + x].type != ParticleType::SolidMovable &&
		grid.grid[(y + 1) * grid.size.x + x].type != ParticleType::SolidImmovable)
	{
		grid.grid[(y + 1) * grid.size.x + x] = grid.grid[y * grid.size.x + x];
		grid.grid[y * grid.size.x + x] = emptyCell;
		return true;
	}
	return false;
}


bool MovementSystem::SolidMovableMovement::TryMoveDownLeft(uint32_t x, uint32_t y, Grid& grid)
{
	if (grid.grid[(y + 1) * grid.size.x + x - 1].type != ParticleType::SolidMovable &&
		grid.grid[(y + 1) * grid.size.x + x - 1].type != ParticleType::SolidImmovable &&
		x > 0)
	{
		grid.grid[(y + 1) * grid.size.x + x - 1] = grid.grid[y * grid.size.x + x];
		grid.grid[y * grid.size.x + x] = emptyCell;
		return true;
	}
	return false;
}


bool MovementSystem::SolidMovableMovement::TryMoveDownRight(uint32_t x, uint32_t y, Grid& grid)
{
	if (grid.grid[(y + 1) * grid.size.x + x + 1].type != ParticleType::SolidMovable &&
		grid.grid[(y + 1) * grid.size.x + x + 1].type != ParticleType::SolidImmovable &&
		x + 1 < grid.size.x)
	{
		grid.grid[(y + 1) * grid.size.x + x + 1] = grid.grid[y * grid.size.x + x];
		grid.grid[y * grid.size.x + x] = emptyCell;
		return true;
	}
	return false;
}
