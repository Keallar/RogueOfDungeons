#pragma once
#include "SDL.h"

class UIMenu 
{
private:
	SDL_Renderer* ren;
	SDL_Texture* Font1;
	SDL_Texture* Font2;
public:
	UIMenu(SDL_Renderer* renderer);
	void start();
};

class UILevel
{
private:
	SDL_Renderer* ren;
	SDL_Texture* infoBLock;
	SDL_Texture* inventoryBlock;
public:
	UILevel(SDL_Renderer* renderer);
	void start();
};