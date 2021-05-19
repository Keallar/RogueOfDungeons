#include "UiMain.h"
#include "Managers.h"
#include "EntityPosition.h"
#include <iostream>
#include "Inventory.h"
#include "Player.h"
#include "Enemy.h"
#include "Game.h"

UIInfo::UIInfo(SDL_Renderer* renderer) : ren (renderer)
{
    GameTextures = TextureBase::Instance();

    PATH_IN_FONT = "data/fonts/manaspc.ttf";
    flagHoverSpec = false;

    //Version
    versionBLock = FontManager::renderText("ROGUE OF DUNGEONS V-0.1 ALPHA", PATH_IN_FONT, color, 32, ren);

    infoBlock = GameTextures->GetTexture("InfoBlock");
    info = FontManager::renderText("Info", PATH_IN_FONT, color, 32, ren);

    slashhhhhhhhh = FontManager::renderText("/", PATH_IN_FONT, color, 32, ren);

    SPEC = FontManager::renderText("SPEC", PATH_IN_FONT, color, 32, ren);

    //Mana
    mnBar = GameTextures->GetTexture("ManaBar");
    mnText = FontManager::renderText("MN", PATH_IN_FONT, color, 64, ren);

    //XP
    xpBar = GameTextures->GetTexture("XP");
    xpText = FontManager::renderText("XP", PATH_IN_FONT, color, 64, ren);

    //Level Of Player
    textLevelOfPlayer = FontManager::renderText("Level:", PATH_IN_FONT, color, 32, ren);
    levelOfPlayer = FontManager::renderText("1", PATH_IN_FONT, color, 32, ren);
//    int w, h;
//    SDL_QueryTexture(levelOfPlayer, NULL, NULL, &w, &h);
//    std::cout << w << " " << h << std::endl;

    //Coins
    coinText = FontManager::renderText("Coins: ", PATH_IN_FONT, color, 32, ren);
    coins = FontManager::renderText("0", PATH_IN_FONT, color, 32 ,ren);

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
        [this]()
        {
            if (flagHoverSpec == 0)
                flagHoverSpec = 1;
        }
    };
    auto leaveHoverSpec{
        [this]()
        {
            if (flagHoverSpec == 1)
                flagHoverSpec = 0;
        }
    };
    buttonForCallSpecInfo = new Button("left", GameTextures->GetTexture("Button"), ren , { 1230, 240, 32, 32 },
                                       callSpecOrInfoWin, hoverSpec, leaveHoverSpec);
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
    buttonForCallInvWin = new Button("left", GameTextures->GetTexture("Button"), ren, { 1050, 665, 25, 22 },
                                     callInvWin, NULL, NULL);
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

    //Mana
    RenderManager::CopyToRender(mnBar, ren, 1080, 95, 230, 32, 21, 10, 128, 16);
    RenderManager::CopyToRender(mnText, ren, 1050, 99, 25, 22);

    //XP
    RenderManager::CopyToRender(xpBar, ren, 1080, 150, 200, 32, 21, 10, 128, 16);
    RenderManager::CopyToRender(xpText, ren, 1050, 152, 25, 22);

    //Level of Player
    RenderManager::CopyToRender(textLevelOfPlayer, ren, 1125, 210, 65, 25 );
    RenderManager::CopyToRender(levelOfPlayer, ren, 1187, 212, 21, 32);

    //Coins UNDONE
    RenderManager::CopyToRender(coinText, ren, 1125, 400, 65, 25);
    RenderManager::CopyToRender(coins, ren, 1187, 400, 21, 32);

    //Buttons
    buttonForCallSpecInfo->Render();
}

void UIInfo::AlwaysRender()
{
    RenderManager::CopyToRender(versionBLock, ren, 0, 705, 170, 9);
    buttonForCallInvWin->Render();
}

void UIInfo::Update()
{
    SDL_DestroyTexture(levelOfPlayer);
    levelOfPlayer = 0;
    std::string stringTemp1 = std::to_string(Player::GetLevelOfPlayer(0));
    const char* CHAR_VALUE1 = stringTemp1.c_str();
    levelOfPlayer = FontManager::renderText(CHAR_VALUE1, PATH_IN_FONT, color, 32, ren);

    SDL_DestroyTexture(coins);
    coins = 0;
    std::string stringTemp2 = std::to_string(Player::GetCoinsOfPlayer(0));
    const char* CHAR_VALUE2 = stringTemp2.c_str();
    coins = FontManager::renderText(CHAR_VALUE2, PATH_IN_FONT, color, 32, ren);
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
    Inventory::it = Inventory::ExistingItems.find(Player::EqItems.ArtId);
    if (Player::EqItems.ArtId != -1)
    {
        EquipedItem = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);

        RenderManager::CopyToRender(EquipedItem, ren, 1107, 550, 32, 32);
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
    if (InputManager::MouseInArea(1107, 550, 32, 32, xMouseCoord, yMouseCoord) &&
            Player::EqItems.ArtId != -1)
    {
        FlagManager::flagUnEquip = 2;
    }
}

UIItem::UIItem(SDL_Renderer* renderer) : ren(renderer)
{
    GameTextures = TextureBase::Instance();
    PATH_IN_FONT = "data/fonts/manaspc.ttf";
    color = { 255, 255, 255, 255 };

    itemBlock = GameTextures->GetTexture("InfoBlock");
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
    GameTextures = TextureBase::Instance();

    SDL_Color color = { 255, 255, 255, 255 };
    const char* PATH_IN_FONT = "data/fonts/manaspc.ttf";

    inventoryBlock = GameTextures->GetTexture("InfoBlock");
    inventoryText = FontManager::renderText("Inventory", PATH_IN_FONT, color, 64, ren);
    auto callDrop{
        []()
        {
            if (FlagManager::flagHaveDrop == 0)
            {
                FlagManager::flagHaveDrop = 1;
            }
            else if (FlagManager::flagHaveDrop == 1)
            {
                FlagManager::flagHaveDrop = 0;
            }
        }
    };
    buttonForCallDpor = new Button("left", GameTextures->GetTexture("Button"), ren, { 790, 665, 25, 22 }, callDrop , NULL, NULL);
}

void UIInventory::Render()
{
    RenderManager::CopyToRender(inventoryBlock, ren, 730, 0, 300, 710);
    RenderManager::CopyToRender(inventoryText, ren, 780, 50, 160, 32);
    buttonForCallDpor->Render();

    for (int i = 0; i < INVENTORY_SIZE; i++)
    {
        if (Inventory::inventoryFace[i] != -1)
        {
            Inventory::it = Inventory::ExistingItems.find(Inventory::inventoryFace[i]);
            item = textureManager::LoadTexture((Inventory::it->second)->ItemTexture, ren);
            RenderManager::CopyToRender(item, ren, (770 + 36 * (i % 6)), (100 + ((i / 6) * 50)), 32, 32);
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

    for (int i = 0; i < INVENTORY_SIZE; i++)
    {
        if (InputManager::MouseInArea((770 + 36 * (i % 6)), (100 + ((i / 6) * 50)), 32, 32, xMouseCoord, yMouseCoord) &&
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


