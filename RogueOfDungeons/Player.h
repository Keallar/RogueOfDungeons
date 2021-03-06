#pragma once
#include "GameObject.h"
#include "Game.h"

class Player
{
private:
    
    SDL_Texture* PlayerTexture;
    SDL_Renderer* ren;
    int xpos = 32;
    int ypos = 32;
    int HP;
    int exp;
    int damageInput;

public:
    Player();
    Player(const char* texturesheet, SDL_Renderer* ren);
    ~Player();
    void Render();
    void Update(int x, int y);
    void clean();
    bool flag = 0;
};
