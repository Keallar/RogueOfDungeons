#pragma once
#include "Game.h"

class InputManager {
public:
	static bool MouseInArea(int x, int y, int w, int h, int MouseX, int MouseY);
};