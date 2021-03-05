#include "GameObject.h"
#include "textureManager.h"

GameObject::GameObject(const char* texturesheet, SDL_Renderer* renderer)
{

}

GameObject::GameObject(SDL_Renderer* renderer,const char* texName)
{
	ren = renderer;
	objTexture = textureManager::LoadTexture(texName, ren);
	
	flag = 0;
}

void GameObject::Update() 
{

}

void GameObject::TextureSet()
{
	RenderManager::CopyToRender(objTexture, ren, srcRect.x, srcRect.y, 32, 32, destRect.x, destRect.y, 32, 32);
}
void GameObject::clean()
{
	SDL_DestroyTexture(objTexture);
}