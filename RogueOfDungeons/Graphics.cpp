#include "Graphics.h"

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
	if (!_texture)
	{
		std::cout << IMG_GetError(); // Можно заменить на SDL_GetError()
	}
}

void Graphics::Destroy() {
	SDL_DestroyTexture(_texture);
}

void GetEvent() {

}