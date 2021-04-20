#pragma once
#include <SDL.h>
#include "Managers.h"
#include "Player.h"
#include <iostream>

class callbackFunctions
{
public:
	static void callInvWin();
	static void callSpecOrInfoWin();
	static void incPlayerSTR();
	static void incPlayerDEX();
	static void incPlayerINT();
	static void incPlayerWSD();
	static void incPlayerPHS();
	static void incPlayerLCK();
	static void callDrop();
};

class hoverFunctions
{
private:
	static SDL_Renderer* renderer;
public:
	static void callSpecWin();
};
