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

    //Version
    versionBLock = FontManager::renderText("ROGUE OF DUNGEONS V-0.1 ALPHA", PATH_IN_FONT, color, 32, ren);

    infoBlock = textureManager::LoadTexture("data/images/InfoBlock.png", ren);
    info = FontManager::renderText("Info", PATH_IN_FONT, color, 32, ren);

    slashhhhhhhhh = FontManager::renderText("/", PATH_IN_FONT, color, 32, ren);

    //SPEC = FontManager::renderText("SPEC", PATH_IN_FONT, color, 32, ren);

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
    buttonForCallSpecInfo = new Button("left", "data/images/Button.png", ren , { 1230, 240, 32, 32 }, callSpecOrInfoWin, NULL);
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
    auto hoverSpec{
        [=]()
        {
            const char* PATH_IN_FONT = "data/fonts/manaspc.ttf";
            SDL_Color color = { 255, 255, 255, 255 };
            SDL_Texture* SPEC = FontManager::renderText("SPEC", PATH_IN_FONT, color, 32, ren);

            if (SPEC != nullptr)
            {
                RenderManager::CopyToRender(SPEC, Game::renderer, 1230, 220, 30, 25);
                std::cout << "Render Hover SPEC" << std::endl;
            }
        }
    };
    buttonForCallInvWin = new Button("left", "data/images/Button.png", ren, { 1050, 665, 25, 22 }, callInvWin, hoverSpec);
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

    //RenderManager::CopyToRender(SPEC, ren, 1230, 220, 30, 25);

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

