#pragma once
#include "Game.h"
#include "Level.h"
#include "Managers.h"
#include <ctime>
#include "UI.h"
#include <vector>
#include <iostream>

Level::Level(SDL_Renderer* renderer)
{
	ren = renderer;
	TileTexture = textureManager::LoadTexture("images/Tiles.png", ren);
	PlayBackground = textureManager::LoadTexture("images/Playback.png", ren);
	player = new Player("images/Hero.png", ren);
	FlagManager::flagPlayer = 0;
	enemy = new Enemy("images/Turtle.png", ren, 10, 3, 4);
	FlagManager::flagEnemy = 0;
	uiInfo = new UIInfo(ren);
	//FlagManager::flagUI = 0;
	uiInventory = new UIInventory(ren);
	uiEnemy = new UIEnemyInfo(ren);
	uiSpec = new UISpecifications(ren);
	for (int i = 0; i < 22; i++) 
	{
		for (int j = 0; j < 32; j++)
		{
			textureLocation[i][j] = 1;
		}
	}
}

Level::~Level()
{
	delete player;
	delete enemy;
	delete uiInfo;
	delete uiInventory;
	delete uiEnemy;
	delete uiSpec;
}
void Level::Update()
{
	if (FlagManager::flagPlayer == 1)
	{
		player->Update();	
	}
	if (FlagManager::flagPlayer == 0)
	{
		enemy->Update();
		SDL_Delay(150);
	}
}

void Level::Start()
{
	//FlagManager::flagUI = 1;
	Level::flagTB = 1;
	FlagManager::flagPlayer = 1;
	Generate();
	FlagManager::flagEnemy = 0;
	
	player->GetLevel(Location);
	player->GetPlayerFirstCoords();
}

void Level::Render()
{
	RenderManager::CopyToRender(PlayBackground, ren);
	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			if (textureLocation[i][j] == 0)
			{
				RenderManager::SetTile(j * 32, i * 32, 2, ren, TileTexture);
			}
			else
			{
				RenderManager::SetTile(j * 32, i * 32, 6, ren, TileTexture);
			}
			if (textureLocation[i][j] == 2) {
				RenderManager::SetTile(j * 32, i * 32, 7, ren, TileTexture);
			}
			if (textureLocation[i][j] == 3) {
				RenderManager::SetTile(j * 32, i * 32, 3, ren, TileTexture);
			}
			if (textureLocation[i][j] == 4) {
				RenderManager::SetTile(j * 32, i * 32, 1, ren, TileTexture);
			}
			if (textureLocation[i][j] == 5) {
				RenderManager::SetTile(j * 32, i * 32, 9, ren, TileTexture);
			}
			if (textureLocation[i][j] == 6) {
				RenderManager::SetTile(j * 32, i * 32, 4, ren, TileTexture);
			}
		}
	}
	player->Render();
	enemy->Render();
	uiInfo->Render();
	uiInventory->Render();
	uiEnemy->Render();
}

//Вызов окошка с характеристиками
//void Level::handleEvents()
//{
//	SDL_Event eventSpecifications;
//	while (SDL_PollEvent(&eventSpecifications))
//	{
//		switch (eventSpecifications.type)
//		{
//		case SDL_MOUSEBUTTONDOWN:
//			SDL_GetMouseState(&mouseCoords.x, &mouseCoords.y);
//			if (uiSpec->flag == 1)
//			{
//
//			}
//		default:
//			break;
//		}
//	}
//}

void Level::CreateChunk(int x, int y) {
	for (int i = x; i < x + 2; i++) {
		for (int j = y; j < y + 4; j++) {
			if ((j <= 31) || (i <= 21)|| (j > 0) || (i > 0)) {
				textureLocation[i][j] = 0;
			}
		}
	}
}

int Level::GetLocation(int x, int y) {
	if (x >= 0 && x < 32 && y >= 0 && y < 22) {
		return textureLocation[y][x];
	}
	else {
		return 1;
	}
}

void Level::ChangeLocation(int x, int y) {
	if (x >= 0, x < 32, y >= 0, y < 22) {
		textureLocation[y][x] = 0;
	}
}

