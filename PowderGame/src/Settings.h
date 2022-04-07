#pragma once

#include <iostream>

#include "Helpers.h"


static Vector2<int> windowSize = { 1200, 800 };
static int cellToPixelScaleFactor = 2; 

static Vector2<int> gridSize = { windowSize.x / cellToPixelScaleFactor, windowSize.y / cellToPixelScaleFactor};

static const char* windowTitle = "Powder Game";
