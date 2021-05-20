#include "UiPlayer.h"
#include "Managers.h"
#include "Player.h"

TextInfo::TextInfo()
{
    GameTextures = TextureBase::Instance();
    PATH_IN_FONT = "data/fonts/manaspc.ttf";
    color = { 255, 255, 255, 255 };
}

TextInfo::~TextInfo()
{
}

HpInfo::HpInfo(SDL_Renderer* renderer) : ren (renderer)
{
    //HP Bar
    hpBar = GameTextures->GetTexture("Hp");
    hpText = FontManager::renderText("HP", PATH_IN_FONT, color, 64, ren);

    std::string stringTemp1 = std::to_string(Player::GetHP(0));
    const char* TEXT_VALUE_CURRENT_HP = stringTemp1.c_str();
    hpCurrent = FontManager::renderText(TEXT_VALUE_CURRENT_HP, PATH_IN_FONT, color, 32, ren);

    std::string stringTemp2 = std::to_string(Player::GetHP(2));
    const char* TEXT_VALUE_MAX = stringTemp2.c_str();
    hpMax = FontManager::renderText(TEXT_VALUE_MAX, PATH_IN_FONT, color, 32, ren);
}

HpInfo::~HpInfo()
{
}

void HpInfo::Update()
{
    std::string stringTemp;
    SDL_DestroyTexture(hpCurrent);
    hpCurrent = 0;
    if (Player::GetHP(0) <= 0)
         stringTemp = std::to_string(0);
    else
         stringTemp = std::to_string(Player::GetHP(0));
    const char* CHAR_VALUE = stringTemp.c_str();
    hpCurrent = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);
}

void HpInfo::UpdateMax()
{
    Player::ChangeMaxHpValue(Player::GetSpecValue(5));
    SDL_DestroyTexture(hpMax);
    hpMax = 0;
    SDL_DestroyTexture(hpCurrent);

    std::string stringTemp1 = std::to_string(Player::GetHP(2));
    const char* CHAR_VALUE1 = stringTemp1.c_str();
    hpMax = FontManager::renderText(CHAR_VALUE1, PATH_IN_FONT, color, 32, ren);

    std::string stringTemp2 = std::to_string(Player::GetHP(0));
    const char* CHAR_VALUE2 = stringTemp2.c_str();
    hpCurrent = FontManager::renderText(CHAR_VALUE2, PATH_IN_FONT, color, 32, ren);
}

void HpInfo::Render()
{
    if (Player::GetHP(0) >= Player::GetHP(2))
    {
        RenderManager::CopyToRender(hpBar, ren, 1080, 40, 160, 32, 0, 0, 128, 16);
    }
    else if ((Player::GetHP(0) >= (Player::GetHP(2) / 4) * 3) &&
             Player::GetHP(0) <= Player::GetHP(2))
    {
        RenderManager::CopyToRender(hpBar, ren, 1080, 40, 160, 32, 0, 16, 128, 16);
    }
    else if ((Player::GetHP(0) <= (Player::GetHP(2) / 4) * 3) &&
             (Player::GetHP(0) >= (Player::GetHP(2) / 4 )* 2))
    {
        RenderManager::CopyToRender(hpBar, ren, 1080, 40, 160, 32, 0, 32, 128, 16);
    }
    else if ((Player::GetHP(0) <= (Player::GetHP(2) / 4) * 2) &&
             (Player::GetHP(0) > 0))
    {
        RenderManager::CopyToRender(hpBar, ren, 1080, 40, 160, 32, 0, 48, 128, 16);
    }
    else if (Player::GetHP(0) == 0)
    {
        RenderManager::CopyToRender(hpBar, ren, 1080, 40, 160, 32, 0, 64, 128, 16);
    }
    RenderManager::CopyToRender(hpText, ren, 1050, 47, 25, 22);
    RenderManager::CopyToRender(hpCurrent, ren, 1120, 72, 32, 20);
    RenderManager::CopyToRender(hpMax, ren, 1180, 72, 32, 20);
}

ManaInfo::ManaInfo(SDL_Renderer* renderer) : ren(renderer)
{
    std::string stringTemp1 = std::to_string(Player::GetMana(0));
    const char* TEXT_VALUE_CURRENT_VALUE = stringTemp1.c_str();
    manaCurrent = FontManager::renderText(TEXT_VALUE_CURRENT_VALUE, PATH_IN_FONT, color, 32, ren);

    std::string stringTemp2 = std::to_string(Player::GetMana(2));
    const char* TEXT_VALUE_MAX = stringTemp2.c_str();
    manaMax = FontManager::renderText(TEXT_VALUE_MAX, PATH_IN_FONT, color, 32, ren);
}

ManaInfo::~ManaInfo()
{
}

