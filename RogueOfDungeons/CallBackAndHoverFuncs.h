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
};

class hoverFunctions
{
public:
	void callSpecWin(SDL_Renderer* ren, SDL_Texture* hoverTexture);
};
