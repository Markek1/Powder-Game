#include "../Elements.h"

#include "../../Engine.h"


bool tryMoveTo_Liquid(Cell& sourceCell, Cell& targetCell)
{
	Element& targetElement = elements[targetCell.elementId];

	if (targetElement.type != ElementType::solid)
	{
		std::swap(sourceCell, targetCell);

		return true;
	}

	return false;
}


bool update_Liquid(int x, int y, Grid& grid)
{
	if (y >= grid.size.y - 1)
		return false;

	Cell& sourceCell = grid.grid[y * grid.size.x + x];
	sourceCell.processed = true;

	if (tryMoveTo_Liquid(sourceCell, grid.grid[(y + 1) * grid.size.x + x]))
		return true;

	if (x >= 1)
	{
		if (tryMoveTo_Liquid(sourceCell, grid.grid[(y + 1) * grid.size.x + x - 1]))
			return true;
	}

	if (x <= grid.size.x - 2)
	{
		if (tryMoveTo_Liquid(sourceCell, grid.grid[(y + 1) * grid.size.x + x + 1]))
			return true;
	}

	return false;
}