void ManaInfo::Update()
{
    SDL_DestroyTexture(manaCurrent);
    manaCurrent = 0;
    std::string stringTemp = std::to_string(Player::GetMana(0));
    const char* CHAR_VALUE = stringTemp.c_str();
    manaCurrent = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);
}

void ManaInfo::UpdateMax()
{
    Player::ChangeMaxManaValue(Player::GetSpecValue(4));
    SDL_DestroyTexture(manaMax);
    manaMax = 0;
    SDL_DestroyTexture(manaCurrent);
    manaCurrent = 0;

    std::string stringTemp1 = std::to_string(Player::GetMana(2));
    const char* CHAR_VALUE1 = stringTemp1.c_str();
    manaMax = FontManager::renderText(CHAR_VALUE1, PATH_IN_FONT, color, 32, ren);

    std::string stringTemp2 = std::to_string(Player::GetMana(0));
    const char* CHAR_VALUE2 = stringTemp2.c_str();
    manaCurrent = FontManager::renderText(CHAR_VALUE2, PATH_IN_FONT, color, 32, ren);


}

void ManaInfo::Render()
{
    RenderManager::CopyToRender(manaCurrent, ren, 1120, 122, 32, 20);
    RenderManager::CopyToRender(manaMax, ren, 1180, 122, 32, 20);
}

ExpInfo::ExpInfo(SDL_Renderer* renderer) : ren (renderer)
{
    std::string stringTemp1 = std::to_string(Player::GetEXP(0));
    const char* TEXT_VALUE_CURRENT_VALUE = stringTemp1.c_str();
    expCurrent = FontManager::renderText(TEXT_VALUE_CURRENT_VALUE, PATH_IN_FONT, color, 32, ren);

    std::string stringTemp2 = std::to_string(Player::GetEXP(2));
    const char* TEXT_VALUE_MAX = stringTemp2.c_str();
    expMax = FontManager::renderText(TEXT_VALUE_MAX, PATH_IN_FONT, color, 32, ren);
}

ExpInfo::~ExpInfo()
{
}

void ExpInfo::Update()
{
    SDL_DestroyTexture(expCurrent);
    expCurrent = 0;
    std::string stringTemp = std::to_string(Player::GetEXP(0));
    const char* CHAR_VALUE = stringTemp.c_str();
    expCurrent = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);
}

void ExpInfo::UpdateMax()
{
    SDL_DestroyTexture(expMax);
    expMax = 0;
    std::string stringTemp = std::to_string(Player::GetEXP(2));
    const char* CHAR_VALUE = stringTemp.c_str();
    expMax = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);
}

void ExpInfo::Render()
{
    RenderManager::CopyToRender(expCurrent, ren, 1120, 175, 32, 20);
    RenderManager::CopyToRender(expMax, ren, 1180, 175, 32, 20);
}

