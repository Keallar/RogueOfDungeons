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
	static void keyForCallSpecWin(const Uint8* keys);
	static void keyForCallInvWin(const Uint8* keys);
	static void keyForIncPlayerSpec(const Uint8* keys);
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

class MouseButtonsPlayer
{
private:
	MCoord mouseCoordsPlayer;
public:
	MouseButtonsPlayer();
	~MouseButtonsPlayer();
	static void buttonsForAttack();
};

