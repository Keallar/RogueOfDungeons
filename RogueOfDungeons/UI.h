#pragma once
#include "SDL.h"

class UI {
	SDL_Renderer* ren;
	SDL_Texture* Font1;
	SDL_Texture* Font2;
public:
	UI(SDL_Renderer* renderer);
	void start();
};