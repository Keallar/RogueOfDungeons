#pragma once
#include "SDL.h"
#include <vector>
class Enemy
{
private:
	int HP;
	int DMG;
	int expReward;
	SDL_Renderer* ren;
	SDL_Texture* enemyTexture;
	int xanim= 0, yanim = 0;
	const int rows = 22, cols = 32;
	int enemyLoc[22][32];
public:
	Enemy() = default;
	Enemy(const char* texturesheet, SDL_Renderer* ren, int HealthP, int Damage, int EXPR);
	~Enemy();
	void Update();
	void GetLoc(int arr[22][32]);
	void Render();
	void Attack();
	
};

