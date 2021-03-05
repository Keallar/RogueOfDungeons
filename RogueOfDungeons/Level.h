#pragma once
#include "Game.h"

class Level 
{
private:
	int Location[22][32];
	SDL_Texture* TileTexture;
	SDL_Texture* PlayBackground;
	SDL_Renderer* ren;
public:
	bool flag;
	Level(SDL_Renderer* renderer);
	void Start();
	void Render();
	void TileSet(int num, int x, int y);
};