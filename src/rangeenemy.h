#ifndef RANGEENEMY_H
#define RANGEENEMY_H

#include "Enemy.h"

class RangeEnemy : public Enemy
{
public:
    RangeEnemy() = default;
    RangeEnemy(const char* texturesheet, int framesOfAnimationForAttack,SDL_Renderer* ren, int HealthP, int MaxHealthP, int Damage, int EXPR);
    virtual void meleeAttackEnemy();
};

#endif // RANGEENEMY_H
