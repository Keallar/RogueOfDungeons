#pragma once
#include <SDL.h>
#include "Managers.h"
#include "Animation.h"

class GameObject
{
protected:
    TextureBase* GameTextures;
	SDL_Renderer* ren;
public:
	SDL_Rect Rect;
    GameObject() = default;
    GameObject(SDL_Renderer* renderer);
    virtual ~GameObject();
	virtual void Update();
    virtual void Render();
    void clean();
    SDL_Rect GetRect();
};