UISpecifications::UISpecifications(SDL_Renderer* renderer) : ren (renderer)
{
    color = { 255, 255, 255, 255 };

    //Specifications
    specBlock = textureManager::LoadTexture("data/images/InfoBlock.png", ren);
    specifcation = FontManager::renderText("Specifications", PATH_IN_FONT, color, 64, ren);
    buttonForCallInfoWin = new Button("data/images/Button.png", ren, { 1230, 240, 32, 32 });

    //STR
    STR = FontManager::renderText("STR", PATH_IN_FONT, color, 64, ren);
    valueSTR = FontManager::renderText("1", PATH_IN_FONT, color, 32, ren);
    auto incSTR{
        []()
        {
            if (FlagManager::flagSTR == 0 && FlagManager::flagUiSpec == 1)
            {
                Player::ChangeValueSpecs(1);
            }
        }
    };
    buttonForIncPlayerSTR = new Button("left", "data/images/Button.png", ren, { 1230, 50, 16, 20 }, incSTR, NULL);
    keyForIncSTR = new Keyboard(SDL_SCANCODE_1, incSTR);
    //DEX
    DEX = FontManager::renderText("DEX", PATH_IN_FONT, color, 64, ren);
    valueDEX = FontManager::renderText("1", PATH_IN_FONT, color, 32, ren);
    auto incDEX{
        []()
        {
            if (FlagManager::flagDEX == 0 && FlagManager::flagUiSpec == 1)
            {
                Player::ChangeValueSpecs(2);
            }
        }
    };
    buttonForIncPlayerDEX = new Button("left", "data/images/Button.png", ren, { 1230, 80, 16, 20 }, incDEX, NULL);
    keyForIncDEX = new Keyboard(SDL_SCANCODE_2, incDEX);
    //INT
    INT = FontManager::renderText("INT", PATH_IN_FONT, color, 64, ren);
    valueINT = FontManager::renderText("1", PATH_IN_FONT, color, 32, ren);
    auto incINT{
        []()
        {
            if (FlagManager::flagINT == 0 && FlagManager::flagUiSpec == 1)
            {
                Player::ChangeValueSpecs(3);
            }
        }
    };
    buttonForIncPlayerINT = new Button("left", "data/images/Button.png", ren, { 1230, 110, 16, 20 }, incINT, NULL);
    keyForIncINT = new Keyboard(SDL_SCANCODE_3, incINT);
    //WSD
    WSD = FontManager::renderText("WSD", PATH_IN_FONT, color, 64, ren);
    valueWSD = FontManager::renderText("1", PATH_IN_FONT, color, 32, ren);
    auto incWSD{
        []()
        {
            if (FlagManager::flagWSD == 0 && FlagManager::flagUiSpec == 1)
            {
                Player::ChangeValueSpecs(4);
            }
        }
    };
    buttonForIncPlayerWSD = new Button("left", "data/images/Button.png", ren, { 1230, 140, 16, 20 }, incWSD, NULL);
    keyForIncWSD = new Keyboard(SDL_SCANCODE_4, incWSD);
    //PHS
    PHS = FontManager::renderText("PHS", PATH_IN_FONT, color, 64, ren);
    valuePHS = FontManager::renderText("1", PATH_IN_FONT, color, 32, ren);
    auto incPHS{
        []()
        {
            if (FlagManager::flagPHS == 0 && FlagManager::flagUiSpec == 1)
            {
                Player::ChangeValueSpecs(5);
            }
        }
    };
    buttonForIncPlayerPHS = new Button("left","data/images/Button.png", ren, { 1230, 170, 16, 20 }, incPHS, NULL);
    keyForIncPHS = new Keyboard(SDL_SCANCODE_5, incPHS);
    //LCK
    LCK = FontManager::renderText("LCK", PATH_IN_FONT, color, 64, ren);
    valueLCK = FontManager::renderText("1", PATH_IN_FONT, color, 32, ren);

    auto incLCK{
        []()
        {
            if (FlagManager::flagLCK == 0 && FlagManager::flagUiSpec == 1)
            {
                Player::ChangeValueSpecs(6);
            }
        }
    };
    buttonForIncPlayerLCK = new Button("left", "data/images/Button.png", ren, { 1230, 200, 16, 20 }, incLCK, NULL);
    keyForIncLCK = new Keyboard(SDL_SCANCODE_6, incLCK);

    //numbers
    one = FontManager::renderText("(1)", PATH_IN_FONT, color, 64, ren);
    two = FontManager::renderText("(2)", PATH_IN_FONT, color, 64, ren);
    three = FontManager::renderText("(3)", PATH_IN_FONT, color, 64, ren);
    four = FontManager::renderText("(4)", PATH_IN_FONT, color, 64, ren);
    five = FontManager::renderText("(5)", PATH_IN_FONT, color, 64, ren);
    six = FontManager::renderText("(6)", PATH_IN_FONT, color, 64, ren);
}

UISpecifications::~UISpecifications()
{
    delete buttonForCallInfoWin;
    delete buttonForIncPlayerSTR;
    delete buttonForIncPlayerDEX;
    delete buttonForIncPlayerINT;
    delete buttonForIncPlayerWSD;
    delete buttonForIncPlayerPHS;
    delete buttonForIncPlayerLCK;
    delete keyForIncSTR;
    delete keyForIncDEX;
    delete keyForIncINT;
    delete keyForIncWSD;
    delete keyForIncPHS;
    delete keyForIncLCK;
}

