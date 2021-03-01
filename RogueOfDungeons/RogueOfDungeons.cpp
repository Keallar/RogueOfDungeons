#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Graphics.h"

using namespace std;

const int WIDTH = 1280;
const int HEIGHT = 720;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* _window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer* _renderer = SDL_CreateRenderer(_window, -1, 0);
	Graphics Test(_window, _renderer);
	Test.OutputTexture(0, 0, 1280, 720, "images/BackgroundMenu.png");
	Graphics Play(_window, _renderer);
	Play.OutputTexture((WIDTH/2-(354/2)), 400, 354, 108, "images/Play.png");
	SDL_RenderPresent(_renderer);
	SDL_RenderClear(_renderer);
	
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
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	Test.Destroy();
	Play.Destroy();
	SDL_Quit();
	return 0;
}