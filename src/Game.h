#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Player.h"
#include <iostream>
#include "MainMenu.h"
#include "Level.h"
#include "Player.h"
#include "ClassChoose.h"

struct COORDS 
{
	int x;
	int y;
};

enum GameState
{
	Menu,
	Settings,
	Exit,
	GamePlay,
	PlayerState
};

class Game
{
private:
	bool isRunning;
	SDL_Window* window;
	SDL_Texture* texture;
	SDL_Rect tex_RECT;
	SDL_Rect tex_posRect;
	COORDS mouseCoord;
	MainMenu* Menu;
	Level* level;
    ClassChoose* classChoose;
	UIInfo* uiLevel;
	//UNDONE (сделать Player static во всей игре)
	//static Player* player; 
public:
	static SDL_Renderer* renderer;
	Game();
	~Game();
	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running();;
};
