#pragma once
#include "SDL.h"
#include <vector>
#include "GameObject.h"
#include "Animation.h"
#include "Coins.h"

class Enemy : public GameObject
{
protected:
	Uint32 Timer;
    Uint32 timer;
    Uint32 timer2;
	bool temp;
    bool temp1;
	int DMG;
	int expReward;
	SDL_Renderer* ren;
	SDL_Texture* enemyTexture;
	int xanim= 0, yanim = 0;
	//���-�� ������ ��� ��������
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
	const int W = 32;         // ������ �������� ����
	const int H = 22;         // ������ �������� ����
	const int WALL = -2;         // ������������ ������
	const int BLANK = -1;         // ��������� ������������ ������
	int px[13 * 13], py[13 * 13];      // ���������� �����, ��������  ����
	int len;                       // ����� ����
	int outputDamageEnemy;
    int currentFrameOfEnemyAnim;
	Animation* enemyAnimation;
    Coins* coin;
    int valueOfCoins;
public:
	int generate = 0;
	Enemy() = default;
    Enemy(const char* texturesheet, int framesOfAnimationForAttack,SDL_Renderer* ren, int HealthP, int MaxHealthP, int Damage, int EXPR, int coins);
	void Update() override;
    void Render() override;
	void GetLoc(int arr[22][32]);
	void GetWay();
	bool WAY(int ax, int ay, int bx, int by);
	void GetEnemyFirstCoords();
	
    virtual void meleeAttackEnemy();
	void attackOfEnemy();
	int enemyDamageCalculation();
	void enemyTurn(); 
	int getDamageEnemy();
    int GetHpEnemy(int numOfHp);
    void CheckHpEnemy();
	void ChahgeHpEnemy(int valueOfChangingHp);
    void CheckTimer();
    Coins* GetCoin();
};

