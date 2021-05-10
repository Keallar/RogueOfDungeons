#include "GameObject.h"
#include "Managers.h"
#include "Animation.h"

GameObject::GameObject(SDL_Renderer* renderer) :
    ren (renderer)
{
    GameTextures = TextureBase::Instance();
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

}

SDL_Rect GameObject::GetRect()
{
    return Rect;
}
