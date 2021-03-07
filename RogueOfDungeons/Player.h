#pragma once
#include "GameObject.h"
#include "SDL.h"

class Player
{
private:
    
    SDL_Texture* PlayerTexture;
    SDL_Renderer* ren;
    SDL_Rect PlayerRect;
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
    void move_RIGHT(SDL_Renderer* render, SDL_Texture* texture, SDL_Rect& destrect, int offset = 32);
    void clean();
    bool flag = 0;
    
};
