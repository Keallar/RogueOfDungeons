#include "GameObject.h"
#include "Managers.h"

GameObject::GameObject()
{

}

GameObject::GameObject(const char* texturesheet, SDL_Renderer* renderer) : ren (renderer)
{
	objTexture = textureManager::LoadTexture(texturesheet, renderer);
}

GameObject::GameObject(const char* texturesheet, SDL_Renderer* renderer, int x, int y, int w, int h) : 
	ren(renderer)
{
	objTexture = textureManager::LoadTexture(texturesheet, renderer);
	Rect.x = x;
	Rect.y = y;
	Rect.w = w;
	Rect.h = h;
}
SDL_Rect GameObject::GetRect()
{
	return Rect;
}
GameObject::~GameObject()
{

}

void GameObject::Update()
{

}

void GameObject::Render()
{

}

void GameObject::clean()
{
	SDL_DestroyTexture(objTexture);
}