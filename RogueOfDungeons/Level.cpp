#pragma once
#include "Game.h"
#include "Level.h"
#include "Managers.h"
#include <iostream>
#include <ctime>
enum Tiles {
	white, green, darkYellowDirt, black, yellowSand,
	brownDesks, lightBrownWood, lilac, redBlood, vinous, blueWater, orangeBrick,
	greenDirt, Dirt, lightBrick, portal1, portal2
};//цвета тайлов
//turquoise = бирюзовый
//vinous = винный, бордовый
//lilac = сиреневый

Level::Level(SDL_Renderer* renderer)
{
	ren = renderer;
	TileTexture = textureManager::LoadTexture("images/Tiles.png", ren);
	PlayBackground = textureManager::LoadTexture("images/Playback.png", ren);
	flagTB = 0;
	player = new Player("images/Hero.png", ren);
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
				RenderManager::SetTile(j * 32, i * 32, 3, ren, TileTexture);
			}
			if (Location[i][j] == 2) {
				RenderManager::SetTile(j * 32, i * 32, 7, ren, TileTexture);
			}
		}
	}
	player->Render();
}

void Level::CreateChunk(int x, int y) {
	for (int i = x; i < x + 2; i++) {
		for (int j = y; j < y + 4; j++) {
			if ((j <= 31) || (i <= 21)|| (j > 0) || (i > 0)) {
				Location[i][j] = 0;
			}
		}
	}
}

int Level::GetLocation(int x, int y) {
	if (x >= 0, x < 32, y >= 0, y < 22) {
		return Location[y][x];
	}
	else {
		return 1;
	}
}

void Level::ChangeLocation(int x, int y) {
	if (x >= 0, x < 32, y >= 0, y < 22) {
		Location[y][x] = 0;
	}
}

void Level::Generate() {

	srand(time(0));
	for (int j = 0; j < 8; j++) {
		int i = rand() % 4 + rand()%3; int count = 0;
		while (count < (5 + rand()%3)) {
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
					Location[i][j] = 0;
				}
				iteration++;
			}
		}
	}


	for (int j = 0; j < 32; j++) {
		for (int i = 0; i < 22; i++) {
			if (!(rand() % 16)) {
				Location[i][j] = 1;
			}
			if (!(rand() % 32)) {
				Location[i][j] = 0;
			}
			if ((j == 31) || (i == 21) || (j == 0) || (i == 0)) {
				Location[i][j] = 2;
			}
		}
	}


	//Здесь можно добавить 2 генератор, потом соединить их на одном массиве и получить их совместный результат, звучит перспективно
	/*for (int j = 0; j < 22; j++) {
		for (int i = 0; i < 32; i++) {
			Location2[j][i] = Location[j][i];
		}
	}

	for (int j = 0; j < 22; j++) {
		for (int i = 0; i < 32; i++) {
			if (Location2[j][i] == 0) {
				Location[j][i] = Location2[j][i];
			}
		}
	}*/
}


