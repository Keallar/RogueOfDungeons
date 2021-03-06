#pragma once
#include "GameObject.h"
#include "Game.h"

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

public:
    Player();
    Player(const char* texturesheet, SDL_Renderer* ren);
    ~Player();
    void Render();
    void Update();
    void clean();
    void UpdateCoord();
    bool flag = 0;
    
};
