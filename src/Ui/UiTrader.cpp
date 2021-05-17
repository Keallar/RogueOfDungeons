#include <iostream>
#include "UiTrader.h"
#include "Managers.h"


UiTrader::UiTrader(SDL_Renderer* renderer): ren (renderer)
{
    GameTextures = TextureBase::Instance();
    traderInventory = new Inventory();
    traderInventory->traderUpdate();
    traderInventory->AddItem(4);
    traderInventory->AddItem(5);
    traderInventory->AddItem(6);

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
    buttonForHpPotion = new Button("left", GameTextures->GetTexture("SmallHpPotion"), ren,
                                   {TSCREEN_WEIGHT / 15 * 2, TSCREEN_HEIGHT / 16 * 12, 64, 64},
                                   [this](){bHpPotion = 1;}, NULL);
    buttonForManaPotion = new Button("left", GameTextures->GetTexture("SmallMpPotion"), ren,
                                     {TSCREEN_WEIGHT / 15 * 4, TSCREEN_HEIGHT / 16 * 12, 64, 64},
                                     [this](){bManaPotion = 1;}, NULL);
    buttonForSkip = new Button("left", GameTextures->GetTexture("Button"), ren,
                               {TSCREEN_WEIGHT / 15 * 14, TSCREEN_HEIGHT / 16 * 14, 32, 32},
                               [](){FlagManager::flagUiTrader = 0;}, NULL);
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
                               chooseSell, NULL);
}

UiTrader::~UiTrader()
{
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

    for (int j = 0; j < TRADING_SIZE; j++)
    {
        if (Inventory::traderFace[TRADING_SIZE] != -1)
        {
            Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[j]);
            item = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
            std::cout <<  (TSCREEN_WEIGHT / 15) * (4 + j + 1) << std::endl;
            RenderManager::CopyToRender(item, ren, (TSCREEN_WEIGHT / 15) * (4 + j + 1), TSCREEN_HEIGHT / 16 * 7, 96, 96);
            SDL_DestroyTexture(item);
            item = 0;
        }
    }
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

    traderInventory->traderUpdate();
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
        }
    }
    if (bManaPotion == 0)
    {
        if (buttonForManaPotion->GetTexture() == 0 &&
                manaBtText == 0)
        {
            buttonForManaPotion->SetTexture(GameTextures->GetTexture("SmallMpPotion"));
            manaBtText = FontManager::renderText("20", PATH_IN_FONT, color, 32, ren);
        }
    }
    if (bFirstItem == 0)
    {

    }
    if (bSecondItem == 0)
    {

    }
    if (bThirdItem == 0)
    {

    }
}

void UiTrader::clickForItemInTrader()
{
    SDL_GetMouseState(&mCoord.x, &mCoord.y);

    for (int j = 0; j < TRADING_SIZE; j++)
    {
        if (InputManager::MouseInArea(TSCREEN_WEIGHT / 15 * (4 + j + 1), TSCREEN_HEIGHT / 16 * 7, 96, 96, mCoord.x, mCoord.y) &&
                Inventory::traderFace[j] != -1 && FlagManager::flagUiTrader == 1)
        {
            if (FlagManager::flagBuy == false)
            {
                FlagManager::flagBuy = j;
            }
        }
    }
}

void UiTrader::handleEvents(SDL_Event &eventInUiTrader)
{
    buttonForHpPotion->handleEvents(eventInUiTrader);
    buttonForManaPotion->handleEvents(eventInUiTrader);
    buttonForSkip->handleEvents(eventInUiTrader);
    buttonForSell->handleEvents(eventInUiTrader);
}

void UiTrader::clear()
{

}