void UISpecifications::Render()
{
    //Specifications
    RenderManager::CopyToRender(specBlock, ren, 1024, 0, 256, 480);
    RenderManager::CopyToRender(specifcation, ren, 1075, 13, 160, 32);
    buttonForCallInfoWin->Render();
    //STR
    RenderManager::CopyToRender(STR, ren, 1050, 50, 64, 20);
    buttonForIncPlayerSTR->Render();
    RenderManager::CopyToRender(valueSTR, ren, 1180, 50, 16, 20);
    RenderManager::CopyToRender(one, ren, 1250, 50, 16, 20);
    //DEX
    RenderManager::CopyToRender(DEX, ren, 1050, 80, 64, 20);
    buttonForIncPlayerDEX->Render();
    RenderManager::CopyToRender(valueDEX, ren, 1180, 80, 16, 20);
    RenderManager::CopyToRender(two, ren, 1250, 80, 16, 20);
    //INT
    RenderManager::CopyToRender(INT, ren, 1050, 110, 64, 20);
    buttonForIncPlayerINT->Render();
    RenderManager::CopyToRender(valueINT, ren, 1180, 110, 16, 20);
    RenderManager::CopyToRender(three, ren, 1250, 110, 16, 20);
    //WSD
    RenderManager::CopyToRender(WSD, ren, 1050, 140, 64, 20);
    buttonForIncPlayerWSD->Render();
    RenderManager::CopyToRender(valueWSD, ren, 1180, 140, 16, 20);
    RenderManager::CopyToRender(four, ren, 1250, 140, 16, 20);
    //PHS
    RenderManager::CopyToRender(PHS, ren, 1050, 170, 64, 20);
    buttonForIncPlayerPHS->Render();
    RenderManager::CopyToRender(valuePHS, ren, 1180, 170, 16, 20);
    RenderManager::CopyToRender(five, ren, 1250, 170, 16, 20);
    //LCK
    RenderManager::CopyToRender(LCK, ren, 1050, 200, 64, 20);
    buttonForIncPlayerLCK->Render();
    RenderManager::CopyToRender(valueLCK, ren, 1180, 200, 16, 20);
    RenderManager::CopyToRender(six, ren, 1250, 200, 16, 20);
}

void UISpecifications::Update()
{

}

void UISpecifications::Update(int value, int num)
{
    switch (num)
    {
    case 1:
    {
        SDL_DestroyTexture(valueSTR);
        valueSTR = 0;
        std::string stringTemp = std::to_string(value);
        const char* CHAR_VALUE = stringTemp.c_str();
        valueSTR = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);
        break;
    }
    case 2:
    {
        SDL_DestroyTexture(valueDEX);
        valueDEX = 0;
        std::string stringTemp = std::to_string(value);
        const char* CHAR_VALUE = stringTemp.c_str();
        valueDEX = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);
        break;
    }
    case 3:
    {
        SDL_DestroyTexture(valueINT);
        valueINT = 0;
        std::string stringTemp = std::to_string(value);
        const char* CHAR_VALUE = stringTemp.c_str();
        valueINT = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);
        break;
    }
    case 4:
    {
        SDL_DestroyTexture(valueWSD);
        valueWSD = 0;
        std::string stringTemp = std::to_string(value);
        const char* CHAR_VALUE = stringTemp.c_str();
        valueWSD = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);
        break;
    }
    case 5:
    {
        SDL_DestroyTexture(valuePHS);
        valuePHS = 0;
        std::string stringTemp = std::to_string(value);
        const char* CHAR_VALUE = stringTemp.c_str();
        valuePHS = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);
        break;
    }
    case 6:
    {
        SDL_DestroyTexture(valueLCK);
        valueLCK = 0;
        std::string stringTemp = std::to_string(value);
        const char* CHAR_VALUE = stringTemp.c_str();
        valueLCK = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);
        break;
    }
    default:
        break;
    }
}

void UISpecifications::UpdateMax()
{

}

