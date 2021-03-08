#pragma once
#include <vector>
#include "Enemy.h"
#include "Player.h"
#include "UI.h"
#include "GameObject.h"

class Level 
{
private:
	//int Location[22][32];
	SDL_Texture* TileTexture;
	SDL_Texture* PlayBackground;
	SDL_Renderer* ren;
	Player* player;
	Enemy* enemy;
	UI* ui;
	std::vector <Enemy> enemies; //����� ����� ��� ������
	std::vector <GameObject> textures; //����� ����� ��� ������ � ������ ��������
public:
	bool flagTB;
	bool flagPlayer;
	bool flagEnemy;
	Level(SDL_Renderer* renderer);
	~Level();
	void Update();
	void Start();
	void Render();
};