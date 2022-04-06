#pragma once

#include <iostream>

#include <SDL.h>

#include "Engine/Engine.h"


class Graphics
{
private:
	SDL_Window* createCenteredWindow(int width, int height, const char* title);
	SDL_Texture* createBackBufferTexture(SDL_Renderer* renderer);

public:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;

	bool initialize();

	void render(SDL_Texture* texture, Grid& grid);
	void shutdown();
};
