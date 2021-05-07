#include "Coins.h"
#include "EntityPosition.h"

Coins::Coins(const char* texturesheet, SDL_Renderer* renderer, int value, int framesOfCoin):
    GameObject(texturesheet, renderer)
{
    coinRect.x = 0;
    coinRect.y = 0;
    coinRect.w = 32;
    coinRect.h = 32;
    ren = renderer;
    valueOfCoin = value;
    coinTexture = textureManager::LoadTexture(texturesheet, ren);
    frameOfCoin = framesOfCoin;
    coinAnimation = new Animation (ren, coinTexture);
    completeCoinAnimation = 0;
}

Coins::~Coins()
{
    delete coinAnimation;
}

void Coins::Update()
{

}

void Coins::Render()
{
    bool temp = false;
    coinAnimation->Render(coinRect.x, coinRect.y);
    if (temp == false)
    {
        completeCoinAnimation = coinAnimation->animationMinusForX(frameOfCoin, completeCoinAnimation);
        Timer = SDL_GetTicks();
        temp = true;
    }
    Uint32 Timer2 = SDL_GetTicks();
    completeCoinAnimation = coinAnimation->animationMinusForX(frameOfCoin, completeCoinAnimation);
    if (Timer2 - Timer >= 200 && temp == true)
    {
        completeCoinAnimation = coinAnimation->animationMinusForX(frameOfCoin, completeCoinAnimation);
        Timer = Timer2;
    }
}

int Coins::GetValueCoins()
{
    return valueOfCoin;
}

SDL_Rect Coins::GetRect()
{
    return coinRect;
}

void Coins::SetRectCoords(int newx, int newy)
{
    coinRect.x = newx;
    coinRect.y = newy;
}

