#include "InputManager.h"

bool InputManager::MouseInArea(int x, int y, int w, int h, int MouseX, int MouseY) {
	if ((MouseX >= x) && (MouseX <= x + w) && (MouseX >= y) && (MouseX <= x + h)) {
		return true;
	}
	else {
		return false;
	}
}
