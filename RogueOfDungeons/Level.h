﻿#pragma once
#include <vector>
#include "Enemy.h"
#include "Player.h"
#include "UI.h"
#include "GameObject.h"

struct MouseCoords
{
	int x;
	int y;
}; 

class Level 
{
private:
	int textureLocation[22][32];
	int Location[22][32];
	//int Location2[22][32];
	SDL_Texture* TileTexture;
	SDL_Texture* PlayBackground;
	SDL_Renderer* ren;
	Player* player;
	Enemy* enemy;
	UIInfo* uiInfo;
	UIInventory* uiInventory;
	UIEnemyInfo* uiEnemy;
	UISpecifications* uiSpec;
	std::vector <Enemy> enemies; //����� ����� ��� ������
	std::vector <GameObject> textures; //����� ����� ��� ������ � ������ ��������
	MouseCoords mouseCoord;
	void CreateChunk(int x, int y);
	std::vector<std::pair<int, int>> pop_front(std::vector<std::pair<int, int>> vec);
	void ChunkGenerationMethod();
	void OtherGeneration();
	bool Search(std::vector<std::pair<int, int>> vector, int x, int y);
	int SearchNum(std::vector<std::pair<int, int>> vector, int x, int y);

public:
	bool flagTB;
	Level(SDL_Renderer* renderer);
	~Level();
	void Update();
	void Start();
	void Render();
	void handleEvents();
	void Generate();
	int GetLocation(int x, int y);
	void ChangeLocation(int x, int y);
};