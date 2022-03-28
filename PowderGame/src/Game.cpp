#include <iostream>

#include "Game.h"
#include "Helpers.h"
#include "Settings.h"

#include "Engine/Engine.h"


bool FPSCounter::Initialize()
{
	totalTicks = 0;
	totalFramesRendered = 0;
	lastTick = 0;

	lastTick = SDL_GetPerformanceCounter();
	firstFrame = false;

	return true;
}


void FPSCounter::Update()
{
	currentTick = SDL_GetPerformanceCounter();
	totalTicks += currentTick - lastTick;
	lastTick = currentTick;
	++totalFramesRendered;
}


void FPSCounter::PrintStats()
{
	std::cout << "Total Frames:    " << totalFramesRendered << "\n";
	std::cout << "Total Time:      " << static_cast<double>(totalTicks) / SDL_GetPerformanceFrequency() << "s\n";
	std::cout << "Average FPS:     " << static_cast<double>(totalFramesRendered) * SDL_GetPerformanceFrequency() / totalTicks << "\n";
}


bool Game::Initialize()
{
	if (error(!engine.Initialize({ gridSize.x, gridSize.y}), "Engine initialization failed. Aborting...\n"))
		return false;

	if (error(!graphics.Initialize(), "Graphics initialization failed. Aborting...\n"))
	{
		graphics.Shutdown();
		return false;
	}

	if (error(!fpsCounter.Initialize(), "FPS counter initialization failed. Aborting...\n"))
		return false;

	running = true;
	paused = false;

	return true;
}


void Game::fillCursorArea(bool clear)
{
	uint32_t startX = std::max(0, (int32_t)mousePos.x - (int32_t)cursorSize / 2);
	uint32_t endX = std::min(engine.grid.size.x - 1, mousePos.x + cursorSize / 2);

	uint32_t startY = std::max(0, (int32_t)mousePos.y - (int32_t)cursorSize / 2);
	uint32_t endY = std::min(engine.grid.size.y - 1, mousePos.y + cursorSize / 2);

	for (uint32_t y = startY; y <= endY; y++)
		for (uint32_t x = startX; x <= endX; x++)
		{
			Cell* cell = &engine.grid.grid[y * engine.grid.size.x + x];

			// I'm pretty sure the compiler optimizes this, so it shouldn't 
			// actually be checking it each iteration in the release build
			// and the debug build is unusable anyway so it doesn't matter
			if (clear)
				*cell = { 0, ParticleType::NullParticle };
			else
				if (cell->id == 0)
					*cell = { currentSelectedId, false };
		}
}


void Game::HandleEvents(SDL_Event& event)
{
	while (SDL_PollEvent(&event))
		switch (event.type)
		{
		case SDL_QUIT:
			running = false;

			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_SPACE:
				paused = !paused;
			}

			break;

		case SDL_MOUSEBUTTONDOWN:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				mouseLeftDown = true;

				break;

			case SDL_BUTTON_RIGHT:
				mouseRightDown = true;

				break;
			}

			break;

		case SDL_MOUSEBUTTONUP:
			switch (event.button.button)
			{
			case SDL_BUTTON_LEFT:
				mouseLeftDown = false;

				break;

			case SDL_BUTTON_RIGHT:
				mouseRightDown = false;

				break;
			}

			break;
		}
}


void Game::GameLoop()
{
	while (running)
	{
		// Everything having to do with the UI, user input and the game itself
		SDL_GetMouseState(&mousePos.x, &mousePos.y);
		mousePos.x /= pxPerUnit;
		mousePos.y /= pxPerUnit;

		SDL_Event event;
		HandleEvents(event);

		if (mouseLeftDown)
			fillCursorArea(false);
		else if (mouseRightDown)
			fillCursorArea(true);


		// Everything engine related
		if (!paused)
		{
			engine.Update();

			// Test particles that spawn forever
			for (uint32_t y = 20; y < 25; y++)
				for (uint32_t x = 100; x < 105; x++)
					engine.grid.grid[y * engine.grid.size.x + x] = { 1, false };
			for (uint32_t y = 20; y < 25; y++)
				for (uint32_t x = 550; x < 555; x++)
					engine.grid.grid[y * engine.grid.size.x + x] = { 3, false };
			for (uint32_t y = 20; y < 25; y++)
				for (uint32_t x = 1000; x < 1005; x++)
					engine.grid.grid[y * engine.grid.size.x + x] = { 5, false };
		}


		// Everything graphics related
		graphics.Render(graphics.pTexture, &engine.grid);


		fpsCounter.Update();
	}
}


void Game::Run()
{
	error(!Initialize(), "Game initialization failed. Aborting...\n");

	GameLoop();

	graphics.Shutdown();

	fpsCounter.PrintStats();
	std::cin.get();
}
