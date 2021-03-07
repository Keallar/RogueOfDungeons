#pragma once
#include "Level.h"
#include "Managers.h"

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
	enemy = new Enemy("images/Turtle.png", ren, 10, 3, 4);
	flagPlayer = 0;
}

Level::~Level()
{
	delete player;
	delete ui;
}
void Level::Update() 
{
	player->Update();
}

void Level::Start()
{
	flagTB = 1;
	flagPlayer = 1;
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