void Level::ChunkGenerationMethod() {
	for (int j = 0; j < 8; j++) {
		int i = rand() % 4 + rand() % 3; int count = 0;
		while (count < (5 + rand() % 3)) {
			if (i + count < 11) {
				CreateChunk((i + count) * 2, j * 4);
			}
			count++;
		}
	}

	for (int j = 0; j < 32; j++) {
		for (int i = 0; i < 22; i++) {
			int iteration = 0;
			while (iteration < 50) {
				int count = 0;
				if (GetLocation(j, i + 1) == 0) {
					count++;
				}
				if (GetLocation(j + 1, i + 1) == 0) {
					count++;
				}
				if (GetLocation(j + 1, i) == 0) {
					count++;
				}
				if (GetLocation(j + 1, i - 1) == 0) {
					count++;
				}
				if (GetLocation(j, i - 1) == 0) {
					count++;
				}
				if (GetLocation(j - 1, i - 1) == 0) {
					count++;
				}
				if (GetLocation(j - 1, i) == 0) {
					count++;
				}
				if (GetLocation(j - 1, i + 1) == 0) {
					count++;
				}
				if (count > 3) {
					textureLocation[i][j] = 0;
				}
				iteration++;
			}
		}
	}


	for (int j = 0; j < 32; j++) {
		for (int i = 0; i < 22; i++) {
			if (!(rand() % 16)) {
				textureLocation[i][j] = 3;
			}
			if (textureLocation[i][j] == 1) {
				if (rand() % 2) {
					textureLocation[i][j] = 5;
				}
			}
			if (textureLocation[i][j] == 0) {
				switch (rand() % 3) {
				case 0:
					break;
				case 1:
					textureLocation[i][j] = 4;
					break;
				case 2:
					textureLocation[i][j] = 6;
					break;
				}
			}
			if ((j == 31) || (i == 21) || (j == 0) || (i == 0)) {
				textureLocation[i][j] = 2;
			}
		}
	}

	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 32; j++) {
			if ((textureLocation[i][j] == 0) || (textureLocation[i][j] == 4) || (textureLocation[i][j] == 6)) {
				Location[i][j] = 0;
			}
			if ((textureLocation[i][j] == 1) || (textureLocation[i][j] == 3) || (textureLocation[i][j] == 5)) {
				Location[i][j] = 1;
			}
			if (textureLocation[i][j] == 2) {
				Location[i][j] = 2;
			}
		}
	}
}

std::vector<std::pair<int, int>> Level::pop_front(std::vector<std::pair<int, int>> vec)
{
	for (int i = 0; i < vec.size() - 1; i++) {
		vec[i] = vec[i + 1];
	}
	vec.pop_back();
	return vec;
}

bool Level::Search(std::vector<std::pair<int, int>> vector, int x, int y) {
	std::pair<int, int> coords = { x ,y };
	bool result = false;
	for (int i = 0; i < vector.size(); i++) {
		if (vector[i] == coords) {
			result = true;
		}
	}
	return result;
}

int SearchNum(std::vector<std::pair<int, int>> vector, int x, int y) {
	std::pair<int, int> coords = { x ,y };
	bool result = false;
	for (int i = 0; i < vector.size(); i++) {
		if (vector[i] == coords) {
			return i;
		}
		else {
			return -1;
		}
	}
}

void Level::OtherGeneration() {
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 32; j++) {
			if ((j == 31) || (i == 21) || (j == 0) || (i == 0)) {
				textureLocation[i][j] = 2;
			}
		}
	}
	COORDS startPoint = { 10,10 };
	COORDS endPoint = { rand()%20+1, rand()%31+1 };
	bool HaveWay = false;
	std::vector< std::pair<int, int> > used;
	std::vector< std::pair<int, int> > queue;
	queue.push_back({ startPoint.x, startPoint.y });
	used.push_back({ startPoint.x, startPoint.y });
	std::pair <int, int> current = { 0, 0 };
	while ((!queue.empty())) {
		current = queue.front();
		queue = pop_front(queue);
		if ((current.first == endPoint.x)&&(current.second == endPoint.y)) {
			HaveWay = true;
			break;
		}
		if (textureLocation[current.first][current.second + 1] == 1) {
			if (!(Search(used, current.first, current.second + 1))) {
				queue.push_back({ current.first, current.second + 1 });
				used.push_back({ current.first, current.second + 1 });
			}
		}
		if (textureLocation[current.first - 1][current.second] == 1) {
			if (!(Search(used, current.first - 1, current.second ))) {
				queue.push_back({ current.first - 1, current.second });
				used.push_back({ current.first - 1, current.second });
			}
		}
		if (textureLocation[current.first][current.second - 1] == 1) {
			if (!(Search(used, current.first, current.second - 1))) {
				queue.push_back({ current.first, current.second - 1 });
				used.push_back({ current.first, current.second - 1 });
			}
		}
		if (textureLocation[current.first + 1][current.second] == 1) {
			if (!(Search(used, current.first + 1, current.second))) {
				queue.push_back({ current.first + 1, current.second });
				used.push_back({ current.first + 1, current.second });
			}
		}
	}

	for (int i = 0; i < used.size(); i++) {
		textureLocation[used[i].first][used[i].second] = 3;
	}
	std::vector< std::pair<int, int> > Way;
	
	textureLocation[startPoint.x][startPoint.y] = 0;
	textureLocation[endPoint.x][endPoint.y] = 0;
}

void Level::Generate() {
	int generateChoose = 1;
	srand(time(0));
	if (generateChoose == 0) {
		ChunkGenerationMethod();
	}
	else {
		OtherGeneration();
	}

	//Здесь можно добавить 2 генератор, потом соединить их на одном массиве и получить их совместный результат, звучит перспективно
	/*for (int j = 0; j < 22; j++) {
		for (int i = 0; i < 32; i++) {
			Location2[j][i] = textureLocation[j][i];
		}
	}

	for (int j = 0; j < 22; j++) {
		for (int i = 0; i < 32; i++) {
			if (Location2[j][i] == 0) {
				textureLocation[j][i] = Location2[j][i];
			}
		}
	}*/
}
