#pragma once
#include "Game.h"
class Enemy
{
private:
	int HP;
	int DMG;
	int expReward;
	SDL_Renderer* ren;
	SDL_Texture* enemyTexture;
	int xpos, ypos, xanim, yanim;
public:
	Enemy(const char* texturesheet, SDL_Renderer* ren, int HealthP, int Damage, int EXPR);
	~Enemy();
	void Update();
	void Render();
};

