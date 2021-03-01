#pragma once
#include <string>
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>

class Graphics {
private:
	SDL_Texture* _texture;
	SDL_Renderer* _renderer;
	SDL_Window* _window;
	SDL_Event event;
public:
	Graphics(SDL_Window* window, SDL_Renderer* renderer);
	~Graphics() {};
	void OutputTexture(int x,int y,int w,int h, std::string file);
	void Destroy();
};