#include "Enemy.h"
#include "Managers.h"
#include "Player.h"
#include <iostream>
#include "EntityPosition.h"
#include "Inventory.h"
#include "Animation.h"

using namespace std;

int Enemy::HP = 0;
int Enemy::HpMax = 0;

Enemy::Enemy(const char* texturesheet, int framesOfAnimationForAttack, SDL_Renderer* renderer, int HealthP, int MaxHealthP, int Damage, int EXPR)
{
	generate = -1;
	expReward = EXPR;
	HP = HealthP;
	HpMax = MaxHealthP;
	DMG = Damage;
	ren = renderer;
	enemyTexture = textureManager::LoadTexture(texturesheet, ren);
	enemyAnimation = new Animation(ren, enemyTexture);
	framesOfAnimForAttack = framesOfAnimationForAttack;
	completeAnimation = 0;
}
Enemy::~Enemy() 
{
	SDL_DestroyTexture(enemyTexture);
}

void Enemy::Render() 
{
	enemyAnimation->Render(EntityPosition::Coords[2], EntityPosition::Coords[3]);
}

void Enemy::clean()
{
	SDL_DestroyTexture(enemyTexture);
}

int Enemy::GetHpEnemy(int numOfHp)
{
	switch (numOfHp)
	{
	case 0:
		return HP;
	case 1:
		return HpMax;
	default:
		break;
	}
}

void Enemy::CheckHpEnemy()
{
	if (Enemy::HP <= 0)
	{
		static int iter = 0;
		if (iter == 0)
		{
			FlagManager::flagCheckHpEnemy = 1;
			HpMax = HP;
			iter++;
			FlagManager::flagEnemy = 0;
			FlagManager::flagMeleeAttackEnemy = 0;
		}
		else if (iter == 1)
		{
			FlagManager::flagEnemy = 0;
			FlagManager::flagMeleeAttackEnemy = 0;
		}

	}
	else if (Enemy::HP != Enemy::HpMax && FlagManager::flagCheckHpEnemy == 0)
	{
		FlagManager::flagCheckHpEnemy = 1;
	}
	else if (Enemy::HP == Enemy::HpMax && FlagManager::flagCheckHpEnemy == 1)
	{
		FlagManager::flagCheckHpEnemy = 0;
	}
}

void Enemy::ChahgeHpEnemy(int valueOfChangingHp)
{
	if ((FlagManager::flagMeleeAttackPlayer == 1 || 
		FlagManager::flagRangeAttack == 1))
	{
		Enemy::HP -= valueOfChangingHp;
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

void Enemy::GetEnemyFirstCoords() {
	EntityPosition::Coords[2] = (rand() % 30) * 32;
	EntityPosition::Coords[3] = (rand() % 20) * 32;
	if (generate != 4 && generate != 5) {
		while ((enemyLoc[EntityPosition::Coords[3] / 32][EntityPosition::Coords[2] / 32] == -2) ||
			((enemyLoc[EntityPosition::Coords[3] / 32][(EntityPosition::Coords[2] / 32) - 1] != -1) ||
			(enemyLoc[EntityPosition::Coords[3] / 32][(EntityPosition::Coords[2] / 32) + 1] != -1) ||
			(enemyLoc[(EntityPosition::Coords[3] / 32) - 1][EntityPosition::Coords[2] / 32] != -1) ||
			(enemyLoc[(EntityPosition::Coords[3] / 32) + 1][EntityPosition::Coords[2] / 32] != -1)))
		{
			EntityPosition::Coords[2] = (rand() % 30) * 32;
			EntityPosition::Coords[3] = (rand() % 20) * 32;
		}
	}
	else {
		while ((enemyLoc[EntityPosition::Coords[3] / 32][EntityPosition::Coords[2] / 32] == -2))
		{
			EntityPosition::Coords[2] = (rand() % 30) * 32;
			EntityPosition::Coords[3] = (rand() % 20) * 32;
		}
	}
}

bool Enemy::WAY(int ax, int ay, int bx, int by)   // ����� ���� �� ������ (ax, ay) � ������ (bx, by)
{
	int dx[4] = { 1, 0, -1, 0 };   // ��������, ��������������� ������� ������
	int dy[4] = { 0, 1, 0, -1 };   // ������, �����, ����� � ������
	int d, x, y, k;
	bool stop = false;

	if (enemyLoc[ay][ax] == -2 || enemyLoc[by][bx] == -2) return false;  // ������ (ax, ay) ��� (bx, by) - �����

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
	EntityPosition::Coords[2] = px[1] * 32;
	EntityPosition::Coords[3] = py[1] * 32;
	return true;
}

void Enemy::Update()
{
	/*if ((abs(EntityPosition::Coords[2] / 32 - EntityPosition::Coords[0] / 32) +
		abs(EntityPosition::Coords[3] / 32 - EntityPosition::Coords[1] / 32)) < 14){*/
		//�������� enemy (����� ����������� ����)
		if ((abs(EntityPosition::Coords[2] / 32 - EntityPosition::Coords[0] / 32) +
			abs(EntityPosition::Coords[3] / 32 - EntityPosition::Coords[1] / 32)) > 1 &&
			FlagManager::flagPlayer == 0 && FlagManager::flagEnemy == 1)
		{
			WAY(EntityPosition::Coords[2] / 32, EntityPosition::Coords[3] / 32,
				EntityPosition::Coords[0] / 32, EntityPosition::Coords[1] / 32);

				FlagManager::flagPlayer = 1;
				FlagManager::flagEnemy = 0;
		}

		Enemy::meleeAttackEnemy();

		Enemy::CheckHpEnemy();
	//}
}

void Enemy::attackOfEnemy()
{
	//UNDONE ��������� ���� �������
	if (completeAnimation == 0)
	{
		completeAnimation = enemyAnimation->animationPlusForX(framesOfAnimForAttack, completeAnimation);
	}
	else if (completeAnimation == 1)
	{
		completeAnimation = 0;
		Player::ChangeHpValue(-Enemy::enemyDamageCalculation());
		std::cout << "Heat" << std::endl;
		Player::playerTurn();
	}
}

void Enemy::enemyTurn()
{
	FlagManager::flagPlayer = 0;
	FlagManager::flagMeleeAttackPlayer = 0;
	FlagManager::flagRangeAttack = 0;
	FlagManager::flagEnemy = 1;
	FlagManager::flagMeleeAttackEnemy = 1;
}

void Enemy::meleeAttackEnemy()
{
	//����� enemy ������, ���� ����� ������ ������� 
	if ((((EntityPosition::Coords[2] == EntityPosition::Coords[0]) &&
		(EntityPosition::Coords[3] == EntityPosition::Coords[1] + 32)) ||
		((EntityPosition::Coords[2] == EntityPosition::Coords[0]) &&
			(EntityPosition::Coords[3] == EntityPosition::Coords[1] - 32)) ||
		((EntityPosition::Coords[3] == EntityPosition::Coords[1]) &&
			(EntityPosition::Coords[2] == EntityPosition::Coords[0] + 32)) ||
		((EntityPosition::Coords[3] == EntityPosition::Coords[1]) &&
			(EntityPosition::Coords[2] == EntityPosition::Coords[0] - 32))) &&
		(FlagManager::flagMeleeAttackEnemy == 1 && FlagManager::flagEnemy == 1))
	{
		Enemy::enemyTurn();
		
		Enemy::attackOfEnemy();
	}
	else
	{
		Player::playerTurn();
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