#ifndef UIENEMY_H
#define UIENEMY_H
#include "Managers.h"
#include <SDL.h>
#include "Enemy.h"
#include "Buttons.h"
#include "TextureBase.h"


class UIEnemy
{
private:
    TextureBase* GameTextures;
    SDL_Renderer* ren;
    const char* PATH_IN_FONT;
    SDL_Color color;
    Enemy* tempEnemy;
    SDL_Texture* enemyTex;
    SDL_Texture* hpEnemyBar;
    SDL_Texture* hpTextEnemy;
    SDL_Texture* hpCurrentTextEnemy;
    SDL_Texture* hpMaxEnemy;
    SDL_Texture* slashhhhhhhhh;
    Button* buttonForCallEnemyInfo;
public:
    UIEnemy(SDL_Renderer* renderer, Enemy* enemy);
    ~UIEnemy();
    void Render();
    void Update(Enemy* enemy);
    void UpdateMax(Enemy* enemy);
    void handleEvents(SDL_Event &eventInUIEnemy);
};


#endif // UIENEMY_H
