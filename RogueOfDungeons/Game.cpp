#include "Game.h"
using namespace std;

int Game::quit() {
				SDL_DestroyWindow(win);
				SDL_Quit();
			return 0;
}
