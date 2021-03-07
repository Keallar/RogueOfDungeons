#pragma once
#include "Enemy.h"
#include "Player.h"
#include "UI.h"

//цвета тайлов
enum Tiles
{
	white,
	green,
	darkYellowDirt,
	black,
	yellowSand,
	brownDesks,
	lightBrownWood,
	lilac,
	redBlood,
	vinous,
	blueWater,
	orangeBrick,
	greenDirt,
	Dirt,
	lightBrick,
	portal1,
	portal2
};
//turquoise = бирюзовый
//vinous = винный, бордовый
//lilac = сиреневый

class Level 
{
private:
	//int Location[22][32];
	SDL_Texture* TileTexture;
	SDL_Texture* PlayBackground;
	SDL_Renderer* ren;
	Player* player;
	Enemy* enemy;
	UI* ui;
public:
	bool flagTB;
	bool flagPlayer;
	Level(SDL_Renderer* renderer);
	~Level();
	void Update();
	void Start();
	void Render();
	void TileSet(int num, int x, int y);
};