#include "GameObject.h"
#include "Managers.h"

GameObject::GameObject()
{
}

GameObject::GameObject(const char* texturesheet, SDL_Renderer* renderer) : ren (renderer)
{
    objTexture = textureManager::LoadTexture(texturesheet, ren);
}

GameObject::GameObject(const char* texturesheet, SDL_Renderer* renderer,
                       int x, int y, int w, int h) : ren(renderer)
{
    objTexture = textureManager::LoadTexture(texturesheet, ren);
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
    RenderManager::CopyToRender(objTexture, ren, Rect.x, Rect.y, Rect.w, Rect.h);
}

void GameObject::clean()
{
	SDL_DestroyTexture(objTexture);
}
