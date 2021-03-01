#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Graphics.h"

using namespace std;

int main(int argc, char* argv[])
{
	Graphics Test;
	Test.SimpleWindow();
	return 0;
	SDL_Event e;
	while (true) {
		if (e.type == SDL_QUIT) { break; }
		if (e.type == SDL_KEYDOWN) { break; }
		if (e.type == SDL_MOUSEBUTTONDOWN) { break; }
		SDL_Delay(10);
	}
	Test.Destroy();
	SDL_Quit();
	return 0;
}