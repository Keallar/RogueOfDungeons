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

class FontManager {
private:
	
public:
	static SDL_Texture* renderText(const char* text, const char * fontFile, Uint8 rgb_r, Uint8 rbg_b, Uint8 rgb_g, Uint8 rgb_a, int fontSize, SDL_Renderer* renderer);
};

class FlagManager {
public:
	static SDL_Texture* renderText(const char* text, const char* fontFile, Uint8 rgb_r, Uint8 rbg_b, Uint8 rgb_g, Uint8 rgb_a, int fontSize, SDL_Renderer* renderer);
};

class FlagManager {
public:
	static int 	flagPlayer;
	static int flagEnemy;
};