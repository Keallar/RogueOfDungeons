#pragma once
#include <SDL.h>
#include "Managers.h"
#include "Animation.h"

class GameObject
{
protected:
	SDL_Texture* objTexture;
	SDL_Renderer* ren;
    Animation* objAnim;
public:
	SDL_Rect Rect;
    GameObject() = default;
    GameObject(const char* texturesheet, SDL_Renderer* renderer);
    virtual ~GameObject();
	virtual void Update();
    virtual void handleEvents(SDL_Event e);
    virtual void Render();
    void clean();
    SDL_Rect GetRect();
};