void UISpecifications::handleEvents(SDL_Event& eventInSpec)
{
    buttonForIncPlayerSTR->handleEvents(eventInSpec);
    buttonForIncPlayerDEX->handleEvents(eventInSpec);
    buttonForIncPlayerINT->handleEvents(eventInSpec);
    buttonForIncPlayerWSD->handleEvents(eventInSpec);
    buttonForIncPlayerPHS->handleEvents(eventInSpec);
    buttonForIncPlayerLCK->handleEvents(eventInSpec);
    keyForIncSTR->handleEvents(eventInSpec);
    keyForIncDEX->handleEvents(eventInSpec);
    keyForIncINT->handleEvents(eventInSpec);
    keyForIncWSD->handleEvents(eventInSpec);
    keyForIncPHS->handleEvents(eventInSpec);
    keyForIncLCK->handleEvents(eventInSpec);
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


UIEnemyInfo::UIEnemyInfo(SDL_Renderer* renderer, Enemy* enemy):
    ren (renderer), tempEnemy(enemy)
{
    PATH_IN_FONT = "data/fonts/manaspc.ttf";
    color = { 255, 255, 255, 255 };
    std::string stringValue1 = std::to_string(enemy->GetHpEnemy(0));
    const char* TEXT_VALUE_CURRENT = stringValue1.c_str();
    enemyTex = FontManager::renderText("Enemy", PATH_IN_FONT, color, 32, ren);
    hpEnemyBar = textureManager::LoadTexture("data/images/EnemyBar.png", ren);
    hpTextEnemy = FontManager::renderText("HP", PATH_IN_FONT, color, 64, ren);
    hpCurrentTextEnemy = FontManager::renderText(TEXT_VALUE_CURRENT, PATH_IN_FONT, color, 32, ren);
    slashhhhhhhhh = FontManager::renderText("/", PATH_IN_FONT, color, 32, ren);
    std::string stringValue2 = std::to_string(enemy->GetHpEnemy(1));
    const char* TEXT_VALUE_MAX = stringValue2.c_str();
    hpMaxEnemy = FontManager::renderText(TEXT_VALUE_MAX, PATH_IN_FONT, color, 32, ren);
    auto callEnemyInfo{
        []()
        {
            if (FlagManager::flagUiEnemy == 0)
            {
                FlagManager::flagUiEnemy = 1;
                std::cout << "EnemyInfo\n";
            }
            else if (FlagManager::flagUiEnemy == 1)
            {
                FlagManager::flagUiEnemy = 0;
            }
        }
    };
    buttonForCallEnemyInfo = new Button("right", NULL, ren, {tempEnemy->Rect.x,tempEnemy ->Rect.y, 32, 32}, callEnemyInfo, NULL);
}

void UIEnemyInfo::Render()
{
    RenderManager::CopyToRender(enemyTex, ren, 1116, 250, 64, 32);
    RenderManager::CopyToRender(hpEnemyBar, ren, 1080, 290, 190, 45, 20, 5, 256, 32);
    RenderManager::CopyToRender(hpTextEnemy, ren, 1050, 300, 25, 22);
    RenderManager::CopyToRender(hpCurrentTextEnemy, ren, 1120, 325, 32, 20);
    RenderManager::CopyToRender(slashhhhhhhhh, ren, 1152, 325, 32, 20);
    RenderManager::CopyToRender(hpMaxEnemy, ren, 1180, 325, 32, 20);
}

void UIEnemyInfo::Update()
{
    //tempEnemy = enemy;
    SDL_DestroyTexture(hpCurrentTextEnemy);
    hpCurrentTextEnemy = 0;
    std::string stringTemp = std::to_string(tempEnemy->GetHpEnemy(0));
    const char* CHAR_VALUE = stringTemp.c_str();
    hpCurrentTextEnemy = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);

    buttonForCallEnemyInfo->updateCoords(tempEnemy->Rect.x, tempEnemy->Rect.y);
}

void UIEnemyInfo::UpdateMax(Enemy* enemy)
{
    tempEnemy = enemy;
    SDL_DestroyTexture(hpCurrentTextEnemy);
    hpMaxEnemy = 0;
    std::string stringTemp = std::to_string(tempEnemy->GetHpEnemy(2));
    const char* CHAR_VALUE = stringTemp.c_str();
    hpMaxEnemy = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);
}

void UIEnemyInfo::handleEvents(SDL_Event &eventInUiEnemyInfo)
{
    buttonForCallEnemyInfo->handleEvents(eventInUiEnemyInfo);
}
