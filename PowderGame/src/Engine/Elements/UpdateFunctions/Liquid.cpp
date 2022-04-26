#include "../Element.h"

#include "../../Engine.h"
#include "../../../Helpers.h"


static bool tryMoveTo(Cell& sourceCell, Cell& targetCell)
{
	Element& sourceElement = elements[sourceCell.elementId];
	Element& targetElement = elements[targetCell.elementId];

	switch (sourceCell.elementId)
	{
	case ElementId::LAVA:
		if (targetCell.elementId == ElementId::WATR)
		{
			sourceCell.elementId = ElementId::STNE;
			targetCell.elementId = ElementId::STNE;
			return true;
		}

		break;

	case ElementId::WATR:
		if (targetCell.elementId == ElementId::LAVA)
		{
			sourceCell.elementId = ElementId::OBSD;
			targetCell.elementId = ElementId::OBSD;
			return true;
		}

		break;
	}

	if (targetElement.type == ElementType::liquid && sourceCell.elementId != targetCell.elementId)
	{
		if (fastRand() < sourceElement.spreadFactor * 1000000)
			std::swap(sourceCell, targetCell);
		return true;
	}

	if (targetElement.type != ElementType::solid
		&& targetElement.type != ElementType::liquid)
	{
		std::swap(sourceCell, targetCell);

		return true;
	}

	return false;
}


static bool tryMoveBottomLeft(int& x, int& y, Grid& grid)
{
	Cell& sourceCell = grid.grid[y * grid.size.x + x];

	if (x >= 1
		&& tryMoveTo(sourceCell, grid.grid[(y + 1) * grid.size.x + x - 1]))
	{
		++y, --x;
		return true;
	}


	return false;
}


static bool tryMoveBottomRight(int& x, int& y, Grid& grid)
{
	Cell& sourceCell = grid.grid[y * grid.size.x + x];

	if (x <= grid.size.x - 2
		&& tryMoveTo(sourceCell, grid.grid[(y + 1) * grid.size.x + x + 1]))
	{
		++y, ++x;
		return true;
	}


	return false;
}


static bool tryMoveLeft(int& x, int& y, Grid& grid)
{
	Cell& sourceCell = grid.grid[y * grid.size.x + x];

	if (x >= 1
		&& tryMoveTo(sourceCell, grid.grid[y * grid.size.x + x - 1]))
	{
		--x;
		return true;
	}


	return false;
}


static bool tryMoveRight(int& x, int& y, Grid& grid)
{
	Cell& sourceCell = grid.grid[y * grid.size.x + x];

	if (x <= grid.size.x - 2
		&& tryMoveTo(sourceCell, grid.grid[y * grid.size.x + x + 1]))
	{
		++x;
		return true;
	}


	return false;
}


bool update_Liquid(int x, int y, Grid& grid)
{
	Cell& sourceCell = grid.grid[y * grid.size.x + x];
	Element& element = elements[sourceCell.elementId];
	sourceCell.processed = true;

	unsigned long random = fastRand();

	for (int i{ 0 }; i < element.spreadFactor; ++i)
	{
		Cell& sourceCell = grid.grid[y * grid.size.x + x];
		if (y < grid.size.y - 1)
		{
			if (tryMoveTo(sourceCell, grid.grid[(y + 1) * grid.size.x + x]))
			{
				continue;
				++y;
			}

			switch (random % 2)
			{
			case 0:
				if (tryMoveBottomLeft(x, y, grid)
					|| tryMoveBottomRight(x, y, grid))
					continue;

				break;

			case 1:
				if (tryMoveBottomRight(x, y, grid)
					|| tryMoveBottomLeft(x, y, grid))
					continue;

				break;
			}
		}

		switch (random % 2)
		{
		case 0:
			if (tryMoveRight(x, y, grid)
				|| tryMoveLeft(x, y, grid))
				continue;

			break;

		case 1:
			if (tryMoveLeft(x, y, grid)
				|| tryMoveRight(x, y, grid))
				continue;

			break;
		}

		return false;
	}

	return false;
}