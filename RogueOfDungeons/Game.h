#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Player.h"
#include <iostream>
#include "MainMenu.h"
#include "Level.h"

struct COORDS {
	int x;
	int y;
};


enum GameState
{
	MainMenu,
	Settings,
	Exit,
	GamePlay,
	Player
};

class Game
{
private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Rect tex_RECT;
	SDL_Rect tex_posRect;
	COORDS mouseCoord;
	MainMenu* Menu;
	Level* level;
public:
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running();
	int playerCoordx;
	int playerCoordy;
};
