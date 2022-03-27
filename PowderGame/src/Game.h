#pragma once

#include "Graphics.h"
#include "Helpers.h"

#include "Engine/Engine.h"


class FPSCounter
{
private:
	uint64_t totalTicks;
	uint64_t totalFramesRendered;
	uint64_t currentTick;
	uint64_t lastTick;

	bool firstFrame;

public:
	bool Initialize();
	void Update();
	void PrintStats();
};


class Game
{
private:
	Engine engine;
	Graphics graphics;
	FPSCounter fpsCounter;
	bool running = false;
	bool paused = false;

	uint8_t currentSelectedId = 2;
	bool mouseLeftDown = false;
	bool mouseRightDown = false;
	Vector2<int> mousePos;
	uint32_t cursorSize = 35;

	void fillCursorArea(bool clear);

	void HandleEvents(SDL_Event& event);
	void GameLoop();

public:
	bool Initialize();
	void Run();
};
