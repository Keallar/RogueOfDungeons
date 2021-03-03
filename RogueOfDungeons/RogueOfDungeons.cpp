#include "Game.h"
#include "SDL.h"
#include <iostream>
#include "Graphics.h"


Game* game = nullptr;
int main(int argc, char* argv[])
{
	game = new Game();
	game->init("ROD", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, false);
	SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
	while (game->running()) 
	{
		game->handleEvents();
		game->update();
		game->render();
	}
	game->clean();
	return 0;
};