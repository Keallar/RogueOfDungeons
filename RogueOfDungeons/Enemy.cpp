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

void Enemy::Update()
{
	if (EntityPosition::Coords[3] > (EntityPosition::Coords[1] + 32))
	{
		EntityPosition::Coords[3] -= 32;
		FlagManager::flagPlayer = 1;
		//std::cout << EntityPosition::Coords[0] << " , " << EntityPosition::Coords[1] << std::endl;
		//SDL_Delay(400);
	}
	else if (EntityPosition::Coords [3] < (EntityPosition::Coords[1] - 32))
	{
		EntityPosition::Coords[3] += 32;
		FlagManager::flagPlayer = 1;
		//SDL_Delay(400);
	}
	else if (EntityPosition::Coords[2] < (EntityPosition::Coords[0] - 32) )
	{
		EntityPosition::Coords[2] += 32;
		FlagManager::flagPlayer = 1;
		//SDL_Delay(400);
	}
	else if (EntityPosition::Coords[2] > (EntityPosition::Coords[0] + 32) )
	{
		EntityPosition::Coords[2] -= 32;
		FlagManager::flagPlayer = 1;
		//SDL_Delay(400);
	}
	else if (((EntityPosition::Coords[2] == EntityPosition::Coords[0]) && (EntityPosition::Coords[3] == EntityPosition::Coords[1] + 32)) ||
		((EntityPosition::Coords[2] == EntityPosition::Coords[0]) && (EntityPosition::Coords[3] == EntityPosition::Coords[1] - 32)) ||
		((EntityPosition::Coords[3] == EntityPosition::Coords[1]) && (EntityPosition::Coords[2] == EntityPosition::Coords[0] + 32)) ||
		((EntityPosition::Coords[3] == EntityPosition::Coords[1]) && (EntityPosition::Coords[2] == EntityPosition::Coords[0] - 32)))
	{
		if (xanim == 96)
		{
			xanim = 0;
			FlagManager::flagPlayer = 1;
		}
		/*else if (xanim == 64)
		{
			
		}*/
		else
		{
			xanim += 32;
		}
	}
	else
	{
		FlagManager::flagPlayer = 1;
	}
	std::cout << EntityPosition::Coords[2] <<"," << EntityPosition::Coords[3] << "/"<< FlagManager::flagPlayer << std::endl;
}
