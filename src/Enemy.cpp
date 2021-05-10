#include "Enemy.h"
#include "Managers.h"
#include "Player.h"
#include <iostream>
#include "EntityPosition.h"
#include "Inventory.h"

using namespace std;

Enemy::Enemy(const char* texturesheet, int framesOfAnimationForAttack,
             SDL_Renderer* renderer, int HealthP, int MaxHealthP, int Damage, int EXPR, int coins, int type):
    GameObject(texturesheet, renderer)
{
    ren = renderer;
    HP = HealthP;
    HpMax = MaxHealthP;
    prevHp = MaxHealthP;
    temp = false;
    Timer = 0;
    generate = -1;
    expReward = EXPR;
    HP = HealthP;
    HpMax = MaxHealthP;
    DMG = Damage;
    valueOfCoins = coins;
    coin = new Coins (GameTextures->GetTexture("Coin"), ren, valueOfCoins, 1);
    enemyTexture = textureManager::LoadTexture(texturesheet, ren);
    enemyAnimation = new Animation(ren, enemyTexture);
    framesOfAnimForAttack = framesOfAnimationForAttack;
    completeEnemyAnimation = 0;
    Type = type;
}
Enemy::Enemy(Enemy* enemy)
{
    ren = enemy->ren;

    HpMax = enemy->HpMax;
    HP = HpMax;
    prevHp = HpMax;
    temp = false;
    Timer = 0;
    generate = -1;
    expReward = enemy->expReward;
    DMG = enemy->DMG;
    valueOfCoins = enemy->valueOfCoins;
    coin = new Coins ("data/images/Coin->png", ren, valueOfCoins, 1);
    enemyTexture = enemy->enemyTexture;
    enemyAnimation = new Animation(ren, enemyTexture);
    framesOfAnimForAttack = enemy->framesOfAnimForAttack;
    completeEnemyAnimation = 0;
    Type = enemy->Type;
}
void Enemy::Render()
{
    enemyAnimation->Render(Rect.x, Rect.y);
}

int Enemy::GetHpEnemy(int numOfHp)
{
    switch (numOfHp)
    {
    case 0:
        return HP;
    case 1:
        return prevHp;
    case 2:
        return HpMax;
    default:
        break;
    }
}

Coins* Enemy::GetCoin()
{
    return coin;
}

void Enemy::CheckHpEnemy()
{
    if (HP <= 0)
    {
        int iter = 0;
        if (iter == 0)
        {
            FlagManager::flagCheckHpEnemy = 1;
            HpMax = HP;
            iter++;
            FlagManager::flagTurn = 0;
            FlagManager::flagMeleeAttackEnemy = 0;
        }
        else if (iter == 1)
        {
            FlagManager::flagTurn = 0;
            FlagManager::flagMeleeAttackEnemy = 0;
        }

    }
    else if (HP != prevHp && FlagManager::flagCheckHpEnemy == 0)
    {
        FlagManager::flagCheckHpEnemy = 1;
        Enemy::prevHp = HP;
    }
    else if (HP == prevHp && FlagManager::flagCheckHpEnemy == 1)
    {
        FlagManager::flagCheckHpEnemy = 0;
    }
}

void Enemy::ChahgeHpEnemy(int valueOfChangingHp)
{
    if ((FlagManager::flagMeleeAttackPlayer == 1 ||
         FlagManager::flagRangeAttackPlayer == 1) && HP != 0 &&
            HP <= HpMax)
    {
        HP += valueOfChangingHp;
        cout << "HpEnemy Changing" << endl;
    }
}

void Enemy::GetLoc(int arr[22][32]) 
{
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            enemyLoc[i][j] = arr[i][j];
            if (arr[i][j] >= 1)
            {
                enemyLoc[i][j] = -2;
            }
            if (arr[i][j] == 0)
            {
                enemyLoc[i][j] = -1;
            }
        }
    }
}

