#include <iostream>
#include "UiTrader.h"
#include "Managers.h"


UiTrader::UiTrader(SDL_Renderer* renderer): ren (renderer)
{
    GameTextures = TextureBase::Instance();
    PATH_IN_FONT = "data/fonts/manaspc.ttf";

    //trader
    trader = GameTextures->GetTexture("");
    traderText = FontManager::renderText("Trader", PATH_IN_FONT, color, 32, ren);

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
    manaBtText = FontManager::renderText("20", PATH_IN_FONT, color, 32, ren);

    skip = FontManager::renderText("Skip", PATH_IN_FONT, color, 32, ren);

    sell = FontManager::renderText("Sell", PATH_IN_FONT, color, 32, ren);

    //Buttons
    buttonForFirstItem = new Button("left", GameTextures->GetTexture("ShortSword"), ren,
                                    {TSCREEN_WEIGHT / 15 * 5, TSCREEN_HEIGHT / 16 * 7, 96, 96},
                                    [this](){bFirstItem = 1;}, NULL, NULL);
    buttonForSecondItem = new Button("left", GameTextures->GetTexture("ShortBow"), ren,
                                     {TSCREEN_WEIGHT / 15 * 7, TSCREEN_HEIGHT / 16 * 7, 96, 96},
                                     [this](){bSecondItem = 1;}, NULL, NULL);
    buttonForThirdItem = new Button("left", GameTextures->GetTexture("Spear"), ren,
                                    {TSCREEN_WEIGHT/ 15 * 9, TSCREEN_HEIGHT / 16 * 7, 96, 96},
                                    [this](){bThirdItem = 1;}, NULL, NULL);
    buttonForHpPotion = new Button("left", GameTextures->GetTexture("SmallHpPotion"), ren,
                                   {TSCREEN_WEIGHT / 15 * 2, TSCREEN_HEIGHT / 16 * 12, 64, 64},
                                   [this](){bHpPotion = 1;}, NULL, NULL);
    buttonForManaPotion = new Button("left", GameTextures->GetTexture("SmallMpPotion"), ren,
                                     {TSCREEN_WEIGHT / 15 * 4, TSCREEN_HEIGHT / 16 * 12, 64, 64},
                                     [this](){bManaPotion = 1;}, NULL, NULL);
    buttonForSkip = new Button("left", GameTextures->GetTexture("Button"), ren,
                               {TSCREEN_WEIGHT / 15 * 14, TSCREEN_HEIGHT / 16 * 14, 32, 32},
                               [](){FlagManager::flagUiTrader = 0;}, NULL, NULL);
    auto chooseSell{
        []()
        {
            if (FlagManager::flagSell == 0)
            {
                FlagManager::flagSell = 1;
            }
            else if (FlagManager::flagSell == 1)
            {
                FlagManager::flagSell = 0;
            }
        }
    };
    buttonForSell = new Button("left", GameTextures->GetTexture("Button"), ren,
                               {TSCREEN_WEIGHT / 15 * 14, TSCREEN_HEIGHT / 16 * 9, 32, 32},
                               chooseSell, NULL, NULL);

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
    RenderManager::CopyToRender(GameTextures->GetTexture("PlayBack"), ren, 32, 32,
                                TSCREEN_WEIGHT, TSCREEN_HEIGHT);
    //RenderManager::CopyToRender(trader, ren, 1, 1, 1, 1, 1, 1, 1, 1);

    SDL_QueryTexture(traderText, NULL, NULL, &textW, &textH);
    RenderManager::CopyToRender(traderText, ren, (TSCREEN_WEIGHT-textW)/2,
                                (TSCREEN_HEIGHT-textH)/2 - 200, textW, textH);
    buttonForFirstItem->Render();
    SDL_QueryTexture(firstCost, NULL, NULL, &textW, &textH);
    RenderManager::CopyToRender(firstCost, ren, TSCREEN_WEIGHT / 15 * 5,
                                TSCREEN_HEIGHT / 16 * 10, textW, textH);
    buttonForSecondItem->Render();
    SDL_QueryTexture(secondCost, NULL, NULL, &textW, &textH);
    RenderManager::CopyToRender(secondCost, ren, TSCREEN_WEIGHT / 15 * 7,
                                TSCREEN_HEIGHT / 16 * 10, textW, textH);
    buttonForThirdItem->Render();
    SDL_QueryTexture(thirdCost, NULL, NULL, &textW, &textH);
    RenderManager::CopyToRender(thirdCost, ren, TSCREEN_WEIGHT / 15 * 9,
                                TSCREEN_HEIGHT / 16 * 10, textW, textH);
    buttonForHpPotion->Render();
    SDL_QueryTexture(hpBtText, NULL, NULL, &textW, &textH);
    RenderManager::CopyToRender(hpBtText, ren, TSCREEN_WEIGHT / 15 * 2 + 10,
                                TSCREEN_HEIGHT / 16 * 14, textW, textH);
    buttonForManaPotion->Render();
    SDL_QueryTexture(manaBtText, NULL, NULL, &textW, &textH);
    RenderManager::CopyToRender(manaBtText, ren, TSCREEN_WEIGHT / 15 * 4 + 10,
                                TSCREEN_HEIGHT / 16 * 14, textW, textH);
    buttonForSkip->Render();
    SDL_QueryTexture(skip, NULL, NULL, &textW, &textH);
    RenderManager::CopyToRender(skip, ren, TSCREEN_WEIGHT / 15 * 14,
                                TSCREEN_HEIGHT / 16 * 13, textW, textH);
    buttonForSell->Render();
    SDL_QueryTexture(sell, NULL, NULL, &textW, &textH);
    RenderManager::CopyToRender(sell, ren, TSCREEN_WEIGHT / 15 * 14,
                                TSCREEN_HEIGHT / 16 * 8, textW, textH);
}

