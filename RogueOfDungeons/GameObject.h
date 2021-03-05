#pragma once
#include "Game.h"
#include "textureManager.h"

class GameObject
{
public:
	GameObject(); //конструктор по умлочанию
	GameObject(const char* texturesheet, SDL_Renderer* renderer);
	GameObject(const char* texturesheet, SDL_Renderer* renderer, int x, int y);
	~GameObject();
	void Update();
	void Render();
	void clean();

private:
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;
protected:
	int xpos;
	int ypos;
};

