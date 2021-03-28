#pragma once
#include <SDL.h>

struct MCoord
{
	int x;
	int y;
};

class KeyboardButtonsInLevel
{
private:
	const Uint8* keys = SDL_GetKeyboardState(NULL);
public:
	KeyboardButtonsInLevel();
	void keyForCallSpecWin();
	void keyForCallInvWin();
	void keyForIncPlayerSpec();
};

class MouseButtonsInLevel
{
private:
	static MCoord mouseCoords;
	
public:
	MouseButtonsInLevel();
	static void buttonsForItemsInInv();
	static void buttonForCallSpecWin();
	static void buttonForCallInvWin();
	static void buttonForCallEnemyInfo();
	static void buttonForIncPlayerSpec();
};

//class KeyboardButtonInPlayer
//{
//private:
//	MCoord mouseCoords;
//	const Uint8* keys = SDL_GetKeyboardState(NULL);
//public:
//	KeyboardButtonInPlayer();
//	void movePlayer(SDL_Event &eventForMovePlayer);
//};

