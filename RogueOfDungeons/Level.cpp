#pragma once
#include "Level.h"
#include "Player.h"

enum Tiles {};//����� ������

Level::Level(SDL_Renderer* renderer) 
{
	ren = renderer;
	TileTexture = textureManager::LoadTexture("images/Tiles.png", ren);
	PlayBackground = textureManager::LoadTexture("images/Playback.png", ren);
	flagTB = 0;
	//player();
	flagPlayer = 0;
}

void Level::Start() {
	flag = 1;
}


void Level::Render()
{
	SDL_RenderCopy(ren, PlayBackground, NULL, NULL);
	for (int i = 0; i < 22; i++) 
	{
		for (int j = 0; j < 32; j++) 
		{
			if ((i == 0) || (j == 0) || (i == 21) || (j == 31))
			{
				TileSet(14, j*32, i*32);
			}
			else
			{
				TileSet(2, j*32, i*32);
			}
		}
	}

}

void Level::TileSet(int num, int x, int y) 
{
	switch (num)
	{
	case 0:
		RenderManager::CopyToRender(TileTexture, ren, x, y, 32, 32, 0, 0, 32, 32);
		break;
	case 1:
		RenderManager::CopyToRender(TileTexture, ren, x, y, 32, 32, 0, 32, 32, 32);
		break;
	case 2:
		RenderManager::CopyToRender(TileTexture, ren, x, y, 32, 32, 0, 64, 32, 32);
		break;
	case 3:
		RenderManager::CopyToRender(TileTexture, ren, x, y, 32, 32, 0, 96, 32, 32);
		break;
	case 4:
		RenderManager::CopyToRender(TileTexture, ren, x, y, 32, 32, 32, 0, 32, 32);
		break;
	case 5:
		RenderManager::CopyToRender(TileTexture, ren, x, y, 32, 32, 32, 32, 32, 32);
		break;
	case 6:
		RenderManager::CopyToRender(TileTexture, ren, x, y, 32, 32, 32, 64, 32, 32);
		break;
	case 7:
		RenderManager::CopyToRender(TileTexture, ren, x, y, 32, 32, 32, 96, 32, 32);
		break;
	case 8:
		RenderManager::CopyToRender(TileTexture, ren, x, y, 32, 32, 64, 0, 32, 32);
		break;
	case 9:
		RenderManager::CopyToRender(TileTexture, ren, x, y, 32, 32, 64, 32, 32, 32);
		break;
	case 10:
		RenderManager::CopyToRender(TileTexture, ren, x, y, 32, 32, 64, 64, 32, 32);
		break;
	case 11:
		RenderManager::CopyToRender(TileTexture, ren, x, y, 32, 32, 64, 96, 32, 32);
		break;
	case 12:
		RenderManager::CopyToRender(TileTexture, ren, x, y, 32, 32, 96, 0, 32, 32);
		break;
	case 13:
		RenderManager::CopyToRender(TileTexture, ren, x, y, 32, 32, 96, 32, 32, 32);
		break;
	case 14:
		RenderManager::CopyToRender(TileTexture, ren, x, y, 32, 32, 96, 64, 32, 32);
		break;
	case 15:
		RenderManager::CopyToRender(TileTexture, ren, x, y, 32, 32, 96, 96, 32, 32);
		break;
	default:
		break;
	}
}