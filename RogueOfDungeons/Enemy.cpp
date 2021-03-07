#include "Enemy.h"
#include "Managers.h"
#include "Player.h"
#include <iostream>
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
	RenderManager::CopyToRender(enemyTexture, ren, Coords[2], Coords[3], 64, 64, xanim, yanim, 32, 32);
}

void Enemy::Update()
{
	if (Coords[3] > (Coords[1] + 32))
	{
		Coords[3] -= 32;
		std::cout << Coords[0] << " , " << Coords[1] << std::endl;
	}
	else if (Coords [3] < (Coords[1] - 32))
	{
		Coords[3] += 32;
	}
	else if (Coords[2] < (Coords[0] - 32) )
	{
		Coords[2] += 32;
	}
	else if (Coords[2] > (Coords[0] + 32) )
	{
		Coords[2] -= 32;
	}
}