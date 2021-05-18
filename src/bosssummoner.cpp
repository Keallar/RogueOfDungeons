#include "bosssummoner.h"
#include "EntityPosition.h"
#include "Player.h"
#include <iostream>
#include "Enemy.h"
BossSummoner::BossSummoner(const char* texturesheet, int framesOfAnimationForAttack, SDL_Renderer* ren, int HealthP, int MaxHealthP, int Damage, int EXPR, int coins, int type):Enemy(texturesheet, framesOfAnimationForAttack, ren, HealthP, MaxHealthP, Damage, EXPR, coins, type)
{

}
BossSummoner::BossSummoner(Enemy* enemy):Enemy(enemy)
{

}
void BossSummoner::meleeAttackEnemy()
{
    DidMeAttacked = true;
}
