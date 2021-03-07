#include "GameObject.h"
#include "Managers.h"

GameObject::GameObject()
{}

GameObject::GameObject(const char* texturesheet, SDL_Renderer* renderer)
{
	ren = renderer;
	objTexture = textureManager::LoadTexture(texturesheet, renderer);
}

GameObject::GameObject(const char* texturesheet, SDL_Renderer* renderer, int x, int y, int w, int h)
{
	ren = renderer;
	objTexture = textureManager::LoadTexture(texturesheet, renderer);
	xpos = x;
	ypos = y;
	weight = w;
	height = h;
}

GameObject::~GameObject()
{}

void GameObject::Update()
{

}

void GameObject::Render(SDL_Renderer* renderer)
{
	RenderManager::CopyToRender(objTexture, ren);
}

void GameObject::clean()
{
	SDL_DestroyTexture(objTexture);
}