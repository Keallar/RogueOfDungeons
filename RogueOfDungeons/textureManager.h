#pragma once
#include "Game.h"

class textureManager
{
public:
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);
};

class RenderManager 
{
private:
	static SDL_Rect COORD;
	static SDL_Rect dCOORD;
public:
	static void CopyToRender(SDL_Texture* texture, SDL_Renderer* ren, int x, int y, int w, int h, int dx, int dy, int dw, int dh);
	static void CopyToRender(SDL_Texture* texture, SDL_Renderer* ren, int x, int y, int w, int h);
	static void CopyToRender(SDL_Texture* texture, SDL_Renderer* ren);
};

class InputManager
{
private:
	SDL_Rect player;
public:
	static bool MouseInArea(int x, int y, int w, int h, int MouseX, int MouseY);
	static bool pressW();
	static bool pressA();
	static bool pressS();
	static bool pressD();
};
