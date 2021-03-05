#pragma once
#include "Game.h"
class GameObject
{
public:
	GameObject(); //конструктор по умлочанию
	GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y);
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

