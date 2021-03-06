#include "textureManager.h"
#include "SDL.h"
#include "SDL_image.h"

SDL_Rect RenderManager::COORD;
SDL_Rect RenderManager::dCOORD;

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

bool InputManager::pressW()
{

}

bool InputManager::pressA()
{

}

bool InputManager::pressS()
{

}

bool InputManager::pressD()
{

}

void RenderManager::CopyToRender(SDL_Texture* texture, SDL_Renderer* ren, int x, int y, int w, int h, int dx, int dy, int dw, int dh) 
{
	COORD.x = x; COORD.y = y; COORD.w = w; COORD.h = h;
	dCOORD.x = dx; dCOORD.y = dy; dCOORD.w = dw; dCOORD.h = dh;
	SDL_RenderCopy(ren, texture, &dCOORD, &COORD);
}
void RenderManager::CopyToRender(SDL_Texture* texture, SDL_Renderer* ren, int x, int y, int w, int h) 
{
	COORD.x = x; COORD.y = y; COORD.w = w; COORD.h = h;
	SDL_RenderCopy(ren, texture, NULL, &COORD);
}	
void RenderManager::CopyToRender(SDL_Texture* texture, SDL_Renderer* ren) {
	SDL_RenderCopy(ren, texture, NULL, NULL);
}