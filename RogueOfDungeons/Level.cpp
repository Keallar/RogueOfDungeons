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
				RenderManager::SetTile(j * 32, i * 32, 8, ren, TileTexture);
			}
			else
			{
				RenderManager::SetTile(j * 32, i * 32, 7, ren, TileTexture);
			}
		}
	}
	player->Render();
}

void Level::ChangeLocation(int x, int y) {
	if (x >= 0, x < 32, y >= 0, y < 22) {
		Location[y][x] = 0;
	}
}
int Level::GetLocation(int x, int y) {
	if (x >= 0, x < 32, y >= 0, y < 22) {
		return Location[y][x];
	}
	else {
		return 0;
	}
}

void Level::Generate() {
	srand(time(0));
	COORDS startPoint = { rand() % 32, rand() % 4 };
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
	
}