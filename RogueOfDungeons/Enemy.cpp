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
	RenderManager::CopyToRender(enemyTexture, ren, EntityPosition::Coords[2], EntityPosition::Coords[3], 64, 64, xanim, yanim, 32, 32);
}

void Enemy::Update()
{
	if (EntityPosition::Coords[3] > (EntityPosition::Coords[1] + 32))
	{
		EntityPosition::Coords[3] -= 32;
		std::cout << EntityPosition::Coords[0] << " , " << EntityPosition::Coords[1] << std::endl;
	}
	else if (EntityPosition::Coords [3] < (EntityPosition::Coords[1] - 32))
	{
		EntityPosition::Coords[3] += 32;
	}
	else if (EntityPosition::Coords[2] < (EntityPosition::Coords[0] - 32) )
	{
		EntityPosition::Coords[2] += 32;
	}
	else if (EntityPosition::Coords[2] > (EntityPosition::Coords[0] + 32) )
	{
		EntityPosition::Coords[2] -= 32;
	}
}