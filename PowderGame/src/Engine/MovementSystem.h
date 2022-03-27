#pragma once

#include <iostream>

#include "Engine.h"


class MovementSystem
{
public:
	class SolidMovableMovement
	{
	public:
		static bool TryMoveDown(uint32_t x, uint32_t y, Grid& grid);
		static bool TryMoveDownLeft(uint32_t x, uint32_t y, Grid& grid);
		static bool TryMoveDownRight(uint32_t x, uint32_t y, Grid& grid);
	};
};
