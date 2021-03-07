#pragma once
#include "GameObject.h"
#include "SDL.h"

class Player
{
private:
    
    SDL_Texture* PlayerTexture;
    SDL_Renderer* ren;
    int HP;
    int exp;
    int damageInput;
    int playerCoordx = 32;
    int playerCoordy = 32;
    const Uint8* keys = SDL_GetKeyboardState(NULL);

public:
    Player() = default;
    Player(const char* texturesheet, SDL_Renderer* ren);
    ~Player();
    void Render();
    void Update();
    void clean();
    bool flag = 0;
    
};
