#include <iostream>
#include "UiTrader.h"
#include "Managers.h"
#include <cassert>
#include <random>

UiTrader::UiTrader(SDL_Renderer* renderer): ren (renderer)
{
    GameTextures = TextureBase::Instance();
    traderInventory = new Inventory();
    first = rand() % 26 + 1;
    traderInventory->AddPlaceItem(first, 0);
    second = rand() % 26 + 1;
    traderInventory->AddPlaceItem(second, 1);
    third = rand() % 26 + 1;
    traderInventory->AddPlaceItem(third, 2);
    four = 6;
    traderInventory->AddPlaceItem(four, 3);
    five = 7;
    traderInventory->AddPlaceItem(five, 4);
    six = 23;
    traderInventory->AddPlaceItem(six, 5);
    traderInventory->traderUpdate();

    //trader
    trader = GameTextures->GetTexture("");
    traderText = FontManager::renderText("Trader", PATH_IN_FONT, color, 32, ren);

    //items
    Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[0]);
    firstItem = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
    std::string stringTemp0 = std::to_string(Inventory::it->second->GetCost());
    const char* CHAR_VALUE0 = stringTemp0.c_str();
    firstCost = FontManager::renderText(CHAR_VALUE0, PATH_IN_FONT, color, 32, ren);

    Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[1]);
    secondItem =  textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
    std::string stringTemp1 = std::to_string(Inventory::it->second->GetCost());
    const char* CHAR_VALUE1 = stringTemp1.c_str();
    secondCost = FontManager::renderText(CHAR_VALUE1, PATH_IN_FONT, color, 32, ren);

    Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[2]);
    thirdItem = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
    std::string stringTemp2 = std::to_string(Inventory::it->second->GetCost());
    const char* CHAR_VALUE2 = stringTemp2.c_str();
    thirdCost = FontManager::renderText(CHAR_VALUE2, PATH_IN_FONT, color, 32, ren);

    //Potions
    Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[3]);
    hpBottle = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
    std::string stringTemp3 = std::to_string(Inventory::it->second->GetCost());
    const char* CHAR_VALUE3 = stringTemp3.c_str();
    hpBtText = FontManager::renderText(CHAR_VALUE3, PATH_IN_FONT, color, 32, ren);

    Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[4]);
    manaBottle = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
    std::string stringTemp4 = std::to_string(Inventory::it->second->GetCost());
    const char* CHAR_VALUE4 = stringTemp4.c_str();
    manaBtText = FontManager::renderText(CHAR_VALUE4, PATH_IN_FONT, color, 32, ren);

    Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[5]);
    randBottle = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
    std::string stringTemp5 = std::to_string(Inventory::it->second->GetCost());
    const char* CHAR_VALUE5 = stringTemp5.c_str();
    randBtText = FontManager::renderText(CHAR_VALUE5, PATH_IN_FONT, color, 32, ren);

    skip = FontManager::renderText("Skip", PATH_IN_FONT, color, 32, ren);

    //sell = FontManager::renderText("Sell", PATH_IN_FONT, color, 32, ren);

    //Buttons
    buttonForFirstItem = new Button("left", firstItem, ren,
                                    {(TSCREEN_WEIGHT / 15) * 5, TSCREEN_HEIGHT / 16 * 7, 96, 96},
                                    [this](){iFirstItem = 1;}, NULL, NULL);
    buttonForSecondItem = new Button("left", secondItem, ren,
                                     {(TSCREEN_WEIGHT / 15) * 7, TSCREEN_HEIGHT / 16 * 7, 96, 96},
                                     [this](){iSecondItem = 1;}, NULL, NULL);
    buttonForThirdItem = new Button("left", thirdItem, ren,
                                    {(TSCREEN_WEIGHT / 15) * 9, TSCREEN_HEIGHT / 16 * 7, 96, 96},
                                    [this](){iThirdItem = 1;}, NULL, NULL);
    buttonForHpPotion = new Button("left",hpBottle, ren,
                                   {TSCREEN_WEIGHT / 15 * 2, TSCREEN_HEIGHT / 16 * 12, 64, 64},
                                   [this](){iHpPotion = 1;}, NULL, NULL);
    buttonForManaPotion = new Button("left", manaBottle, ren,
                                     {TSCREEN_WEIGHT / 15 * 2, TSCREEN_HEIGHT / 16 * 9, 64, 64},
                                     [this](){iManaPotion = 1;}, NULL, NULL);
    buttonForRandPotion = new Button("left", randBottle, ren,
                                     {TSCREEN_WEIGHT / 15 * 2, TSCREEN_HEIGHT / 16 * 6, 64, 64},
                                     [this](){iRandPotion = 1;}, NULL, NULL);
    buttonForSkip = new Button("left", GameTextures->GetTexture("Button"), ren,
                               {TSCREEN_WEIGHT / 15 * 14, TSCREEN_HEIGHT / 16 * 14, 32, 32},
                               [this](){FlagManager::flagUiTrader = 0; bSkip = 1;}, NULL, NULL);
    //    auto chooseSell{
    //        []()
    //        {
    //            if (FlagManager::flagSell == 0)
    //            {
    //                FlagManager::flagSell = 1;
    //            }
    //            else if (FlagManager::flagSell == 1)
    //            {
    //                FlagManager::flagSell = 0;
    //            }
    //        }
    //    };
    //buttonForSell = new Button("left", GameTextures->GetTexture("Button"), ren,
    //                               {TSCREEN_WEIGHT / 15 * 14, TSCREEN_HEIGHT / 16 * 9, 32, 32},
    //                               chooseSell, NULL, NULL);
}

