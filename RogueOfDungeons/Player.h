#pragma once
#include "GameObject.h"
#include "Game.h"
#include "Game.cpp"

class Player :
    public GameObject
{
private:
    SDL_Texture* PlayerTexture;
    SDL_Renderer* ren;
    SDL_Event PlayerEvent;
    bool Mov = 0;
    int LVL = 1;
    int HP = 10;
    int maxHP = 10;
    int STR = 1;
    int AGI = 1;
    int INT = 1;
    int EXP = 0;
    int EXPFORLVL = 5;
    int ChargePTS = 0;
    int *combatDMG = &STR;
    int *rangeDMG = &AGI;
    int *magicDMG = &INT;


public:
    Player(const char* texturesheet, SDL_Renderer* ren, int x, int y);
    ~Player();
    void Render() {
        GameObject::TextureSet();
    }
    void Update();
    void clean() {
        GameObject::clean();
    }
    bool flag = 0;
};
