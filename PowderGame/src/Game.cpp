#include <iostream>

#include "Game.h"
#include "Helpers.h"
#include "Settings.h"

#include "Engine/Engine.h"


bool FPSCounter::initialize()
{
	m_totalTicks = 0;
	m_totalFramesRendered = 0;
	m_lastTick = 0;

	m_lastTick = SDL_GetPerformanceCounter();
	m_firstFrame = false;

	return true;
}


void FPSCounter::update()
{
	m_currentTick = SDL_GetPerformanceCounter();
	m_totalTicks += m_currentTick - m_lastTick;
	m_lastTick = m_currentTick;
	++m_totalFramesRendered;
}


void FPSCounter::printStats()
{
	std::cout << "Total Frames:    " << m_totalFramesRendered << "\n";
	std::cout << "Total Time:      " << static_cast<double>(m_totalTicks) / SDL_GetPerformanceFrequency() << "s\n";
	std::cout << "Average FPS:     " << static_cast<double>(m_totalFramesRendered) * SDL_GetPerformanceFrequency() / m_totalTicks << "\n";
}


bool Game::initialize()
{
	if (!catch_error(engine.initialize({ g_gridSize.x, g_gridSize.y}), "Engine initialization failed. Aborting...\n"))
		return false;

	if (!catch_error(graphics.initialize(), "Graphics initialization failed. Aborting...\n"))
	{
		graphics.shutdown();
		return false;
	}

	if (!catch_error(fpsCounter.initialize(), "FPS counter initialization failed. Aborting...\n"))
		return false;

	running = true;
	paused = false;

	return true;
}


void Game::fillCursorArea(bool clear)
{
	int startX = std::max(0, mousePos.x - cursorSize / 2);
	int endX = std::min(engine.grid.size.x - 1, mousePos.x + cursorSize / 2);

	int startY = std::max(0, mousePos.y - cursorSize / 2);
	int endY = std::min(engine.grid.size.y - 1, mousePos.y + cursorSize / 2);

	for (int y = startY; y <= endY; y++)
		for (int x = startX; x <= endX; x++)
		{
			Cell& cell = engine.grid.grid[y * engine.grid.size.x + x];

			// I'm pretty sure the compiler optimizes this, so it shouldn't 
			// actually be checking it each iteration in the release build
			// and the debug build is unusable anyway so it doesn't matter
			if (clear)
				cell = { 0, false };
			else
				if (cell.m_elementId == 0)
					cell = { currentSelectedId, false };
		}
}


void Game::handleEvents(SDL_Event& event)
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


void Game::gameLoop()
{
	while (running)
	{
		// Everything having to do with the UI, user input and the game itself
		SDL_GetMouseState(&mousePos.x, &mousePos.y);
		mousePos.x /= g_pxPerUnit;
		mousePos.y /= g_pxPerUnit;

		SDL_Event event;
		handleEvents(event);

		if (mouseLeftDown)
			fillCursorArea(false);
		else if (mouseRightDown)
			fillCursorArea(true);


		// Everything engine related
		if (!paused)
		{
			engine.update();

			//Test particles that spawn forever
			for (int y = 20; y < 25; y++)
				for (int x = 100; x < 105; x++)
					engine.grid.grid[y * engine.grid.size.x + x] = { 2, false };
			for (int y = 20; y < 25; y++)
				for (int x = 550; x < 555; x++)
					engine.grid.grid[y * engine.grid.size.x + x] = { 3, false };
			for (int y = 20; y < 25; y++)
				for (int x = 1000; x < 1005; x++)
					engine.grid.grid[y * engine.grid.size.x + x] = { 5, false };
		}


		// Everything graphics related
		graphics.render(graphics.pTexture, engine.grid);


		fpsCounter.update();
	}
}


void Game::run()
{
	catch_error(!initialize(), "Game initialization failed. Aborting...\n");

	gameLoop();

	graphics.shutdown();

	fpsCounter.printStats();
	std::cin.get();
}