UiTrader::~UiTrader() noexcept
{
    delete buttonForFirstItem;
    delete buttonForSecondItem;
    delete buttonForThirdItem;
    delete buttonForHpPotion;
    delete buttonForManaPotion;
    delete buttonForRandPotion;
    delete buttonForSkip;
//    delete buttonForSell;
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
    RenderManager::CopyToRender(manaBtText, ren, TSCREEN_WEIGHT / 15 * 2 + 10,
                                TSCREEN_HEIGHT / 16 * 11, textW, textH);
    buttonForRandPotion->Render();
    SDL_QueryTexture(randBtText, NULL, NULL, &textW, &textH);
    RenderManager::CopyToRender(randBtText, ren, TSCREEN_WEIGHT / 15 * 2 + 10,
                                TSCREEN_HEIGHT / 16 * 8, textW, textH);
    buttonForSkip->Render();
    SDL_QueryTexture(skip, NULL, NULL, &textW, &textH);
    RenderManager::CopyToRender(skip, ren, TSCREEN_WEIGHT / 15 * 14,
                                TSCREEN_HEIGHT / 16 * 13, textW, textH);
    //buttonForSell->Render();
    //SDL_QueryTexture(sell, NULL, NULL, &textW, &textH);
    //RenderManager::CopyToRender(sell, ren, TSCREEN_WEIGHT / 15 * 14,
    //                            TSCREEN_HEIGHT / 16 * 8, textW, textH);
}