void UiTrader::Update(Player* player)
{   
    if (bHpPotion == 1)
    {
        if (buttonForHpPotion->GetTexture() != 0)
        {
            if (Player::GetCoinsOfPlayer(0) >= 20)
            {
                bHpPotion = 0;
                Player::ChangeCoins(-20);
                player->itemInInv(6);
                SDL_DestroyTexture(hpBtText);
                hpBtText = 0;
                buttonForHpPotion->deleteTexture();
            }
        }
    }

    if (bManaPotion == 1)
    {
        if (buttonForManaPotion->GetTexture() != 0)
        {
            if (Player::GetCoinsOfPlayer(0) >= 20)
            {
                bManaPotion = 0;
                Player::ChangeCoins(-20);
                player->itemInInv(7);
                SDL_DestroyTexture(manaBtText);
                manaBtText = 0;
                buttonForManaPotion->deleteTexture();
            }
        }
    }
}

void UiTrader::Check()
{
    if (bHpPotion == 0)
    {
        if (buttonForHpPotion->GetTexture() == 0 &&
                hpBtText == 0)
        {
            buttonForHpPotion->SetTexture(GameTextures->GetTexture("SmallHpPotion"));
            hpBtText = FontManager::renderText("20", PATH_IN_FONT, color, 32, ren);
            //std::cout <<"Check in UiTrader\n";
        }
    }
    if (bManaPotion == 0)
    {
        if (buttonForManaPotion->GetTexture() == 0 &&
                manaBtText == 0)
        {
            buttonForManaPotion->SetTexture(GameTextures->GetTexture("SmallMpPotion"));
            manaBtText = FontManager::renderText("20", PATH_IN_FONT, color, 32, ren);
            //std::cout <<"Check in UiTrader\n";
        }
    }
    if (bFirstItem == 0)
    {
        //if (Inventory::ExistingItems[])
    }
    if (bSecondItem == 0)
    {

    }
    if (bThirdItem == 0)
    {

    }
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
