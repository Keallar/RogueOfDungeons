#ifndef COINS_H
#define COINS_H
#include <SDL.h>
#include <SDL_image.h>
#include "GameObject.h"

class Coins : public GameObject
{
private:
    SDL_Texture* coinTexture;
    SDL_Rect coinRect;
    int valueOfCoin;
public:
    Coins();
    ~Coins() override;
    void Render() override;
    void Update() override;
    void clean() override;
};

#endif // COINS_H
