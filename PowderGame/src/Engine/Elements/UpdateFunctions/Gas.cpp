#include "..//Element.h"

#include "../../Engine.h"


static bool tryMoveTo(Cell& sourceCell, Cell& targetCell)
{
	Element& targetElement = elements[targetCell.elementId];

	if (targetElement.type == ElementType::null)
	{
		std::swap(sourceCell, targetCell);

		return true;
	}

	return false;
}


bool update_Gas(int x, int y, Grid& grid)
{
	Cell& sourceCell = grid.grid[y * grid.size.x + x];
	sourceCell.processed = true;

	unsigned long random = fastRand();

	switch (random % 10)
	{
	case 0:
		if (y >= 1
			&& tryMoveTo(sourceCell, grid.grid[(y - 1) * grid.size.x + x]))
			return true;

		break;

	case 1:
		if (y >= 1
			&& x >= 1
			&& tryMoveTo(sourceCell, grid.grid[(y - 1) * grid.size.x + x - 1]))
			return true;

		break;

	case 2:
		if (y >= 1
			&& x <= grid.size.x - 2
			&& tryMoveTo(sourceCell, grid.grid[(y - 1) * grid.size.x + x + 1]))
			return true;

		break;

	// Move somewhere down
	case 3:
		if (y > grid.size.y - 2)
			break;

		switch (random % 3)
		{
		case 0:
			if (tryMoveTo(sourceCell, grid.grid[(y + 1) * grid.size.x + x]))
				return true;

			break;

		case 1:
			if (x >= 1
				&& tryMoveTo(sourceCell, grid.grid[(y + 1) * grid.size.x + x - 1]))
				return true;

			break;

		case 2:
			if (x <= grid.size.x - 2
				&& tryMoveTo(sourceCell, grid.grid[(y + 1) * grid.size.x + x + 1]))
				return true;

			break;
		}

		break;

	// Move sideways
	default:
		switch (random % 2)
		{
		case 0:
			if (x >= 1
				&& tryMoveTo(sourceCell, grid.grid[y * grid.size.x + x - 1]))
				return true;

			break;

		case 1:
			if (x <= grid.size.x - 2
				&& tryMoveTo(sourceCell, grid.grid[y * grid.size.x + x + 1]))
				return true;

			break;
		}
	
		break;
	}

	return false;
}
