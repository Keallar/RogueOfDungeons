
#include "Game.h"
#include <SDL.h>
#include <iostream>




Game* game = nullptr;
int main(int argc, char* argv[])
{
	game = new Game();
	game->init("ROD", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
	while (game->running()) 
	{
		game->handleEvents();
		
		game->render();
		game->update();
	}
	game->clean();
	return 0;
};