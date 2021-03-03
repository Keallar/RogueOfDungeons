#include "Game.h"
#include <SDL.h>
#include <iostream>
#include "MainMenu.h"




Game* game = nullptr;
int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;
	int player = 0;
	game = new Game();
	game->init("ROD", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	while (game->running()) 
	{

		frameStart = SDL_GetTicks();
		game->handleEvents();
		
		game->render();
		game->update();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
	game->clean();
	return 0;
};