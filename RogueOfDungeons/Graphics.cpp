#include <SDL.h>
#include <SDL_Image.h>
#include "Graphics.h"
#include <iostream>

const int WIDTH = 1280;
const int HEIGHT = 720;



Graphics::Graphics() {
	SDL_Init(SDL_INIT_EVERYTHING);
	_window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	_renderer = SDL_CreateRenderer(_window, -1, 0);
}

void renderTexture(SDL_Texture *tex, SDL_Renderer *ren, int x, int y, int w, int h)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}

void Graphics::SimpleWindow() {
	_backgroundMenu = IMG_LoadTexture(_renderer, "images/BackgroundMenu.png");
	renderTexture(_backgroundMenu,_renderer, 0, 0, 1280, 720);
	SDL_RenderPresent(_renderer);
	SDL_RenderClear(_renderer);
	SDL_Delay(3000);
}
void Graphics::Destroy() {
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
}