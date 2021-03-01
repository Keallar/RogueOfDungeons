#include <SDL.h>
#include <SDL_Image.h>
#include "Graphics.h"
#include <iostream>
#include <string>

Graphics::Graphics(SDL_Window* window, SDL_Renderer* renderer) : _window(window), _renderer(renderer) {
	
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

void Graphics::OutputTexture(int x,int  y,int  w,int h, std::string file) {
	_texture = IMG_LoadTexture(_renderer, file.c_str());
	renderTexture(_texture,_renderer, x, y, w, h);
}

void Graphics::Destroy() {
	SDL_DestroyTexture(_texture);
}

void GetEvent() {

}