#pragma once
#include "SDL.h"
class Enemy
{
private:
	static int HP;
	static int DMG;
	static int expReward;
	SDL_Renderer* ren;
	SDL_Texture* enemyTexture;
	int xanim= 0, yanim = 0;
public:
	Enemy() = default;
	Enemy(const char* texturesheet, SDL_Renderer* ren, int HealthP, int Damage, int EXPR);
	~Enemy();
	void Update();
	void Render();
	void Attack();
};

