#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "GameObject.h"
#include "Animation.h"
#include "Buttons.h"

class Coins : public GameObject
{
private:
    Uint32 Timer;
    SDL_Renderer* ren;
    SDL_Texture* coinTexture;
    Animation* coinAnimation;
    SDL_Rect coinRect;
    int valueOfCoin;
    int frameOfCoin;
    int currentFrameOfCoinAnim;
public:
    Coins(const char* texturesheet, SDL_Renderer* renderer, int value, int framesOfCoin);
    ~Coins();
    void Update() override;
    void Render() override;
    int GetValueCoins();
    SDL_Rect GetRect();
    void SetRectCoords(int newx, int newy);
    void deleteCoin();
};


