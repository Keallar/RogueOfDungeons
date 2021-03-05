#pragma once
#include "Game.h"
#include <ctime>
class Level 
{
private:
	int Location[22][32];
	SDL_Texture* TileTexture[5];
public:
	bool Start();
	void TileSet(int num);
	int Random(int min, int max);
	
};