void UiTrader::Update(Player* player)
{
    if (FlagManager::flagUiTrader == 1)
    {
        if (iHpPotion == 1)
        {
            if (buttonForHpPotion->GetTexture() != 0)
            {
                Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[3]);
                if (Player::GetCoinsOfPlayer(0) >= Inventory::it->second->GetCost())
                {
                    iHpPotion = 2;
                    Player::ChangeCoins(-Inventory::it->second->GetCost());
                    traderInventory->inventory[3] = -1;
                    player->itemInInv(four);
                    buttonForHpPotion->deleteTexture();
                    SDL_DestroyTexture(hpBottle);
                    hpBottle = 0;
                    SDL_DestroyTexture(hpBtText);
                    hpBtText = 0;
                }
            }
        }

        if (iManaPotion == 1)
        {
            if (buttonForManaPotion->GetTexture() != 0)
            {
                Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[4]);
                if (Player::GetCoinsOfPlayer(0) >= Inventory::it->second->GetCost())
                {
                    iManaPotion = 2;
                    Player::ChangeCoins(-Inventory::it->second->GetCost());
                    traderInventory->inventory[4] = -1;
                    player->itemInInv(five);
                    buttonForManaPotion->deleteTexture();
                    SDL_DestroyTexture(manaBottle);
                    manaBottle = 0;
                    SDL_DestroyTexture(manaBtText);
                    manaBtText = 0;
                }
            }
        }
        if (iRandPotion == 1)
        {
            if (buttonForRandPotion->GetTexture() != 0)
            {
                Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[5]);
                if (Player::GetCoinsOfPlayer(0) >= Inventory::it->second->GetCost())
                {
                    iRandPotion = 2;
                    Player::ChangeCoins(-Inventory::it->second->GetCost());
                    traderInventory->inventory[5] = -1;
                    player->itemInInv(first);
                    buttonForRandPotion->deleteTexture();
                    SDL_DestroyTexture(randBottle);
                    randBottle = 0;
                    SDL_DestroyTexture(randBtText);
                    randBtText = 0;
                }
            }
        }
        if (iFirstItem == 1)
        {
            if (buttonForFirstItem->GetTexture() != 0)
            {
                Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[0]);
                if (Player::GetCoinsOfPlayer(0) >= Inventory::it->second->GetCost())
                {
                    iFirstItem = 2;
                    Player::ChangeCoins(-Inventory::it->second->GetCost());
                    traderInventory->inventory[0] = -1;
                    player->itemInInv(first);
                    buttonForFirstItem->deleteTexture();
                    SDL_DestroyTexture(firstItem);
                    firstItem = 0;
                    SDL_DestroyTexture(firstCost);
                    firstCost = 0;
                }
            }
        }
        if (iSecondItem == 1)
        {
            Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[1]);
            if (buttonForSecondItem->GetTexture() != 0)
            {
                if (Player::GetCoinsOfPlayer(0) >= Inventory::it->second->GetCost())
                {
                    iSecondItem = 2;
                    Player::ChangeCoins(-Inventory::it->second->GetCost());
                    traderInventory->inventory[1] = -1;
                    player->itemInInv(second);
                    buttonForSecondItem->deleteTexture();
                    SDL_DestroyTexture(secondCost);
                    secondItem = 0;
                    SDL_DestroyTexture(secondCost);
                    secondCost = 0;

                }
            }
        }
        if (iThirdItem == 1)
        {
            Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[2]);
            if (buttonForThirdItem->GetTexture() != 0)
            {
                if (Player::GetCoinsOfPlayer(0) >= Inventory::it->second->GetCost())
                {
                    iThirdItem = 2;
                    Player::ChangeCoins(-Inventory::it->second->GetCost());
                    traderInventory->inventory[2] = -1;
                    player->itemInInv(third);
                    buttonForThirdItem->deleteTexture();
                    SDL_DestroyTexture(thirdItem);
                    thirdItem = 0;
                    SDL_DestroyTexture(thirdCost);
                    thirdCost = 0;

                }
            }
        }
    }

    if (bSkip == 1)
    {
        if (iFirstItem == 0)
            iFirstItem = 3;
        if (iSecondItem == 0)
            iSecondItem = 3;
        if (iThirdItem == 0)
            iThirdItem = 3;
//        if (iRandPotion == 0)
//            iRandPotion = 3;
    }

    traderInventory->traderUpdate();
}

