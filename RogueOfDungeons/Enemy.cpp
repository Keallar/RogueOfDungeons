#include "Enemy.h"
#include "Managers.h"
#include "Player.h"

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
	RenderManager::CopyToRender(enemyTexture, ren, xpos, ypos, 128, 128, xanim, yanim, 32, 32);
}

void Enemy::Update()
{
}