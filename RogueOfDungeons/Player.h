#pragma once
#include "GameObject.h"
#include "Game.h"

class Player : public GameObject
{
private:
    GameObject Player1;
    SDL_Texture* PlayerTexture;
    SDL_Renderer* ren;
    int PlayerLVL;
public:
    Player(const char* texturesheet, SDL_Renderer* ren, int x, int y);
    ~Player();
    void Render() {
       GameObject::Render();
    }
    void Update() {
        GameObject::Update();
    }
    void clean() {
        GameObject::clean();
    }
    bool flag = 0;
};

