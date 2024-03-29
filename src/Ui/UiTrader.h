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
    SDL_Texture* firstCost;
    SDL_Texture* firstInfo;
    SDL_Texture* secondItem;
    SDL_Texture* secondCost;
    SDL_Texture* secondInfo;
    SDL_Texture* thirdItem;
    SDL_Texture* thirdInfo;
    SDL_Texture* thirdCost;
    SDL_Texture* hpBottle;
    SDL_Texture* hpBtText;
    SDL_Texture* hpbtInfo;
    SDL_Texture* manaBottle;
    SDL_Texture* manaBtText;
    SDL_Texture* manaBtInfo;
    SDL_Texture* randBottle;
    SDL_Texture* randBtText;
    SDL_Texture* randBtInfo;
    SDL_Texture* skip;
    //SDL_Texture* sell;
    SDL_Texture* item;
    int first = 0, second = 0, third = 0, four = 0, five = 0, six = 0;

    Inventory* traderInventory;

    Button* buttonForFirstItem;
    Button* buttonForSecondItem;
    Button* buttonForThirdItem;
    Button* buttonForHpPotion;
    Button* buttonForManaPotion;
    Button* buttonForRandPotion;
    Button* buttonForSkip;
    //Button* buttonForSell;

    int iFirstItem = 0;
    int iSecondItem = 0;
    int iThirdItem = 0;
    int iHpPotion = 0;
    int iManaPotion = 0;
    int iRandPotion = 0;
    bool bSkip = 0;
    bool bSell = 0;
public:
    UiTrader() = default;
    UiTrader(SDL_Renderer* renderer);
    ~UiTrader() noexcept;
    void Render();
    void Update(Player* player);
    void Check();
    void handleEvents(SDL_Event& eventInUiTrader);
    void clear();
};


