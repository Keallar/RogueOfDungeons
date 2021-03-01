#include "Graphics.h"
#include <SDL.h>

Graphics::Graphics() {
	SDL_Init(SDL_INIT_EVERYTHING);
	_window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1272, 720, SDL_WINDOW_SHOWN);
	_renderer = SDL_CreateRenderer(_window, -1, 0);
}

void Graphics::SimpleWindow() {
	SDL_SetRenderDrawColor(_renderer, 117, 187, 253, 255);
	SDL_RenderClear(_renderer);
	SDL_RenderPresent(_renderer);
	SDL_Delay(3000);
}
void Graphics::Destroy() {
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
}