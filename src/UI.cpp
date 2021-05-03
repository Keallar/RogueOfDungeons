#include "UI.h"
#include "Managers.h"
#include "EntityPosition.h"
#include <iostream>
#include "Inventory.h"
#include "Player.h"
#include "Enemy.h"
#include "Game.h"

UIInfo::UIInfo(SDL_Renderer* renderer) : ren (renderer)
{
    PATH_IN_FONT = "data/fonts/manaspc.ttf";
    flagHoverSpec = false;

    //Version
    versionBLock = FontManager::renderText("ROGUE OF DUNGEONS V-0.1 ALPHA", PATH_IN_FONT, color, 32, ren);

    infoBlock = textureManager::LoadTexture("data/images/InfoBlock.png", ren);
    info = FontManager::renderText("Info", PATH_IN_FONT, color, 32, ren);

    slashhhhhhhhh = FontManager::renderText("/", PATH_IN_FONT, color, 32, ren);

    SPEC = FontManager::renderText("SPEC", PATH_IN_FONT, color, 32, ren);

    //HP
    hpBar = textureManager::LoadTexture("data/images/hp.png", ren);
    hpText = FontManager::renderText("HP", PATH_IN_FONT, color, 64, ren);

    //Mana
    mnBar = textureManager::LoadTexture("data/images/ManaBar.png", ren);
    mnText = FontManager::renderText("MN", PATH_IN_FONT, color, 64, ren);

    //XP
    xpBar = textureManager::LoadTexture("data/images/XP.png", ren);
    xpText = FontManager::renderText("XP", PATH_IN_FONT, color, 64, ren);

    //Buttons
    auto callSpecOrInfoWin{
        []()
        {
            if (FlagManager::flagUiSpec == 0)
            {
                FlagManager::flagUiSpec = 1;
                FlagManager::flagUI = 0;
            }
            else if (FlagManager::flagUiSpec == 1)
            {
                FlagManager::flagUI = 1;
                FlagManager::flagUiSpec = 0;
            }
        }
    };
    auto hoverSpec{
        [=]()
        {
            if (flagHoverSpec == 0)
                flagHoverSpec = 1;
            else if (flagHoverSpec == 1)
                flagHoverSpec = 0;
        }
    };
    buttonForCallSpecInfo = new Button("left", "data/images/Button.png", ren , { 1230, 240, 32, 32 },
                                       callSpecOrInfoWin, hoverSpec);
    keyForCallSpecInfo = new Keyboard(SDL_SCANCODE_Q, callSpecOrInfoWin);
    auto callInvWin{
        []()
        {
            if (FlagManager::flagInv == 0)
            {
                FlagManager::flagInv = 1;
            }
            else if (FlagManager::flagInv == 1)
            {
                FlagManager::flagInv = 0;
            }
        }
    };
    buttonForCallInvWin = new Button("left", "data/images/Button.png", ren, { 1050, 665, 25, 22 },
                                     callInvWin, NULL);
    keyForcCallInvWin = new Keyboard(SDL_SCANCODE_I, callInvWin);
}

UIInfo::~UIInfo()
{
    delete buttonForCallSpecInfo;
    delete buttonForCallInvWin;
    delete keyForCallSpecInfo;
    delete keyForcCallInvWin;
}

void UIInfo::Render()
{
    RenderManager::CopyToRender(infoBlock, ren, 1024, 0, 256, 480);
    RenderManager::CopyToRender(info, ren, 1116, 13, 64, 32);
    RenderManager::CopyToRender(slashhhhhhhhh, ren, 1152, 72, 32, 20);
    RenderManager::CopyToRender(slashhhhhhhhh, ren, 1152, 122, 32, 20);
    RenderManager::CopyToRender(slashhhhhhhhh, ren, 1152, 175, 32, 20);

    if (flagHoverSpec == 1)
        RenderManager::CopyToRender(SPEC, ren, 1230, 220, 30, 25);

    //HP
    RenderManager::CopyToRender(hpBar, ren, 1080, 40, 160, 32, 0, 0, 128, 16);
    RenderManager::CopyToRender(hpText, ren, 1050, 47, 25, 22);

    //Mana
    RenderManager::CopyToRender(mnBar, ren, 1080, 95, 230, 32, 21, 10, 128, 16);
    RenderManager::CopyToRender(mnText, ren, 1050, 99, 25, 22);

    //XP
    RenderManager::CopyToRender(xpBar, ren, 1080, 150, 200, 32, 21, 10, 128, 16);
    RenderManager::CopyToRender(xpText, ren, 1050, 152, 25, 22);

    //Buttons
    buttonForCallSpecInfo->Render();
}

void UIInfo::AlwaysRender()
{
    RenderManager::CopyToRender(versionBLock, ren, 0, 705, 170, 9);
    buttonForCallInvWin->Render();
}

void UIInfo::handleEvents(SDL_Event& eventInUiInfo)
{
    //Buttons
    buttonForCallSpecInfo->handleEvents(eventInUiInfo);
    buttonForCallInvWin->handleEvents(eventInUiInfo);

    //Keyboard
    keyForCallSpecInfo->handleEvents(eventInUiInfo);
    keyForcCallInvWin->handleEvents(eventInUiInfo);

}



UIEquipedItem::UIEquipedItem(SDL_Renderer* renderer) : ren (renderer)
{

}