void UiTrader::Check()
{
        if (iHpPotion == 2)
        {
            if (buttonForHpPotion->GetTexture() == 0 &&
                    hpBtText == 0)
            {
                iHpPotion = 0;
                four = 6;
                traderInventory->AddPlaceItem(four, 3);
                traderInventory->traderUpdate();
                Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[3]);
                hpBottle = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
                buttonForHpPotion->updateTexture(hpBottle);
                std::string stringTemp3 = std::to_string(Inventory::it->second->GetCost());
                const char* CHAR_VALUE3 = stringTemp3.c_str();
                hpBtText = FontManager::renderText(CHAR_VALUE3, PATH_IN_FONT, color, 32, ren);
            }
        }
        if (iManaPotion == 0)
        {
            if (buttonForManaPotion->GetTexture() == 0 &&
                    manaBtText == 0)
            {
                iManaPotion = 0;
                five = 7;
                traderInventory->AddPlaceItem(five, 4);
                traderInventory->traderUpdate();
                Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[4]);
                manaBottle = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
                buttonForManaPotion->updateTexture(manaBottle);
                std::string stringTemp4 = std::to_string(Inventory::it->second->GetCost());
                const char* CHAR_VALUE4 = stringTemp4.c_str();
                manaBtText = FontManager::renderText(CHAR_VALUE4, PATH_IN_FONT, color, 32, ren);
            }
        }
        if (iRandPotion == 0)
        {
            if (buttonForRandPotion->GetTexture() == 0 &&
                    randBtText == 0)
            {
                iRandPotion = 0;
                six = 23;
                traderInventory->AddPlaceItem(six, 5);
                traderInventory->traderUpdate();
                Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[5]);
                randBottle = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
                buttonForRandPotion->updateTexture(randBottle);
                std::string stringTemp5 = std::to_string(Inventory::it->second->GetCost());
                const char* CHAR_VALUE5 = stringTemp5.c_str();
                randBtText = FontManager::renderText(CHAR_VALUE5, PATH_IN_FONT, color, 32, ren);
            }
        }
        if (iFirstItem == 2)
        {
            if (buttonForFirstItem->GetTexture() == 0 &&
                    firstCost == 0)
            {
                iFirstItem = 0;
                first = rand() % 26 + 1;
                traderInventory->AddPlaceItem(first, 0);
                traderInventory->traderUpdate();
                Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[0]);
                firstItem = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
                buttonForFirstItem->updateTexture(firstItem);
                std::string stringTemp1 = std::to_string(Inventory::it->second->GetCost());
                const char* CHAR_VALUE1 = stringTemp1.c_str();
                firstCost = FontManager::renderText(CHAR_VALUE1, PATH_IN_FONT, color, 32, ren);
            }
        }
        if (iSecondItem == 2)
        {
            if (buttonForSecondItem->GetTexture() == 0 &&
                    secondCost == 0)
            {
                iSecondItem = 0;
                second = rand() % 26 + 1;
                traderInventory->AddPlaceItem(second, 1);
                traderInventory->traderUpdate();
                Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[1]);
                secondItem =  textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
                buttonForSecondItem->updateTexture(secondItem);
                std::string stringTemp2 = std::to_string(Inventory::it->second->GetCost());
                const char* CHAR_VALUE2 = stringTemp2.c_str();
                secondCost = FontManager::renderText(CHAR_VALUE2, PATH_IN_FONT, color, 32, ren);

            }
        }
        if (iThirdItem == 2)
        {
            if (buttonForThirdItem->GetTexture() == 0 &&
                    thirdCost == 0)
            {
                iThirdItem = 0;
                third = rand() % 26 + 1;
                traderInventory->AddPlaceItem(third, 2);
                traderInventory->traderUpdate();
                Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[2]);
                thirdItem = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
                buttonForThirdItem->updateTexture(thirdItem);
                std::string stringTemp3 = std::to_string(Inventory::it->second->GetCost());
                const char* CHAR_VALUE3 = stringTemp3.c_str();
                thirdCost = FontManager::renderText(CHAR_VALUE3, PATH_IN_FONT, color, 32, ren);

            }
        }
        if (bSkip == 1)
        {
            if (iFirstItem == 3)
            {
                if (buttonForFirstItem->GetTexture() != 0 &&
                        firstCost != 0)
                {
                    iFirstItem = 0;
                    buttonForFirstItem->deleteTexture();
                    SDL_DestroyTexture(firstItem);
                    firstItem = 0;
                    SDL_DestroyTexture(firstCost);
                    firstCost = 0;
                    traderInventory->inventory[0] = -1;
                    first = rand() % 26 + 1;
                    traderInventory->AddPlaceItem(first, 0);
                    traderInventory->traderUpdate();
                    Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[0]);
                    firstItem = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
                    buttonForFirstItem->updateTexture(firstItem);
                    std::string stringTemp1 = std::to_string(Inventory::it->second->GetCost());
                    const char* CHAR_VALUE1 = stringTemp1.c_str();
                    firstCost = FontManager::renderText(CHAR_VALUE1, PATH_IN_FONT, color, 32, ren);
                    iFirstItem = 0;
                }
            }
            if (iSecondItem == 3)
            {
                if (buttonForSecondItem->GetTexture() != 0 &&
                        secondCost != 0)
                {
                    iSecondItem = 0;
                    buttonForSecondItem->deleteTexture();
                    SDL_DestroyTexture(secondItem);
                    secondItem = 0;
                    SDL_DestroyTexture(secondCost);
                    secondCost = 0;
                    traderInventory->inventory[1] = -1;
                    second = rand() % 26 + 1;
                    traderInventory->AddPlaceItem(second, 1);
                    traderInventory->traderUpdate();
                    Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[1]);
                    secondItem = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
                    buttonForSecondItem->updateTexture(secondItem);
                    std::string stringTemp2 = std::to_string(Inventory::it->second->GetCost());
                    const char* CHAR_VALUE2 = stringTemp2.c_str();
                    secondCost = FontManager::renderText(CHAR_VALUE2, PATH_IN_FONT, color, 32, ren);
                    iSecondItem = 0;
                }
            }
            if (iThirdItem == 3)
            {
                if (buttonForThirdItem->GetTexture() != 0 &&
                        thirdCost != 0)
                {
                    iThirdItem = 0;
                    buttonForThirdItem->deleteTexture();
                    SDL_DestroyTexture(thirdItem);
                    thirdItem = 0;
                    SDL_DestroyTexture(thirdCost);
                    thirdCost = 0;
                    traderInventory->inventory[2] = -1;
                    third = rand() % 26 + 1;
                    traderInventory->AddPlaceItem(third, 2);
                    traderInventory->traderUpdate();
                    Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[2]);
                    thirdItem = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
                    buttonForThirdItem->updateTexture(thirdItem);
                    std::string stringTemp3 = std::to_string(Inventory::it->second->GetCost());
                    const char* CHAR_VALUE3 = stringTemp3.c_str();
                    thirdCost = FontManager::renderText(CHAR_VALUE3, PATH_IN_FONT, color, 32, ren);
                    iThirdItem = 0;
                }
            }
            if (iRandPotion == 3)
            {
                if (buttonForRandPotion->GetTexture() != 0 &&
                        randBtText != 0)
                {
                    iRandPotion = 0;
                    buttonForRandPotion->deleteTexture();
                    SDL_DestroyTexture(randBottle);
                    randBottle = 0;
                    SDL_DestroyTexture(randBtText);
                    randBtText = 0;
                    traderInventory->inventory[5] = -1;
                    six = 23;
                    traderInventory->AddPlaceItem(six, 5);
                    traderInventory->traderUpdate();
                    Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[5]);
                    randBottle = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
                    buttonForThirdItem->updateTexture(randBottle);
                    std::string stringTemp5 = std::to_string(Inventory::it->second->GetCost());
                    const char* CHAR_VALUE5 = stringTemp5.c_str();
                    randBtText = FontManager::renderText(CHAR_VALUE5, PATH_IN_FONT, color, 32, ren);
                    iRandPotion = 0;
                }
            }
            if (bSkip == 1)
                bSkip = 0;
        }
    traderInventory->traderUpdate();
}