UISpecifications::UISpecifications(SDL_Renderer* renderer) : ren (renderer)
{
    color = { 255, 255, 255, 255 };

    GameTextures = TextureBase::Instance();

    //Specifications
    specBlock = GameTextures->GetTexture("InfoBlock");
    specifcation = FontManager::renderText("Specifications", PATH_IN_FONT, color, 64, ren);
    buttonForCallInfoWin = new Button(GameTextures->GetTexture("Button"), ren, { 1230, 240, 32, 32 });

    //STR
    STR = FontManager::renderText("STR", PATH_IN_FONT, color, 64, ren);
    valueSTR = FontManager::renderText("1", PATH_IN_FONT, color, 32, ren);
    auto incSTR{
        []()
        {
            if (FlagManager::flagSTR == 0 &&
                    FlagManager::flagUiSpec == 1 &&
                    FlagManager::flagPointOfSpec == 1)
            {
                Player::ChangeValueSpecs(1);
            }
        }
    };
    buttonForIncPlayerSTR = new Button("left", GameTextures->GetTexture("Button"), ren, { 1230, 50, 16, 20 }, incSTR, NULL, NULL);
    keyForIncSTR = new Keyboard(SDL_SCANCODE_1, incSTR);
    //DEX
    DEX = FontManager::renderText("DEX", PATH_IN_FONT, color, 64, ren);
    valueDEX = FontManager::renderText("1", PATH_IN_FONT, color, 32, ren);
    auto incDEX{
        []()
        {
            if (FlagManager::flagDEX == 0 &&
                    FlagManager::flagUiSpec == 1 &&
                    FlagManager::flagPointOfSpec == 1)
            {
                Player::ChangeValueSpecs(2);
            }
        }
    };
    buttonForIncPlayerDEX = new Button("left", GameTextures->GetTexture("Button"), ren, { 1230, 80, 16, 20 }, incDEX, NULL, NULL);
    keyForIncDEX = new Keyboard(SDL_SCANCODE_2, incDEX);
    //INT
    INT = FontManager::renderText("INT", PATH_IN_FONT, color, 64, ren);
    valueINT = FontManager::renderText("1", PATH_IN_FONT, color, 32, ren);
    auto incINT{
        []()
        {
            if (FlagManager::flagINT == 0 &&
                    FlagManager::flagUiSpec == 1 &&
                    FlagManager::flagPointOfSpec == 1)
            {
                Player::ChangeValueSpecs(3);
            }
        }
    };
    buttonForIncPlayerINT = new Button("left", GameTextures->GetTexture("Button"), ren, { 1230, 110, 16, 20 }, incINT, NULL, NULL);
    keyForIncINT = new Keyboard(SDL_SCANCODE_3, incINT);
    //WSD
    WSD = FontManager::renderText("WSD", PATH_IN_FONT, color, 64, ren);
    valueWSD = FontManager::renderText("1", PATH_IN_FONT, color, 32, ren);
    auto incWSD{
        []()
        {
            if (FlagManager::flagWSD == 0 &&
                    FlagManager::flagUiSpec == 1 &&
                    FlagManager::flagPointOfSpec == 1)
            {
                Player::ChangeValueSpecs(4);
            }
        }
    };
    buttonForIncPlayerWSD = new Button("left", GameTextures->GetTexture("Button"), ren, { 1230, 140, 16, 20 }, incWSD, NULL, NULL);
    keyForIncWSD = new Keyboard(SDL_SCANCODE_4, incWSD);
    //PHS
    PHS = FontManager::renderText("PHS", PATH_IN_FONT, color, 64, ren);
    valuePHS = FontManager::renderText("1", PATH_IN_FONT, color, 32, ren);
    auto incPHS{
        []()
        {
            if (FlagManager::flagPHS == 0 &&
                    FlagManager::flagUiSpec == 1 &&
                    FlagManager::flagPointOfSpec == 1)
            {
                Player::ChangeValueSpecs(5);
            }
        }
    };
    buttonForIncPlayerPHS = new Button("left",GameTextures->GetTexture("Button"), ren, { 1230, 170, 16, 20 }, incPHS, NULL, NULL);
    keyForIncPHS = new Keyboard(SDL_SCANCODE_5, incPHS);
    //LCK
    LCK = FontManager::renderText("LCK", PATH_IN_FONT, color, 64, ren);
    valueLCK = FontManager::renderText("1", PATH_IN_FONT, color, 32, ren);

    auto incLCK{
        []()
        {
            if (FlagManager::flagLCK == 0 &&
                    FlagManager::flagUiSpec == 1 &&
                    FlagManager::flagPointOfSpec == 1)
            {
                Player::ChangeValueSpecs(6);
            }
        }
    };
    buttonForIncPlayerLCK = new Button("left", GameTextures->GetTexture("Button"), ren, { 1230, 200, 16, 20 }, incLCK, NULL, NULL);
    keyForIncLCK = new Keyboard(SDL_SCANCODE_6, incLCK);

    //Points
    textPointOfSpec = FontManager::renderText("Points:", PATH_IN_FONT, color, 32, ren);
    pointOfSpec = FontManager::renderText("0", PATH_IN_FONT, color, 32, ren);

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
    SDL_DestroyTexture(specifcation);
    SDL_DestroyTexture(STR);
    SDL_DestroyTexture(valueSTR);
    SDL_DestroyTexture(DEX);
    SDL_DestroyTexture(valueDEX);
    SDL_DestroyTexture(INT);
    SDL_DestroyTexture(valueINT);
    SDL_DestroyTexture(WSD);
    SDL_DestroyTexture(valueWSD);
    SDL_DestroyTexture(PHS);
    SDL_DestroyTexture(valuePHS);
    SDL_DestroyTexture(LCK);
    SDL_DestroyTexture(valueLCK);
    SDL_DestroyTexture(textPointOfSpec);
    SDL_DestroyTexture(pointOfSpec);
    SDL_DestroyTexture(one);
    SDL_DestroyTexture(two);
    SDL_DestroyTexture(three);
    SDL_DestroyTexture(four);
    SDL_DestroyTexture(five);
    SDL_DestroyTexture(six);
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
    //Points
    RenderManager::CopyToRender(textPointOfSpec, ren, 1150, 400, 80, 32);
    RenderManager::CopyToRender(pointOfSpec, ren, 1230, 403, 21, 32);
}

void UISpecifications::Update()
{
    SDL_DestroyTexture(pointOfSpec);
    pointOfSpec = 0;
    std::string stringTemp = std::to_string(Player::GetPointOfSpec(0));
    const char* CHAR_VALUE = stringTemp.c_str();
    pointOfSpec = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);
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
