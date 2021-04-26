#include "UiPlayer.h"
#include "Managers.h"
#include "Player.h"

TextInfo::TextInfo()
{
    PATH_IN_FONT = "data/fonts/manaspc.ttf";
    color = { 255, 255, 255, 255 };
}

TextInfo::~TextInfo()
{

}

HpInfo::HpInfo(SDL_Renderer* renderer) : ren (renderer)
{
    std::string stringTemp1 = std::to_string(Player::GetHP(0));
    const char* TEXT_VALUE_CURRENT_HP = stringTemp1.c_str();
    hpText = FontManager::renderText(TEXT_VALUE_CURRENT_HP, PATH_IN_FONT, color, 32, ren);

    std::string stringTemp2 = std::to_string(Player::GetHP(2));
    const char* TEXT_VALUE_MAX = stringTemp2.c_str();
    hpMax = FontManager::renderText(TEXT_VALUE_MAX, PATH_IN_FONT, color, 32, ren);
}

HpInfo::~HpInfo()
{

}

void HpInfo::Update()
{
    SDL_DestroyTexture(hpText);
    hpText = 0;
    std::string stringTemp = std::to_string(Player::GetHP(0));
    const char* CHAR_VALUE = stringTemp.c_str();
    hpText = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);
}

void HpInfo::UpdateMax()
{
    Player::ChangeMaxHpValue();
    SDL_DestroyTexture(hpMax);
    hpMax = 0;
    SDL_DestroyTexture(hpText);

    std::string stringTemp1 = std::to_string(Player::GetHP(2));
    const char* CHAR_VALUE1 = stringTemp1.c_str();
    hpMax = FontManager::renderText(CHAR_VALUE1, PATH_IN_FONT, color, 32, ren);

    std::string stringTemp2 = std::to_string(Player::GetHP(0));
    const char* CHAR_VALUE2 = stringTemp2.c_str();
    hpText = FontManager::renderText(CHAR_VALUE2, PATH_IN_FONT, color, 32, ren);
}

void HpInfo::Render()
{
    RenderManager::CopyToRender(hpText, ren, 1120, 72, 32, 20);
    RenderManager::CopyToRender(hpMax, ren, 1180, 72, 32, 20);
}

ManaInfo::ManaInfo(SDL_Renderer* renderer) : ren(renderer)
{
    std::string stringTemp1 = std::to_string(Player::GetMana(0));
    const char* TEXT_VALUE_CURRENT_VALUE = stringTemp1.c_str();
    manaText = FontManager::renderText(TEXT_VALUE_CURRENT_VALUE, PATH_IN_FONT, color, 32, ren);

    std::string stringTemp2 = std::to_string(Player::GetMana(2));
    const char* TEXT_VALUE_MAX = stringTemp2.c_str();
    manaMax = FontManager::renderText(TEXT_VALUE_MAX, PATH_IN_FONT, color, 32, ren);
}

ManaInfo::~ManaInfo()
{

}

void ManaInfo::Update()
{
    SDL_DestroyTexture(manaText);
    manaText = 0;
    std::string stringTemp = std::to_string(Player::GetMana(0));
    const char* CHAR_VALUE = stringTemp.c_str();
    manaText = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);
}

void ManaInfo::UpdateMax()
{
    Player::ChangeMaxManaValue();
    SDL_DestroyTexture(manaMax);
    manaMax = 0;
    SDL_DestroyTexture(manaText);
    manaText = 0;

    std::string stringTemp1 = std::to_string(Player::GetMana(2));
    const char* CHAR_VALUE1 = stringTemp1.c_str();
    manaMax = FontManager::renderText(CHAR_VALUE1, PATH_IN_FONT, color, 32, ren);

    std::string stringTemp2 = std::to_string(Player::GetMana(0));
    const char* CHAR_VALUE2 = stringTemp2.c_str();
    manaText = FontManager::renderText(CHAR_VALUE2, PATH_IN_FONT, color, 32, ren);


}

void ManaInfo::Render()
{
    RenderManager::CopyToRender(manaText, ren, 1120, 122, 32, 20);
    RenderManager::CopyToRender(manaMax, ren, 1180, 122, 32, 20);
}

ExpInfo::ExpInfo(SDL_Renderer* renderer) : ren (renderer)
{
    std::string stringTemp1 = std::to_string(Player::GetEXP(0));
    const char* TEXT_VALUE_CURRENT_VALUE = stringTemp1.c_str();
    expText = FontManager::renderText(TEXT_VALUE_CURRENT_VALUE, PATH_IN_FONT, color, 32, ren);

    std::string stringTemp2 = std::to_string(Player::GetEXP(2));
    const char* TEXT_VALUE_MAX = stringTemp2.c_str();
    expMax = FontManager::renderText(TEXT_VALUE_MAX, PATH_IN_FONT, color, 32, ren);
}

ExpInfo::~ExpInfo()
{

}

void ExpInfo::Update()
{
    SDL_DestroyTexture(expText);
    expText = 0;
    std::string stringTemp = std::to_string(Player::GetEXP(0));
    const char* CHAR_VALUE = stringTemp.c_str();
    expText = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);
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
    RenderManager::CopyToRender(expText, ren, 1120, 175, 32, 20);
    RenderManager::CopyToRender(expMax, ren, 1180, 175, 32, 20);
}


