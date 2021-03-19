#include "Enemy.h"
#include "Managers.h"
#include "Player.h"
#include <iostream>
#include "EntityPosition.h"
Enemy::Enemy(const char* texturesheet, SDL_Renderer* renderer, int HealthP, int Damage, int EXPR) 
{
	expReward = EXPR;
	HP = HealthP;
	DMG = Damage;
	ren = renderer;
	enemyTexture = textureManager::LoadTexture(texturesheet, ren);
}
Enemy::~Enemy() 
{
	if (HP == 0)
	{
		SDL_DestroyTexture(enemyTexture);
	}
}
void Enemy::Render() 
{
	RenderManager::CopyToRender(enemyTexture, ren, EntityPosition::Coords[2], EntityPosition::Coords[3], 32, 32, xanim, yanim, 32, 32);
}
void Enemy::GetLoc(int arr[22][32]) 
{
	for (int i = 0; i < 22; i++) 
	{
		for (int j = 0; j < 32; j++) 
		{
			enemyLoc[i][j] = arr[i][j];
			if (arr[i][j] == 1) 
			{
				enemyLoc[i][j] = -2;
			}
			if (arr[i][j] == 2) {
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
	EntityPosition::Coords[2] = (rand() % 30 + 1) * 32;
	EntityPosition::Coords[3] = (rand() % 20 + 1) * 32;
	while ((enemyLoc[EntityPosition::Coords[2] / 32][EntityPosition::Coords[3] / 32] == -2) ||
		((enemyLoc[EntityPosition::Coords[2] / 32][EntityPosition::Coords[3] / 32 - 1] != -1) &&
		(enemyLoc[EntityPosition::Coords[2] / 32][EntityPosition::Coords[3] / 32 + 1] != -1) &&
			(enemyLoc[EntityPosition::Coords[2] / 32 - 1][EntityPosition::Coords[3] / 32] != -1) &&
			(enemyLoc[EntityPosition::Coords[2] / 32 + 1][EntityPosition::Coords[3] / 32] != -1)))
	{
		EntityPosition::Coords[2] = (rand() % 30 + 1) * 32;
		EntityPosition::Coords[3] = (rand() % 20 + 1) * 32;
	}
}

bool Enemy::WAY(int ax, int ay, int bx, int by)   // поиск пути из €чейки (ax, ay) в €чейку (bx, by)
{
	int dx[4] = { 1, 0, -1, 0 };   // смещени€, соответствующие сосед€м €чейки
	int dy[4] = { 0, 1, 0, -1 };   // справа, снизу, слева и сверху
	int d, x, y, k;
	bool stop = false;

	if (enemyLoc[ay][ax] == -2 || enemyLoc[by][bx] == -2) return false;  // €чейка (ax, ay) или (bx, by) - стена

	// распространение волны
	d = 0;
	enemyLoc[ay][ax] = 0;            // стартова€ €чейка помечена 0
	do {
		stop = true;               // предполагаем, что все свободные клетки уже помечены
		for (y = 0; y < 22; ++y) 
		{
			for (x = 0; x < 32; ++x)
			{
				if (enemyLoc[y][x] == d)                         // €чейка (x, y) помечена числом d
				{
					for (k = 0; k < 4; ++k)                    // проходим по всем непомеченным сосед€м
					{
						int iy = y + dy[k], ix = x + dx[k];
						if (iy >= 0 && iy < H && ix >= 0 && ix < W &&
							enemyLoc[iy][ix] == BLANK)
						{
							stop = false;              // найдены непомеченные клетки
							enemyLoc[iy][ix] = d + 1;

						}

					}

				}
			}
		}
		d++;
	} while (!stop && enemyLoc[by][bx] == BLANK);
	//if (enemyLoc[bx][by] == BLANK) return false;  // путь не найден
	// восстановление пути
	len = enemyLoc[by][bx];            // длина кратчайшего пути из (ax, ay) в (bx, by)
	x = bx;
	y = by;
	d = len;
	while (d > 0)
	{
		px[d] = x;
		py[d] = y;                   // записываем €чейку (x, y) в путь
		d--;
		for (k = 0; k < 4; ++k)
		{
			int iy = y + dy[k], ix = x + dx[k];
			if (iy >= 0 && iy < H && ix >= 0 && ix < W &&
				enemyLoc[iy][ix] == d)
			{
				x = x + dx[k];
				y = y + dy[k];           // переходим в €чейку, котора€ на 1 ближе к старту
				break;
			}
		}
	}
	px[0] = ax;
	py[0] = ay;                    
	EntityPosition::Coords[2] = px[1] * 32;
	EntityPosition::Coords[3] = py[1] * 32;
	return true;
}

void Enemy::Update()
{
	if ((abs(EntityPosition::Coords[2]/32 - EntityPosition::Coords[0]/32) + abs(EntityPosition::Coords[3]/32 - EntityPosition::Coords[1]/32)) > 1)
		{
		WAY(EntityPosition::Coords[2] / 32, EntityPosition::Coords[3] / 32, EntityPosition::Coords[0] / 32, EntityPosition::Coords[1] / 32);
		Attackflag = 0;
		}
	if ((((EntityPosition::Coords[2] == EntityPosition::Coords[0]) && (EntityPosition::Coords[3] == EntityPosition::Coords[1] + 32)) ||
		((EntityPosition::Coords[2] == EntityPosition::Coords[0]) && (EntityPosition::Coords[3] == EntityPosition::Coords[1] - 32)) ||
		((EntityPosition::Coords[3] == EntityPosition::Coords[1]) && (EntityPosition::Coords[2] == EntityPosition::Coords[0] + 32)) ||
		((EntityPosition::Coords[3] == EntityPosition::Coords[1]) && (EntityPosition::Coords[2] == EntityPosition::Coords[0] - 32)))&&Attackflag == 1)
	{
		if (xanim == 96)
		{
			xanim = 0;
			FlagManager::flagPlayer = 1;
		}
		else
		{
			xanim += 32;
		}
	}
	else
	{
		FlagManager::flagPlayer = 1;
	}
	Attackflag = 1;
}
