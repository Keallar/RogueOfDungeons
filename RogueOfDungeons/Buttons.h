#pragma once
#include <SDL.h>

struct MCoord
{
	int x;
	int y;
};

class KeyboardButtons
{
private:
	const Uint8* keys = SDL_GetKeyboardState(NULL);
public:

};

class MouseButton
{
private:
	MCoord mouseCoords;
public:
	MouseButton();
	void buttonsForItemsInInv(SDL_Event eventForItemsInInv);
};