void Enemy::GetEnemyFirstCoords()
{
    Rect.x = (rand() % 30) * 32;
    Rect.y = (rand() % 20) * 32;
    if (generate != 4 && generate != 5) {
        while ((enemyLoc[Rect.y / 32][Rect.x / 32] == -2) ||
               ((enemyLoc[Rect.y / 32][(Rect.x / 32) - 1] != -1) ||
                (enemyLoc[Rect.y / 32][(Rect.x / 32) + 1] != -1) ||
                (enemyLoc[(Rect.y / 32) - 1][Rect.x / 32] != -1) ||
                (enemyLoc[(Rect.y / 32) + 1][Rect.x / 32] != -1)))
        {
            Rect.x = (rand() % 30) * 32;
            Rect.y = (rand() % 20) * 32;
        }
    }
    else
    {
        while (enemyLoc[Rect.y / 32][Rect.x / 32] == -2)
        {
            Rect.x = (rand() % 30) * 32;
            Rect.y = (rand() % 20) * 32;
        }
    }
    coin->SetRectCoords(Rect.x, Rect.y);
}

bool Enemy::WAY(int ax, int ay, int bx, int by)   // ����� ���� �� ������ (ax, ay) � ������ (bx, by)
{
    int dx[4] = { 1, 0, -1, 0 };   // ��������, ��������������� ������� ������
    int dy[4] = { 0, 1, 0, -1 };   // ������, �����, ����� � ������
    int d, x, y, k;
    bool stop = false;

    if (enemyLoc[ay][ax] == -2 || enemyLoc[by][bx] == -2)
        return false;  // ������ (ax, ay) ��� (bx, by) - �����

    // ��������������� �����
    d = 0;
    enemyLoc[ay][ax] = 0;            // ��������� ������ �������� 0
    do {
        stop = true;               // ������������, ��� ��� ��������� ������ ��� ��������
        for (y = 0; y < 22; ++y)
        {
            for (x = 0; x < 32; ++x)
            {
                if (enemyLoc[y][x] == d)                         // ������ (x, y) �������� ������ d
                {
                    for (k = 0; k < 4; ++k)                    // �������� �� ���� ������������ �������
                    {
                        int iy = y + dy[k], ix = x + dx[k];
                        if (iy >= 0 && iy < H && ix >= 0 && ix < W &&
                                enemyLoc[iy][ix] == BLANK)
                        {
                            stop = false;              // ������� ������������ ������
                            enemyLoc[iy][ix] = d + 1;
                        }
                    }
                }
            }
        }
        d++;
    } while (!stop && enemyLoc[by][bx] == BLANK);
    //if (enemyLoc[bx][by] == BLANK) return false;  // ���� �� ������
    // �������������� ����
    len = enemyLoc[by][bx];            // ����� ����������� ���� �� (ax, ay) � (bx, by)
    x = bx;
    y = by;
    d = len;
    while (d > 0)
    {
        px[d] = x;
        py[d] = y;                   // ���������� ������ (x, y) � ����
        d--;
        for (k = 0; k < 4; ++k)
        {
            int iy = y + dy[k], ix = x + dx[k];
            if (iy >= 0 && iy < H && ix >= 0 && ix < W &&
                    enemyLoc[iy][ix] == d)
            {
                x = x + dx[k];
                y = y + dy[k];           // ��������� � ������, ������� �� 1 ����� � ������
                break;
            }
        }
    }
    px[0] = ax;
    py[0] = ay;
    //�������� ������� enemy
    if (FlagManager::flagMeleeAttackEnemy == 0)
    {
        Rect.x = px[1] * 32;
        Rect.y = py[1] * 32;
    }
    return true;
}

void Enemy::Update()
{
    if ((abs(EntityPosition::Coords[0] - this->Rect.x)/32 +
         abs(EntityPosition::Coords[1] - this->Rect.y)/32) < 9)
    {
        meleeAttackEnemy();
        if ((abs(Rect.x / 32 - EntityPosition::Coords[0] / 32) +
             abs(Rect.y / 32 - EntityPosition::Coords[1] / 32)) > 1)
        {
            WAY(Rect.x / 32, Rect.y / 32, EntityPosition::Coords[0] / 32, EntityPosition::Coords[1] / 32);
            coin->SetRectCoords(Rect.x, Rect.y);
        }
    }
    CheckHpEnemy();
    if (currentFrameOfEnemyAnim == framesOfAnimForAttack - 1 &&
            FlagManager::flagTimerTurn == 0)
        FlagManager::flagTimerTurn = 1;
}

