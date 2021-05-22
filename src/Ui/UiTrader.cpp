#include <iostream>
#include "UiTrader.h"
#include "Managers.h"
#include <cassert>
#include <random>

UiTrader::UiTrader(SDL_Renderer* renderer): ren (renderer)
{
    GameTextures = TextureBase::Instance();
    traderInventory = new Inventory();
    first = rand() % 20 + 1;
    traderInventory->AddItem(first);
    second = rand() % 20 + 1;
    traderInventory->AddItem(second);
    third = rand() % 20 + 1;
    traderInventory->AddItem(third);
    traderInventory->traderUpdate();

    //trader
    trader = GameTextures->GetTexture("");
    traderText = FontManager::renderText("Trader", PATH_IN_FONT, color, 32, ren);

    //items
    Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[0]);
    firstItem = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
    std::string stringTemp1 = std::to_string(Inventory::it->second->GetCost());
    const char* CHAR_VALUE1 = stringTemp1.c_str();
    firstCost = FontManager::renderText(CHAR_VALUE1, PATH_IN_FONT, color, 32, ren);

    Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[1]);
    secondItem =  textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
    std::string stringTemp2 = std::to_string(Inventory::it->second->GetCost());
    const char* CHAR_VALUE2 = stringTemp2.c_str();
    secondCost = FontManager::renderText(CHAR_VALUE2, PATH_IN_FONT, color, 32, ren);

    Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[2]);
    thirdItmem = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
    std::string stringTemp3 = std::to_string(Inventory::it->second->GetCost());
    const char* CHAR_VALUE3 = stringTemp3.c_str();
    thirdCost = FontManager::renderText(CHAR_VALUE3, PATH_IN_FONT, color, 32, ren);

    //Potions
    hpBottle = GameTextures->GetTexture("SmallHpPotion");
    hpBtText = FontManager::renderText("10", PATH_IN_FONT, color, 32, ren);
    manaBottle = GameTextures->GetTexture("SmallMpPotion");
    manaBtText = FontManager::renderText("10", PATH_IN_FONT, color, 32, ren);

    skip = FontManager::renderText("Skip", PATH_IN_FONT, color, 32, ren);

    sell = FontManager::renderText("Sell", PATH_IN_FONT, color, 32, ren);

    //Buttons
    buttonForFirstItem = new Button("left", firstItem, ren,
                                    {(TSCREEN_WEIGHT / 15) * 5, TSCREEN_HEIGHT / 16 * 7, 96, 96},
                                    [this](){bFirstItem = 1;}, NULL, NULL);
    buttonForSecondItem = new Button("left", secondItem, ren,
                                     {(TSCREEN_WEIGHT / 15) * 7, TSCREEN_HEIGHT / 16 * 7, 96, 96},
                                     [this](){bSecondItem = 1;}, NULL, NULL);
    buttonForThirdItem = new Button("left", thirdItmem, ren,
                                    {(TSCREEN_WEIGHT / 15) * 9, TSCREEN_HEIGHT / 16 * 7, 96, 96},
                                    [this](){bThirdItem = 1;}, NULL, NULL);
    buttonForHpPotion = new Button("left", GameTextures->GetTexture("SmallHpPotion"), ren,
                                   {TSCREEN_WEIGHT / 15 * 2, TSCREEN_HEIGHT / 16 * 12, 64, 64},
                                   [this](){bHpPotion = 1;}, NULL, NULL);
    buttonForManaPotion = new Button("left", GameTextures->GetTexture("SmallMpPotion"), ren,
                                     {TSCREEN_WEIGHT / 15 * 4, TSCREEN_HEIGHT / 16 * 12, 64, 64},
                                     [this](){bManaPotion = 1;}, NULL, NULL);
    buttonForSkip = new Button("left", GameTextures->GetTexture("Button"), ren,
                               {TSCREEN_WEIGHT / 15 * 14, TSCREEN_HEIGHT / 16 * 14, 32, 32},
                               [this](){FlagManager::flagUiTrader = 0; bSkip = 1;}, NULL, NULL);
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

UiTrader::~UiTrader() noexcept
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
}

