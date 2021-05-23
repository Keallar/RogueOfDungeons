#pragma once
#include "Enemy.h"

class BossSummoner : public Enemy
{
public:
    BossSummoner() = default;
    BossSummoner(Enemy* enemy);
    BossSummoner(const char* texturesheet, int framesOfAnimationForAttack,SDL_Renderer* ren, int HealthP, int MaxHealthP, int Damage, int EXPR, int coins, int type, int range);
    virtual void meleeAttackEnemy();
};
