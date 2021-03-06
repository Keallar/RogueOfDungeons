#pragma once
#include "textureManager.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>

SDL_Rect RenderManager::COORD;
SDL_Rect RenderManager::dCOORD;
SDL_Rect InputManager::player;
const Uint8* key = SDL_GetKeyboardState(0);


SDL_Texture* textureManager::LoadTexture(const char* texName, SDL_Renderer* ren) 
{
	SDL_Texture* tex = IMG_LoadTexture(ren, texName);
	return tex;
}

bool InputManager::MouseInArea(int x, int y, int w, int h, int MouseX, int MouseY) 
{
	if ((MouseX >= x) && (MouseX <= x + w) && (MouseY >= y) && (MouseY <= y + h)) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

int InputManager::pressW(int y)
{
	y = y - 32;
	return y;
}

int InputManager::pressA(int x)
{
	x = x - 32;
	return x;
}

int InputManager::pressS(int y)
{
	y = y + 32;
	return y;
}

int InputManager::pressD(int x)
{
	x = x + 32;
	return x;
}

void RenderManager::CopyToRender(SDL_Texture* texture, SDL_Renderer* ren, int x, int y, int w, int h, int dx, int dy, int dw, int dh) 
{
	SDL_Rect src = {0, 0, dw, dh};
	SDL_Rect dest = { x, y, w, h };
	COORD.x = x; COORD.y = y; COORD.w = w; COORD.h = h;
	dCOORD.x = dx; dCOORD.y = dy; dCOORD.w = dw; dCOORD.h = dh;
	SDL_RenderCopy(ren, texture, &src, &dest);
	std::cout << x<< ","<< y << std::endl;
}
void RenderManager::CopyToRender(SDL_Texture* texture, SDL_Renderer* ren, int x, int y, int w, int h) 
{
	COORD.x = x; COORD.y = y; COORD.w = w; COORD.h = h;
	SDL_RenderCopy(ren, texture, NULL, &COORD);
}	
void RenderManager::CopyToRender(SDL_Texture* texture, SDL_Renderer* ren) {
	SDL_RenderCopy(ren, texture, NULL, NULL);
}

SDL_Surface* FontManager::surf;
SDL_Color FontManager::fontColor;
TTF_Font* FontManager::font;
SDL_Texture* FontManager::fontTexture;

SDL_Texture* FontManager::renderText(const char* text, const char* fontFile, Uint8 rgb_r, Uint8 rgb_b, Uint8 rgb_g, Uint8 rgb_a, int fontSize, SDL_Renderer* renderer) {
	fontColor = { rgb_r, rgb_b, rgb_g, rgb_a };
	font = TTF_OpenFont("fonts/manaspc.ttf", fontSize);
	surf = TTF_RenderText_Blended(font, text, fontColor);
	fontTexture = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	return fontTexture;
}