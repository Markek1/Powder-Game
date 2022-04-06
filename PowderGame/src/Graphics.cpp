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

	SDL_Window* pWindow = SDL_CreateWindow(title, x, y, width, height,
		SDL_WINDOW_ALLOW_HIGHDPI);

	catch_error(pWindow, "Failed to create Window\n");

	return pWindow;
}


// Create an SDL Texture to use as a "back buffer"
SDL_Texture* Graphics::createBackBufferTexture(SDL_Renderer* pRenderer)
{
	SDL_Texture* pTexture = SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, g_windowSize.x, g_windowSize.y);

	catch_error(pTexture, "Failed to create Back Buffer Texture\n");

	return pTexture;
}


void Graphics::shutdown()
{
	if (pTexture)
	{
		SDL_DestroyTexture(pTexture);
		pTexture = nullptr;
	}

	if (pRenderer)
	{
		SDL_DestroyRenderer(pRenderer);
		pRenderer = nullptr;
	}

	if (pWindow)
	{
		SDL_DestroyWindow(pWindow);
		pWindow = nullptr;
	}
}


bool Graphics::initialize()
{
	SDL_Init(SDL_INIT_VIDEO);

	pWindow = createCenteredWindow(g_windowSize.x, g_windowSize.y, g_windowTitle);

	if (!catch_error(pWindow, "No Window. Aborting..."))
	{
		shutdown();

		return false;
	}

	//pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED + SDL_RENDERER_PRESENTVSYNC);
	pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);

	if (!catch_error(pRenderer, "No Renderer. Aborting..."))
	{
		shutdown();

		return false;
	}

	pTexture = createBackBufferTexture(pRenderer);

	if (!catch_error(pTexture, "No back buffer Texture. Aborting..."))
	{
		shutdown();

		return false;
	}

	return true;
}


void Graphics::render(SDL_Texture* pTexture, Grid& grid)
{
	// The Back Buffer texture may be stored with an extra bit of width (pitch) on the video card in order to properly
	// align it in VRAM should the width not lie on the correct memory boundary (usually four bytes).
	int32_t pitch = 0;

	// This will hold a pointer to the memory position in VRAM where our Back Buffer texture lies
	uint32_t* pPixelBuffer = nullptr;

	SDL_LockTexture(pTexture, NULL, (void**)&pPixelBuffer, &pitch);

	// The pitch of the Back Buffer texture in VRAM must be divided by four bytes
	// as it will always be a multiple of four
	pitch /= sizeof(uint32_t);

	int yPx = 0;
	for (int yU = 0; yU < grid.size.y; yU++)
		for (int i = 0; i < g_pxPerUnit; i++, yPx++)
		{
			int xPx = 0;
			for (int xU = 0; xU < grid.size.x; xU++)
				for (int j = 0; j < g_pxPerUnit; j++, xPx++)
				{
					int pixelPos = yPx * g_windowSize.x + xPx;
					int cellPos = yU * grid.size.x + xU;

					Cell& cell = grid.grid[cellPos];
					Element& element = elements[cell.m_elementId];

					// treating the 4 bytes as an unsigned int allows for fast conversion
					pPixelBuffer[pixelPos] = *((uint32_t*)element.m_color);
				}
		}

	SDL_UnlockTexture(pTexture);

	SDL_RenderCopy(pRenderer, pTexture, NULL, NULL);

	SDL_RenderPresent(pRenderer);
}
