﻿#pragma once
#include "Game.h"
#include "Level.h"
#include "Managers.h"
#include "UI.h"

Level::Level(SDL_Renderer* renderer) 
{
	ren = renderer;
	TileTexture = textureManager::LoadTexture("images/Tiles.png", ren);
	PlayBackground = textureManager::LoadTexture("images/Playback.png", ren);
	flagTB = 0;
	player = new Player("images/Hero.png", ren);
	flagPlayer = 0;
	enemy = new Enemy("images/Turtle.png", ren, 10, 3, 4);
	flagEnemy = 0;
	uiLevel = new UILevel(ren);
	flagUI = 0;
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 32; j++) {
			Location[i][j] = 1;
		}
	}
	uiLevel = new UILevel(renderer);
}

Level::~Level()
{
	delete uiLevel;
	delete player;
	delete enemy;
	delete uiLevel;
}
void Level::Update() 
{
	if (flagPlayer == 1)
	{
		player->Update();
		flagPlayer = 0;
		flagEnemy = 1;
	}
	if (flagPlayer == 0)
	{
		enemy->Update();
		flagEnemy = 0;
		flagPlayer = 1;
	}
}

void Level::Start()
{
	flagTB = 1;
	flagPlayer = 1;
	flagUI = 1;
	Generate();
	flagEnemy = 0;
}

void Level::Render()
{
	RenderManager::CopyToRender(PlayBackground, ren);
	for (int i = 0; i < 22; i++) 
	{
		for (int j = 0; j < 32; j++) 
		{
			if (Location[i][j] == 0)
			{
				RenderManager::SetTile(j * 32, i * 32, 8, ren, TileTexture);
			}
			else
			{
				RenderManager::SetTile(j * 32, i * 32, 7, ren, TileTexture);
			}
			if (Location[i][j] == 2) 
			{
				RenderManager::SetTile(j * 32, i * 32, 10, ren, TileTexture);
			}
			if (Location[i][j] == 3) 
			{
				RenderManager::SetTile(j * 32, i * 32, 3, ren, TileTexture);
			}
		}
	}
	player->Render();
	enemy->Render();
	uiLevel->Render();
}

void Level::ChangeLocation(int x, int y) {
	if (x >= 0 && x < 32 && y >= 0 && y < 22) {
		Location[y][x] = 0;
	}
}
int Level::GetLocation(int x, int y) {
	if (x >= 0 && x < 32 && y >= 0 && y < 22) {
		return Location[y][x];
	}
	else {
		return 0;
	}
}

void Level::Generate() {
	//1 = стенки
	//0 = дорога
	//2 = граница мапы
	//3 = вместо 0 
	srand(time(0));
	COORDS startPoint = { rand() % 32, rand() % 4 }; //пустой тайл, от котороо всё генерится
	ChangeLocation(startPoint.x, startPoint.y);
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 32; j++) {
			int count = 0;
			if (GetLocation(j, i + 1) == 0) {
				count++;
			}
			if (GetLocation(j+1, i + 1) == 0) {
				count++;
			}
			if (GetLocation(j+1, i) == 0) {
				count++;
			}
			if (GetLocation(j+1, i - 1) == 0) {
				count++;
			}
			if (GetLocation(j, i - 1) == 0) {
				count++;
			}
			if (GetLocation(j-1, i - 1) == 0) {
				count++;
			}
			if (GetLocation(j-1, i) == 0) {
				count++;
			}
			if (GetLocation(j-1, i + 1) == 0) {
				count++;
			}
			if (count == 1) {
				if (rand() % 3) {
					ChangeLocation(j, i);
				}
			}
			if (count == 2) {
				if (rand() % 3) {
					ChangeLocation(j, i);
				}	
			}
			if (count == 3) {
				if (rand() % 3) {
					ChangeLocation(j, i);
				}
			}
			if (count == 4) {
				if (!(rand() % 4)) {
					ChangeLocation(j, i);
				}
			}
			if (count == 5) {
				if (!(rand() % 4)) {
					ChangeLocation(j, i);
				}
			}
		}
	}

	int countPoints = 0; 
	COORDS lastPoint = startPoint;
	while (countPoints <= 200) {
		int choose = rand() % 5;
		if (choose == 4) {
			if (32 - lastPoint.x < 32 / 2) {
				if (22 - lastPoint.y < 22 / 2) {
					if (rand() % 2) {
						choose = 1;
					}
					else {
						choose = 3;
					}
				}
				else {
					if (rand() % 2) {
						choose = 1;
					}
					else {
						choose = 2;
					}
				}
			}
			else {
				if (22 - lastPoint.y >= 22 / 2) {
					if (rand() % 2) {
						choose = 0;
					}
					else {
						choose = 2;
					}
				}
				else {
					if (rand() % 2) {
						choose = 0;
					}
					else {
						choose = 3;
					}
				}
			}
		}
		switch (choose) {
		case 0:
			if ((GetLocation(lastPoint.y, lastPoint.x + 1)) != 0) {
				ChangeLocation(lastPoint.y, lastPoint.x + 1);
				lastPoint = { lastPoint.x + 1, lastPoint.y };
				break;
			}
		case 1:
			if ((GetLocation(lastPoint.y, lastPoint.x - 1)) != 0) {
				ChangeLocation(lastPoint.y, lastPoint.x - 1);
				lastPoint = { lastPoint.x - 1, lastPoint.y };
				break;
			}
		case 2:
			if ((GetLocation(lastPoint.y + 1, lastPoint.x)) != 0) {
				ChangeLocation(lastPoint.y + 1, lastPoint.x);
				lastPoint = { lastPoint.x , lastPoint.y + 1 };
				break;
			}
		case 3:
			if ((GetLocation(lastPoint.y - 1, lastPoint.x)) != 0) {
				ChangeLocation(lastPoint.y - 1, lastPoint.x);
				lastPoint = { lastPoint.x, lastPoint.y - 1 };
				break;
			}
		default:
			lastPoint = { rand() % 32, rand() % 22 };
			break;
		}
		countPoints++;
	}

	//камушки и крпичи вокруг мапы
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 22; j++) {
			if ((i == 0) || (i == 31) || (j == 0) || (j == 21)) {
				Location[j][i] = 2;
			}
			if (Location[j][i] == 0) {
				if (!(rand() % 6)) {
					Location[j][i] = 3;
				}
			}
		}
	}
}
