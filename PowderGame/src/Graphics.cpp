#include <iostream>
#include <string>

#include <SDL.h>

#include "Graphics.h"
#include "Helpers.h"
#include "Settings.h"


SDL_Window* Graphics::CreateCenteredWindow(uint32_t width, uint32_t height, std::string title)
{
	// Get current device's Display Mode to calculate window position
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);

	const int32_t x = DM.w / 2 - width / 2;
	const int32_t y = DM.h / 2 - height / 2;

	SDL_Window* pWindow = SDL_CreateWindow(g_windowTitle, x, y, width, height,
		SDL_WINDOW_ALLOW_HIGHDPI);

	error(!pWindow, "Failed to create Window\n");

	return pWindow;
}


// Create an SDL Texture to use as a "back buffer"
SDL_Texture* Graphics::CreateBackBufferTexture(SDL_Renderer* pRenderer)
{
	SDL_Texture* pTexture = SDL_CreateTexture(pRenderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, g_windowWidth, g_windowHeight);

	error(!pTexture, "Failed to create Back Buffer Texture\n");

	return pTexture;
}


void Graphics::Shutdown()
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


bool Graphics::Initialize()
{
	SDL_Init(SDL_INIT_VIDEO);

	pWindow = CreateCenteredWindow(g_windowWidth, g_windowHeight, g_windowTitle);

	if (error(!pWindow, "No Window. Aborting..."))
	{
		Shutdown();

		return false;
	}

	//pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED + SDL_RENDERER_PRESENTVSYNC);
	pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);

	if (error(!pRenderer, "No Renderer. Aborting..."))
	{
		Shutdown();

		return false;
	}

	pTexture = CreateBackBufferTexture(pRenderer);

	if (error(!pTexture, "No back buffer Texture. Aborting..."))
	{
		Shutdown();

		return false;
	}

	return true;
}


// the format here is BGRA
std::vector<Vector4<uint8_t>> IDToColor = {
	{0, 0, 0, 255},
	{0, 215, 255, 255},
	{255, 100, 100, 255},
	{80, 80, 255, 255},
	{120, 255, 60, 255},
	{0, 180, 255, 255}
};


void Graphics::Render(SDL_Texture* pTexture, Grid* grid)
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

	for (uint32_t y = 0; y < grid->size.y; y++)
		for (uint32_t x = 0; x < grid->size.x; x++)
			// treating the 4 bytes as an unsigned int allows for fast conversion
			pPixelBuffer[y * grid->size.x + x] = *((uint32_t*)IDToColor.data() + grid->grid[y * grid->size.x + x].id);

	SDL_UnlockTexture(pTexture);

	SDL_RenderCopy(pRenderer, pTexture, NULL, NULL);

	SDL_RenderPresent(pRenderer);
}
