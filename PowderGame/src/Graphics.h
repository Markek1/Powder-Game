#pragma once

#include <iostream>

#include <SDL.h>

#include "Engine/Engine.h"


class Graphics
{
private:
	SDL_Window* createCenteredWindow(int width, int height, const char* title);
	SDL_Texture* createBackBufferTexture(SDL_Renderer* pRenderer);

public:
	SDL_Window* pWindow = nullptr;
	SDL_Renderer* pRenderer = nullptr;
	SDL_Texture* pTexture = nullptr;

	bool initialize();

	void render(SDL_Texture* pTexture, Grid& grid);
	void shutdown();
};
