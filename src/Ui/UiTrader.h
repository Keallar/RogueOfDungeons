#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Inventory.h"
#include "Buttons.h"
#include "Player.h"
#include "TextureBase.h"
#define TSCREEN_WEIGHT 960
#define TSCREEN_HEIGHT 640

struct sCoord{
    int x;
    int y;
};

class UiTrader
{
private:
    TextureBase* GameTextures;
    const char* PATH_IN_FONT = "data/fonts/manaspc.ttf";
    SDL_Color color = { 255, 255, 255, 255 };
    int textW, textH;
    sCoord mCoord;
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
    SDL_Texture* sell;
    SDL_Texture* item;
    int first = 0, second = 0, third = 0;

    Inventory* traderInventory;

    Button* buttonForFirstItem;
    Button* buttonForSecondItem;
    Button* buttonForThirdItem;
    Button* buttonForHpPotion;
    Button* buttonForManaPotion;
    Button* buttonForSkip;
    Button* buttonForSell;

    bool bFirstItem = 1;
    bool bSecondItem = 1;
    bool bThirdItem = 1;
    bool bHpPotion = 0;
    bool bManaPotion = 0;
    bool bSkip = 0;
    bool bSell = 0;
public:
    UiTrader(SDL_Renderer* renderer);
    ~UiTrader();
    void Render();
    void Update(Player* player);
    void Check();
    void handleEvents(SDL_Event& eventInUiTrader);
    void clear();
};


