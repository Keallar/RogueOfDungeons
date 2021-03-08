#pragma once
#include "Managers.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>

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

void RenderManager::CopyToRender(SDL_Texture* texture, SDL_Renderer* ren, int x, int y, int w, int h, int dx, int dy, int dw, int dh) 
{
	SDL_Rect COORD; SDL_Rect dCOORD;
	COORD.x = x; COORD.y = y; COORD.w = w; COORD.h = h;
	dCOORD.x = dx; dCOORD.y = dy; dCOORD.w = dw; dCOORD.h = dh;
	SDL_RenderCopy(ren, texture, &dCOORD, &COORD);
}
void RenderManager::CopyToRender(SDL_Texture* texture, SDL_Renderer* ren, int x, int y, int w, int h) 
{	
	SDL_Rect COORD; SDL_Rect dCOORD;
	COORD.x = x; COORD.y = y; COORD.w = w; COORD.h = h;
	SDL_RenderCopy(ren, texture, NULL, &COORD);
}	
void RenderManager::CopyToRender(SDL_Texture* texture, SDL_Renderer* ren) {
	SDL_RenderCopy(ren, texture, NULL, NULL);
}

void RenderManager::SetTile(int x, int y, int tile, SDL_Renderer* renderer, SDL_Texture* TileTexture) {
	switch (tile)
	{
	case 0:
		RenderManager::CopyToRender(TileTexture, renderer, x, y, 32, 32, 0, 0, 32, 32);
		break;
	case 1:
		RenderManager::CopyToRender(TileTexture, renderer, x, y, 32, 32, 0, 32, 32, 32);
		break;
	case 2:
		RenderManager::CopyToRender(TileTexture, renderer, x, y, 32, 32, 0, 64, 32, 32);
		break;
	case 3:
		RenderManager::CopyToRender(TileTexture, renderer, x, y, 32, 32, 0, 96, 32, 32);
		break;
	case 4:
		RenderManager::CopyToRender(TileTexture, renderer, x, y, 32, 32, 32, 0, 32, 32);
		break;
	case 5:
		RenderManager::CopyToRender(TileTexture, renderer, x, y, 32, 32, 32, 32, 32, 32);
		break;
	case 6:
		RenderManager::CopyToRender(TileTexture, renderer, x, y, 32, 32, 32, 64, 32, 32);
		break;
	case 7:
		RenderManager::CopyToRender(TileTexture, renderer, x, y, 32, 32, 32, 96, 32, 32);
		break;
	case 8:
		RenderManager::CopyToRender(TileTexture, renderer, x, y, 32, 32, 64, 0, 32, 32);
		break;
	case 9:
		RenderManager::CopyToRender(TileTexture, renderer, x, y, 32, 32, 64, 32, 32, 32);
		break;
	case 10:
		RenderManager::CopyToRender(TileTexture, renderer, x, y, 32, 32, 64, 64, 32, 32);
		break;
	case 11:
		RenderManager::CopyToRender(TileTexture, renderer, x, y, 32, 32, 64, 96, 32, 32);
		break;
	case 12:
		RenderManager::CopyToRender(TileTexture, renderer, x, y, 32, 32, 96, 0, 32, 32);
		break;
	case 13:
		RenderManager::CopyToRender(TileTexture, renderer, x, y, 32, 32, 96, 32, 32, 32);
		break;
	case 14:
		RenderManager::CopyToRender(TileTexture, renderer, x, y, 32, 32, 96, 64, 32, 32);
		break;
	case 15:
		RenderManager::CopyToRender(TileTexture, renderer, x, y, 32, 32, 96, 96, 32, 32);
		break;
	default:
		break;
	}
}

SDL_Texture* FontManager::renderText(const char* text, const char* fontFile, SDL_Color color, int fontSize, SDL_Renderer* renderer)
{
	TTF_Font* font = TTF_OpenFont(fontFile, fontSize);
	if (font == nullptr)
	{
		std::cout << "Error TTF_OpenFont";
		return nullptr;
	}

	SDL_Surface* surf = TTF_RenderText_Blended(font, text, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return texture;
}