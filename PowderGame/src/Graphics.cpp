#include <iostream>
#include <string>

#include <SDL.h>

#include "Graphics.h"
#include "Helpers.h"
#include "Settings.h"

#include "Engine/Engine.h"
#include "Engine/Elements/Elements.h"


SDL_Window* Graphics::createCenteredWindow(int width, int height, const char* title)
{
	// Get current device's Display Mode to calculate window position
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);

	int x = DM.w / 2 - width / 2;
	int y = DM.h / 2 - height / 2;

	SDL_Window* window = SDL_CreateWindow(title, x, y, width, height,
		SDL_WINDOW_ALLOW_HIGHDPI);

	catch_error(window, "Failed to create Window\n");

	return window;
}


// Create an SDL Texture to use as a "back buffer"
SDL_Texture* Graphics::createBackBufferTexture(SDL_Renderer* renderer)
{
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, windowSize.x, windowSize.y);

	catch_error(texture, "Failed to create Back Buffer Texture\n");

	return texture;
}


void Graphics::shutdown()
{
	if (texture)
	{
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}

	if (renderer)
	{
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
	}

	if (window)
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}
}


bool Graphics::initialize()
{
	SDL_Init(SDL_INIT_VIDEO);

	window = createCenteredWindow(windowSize.x, windowSize.y, windowTitle);

	if (!catch_error(window, "No Window. Aborting..."))
	{
		shutdown();

		return false;
	}

	//pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED + SDL_RENDERER_PRESENTVSYNC);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if (!catch_error(renderer, "No Renderer. Aborting..."))
	{
		shutdown();

		return false;
	}

	texture = createBackBufferTexture(renderer);

	if (!catch_error(texture, "No back buffer Texture. Aborting..."))
	{
		shutdown();

		return false;
	}

	return true;
}


void Graphics::render(SDL_Texture* texture, Grid& grid)
{
	// The Back Buffer texture may be stored with an extra bit of width (pitch) on the video card in order to properly
	// align it in VRAM should the width not lie on the correct memory boundary (usually four bytes).
	int32_t pitch = 0;

	// This will hold a pointer to the memory position in VRAM where our Back Buffer texture lies
	uint32_t* pixelBuffer = nullptr;

	SDL_LockTexture(texture, NULL, (void**)&pixelBuffer, &pitch);

	// The pitch of the Back Buffer texture in VRAM must be divided by four bytes
	// as it will always be a multiple of four
	pitch /= sizeof(uint32_t);

	int yPx = 0;
	for (int yU = 0; yU < grid.size.y; yU++)
		for (int i = 0; i < pxPerUnit; i++, yPx++)
		{
			int xPx = 0;
			for (int xU = 0; xU < grid.size.x; xU++)
				for (int j = 0; j < pxPerUnit; j++, xPx++)
				{
					int pixelPos = yPx * windowSize.x + xPx;
					int cellPos = yU * grid.size.x + xU;

					Cell& cell = grid.grid[cellPos];
					Element& element = elements[cell.elementId];

					// treating the 4 bytes as an unsigned int allows for fast conversion
					pixelBuffer[pixelPos] = *((uint32_t*)element.color);
				}
		}

	SDL_UnlockTexture(texture);

	SDL_RenderCopy(renderer, texture, NULL, NULL);

	SDL_RenderPresent(renderer);
}