void Enemy::attackOfEnemy(bool damage)
{
    if (currentFrameOfEnemyAnim == framesOfAnimForAttack - 1)
    {
        std::cout << "Chance of trick" << std::endl;
        if (FlagManager::flagTimerTurn == 0)
        {
            std::cout << "Delay Melee Attack" << std::endl;
            currentFrameOfEnemyAnim = enemyAnimation->animationPlusForX(framesOfAnimForAttack);
        }
    }
    else if (currentFrameOfEnemyAnim == framesOfAnimForAttack &&
             damage == false)
    {
        temp1 = false;
        temp = false;
        currentFrameOfEnemyAnim = enemyAnimation->animationPlusForX(framesOfAnimForAttack);
        std::cout << "Hit1" << std::endl;
        Player::playerTurn();
    }
    else if (currentFrameOfEnemyAnim == framesOfAnimForAttack &&
             damage == true)
    {
        temp1 = false;
        temp = false;
        currentFrameOfEnemyAnim = enemyAnimation->animationPlusForX(framesOfAnimForAttack);
        Player::ChangeHpValue(-Enemy::enemyDamageCalculation());
        std::cout << "Hit2" << std::endl;
        Player::playerTurn();
    }
    else if (currentFrameOfEnemyAnim < framesOfAnimForAttack)
    {
        currentFrameOfEnemyAnim = enemyAnimation->animationPlusForX(framesOfAnimForAttack);
        Enemy::enemyTurn();
    }
}

void Enemy::enemyTurn()
{
    FlagManager::flagTurn = 1;
    FlagManager::flagInAreaOfAnemy = 1;
    FlagManager::flagMeleeAttackPlayer = 0;
    FlagManager::flagRangeAttackPlayer = 0;
    FlagManager::flagMeleeAttackEnemy = 1;
}

void Enemy::meleeAttackEnemy()
{
    if ((((Rect.x == EntityPosition::Coords[0]) &&
          (Rect.y == EntityPosition::Coords[1] + 32)) ||
         ((Rect.x == EntityPosition::Coords[0]) &&
          (Rect.y == EntityPosition::Coords[1] - 32)) ||
         ((Rect.y == EntityPosition::Coords[1]) &&
          (Rect.x == EntityPosition::Coords[0] + 32)) ||
         ((Rect.y == EntityPosition::Coords[1]) &&
          (Rect.x == EntityPosition::Coords[0] - 32))))
    {

        if (temp == false)
        {
            Timer = SDL_GetTicks();
            temp = true;
        }
        Uint32 Timer2 = SDL_GetTicks();
        Enemy::enemyTurn();
        if (Timer2 - Timer >= 100 && temp == true)
        {
            Enemy::attackOfEnemy(true);
            Timer = Timer2;
        }
    }
    else if ((((Rect.x == EntityPosition::Coords[0]) &&
               (Rect.y == EntityPosition::Coords[1] + 64)) ||
              ((Rect.x == EntityPosition::Coords[0]) &&
               (Rect.y == EntityPosition::Coords[1] - 64)) ||
              ((Rect.y == EntityPosition::Coords[1]) &&
               (Rect.x == EntityPosition::Coords[0] + 64)) ||
              ((Rect.y == EntityPosition::Coords[1]) &&
               (Rect.x == EntityPosition::Coords[0] - 64)) ||
              ((Rect.x == EntityPosition::Coords[0] - 32) &&
               (Rect.y == EntityPosition::Coords[1] + 32)) ||
              ((Rect.x == EntityPosition::Coords[0] + 32) &&
               (Rect.y == EntityPosition::Coords[1] + 32)) ||
              ((Rect.x == EntityPosition::Coords[0] + 32) &&
               (Rect.y == EntityPosition::Coords[1] - 32)) ||
              ((Rect.x == EntityPosition::Coords[0] - 32) &&
               (Rect.y == EntityPosition::Coords[1] - 32))) &&
             FlagManager::flagMeleeAttackEnemy == 1)
    {
        if (temp == false)
        {
            Timer = SDL_GetTicks();
            temp = true;
        }
        Uint32 Timer2 = SDL_GetTicks();
        Enemy::enemyTurn();
        if (Timer2 - Timer >= 100 && temp == true)
        {
            Enemy::attackOfEnemy(false);
            Timer = Timer2;
        }
    }
}

int Enemy::getDamageEnemy()
{
    return DMG;
}

int Enemy::enemyDamageCalculation()
{
    if (Player::EqItems.equipedArmor != nullptr)
        outputDamageEnemy = getDamageEnemy() - Player::EqItems.equipedArmor->DEF;
    else
        outputDamageEnemy = getDamageEnemy();
    return outputDamageEnemy;
}
int Enemy::GetTypeName()
{
    return Type;
}
