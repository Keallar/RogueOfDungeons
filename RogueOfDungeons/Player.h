#pragma once
#include "GameObject.h"
#include "Game.h"
class Player :
    public GameObject
{
private:
	SDL_Renderer* renderer;
    GameObject Player1 = GameObject("aboba", renderer, 0 , 0);
    
public:
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

