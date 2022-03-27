#pragma once

#include <iostream>
#include <string>

#include <SDL.h>

#include "Engine/Engine.h"


class Graphics
{
private:
	SDL_Window* CreateCenteredWindow(uint32_t width, uint32_t height, std::string title);
	SDL_Texture* CreateBackBufferTexture(SDL_Renderer* pRenderer);

public:
	SDL_Window* pWindow = nullptr;
	SDL_Renderer* pRenderer = nullptr;
	SDL_Texture* pTexture = nullptr;

	bool Initialize();

	void Render(SDL_Texture* pTexture, Grid* grid);
	void Shutdown();
};
