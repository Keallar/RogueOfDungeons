#include "rangeenemy.h"
#include "EntityPosition.h"
#include "Player.h"
#include <iostream>
#include "Managers.h"
#include "Inventory.h"
#include "Animation.h"
#include "Level.h"
RangeEnemy::RangeEnemy(const char* texturesheet, int framesOfAnimationForAttack, SDL_Renderer* ren,
                       int HealthP, int MaxHealthP, int Damage, int EXPR, int coins, int type):
    Enemy(texturesheet, framesOfAnimationForAttack, ren, HealthP, MaxHealthP, Damage, EXPR, coins, type)
{

}
RangeEnemy::RangeEnemy(Enemy* enemy):Enemy(enemy)
{

}
void RangeEnemy::meleeAttackEnemy()
{
    int PlPosx = EntityPosition::Coords[0] / 32, PlPosy = EntityPosition::Coords[1] / 32, EnPosx = (Rect.x) / 32, EnPosy = (Rect.y) / 32;
    bool blankflag = true;
    if ((abs(EntityPosition::Coords[0] - Rect.x) == 0)) // разделил чтобы потом проверять на наличие стен
    {
        if (PlPosy > EnPosy)
        {
            for (int i = PlPosy; i > EnPosy; i--)
            {
                if (enemyLoc[i][PlPosx] == -2)
                {
                    blankflag = false;
                }
            }
        }
        else
        {
            for (int i = EnPosy; i > PlPosy; i--)
            {
                if (enemyLoc[i][PlPosx] == -2)
                {
                    blankflag = false;
                }
            }
        }
    }
    else if (/*abs*/(EntityPosition::Coords[1] - Rect.y == 0))
    {
        if (PlPosx > EnPosx)
        {
            for (int i = PlPosx; i > EnPosx; i--)
            {
                if (enemyLoc[PlPosy][i] == -2)
                {
                    blankflag = false;
                }
            }
        }
        else
        {
            for (int i = EnPosx; i > PlPosx; i--)
            {
                if (enemyLoc[PlPosy][i] == -2)
                {
                    blankflag = false;
                }
            }
        }
    }
    else
    {
        int x, y;
        float k = -(((float)(EnPosy - PlPosy) / (PlPosx - EnPosx)));
        float b = -((float)(EnPosx * PlPosy - PlPosx * EnPosy) / (PlPosx - EnPosx));
        if (PlPosx > EnPosx)
        {
            for (x = PlPosx; x > EnPosx; x--)
            {
                if (enemyLoc[(int)(k * x + b)][x] == -2)
                {
                    blankflag = false;
                }
            }
        }
        else if (PlPosx < EnPosx)
        {
            for (x = EnPosx; x > PlPosx; x--)
            {
                if (enemyLoc[(int)(k * x + b)][x] == -2)
                {
                    blankflag = false;
                }
            }
        }
        if (PlPosy < EnPosy)
        {
            for (y = EnPosy; y > PlPosy; y--)
            {
                if (enemyLoc[y][(int)((y - b) / k)] == -2)
                {
                    blankflag = false;
                }
            }
        }
        else if (PlPosy > EnPosy)
        {
            for (y = PlPosy; y > EnPosy; y--)
            {
                if (enemyLoc[y][(int)((y - b) / k)] == -2)
                {
                    blankflag = false;
                }
            }
        }
    }
    if (blankflag == true)
    {
        Player::ChangeHpValue(-this->enemyDamageCalculation());
    }
}
