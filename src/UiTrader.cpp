#include <iostream>
#include "UiTrader.h"
#include "Managers.h"


UiTrader::UiTrader(SDL_Renderer* renderer) : ren (renderer)
{
    GameTextures = TextureBase::Instance();
    PATH_IN_FONT = "data/fonts/manaspc.ttf";

    //trader
    trader = GameTextures->GetTexture("");
    traderText = FontManager::renderText("Trader", PATH_IN_FONT, color, 32, ren);
    SDL_QueryTexture(traderText, NULL, NULL, &textW, &textH);

    //items
    firstItem = GameTextures->GetTexture("ShortSword");
    firstCost = FontManager::renderText("0", PATH_IN_FONT, color, 32, ren);
    secondItem = GameTextures->GetTexture("ShortBow");
    secondCost = FontManager::renderText("0", PATH_IN_FONT, color, 32, ren);
    thirdItmem = GameTextures->GetTexture("Spear");
    thirdCost = FontManager::renderText("0", PATH_IN_FONT, color, 32, ren);

    //Potions
    hpBottle = GameTextures->GetTexture("SmallHpPotion");
    hpBtText = FontManager::renderText("20", PATH_IN_FONT, color, 32, ren);
    manaBottle = GameTextures->GetTexture("SmallMpPotion");
    manaBtText = FontManager::renderText("0", PATH_IN_FONT, color, 32, ren);

    //Coins
    coins = FontManager::renderText("0", PATH_IN_FONT, color, 32, ren);
    coinsText = FontManager::renderText("Coins", PATH_IN_FONT, color, 32, ren);

    skip = FontManager::renderText("Skip", PATH_IN_FONT, color, 32, ren);

    sell = FontManager::renderText("Sell", PATH_IN_FONT, color, 32, ren);

    for (auto item : items)
    {
        item = nullptr;
    }

    //Buttons
    buttonForFirstItem = new Button("left", GameTextures->GetTexture("ShortSword"), ren, {413, 296, 128, 128}, [this](){bFirstItem = 1;}, NULL);
    buttonForSecondItem = new Button("left", GameTextures->GetTexture("ShortBow"), ren, {575, 296, 128, 128}, [this](){bSecondItem = 1;}, NULL);
    buttonForThirdItem = new Button("left", GameTextures->GetTexture("Spear"), ren, {739, 296, 128, 128}, [this](){bThirdItem = 1;}, NULL);
    buttonForHpPotion = new Button("left", GameTextures->GetTexture("SmallHpPotion"), ren, {1280 / 16 * 2, 720 / 12 * 9, 64, 64}, [this](){bHpPotion = 1;}, NULL);
    buttonForManaPotion = new Button("left", GameTextures->GetTexture("SmallMpPotion"), ren, {1280 / 16 * 3, 720 / 12 * 9, 64, 64}, [this](){bManaPotion = 1;}, NULL);
    buttonForSkip = new Button("left", GameTextures->GetTexture("Button"), ren, {1280 / 16 * 14, 720 / 12 * 11, 32, 32}, [](){FlagManager::flagUiTrader = 0;}, NULL);

    auto chooseSell{
        []()
        {

        }
    };
    buttonForSell = new Button("left", GameTextures->GetTexture("Button"), ren, {1280 / 16 * 1, 720 / 12 * 7, 32, 32}, chooseSell, NULL);

    for (auto item : items)
    {
        item = nullptr;
    }
}

UiTrader::~UiTrader()
{
    delete buttonForFirstItem;
    delete buttonForSecondItem;
    delete buttonForThirdItem;
    delete buttonForHpPotion;
    delete buttonForManaPotion;
    delete buttonForSkip;
    delete buttonForSell;
}

void UiTrader::Render()
{
    RenderManager::CopyToRender(GameTextures->GetTexture("PlayBack"), ren);
    //RenderManager::CopyToRender(trader, ren, 1, 1, 1, 1, 1, 1, 1, 1);

    RenderManager::CopyToRender(traderText, ren, (1280-textW)/2, (720-textH)/2 - 200, textW, textH);
    buttonForFirstItem->Render();
    RenderManager::CopyToRender(firstCost, ren, 413, 444, 64, 64);
    buttonForSecondItem->Render();
    RenderManager::CopyToRender(secondCost, ren, 575, 444, 64, 64);
    buttonForThirdItem->Render();
    RenderManager::CopyToRender(thirdCost, ren, 739, 444, 64, 64);
    buttonForHpPotion->Render();
    RenderManager::CopyToRender(hpBtText, ren, 1280 / 16 * 2, 720 / 12 * 11, 64, 64);
    buttonForManaPotion->Render();
    RenderManager::CopyToRender(manaBtText, ren, 1280 / 16 * 3, 720 / 12 * 11, 64, 64);
    RenderManager::CopyToRender(coins, ren , 1280 / 16 * 13, 720 / 12 * 4, 64, 64);
    RenderManager::CopyToRender(coinsText, ren, 1280 / 16 * 13, 720 / 12 * 3, textW, textH);
    buttonForSkip->Render();
    RenderManager::CopyToRender(skip, ren, 1280 / 16 * 14, 720 / 12 * 10, textW, textH);
    buttonForSell->Render();
    RenderManager::CopyToRender(sell, ren, 1280 / 16 * 1, 720 / 12 * 6, textW, textH);
}

void UiTrader::Update(Player* player)
{   
    if (bHpPotion == 1)
    {
        if (buttonForHpPotion->GetTexture() != nullptr)
        {
            if (Player::GetCoinsOfPlayer(0) >= 20)
            {
                Player::ChangeCoins(-20);
                player->itemInInv(6);
                SDL_DestroyTexture(hpBtText);
                hpBtText = 0;
            }
        }
    }

    if (bManaPotion == 1)
    {
        if (buttonForManaPotion->GetTexture() != nullptr)
        {
            if (Player::GetCoinsOfPlayer(0) >= 20)
            {
                Player::ChangeCoins(-20);
                player->itemInInv(7);
                SDL_DestroyTexture(manaBtText);
                manaBtText = 0;
            }
        }
    }
//    SDL_DestroyTexture(hpBtText);
//    hpBtText = 0;
//    std::string stringTemp1 = std::to_string();
//    const char* CHAR_VALUE1 = stringTemp1.c_str();
//    hpBtText = FontManager::renderText(CHAR_VALUE1, PATH_IN_FONT, color, 32, ren);

    SDL_DestroyTexture(coins);
    coins = 0;
    std::string stringTemp2 = std::to_string(Player::GetCoinsOfPlayer(0));
    const char* CHAR_VALUE2 = stringTemp2.c_str();
    coins = FontManager::renderText(CHAR_VALUE2, PATH_IN_FONT, color, 32, ren);
}

void UiTrader::Check()
{

}

void UiTrader::handleEvents(SDL_Event &eventInUiTrader)
{
    buttonForFirstItem->handleEvents(eventInUiTrader);
    buttonForSecondItem->handleEvents(eventInUiTrader);
    buttonForThirdItem->handleEvents(eventInUiTrader);
    buttonForHpPotion->handleEvents(eventInUiTrader);
    buttonForManaPotion->handleEvents(eventInUiTrader);
    buttonForSkip->handleEvents(eventInUiTrader);
    buttonForSell->handleEvents(eventInUiTrader);
}

void UiTrader::clear()
{

}