void UiTrader::handleEvents(SDL_Event &eventInUiTrader)
{
    Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[0]);
    if (Player::GetCoinsOfPlayer(0) >= Inventory::it->second->GetCost())
        buttonForFirstItem->handleEvents(eventInUiTrader);
    Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[1]);
    if (Player::GetCoinsOfPlayer(0) >= Inventory::it->second->GetCost())
        buttonForSecondItem->handleEvents(eventInUiTrader);
    Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[2]);
    if (Player::GetCoinsOfPlayer(0) >= Inventory::it->second->GetCost())
        buttonForThirdItem->handleEvents(eventInUiTrader);
    Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[3]);
    if (Player::GetCoinsOfPlayer(0) >= Inventory::it->second->GetCost())
        buttonForHpPotion->handleEvents(eventInUiTrader);
    Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[4]);
    if (Player::GetCoinsOfPlayer(0) >= Inventory::it->second->GetCost())
        buttonForManaPotion->handleEvents(eventInUiTrader);
    Inventory::it = Inventory::ExistingItems.find(Inventory::traderFace[5]);
    if (Player::GetCoinsOfPlayer(0) >= Inventory::it->second->GetCost())
        buttonForRandPotion->handleEvents(eventInUiTrader);
    buttonForSkip->handleEvents(eventInUiTrader);
    //    buttonForSell->handleEvents(eventInUiTrader);
}

void UiTrader::clear()
{

}
