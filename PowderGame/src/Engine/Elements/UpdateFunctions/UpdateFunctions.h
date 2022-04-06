#pragma once

#include "../../Engine.h"


bool tryMoveTo_SolidMovable(Cell& sourceCell, Cell& targetCell);
bool update_SolidMovable(int x, int y, Grid& grid);