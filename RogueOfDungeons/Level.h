#pragma once
#include "Player.h"
#include "UI.h"


class Level 
{
private:
	//int Location[22][32];
	SDL_Texture* TileTexture;
	SDL_Texture* PlayBackground;
	SDL_Renderer* ren;
	Player* player;
	UI* ui;
public:
	bool flagTB;
	bool flagPlayer;
	Level(SDL_Renderer* renderer);
	void Update();
	void Start();
	void Render();
	void TileSet(int num, int x, int y);
};