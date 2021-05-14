#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Inventory.h"
#include "Buttons.h"
#include "Player.h"
#include "TextureBase.h"


class UiTrader
{
private:
    TextureBase* GameTextures;
    const char* PATH_IN_FONT;
    SDL_Color color = { 255, 255, 255, 255 };
    int textW, textH;
    SDL_Renderer* ren;
    SDL_Texture* trader;
    SDL_Texture* traderText;
    SDL_Texture* firstItem;
    SDL_Texture* secondItem;
    SDL_Texture* thirdItmem;
    SDL_Texture* firstCost;
    SDL_Texture* secondCost;
    SDL_Texture* thirdCost;
    SDL_Texture* hpBottle;
    SDL_Texture* hpBtText;
    SDL_Texture* manaBottle;
    SDL_Texture* manaBtText;
    SDL_Texture* skip;
    SDL_Texture* coins;
    SDL_Texture* coinsText;
    SDL_Texture* sell;

    std::array<Inventory*, 3> items;

    Button* buttonForFirstItem;
    Button* buttonForSecondItem;
    Button* buttonForThirdItem;
    Button* buttonForHpPotion;
    Button* buttonForManaPotion;
    Button* buttonForSkip;
    Button* buttonForSell;
public:
    UiTrader(SDL_Renderer* renderer);
    ~UiTrader();
    void Render();
    void Update();
    void handleEvents(SDL_Event& eventInUiTrader);
    void clear();
};


