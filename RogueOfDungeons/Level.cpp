#include "Level.h"

Level::Level(SDL_Renderer* renderer) {
	ren = renderer;
	TileTexture = textureManager::LoadTexture("images/Tiles.png", ren);
	flag = 0;
}

void Level::Start() {
	SDL_RenderClear(ren);
	flag = 1;
}

void Level::Render()
{
	for (int i = 0; i < 22; i++) 
	{
		for (int j = 0; j < 32; j++) 
		{
			if ((i == 0) || (j == 0) || (i == 21) || (j == 31))
			{
				TileSet(0, j*32, i*32);
			}
			else
			{
				TileSet(1, j*32, i*32);
			}
		}
	}

}

void Level::TileSet(int num, int x, int y) 
{
	switch (num)
	{
	case 0:
		RenderManager::CopyToRender(TileTexture, ren, x, y, 32, 32, 32, 64, 32, 32);
		break;
	case 1:
		RenderManager::CopyToRender(TileTexture, ren, x, y, 32, 32, 0, 96, 32, 32);
		break;
	default:
		break;
	}
}