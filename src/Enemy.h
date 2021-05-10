#pragma once
#include "SDL.h"
#include <vector>
#include "GameObject.h"
#include "Animation.h"
#include "Coins.h"
#include <string.h>

class Enemy : public GameObject
{
protected:
	Uint32 Timer;
	bool temp;
	int DMG;
	int expReward;
	SDL_Renderer* ren;
	SDL_Texture* enemyTexture;
	int xanim= 0, yanim = 0;
	// ол-во кадров дл€ анимации
	int framesOfAnimForAttack;
	int framesOfAnimForMove;
	int framesOfAnimaForIdle;
    int HP = 0;
    int prevHp = 0;
    int HpMax = 0;
	const int rows = 22, cols = 32;
	int enemyLoc[22][32];
	int count = 0;
	int move;
	const int W = 32;         // ширина рабочего пол€
	const int H = 22;         // высота рабочего пол€
	const int WALL = -2;         // непроходима€ €чейка
	const int BLANK = -1;         // свободна€ непомеченна€ €чейка
	int px[13 * 13], py[13 * 13];      // координаты €чеек, вход€щих  путь
	int len;                       // длина пути
	int outputDamageEnemy;
	bool completeEnemyAnimation;
	Animation* enemyAnimation;
    Coins* coin;
    int valueOfCoins;
    int Type;
public:
	int generate = 0;
	Enemy() = default;
    Enemy(Enemy *enemy);
    Enemy(const char* texturesheet, int framesOfAnimationForAttack, SDL_Renderer* ren, int HealthP, int MaxHealthP, int Damage, int EXPR, int coins, int type);
	void Update() override;
    void Render() override;
	void GetLoc(int arr[22][32]);
	void GetWay();
	bool WAY(int ax, int ay, int bx, int by);
	void GetEnemyFirstCoords();
    int GetTypeName();
    virtual void meleeAttackEnemy();
	void attackOfEnemy();
	int enemyDamageCalculation();
	void enemyTurn(); 
	int getDamageEnemy();
    int GetHpEnemy(int numOfHp);
    void CheckHpEnemy();
	void ChahgeHpEnemy(int valueOfChangingHp);
    Coins* GetCoin();
};

