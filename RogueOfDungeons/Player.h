#pragma once
#include "GameObject.h"
#include "SDL.h"
#include "EntityPosition.h"

class Player
{
private:
    SDL_Texture* PlayerTexture;
    SDL_Renderer* ren;
    int HP;
    int exp;
    int damageInput;
    const Uint8* keys = SDL_GetKeyboardState(NULL);
public:
    Player() = default;
    Player(const char* texturesheet, SDL_Renderer* ren);
    ~Player();
    void Render();
    void Update();
    void clean();

};
