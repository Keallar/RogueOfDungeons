#include "GameObject.h"
#include "textureManager.h"


GameObject::GameObject(const char* texturesheet, SDL_Renderer* ren, int x, int y)
{
	renderer = ren;
	objTexture = textureManager::LoadTexture(texturesheet, ren);

	xpos = x;
	ypos = y;
}

void GameObject::Update() 
{

}

void GameObject::Render() 
{
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}
void GameObject::clean()
{
	SDL_DestroyTexture(objTexture);
}