void UIEquipedItem::Render()
{
    Inventory::it = Inventory::ExistingItems.find(Player::EqItems.WeaponId);
    if (Player::EqItems.WeaponId != -1)
    {
        EquipedItem = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);

        RenderManager::CopyToRender(EquipedItem, ren, 1070, 550, 32, 32);
        SDL_DestroyTexture(EquipedItem);
        EquipedItem = 0;
    }
    Inventory::it = Inventory::ExistingItems.find(Player::EqItems.ArmorId);
    if (Player::EqItems.ArmorId != -1)
    {
        EquipedItem = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);

        RenderManager::CopyToRender(EquipedItem, ren, 1070, 587, 32, 32);
        SDL_DestroyTexture(EquipedItem);
        EquipedItem = 0;
    }
}

void UIEquipedItem::clickForItemsInInv()
{
    int xMouseCoord;
    int yMouseCoord;
    SDL_GetMouseState(&xMouseCoord, &yMouseCoord);
    if (InputManager::MouseInArea(1070, 550, 32, 32, xMouseCoord, yMouseCoord) &&
            Player::EqItems.WeaponId > 0)
    {
        FlagManager::flagUnEquip = 0;
    }
    if (InputManager::MouseInArea(1070, 587, 32, 32, xMouseCoord, yMouseCoord) &&
            Player::EqItems.ArmorId != -1)
    {
        FlagManager::flagUnEquip = 1;
    }
}

UIItem::UIItem(SDL_Renderer* renderer) : ren(renderer)
{
    PATH_IN_FONT = "data/fonts/manaspc.ttf";
    color = { 255, 255, 255, 255 };

    itemBlock = textureManager::LoadTexture("data/images/InfoBlock.png", ren);
    item = FontManager::renderText("Items", PATH_IN_FONT, color, 32, ren);
    INV = FontManager::renderText("INV", PATH_IN_FONT, color, 32, ren);
}

void UIItem::Render()
{
    RenderManager::CopyToRender(itemBlock, ren, 1024, 480, 256, 225);
    RenderManager::CopyToRender(item, ren, 1085, 490, 128, 32);
    RenderManager::CopyToRender(INV, ren, 1048, 648, 27, 22);
}

UIInventory::UIInventory(SDL_Renderer* renderer) : ren(renderer)
{
    SDL_Color color = { 255, 255, 255, 255 };
    const char* PATH_IN_FONT = "data/fonts/manaspc.ttf";

    inventoryBlock = textureManager::LoadTexture("data/images/InfoBlock.png", ren);
    inventoryText = FontManager::renderText("Inventory", PATH_IN_FONT, color, 64, ren);
    auto callDrop{
        []()
        {
            if (FlagManager::flagHaveDrop == false)
            {
                FlagManager::flagHaveDrop = true;
            }
            else if (FlagManager::flagHaveDrop == true)
            {
                FlagManager::flagHaveDrop = false;
            }
        }
    };
    buttonForCallDpor = new Button("left","data/images/Button.png", ren, { 790, 665, 25, 22 }, callDrop , NULL);
}

void UIInventory::Render()
{
    RenderManager::CopyToRender(inventoryBlock, ren, 730, 0, 300, 710);
    RenderManager::CopyToRender(inventoryText, ren, 780, 50, 160, 32);
    buttonForCallDpor->Render();

    for (int i = 0; i < 16; i++)
    {
        if (Inventory::inventoryFace[i] != -1)
        {
            Inventory::it = Inventory::ExistingItems.find(Inventory::inventoryFace[i]);
            item = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
            RenderManager::CopyToRender(item, ren, (780 + 36 * (i % 4)), (100 + ((i / 4) * 50)), 32, 32);
            auto callInvItems{
                [=]()
                {
                    SDL_GetMouseState(&xMouseCoord, &yMouseCoord);
                    for (int i = 0; i < 16; i++)
                    {
                        if (InputManager::MouseInArea((780 + 36 * (i % 4)), (100 + ((i / 4) * 50)), 32, 32, xMouseCoord, yMouseCoord) &&
                                Inventory::inventoryFace[i] != -1 && FlagManager::flagInv == 1)
                        {
                            //std::cout << "Item " + i << std::endl;
                            if (FlagManager::flagHaveDrop == false)
                            {
                                FlagManager::flagEquip = i;
                            }
                            else
                            {
                                FlagManager::flagDrop = i;
                            }
                        }
                    }
                }
            };
            SDL_DestroyTexture(item);
            item = 0;
        }
    }
}

void UIInventory::handleEvents(SDL_Event& eventInInv)
{
    buttonForCallDpor->handleEvents(eventInInv);
}

void UIInventory::clickForItemsInInv()
{
    SDL_GetMouseState(&xMouseCoord, &yMouseCoord);

    for (int i = 0; i < 16; i++)
    {
        if (InputManager::MouseInArea((780 + 36 * (i % 4)), (100 + ((i / 4) * 50)), 32, 32, xMouseCoord, yMouseCoord) &&
                Inventory::inventoryFace[i] != -1 && FlagManager::flagInv == 1)
        {
            if (FlagManager::flagHaveDrop == false)
            {
                FlagManager::flagEquip = i;
            }
            else
            {
                FlagManager::flagDrop = i;
            }
        }
    }

}


