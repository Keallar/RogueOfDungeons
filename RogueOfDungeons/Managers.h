#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class textureManager
{
public:
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);
};

class RenderManager 
{
public:
	static void CopyToRender(SDL_Texture* texture, SDL_Renderer* ren, int x, int y, int w, int h, int dx, int dy, int dw, int dh);
	static void CopyToRender(SDL_Texture* texture, SDL_Renderer* ren, int x, int y, int w, int h);
	static void CopyToRender(SDL_Texture* texture, SDL_Renderer* ren);
	static void SetTile(int x, int y, int tile, SDL_Renderer* renderer, SDL_Texture* tiles);
};

class InputManager
{
private:
	static SDL_Rect player;
	

public:
	static bool MouseInArea(int x, int y, int w, int h, int MouseX, int MouseY);	
};

class FontManager 
{
public:
	static SDL_Texture* renderText(const char* text, const char* fontFile, SDL_Color color, int fontSize, SDL_Renderer* renderer);
};