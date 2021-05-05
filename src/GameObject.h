#pragma once
#include <SDL.h>
#include "Managers.h"

class GameObject
{
protected:
	SDL_Texture* objTexture;
	SDL_Renderer* ren;
public:
	SDL_Rect GetRect();
	SDL_Rect Rect;
	GameObject(); //конструктор по умлочанию
	GameObject(const char* texturesheet, SDL_Renderer* renderer, int x, int y, int w, int h);;
	GameObject(const char* texturesheet, SDL_Renderer* renderer);
	virtual ~GameObject();
	virtual void Update();
	virtual void Render();
	virtual void clean();
};

