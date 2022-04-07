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
	bool initialize();
	void update();
	void printStats();
};


class Game
{
private:
	Engine engine;
	Graphics graphics;
	FPSCounter fpsCounter;
	bool running = false;
	bool paused = false;

	uint8_t currentSelectedId{ 9 };
	bool mouseLeftDown = false;
	bool mouseRightDown = false;
	Vector2<int> mousePos;
	int cursorSize{ 10 };

	void fillCursorArea(bool clear);

	void handleEvents(SDL_Event& event);
	void gameLoop();

public:
	bool initialize();
	void run();
};
