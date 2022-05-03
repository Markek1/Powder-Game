#include "../Element.h"

#include "../../Engine.h"


bool update_Fire(int x, int y, Grid& grid)
{
	Cell& sourceCell = grid.grid[y * grid.size.x + x];
	sourceCell.processed = true;

	for (int i = std::max(0, y - 1); i <= std::min(grid.size.y - 1, y + 1); ++i)
		for (int j = std::max(0, x - 1); j <= std::min(grid.size.x - 1, x + 1); ++j)
		{
			Cell& targetCell = grid.grid[i * grid.size.x + j];
			Element& targetElement = elements[targetCell.elementId];

			if (targetElement.flammability == 0)
				continue;

			if (fastRand() < std::numeric_limits<unsigned long>::max() * targetElement.flammability)
			{
				targetCell.elementId = ElementId::FIRE;
			}
		}

	return true;
}
