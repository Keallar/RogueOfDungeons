#pragma once
#include "Player.h"
#include "UI.h"


class Level 
{
private:
	int Location[22][32];
	//int Location2[22][32];
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
	void Generate();
	void CreateChunk(int x, int y);
	int GetLocation(int x, int y);
	void ChangeLocation(int x, int y);
};