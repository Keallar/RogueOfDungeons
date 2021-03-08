#pragma once
#include "Level.h"
#include "Managers.h"

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
}

Level::~Level()
{
	delete player;
	delete enemy;
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
	flagEnemy = 0;
}

void Level::Render()
{
	RenderManager::CopyToRender(PlayBackground, ren);
	for (int i = 0; i < 22; i++) 
	{
		for (int j = 0; j < 32; j++) 
		{
			if ((i == 0) || (j == 0) || (i == 21) || (j == 31))
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
	enemy->Render();
}