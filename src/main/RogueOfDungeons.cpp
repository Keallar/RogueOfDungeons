#include "Game.h"
#include <SDL.h>
#include <iostream>
#define TSCREEN_WEIGHT 960
#define TSCREEN_HEIGHT 640
#define SCREEN_HEGHT 1280
#define SCREEN_WEIGHT 720

Game* game = nullptr;
int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;
	game = new Game();
	game->init("ROD", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false);
	while (game->running()) 
	{
		frameStart = SDL_GetTicks();
		game->handleEvents();		
		game->update();
		game->render();
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) 
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	game->clean();
	return 0;
};
