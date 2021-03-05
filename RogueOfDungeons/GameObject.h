#pragma once
#include "Game.h"
class GameObject
{
public:
	GameObject(SDL_Renderer* renderer, const char* texName);
	GameObject();
	~GameObject();
	void Update();
	void TextureSet();
	void clean();

protected:
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* ren;
	int flag = 0;
};

