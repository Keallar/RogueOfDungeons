#include "UiEnemy.h"
#include <iostream>

UIEnemy::UIEnemy(SDL_Renderer* renderer, Enemy* enemy):
    ren (renderer), tempEnemy(enemy)
{
    GameTextures = TextureBase::Instance();
    PATH_IN_FONT = "data/fonts/manaspc.ttf";
    color = { 255, 255, 255, 255 };
    std::string stringValue1 = std::to_string(enemy->GetHpEnemy(0));
    const char* TEXT_VALUE_CURRENT = stringValue1.c_str();
    enemyTex = FontManager::renderText("Enemy", PATH_IN_FONT, color, 32, ren);
    hpEnemyBar = GameTextures->GetTexture("EnemyBar");
    hpTextEnemy = FontManager::renderText("HP", PATH_IN_FONT, color, 64, ren);
    hpCurrentTextEnemy = FontManager::renderText(TEXT_VALUE_CURRENT, PATH_IN_FONT, color, 32, ren);
    slashhhhhhhhh = FontManager::renderText("/", PATH_IN_FONT, color, 32, ren);
    std::string stringValue2 = std::to_string(enemy->GetHpEnemy(2));
    const char* TEXT_VALUE_MAX = stringValue2.c_str();
    hpMaxEnemy = FontManager::renderText(TEXT_VALUE_MAX, PATH_IN_FONT, color, 32, ren);
    auto callEnemyInfo{
        []()
        {
            if (FlagManager::flagUiEnemy == 0)
            {
                FlagManager::flagUiEnemy = 1;
            }
            else if (FlagManager::flagUiEnemy == 1)
            {
                FlagManager::flagUiEnemy = 0;
            }
        }
    };
    buttonForCallEnemyInfo = new Button("right", NULL, ren, {tempEnemy->Rect.x,tempEnemy ->Rect.y, 32, 32}, callEnemyInfo, NULL, NULL);
}

UIEnemy::~UIEnemy() {
    SDL_DestroyTexture(enemyTex);
    SDL_DestroyTexture(hpTextEnemy);
    SDL_DestroyTexture(hpCurrentTextEnemy);
    SDL_DestroyTexture(slashhhhhhhhh);
    SDL_DestroyTexture(hpMaxEnemy);
    delete buttonForCallEnemyInfo;
}

void UIEnemy::Render()
{
    RenderManager::CopyToRender(enemyTex, ren, 1116, 250, 64, 32);
    RenderManager::CopyToRender(hpEnemyBar, ren, 1080, 290, 190, 45, 20, 5, 256, 32);
    RenderManager::CopyToRender(hpTextEnemy, ren, 1050, 300, 25, 22);
    RenderManager::CopyToRender(hpCurrentTextEnemy, ren, 1120, 325, 32, 20);
    RenderManager::CopyToRender(slashhhhhhhhh, ren, 1152, 325, 32, 20);
    RenderManager::CopyToRender(hpMaxEnemy, ren, 1180, 325, 32, 20);
}

void UIEnemy::Update(Enemy* enemy)
{
    tempEnemy = enemy;
    SDL_DestroyTexture(hpCurrentTextEnemy);
    hpCurrentTextEnemy = 0;
    std::string stringTemp = std::to_string(tempEnemy->GetHpEnemy(0));
    const char* CHAR_VALUE = stringTemp.c_str();
    hpCurrentTextEnemy = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);

    buttonForCallEnemyInfo->updateCoords(tempEnemy->Rect.x, tempEnemy->Rect.y);
}

void UIEnemy::UpdateMax(Enemy* enemy)
{
    tempEnemy = enemy;
    SDL_DestroyTexture(hpMaxEnemy);
    hpMaxEnemy = 0;
    std::string stringTemp = std::to_string(tempEnemy->GetHpEnemy(2));
    const char* CHAR_VALUE = stringTemp.c_str();
    hpMaxEnemy = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);
}

void UIEnemy::handleEvents(SDL_Event &eventInUIEnemy)
{
    buttonForCallEnemyInfo->handleEvents(eventInUIEnemy);
}
