#pragma once
#include "GameObject.h"
#include "Game.h"

class Player
{
private:
    //GameObject mainPlayer;
    SDL_Texture* PlayerTexture;
    SDL_Renderer* ren;

public:
    Player();
    Player(const char* texturesheet, SDL_Renderer* ren);
    ~Player();
    void Render();
    void Update();
    void clean();
    bool flag = 0;
};
