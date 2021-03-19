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
	int count = 0;
	int testCoordx;
	int testCoordy;
	int firstmovx;
	int firstmovy;
	int move;
	int debugcount = 0;
	const int W = 32;         // ������ �������� ����
	const int H = 22;         // ������ �������� ����
	const int WALL = -2;         // ������������ ������
	const int BLANK = -1;         // ��������� ������������ ������

	int px[13 * 13], py[13 * 13];      // ���������� �����, ��������  ����
	int len;                       // ����� ����

public:
	Enemy() = default;
	Enemy(const char* texturesheet, SDL_Renderer* ren, int HealthP, int Damage, int EXPR);
	~Enemy();
	void Update();
	void GetLoc(int arr[22][32]);
	void Render();
	void GetWay();
	bool WAY(int ax, int ay, int bx, int by);
	void GetEnemyFirstCoords();
};

