#include "../Elements.h"

#include "../../Engine.h"
#include "../../../Helpers.h"


static bool tryMoveTo(Cell& sourceCell, Cell& targetCell)
{
	Element& targetElement = elements[targetCell.elementId];

	if (targetElement.type != ElementType::solid
		&& targetElement.type != ElementType::liquid)
	{
		std::swap(sourceCell, targetCell);

		return true;
	}

	return false;
}


static bool tryMoveBottomLeft(int x, int y, Grid& grid)
{
	Cell& sourceCell = grid.grid[y * grid.size.x + x];

	if (x >= 1
		&& tryMoveTo(sourceCell, grid.grid[(y + 1) * grid.size.x + x - 1]))
	{
		return true;
	}

	return false;
}


static bool tryMoveBottomRight(int x, int y, Grid& grid)
{
	Cell& sourceCell = grid.grid[y * grid.size.x + x];

	if (x <= grid.size.x - 2
		&& tryMoveTo(sourceCell, grid.grid[(y + 1) * grid.size.x + x + 1]))
	{
		return true;
	}

	return false;
}


static bool tryMoveLeft(int x, int y, Grid& grid)
{
	Cell& sourceCell = grid.grid[y * grid.size.x + x];

	if (x >= 1
		&& tryMoveTo(sourceCell, grid.grid[y * grid.size.x + x - 1]))
	{
		return true;
	}

	return false;
}


static bool tryMoveRight(int x, int y, Grid& grid)
{
	Cell& sourceCell = grid.grid[y * grid.size.x + x];

	if (x <= grid.size.x - 2
		&& tryMoveTo(sourceCell, grid.grid[y * grid.size.x + x + 1]))
	{
		return true;
	}

	return false;
}


bool update_Liquid(int x, int y, Grid& grid)
{
	Cell& sourceCell = grid.grid[y * grid.size.x + x];
	sourceCell.processed = true;

	unsigned long random = fastRand();

	if (y < grid.size.y - 1)
	{
		if (tryMoveTo(sourceCell, grid.grid[(y + 1) * grid.size.x + x]))
		{
			return true;
		}

		switch (random % 2)
		{
		case 0:
			if (tryMoveBottomLeft(x, y , grid)
				|| tryMoveBottomRight(x, y, grid))
				return true;

			break;

		case 1:
			if (tryMoveBottomRight(x, y, grid)
				|| tryMoveBottomLeft(x, y, grid))
				return true;

			break;
		}
	}

	switch (random % 2)
	{
	case 0:
		if (tryMoveRight(x, y, grid)
			|| tryMoveLeft(x, y, grid))
			return true;

		break;

	case 1:
		if (tryMoveLeft(x, y, grid)
			|| tryMoveRight(x, y, grid))
			return true;

		break;
	}

	return false;
}
