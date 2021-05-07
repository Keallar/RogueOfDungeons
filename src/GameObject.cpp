#include "GameObject.h"
#include "Managers.h"
#include "Animation.h"

GameObject::GameObject(const char* texturesheet, SDL_Renderer* renderer) :
    ren (renderer)
{
    objTexture = textureManager::LoadTexture(texturesheet, ren);
    objAnim = new Animation(ren, objTexture);
}

GameObject::~GameObject()
{
    SDL_DestroyTexture(objTexture);
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

SDL_Rect GameObject::GetRect()
{
    return Rect;
}