void UiTrader::Update(Player* player)
{
    if (FlagManager::flagUiTrader == 1)
    {
        if (bHpPotion == 1)
        {
            if (buttonForHpPotion->GetTexture() != 0)
            {
                if (Player::GetCoinsOfPlayer(0) >= 10)
                {
                    bHpPotion = 0;
                    Player::ChangeCoins(-10);
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
                if (Player::GetCoinsOfPlayer(0) >= 10)
                {
                    bManaPotion = 0;
                    Player::ChangeCoins(-10);
                    player->itemInInv(7);
                    SDL_DestroyTexture(manaBtText);
                    manaBtText = 0;
                    buttonForManaPotion->deleteTexture();
                }
            }
        }
        if (bFirstItem == 1)
        {
            if (buttonForFirstItem->GetTexture() != 0)
            {
                Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[0]);
                if (Player::GetCoinsOfPlayer(0) >= Inventory::it->second->GetCost())
                {
                    bFirstItem = 0;
                    Player::ChangeCoins(-Inventory::it->second->GetCost());
                    traderInventory->inventory[0] = -1;
                    player->itemInInv(first);
                    SDL_DestroyTexture(firstCost);
                    firstCost = 0;
                    buttonForFirstItem->deleteTexture();
                }
            }
        }
        if (bSecondItem == 1)
        {
            Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[1]);
            if (buttonForSecondItem->GetTexture() != 0)
            {
                if (Player::GetCoinsOfPlayer(0) >= Inventory::it->second->GetCost())
                {
                    bSecondItem = 0;
                    Player::ChangeCoins(-Inventory::it->second->GetCost());
                    traderInventory->inventory[1] = -1;
                    player->itemInInv(second);
                    SDL_DestroyTexture(secondCost);
                    secondCost = 0;
                    buttonForSecondItem->deleteTexture();
                }
            }
        }
        if (bThirdItem == 1)
        {
            Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[2]);
            if (buttonForThirdItem->GetTexture() != 0)
            {
                if (Player::GetCoinsOfPlayer(0) >= Inventory::it->second->GetCost())
                {
                    bThirdItem = 0;
                    Player::ChangeCoins(-Inventory::it->second->GetCost());
                    traderInventory->inventory[2] = -1;
                    player->itemInInv(third);
                    SDL_DestroyTexture(thirdCost);
                    thirdCost = 0;
                    buttonForThirdItem->deleteTexture();
                }
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
            hpBtText = FontManager::renderText("10", PATH_IN_FONT, color, 32, ren);
        }
    }
    if (bManaPotion == 0)
    {
        if (buttonForManaPotion->GetTexture() == 0 &&
                manaBtText == 0)
        {
            buttonForManaPotion->SetTexture(GameTextures->GetTexture("SmallMpPotion"));
            manaBtText = FontManager::renderText("10", PATH_IN_FONT, color, 32, ren);
        }
    }
    if (bFirstItem == 0)
    {
        if (buttonForFirstItem->GetTexture() == 0 &&
                firstCost == 0)
        {
            first = rand() % 20 + 1;
            traderInventory->AddItem(first);
            Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[0]);
            firstItem = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
            std::string stringTemp1 = std::to_string(Inventory::it->second->GetCost());
            const char* CHAR_VALUE1 = stringTemp1.c_str();
            firstCost = FontManager::renderText(CHAR_VALUE1, PATH_IN_FONT, color, 32, ren);
        }
    }
    if (bSecondItem == 0)
    {
        if (buttonForSecondItem->GetTexture() == 0 &&
                secondCost == 0)
        {
            second = rand() % 20 + 1;
            traderInventory->AddItem(second);
            Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[1]);
            secondItem =  textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
            std::string stringTemp2 = std::to_string(Inventory::it->second->GetCost());
            const char* CHAR_VALUE2 = stringTemp2.c_str();
            secondCost = FontManager::renderText(CHAR_VALUE2, PATH_IN_FONT, color, 32, ren);
        }
    }
    if (bThirdItem == 0)
    {
        if (buttonForThirdItem->GetTexture() == 0 &&
                thirdCost == 0)
        {
            third = rand() % 20 + 1;
            traderInventory->AddItem(third);
            Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[2]);
            thirdItmem = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
            std::string stringTemp3 = std::to_string(Inventory::it->second->GetCost());
            const char* CHAR_VALUE3 = stringTemp3.c_str();
            thirdCost = FontManager::renderText(CHAR_VALUE3, PATH_IN_FONT, color, 32, ren);
        }
    }
    if (bSkip == 1)
    {
        if (bFirstItem == 1)
        {
            if (buttonForFirstItem->GetTexture() != 0 &&
                    firstCost != 0)
            {
                traderInventory->inventory[0] = -1;
                SDL_DestroyTexture(firstItem);
                firstItem = 0;
                SDL_DestroyTexture(firstCost);
                firstCost = 0;
                buttonForFirstItem->deleteTexture();
                first = rand() % 20 + 1;
                traderInventory->AddItem(first);
                Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[0]);
                firstItem = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
                buttonForFirstItem->updateTexture(firstItem);
                std::string stringTemp1 = std::to_string(Inventory::it->second->GetCost());
                const char* CHAR_VALUE1 = stringTemp1.c_str();
                firstCost = FontManager::renderText(CHAR_VALUE1, PATH_IN_FONT, color, 32, ren);
            }
        }
        if (bSecondItem == 1)
        {
            if (buttonForSecondItem->GetTexture() != 0 &&
                    secondCost != 0)
            {
                traderInventory->inventory[1] = -1;
                SDL_DestroyTexture(secondItem);
                secondItem = 0;
                SDL_DestroyTexture(secondCost);
                secondCost = 0;
                buttonForSecondItem->deleteTexture();
                second = rand() % 20 + 1;
                traderInventory->AddItem(second);
                Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[1]);
                secondItem = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
                buttonForSecondItem->updateTexture(secondItem);
                std::string stringTemp2 = std::to_string(Inventory::it->second->GetCost());
                const char* CHAR_VALUE2 = stringTemp2.c_str();
                secondCost = FontManager::renderText(CHAR_VALUE2, PATH_IN_FONT, color, 32, ren);
            }
        }
        if (bThirdItem == 1)
        {
            if (buttonForThirdItem->GetTexture() != 0 &&
                    thirdCost != 0)
            {
                traderInventory->inventory[2] = -1;
                SDL_DestroyTexture(thirdItmem);
                thirdItmem = 0;
                SDL_DestroyTexture(thirdCost);
                thirdCost = 0;
                buttonForThirdItem->deleteTexture();
                third = rand() % 20 + 1;
                traderInventory->AddItem(third);
                Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[2]);
                buttonForThirdItem->updateTexture(thirdItmem);
                thirdItmem = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
                std::string stringTemp3 = std::to_string(Inventory::it->second->GetCost());
                const char* CHAR_VALUE3 = stringTemp3.c_str();
                thirdCost = FontManager::renderText(CHAR_VALUE3, PATH_IN_FONT, color, 32, ren);
            }
        }
        if (bSkip == 1)
            bSkip = 0;
    }

    traderInventory->traderUpdate();
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
