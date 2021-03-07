#pragma once
#include "Game.h"
#include "Level.h"
#include "Managers.h"
#include <iostream>
#include <ctime>
enum Tiles {white, green, darkYellowDirt, black, yellowSand,
brownDesks, lightBrownWood, lilac, redBlood, vinous, blueWater, orangeBrick,
greenDirt, Dirt, lightBrick, portal1, portal2};//цвета тайлов
//turquoise = бирюзовый
//vinous = винный, бордовый
//lilac = сиреневый

Level::Level(SDL_Renderer* renderer) 
{
	ren = renderer;
	TileTexture = textureManager::LoadTexture("images/Tiles.png", ren);
	PlayBackground = textureManager::LoadTexture("images/Playback.png", ren);
	flagTB = 0;
	player =new Player("images/Hero.png", ren);
	flagPlayer = 0;
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 32; j++) {
			Location[i][j] = 1;
		}
	}
}
void Level::Update() 
{
	player->Update();
}

void Level::Start()
{
	flagTB = 1;
	flagPlayer = 1;
	Generate();
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
				RenderManager::SetTile(j * 32, i * 32, 4, ren, TileTexture);
			}
			else
			{
				RenderManager::SetTile(j * 32, i * 32, 6, ren, TileTexture);
			}
		}
	}
	player->Render();
}

void Level::ChangeLocation(int y, int x) {
	if (x >= 0, x < 32, y >= 0, y < 22) {
		Location[y][x] = 0;
	}
}
int Level::GetLocation(int y, int x) {
	if (x >= 0, x < 32, y >= 0, y < 22) {
		return Location[y][x];
	}
	else {
		return 0;
	}
}

void Level::Generate() {
	srand(time(0));
	COORDS startPoint = { rand() % 32, rand() % 22 };
	int countPoints = 0;
	COORDS lastPoint = startPoint;
	while (countPoints <= 300) {
		int choose = rand() % 5;
		if (choose = 5) {
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
}