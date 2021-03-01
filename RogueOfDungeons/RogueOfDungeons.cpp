#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Graphics.h"

using namespace std;

int main(int argc, char* argv[])
{
	Graphics Test;
	Test.SimpleWindow();
	SDL_Event e;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) { quit = true; }
			if (e.type == SDL_KEYDOWN) { quit = true; }
			if (e.type == SDL_MOUSEBUTTONDOWN) { quit = true; }
			SDL_Delay(10);
		}
	}
	Test.Destroy();
	SDL_Quit();
	return 0;
}