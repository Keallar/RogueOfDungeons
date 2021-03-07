#pragma once
#include <SDL.h>
#include "Managers.h"

class GameObject
{
public:
	GameObject(); //конструктор по умлочанию
	GameObject(const char* texturesheet, SDL_Renderer* renderer, int x, int y, int w, int h);;
	GameObject(const char* texturesheet, SDL_Renderer* renderer);
	~GameObject();
	void Update();
	void Render(SDL_Renderer* renderer);
	void clean();

private:
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* ren;
protected:
	int xpos;
	int ypos;
	int weight;
	int height;
	int index;
	
};

