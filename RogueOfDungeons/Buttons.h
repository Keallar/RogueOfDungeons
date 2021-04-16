#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

struct Mouse
{
	int x;
	int y;
};

struct ButtonRect
{
	int x;
	int y;
	int w;
	int h;
};

class MouseButtonsPlayer
{
private:
	static Mouse mouseCoordsPlayer;
public:
	static void buttonsForAttack();
	static void buttonForRangeAttack();
};


class Button
{
private:
	const char* nameOftexture;
	Mouse mouse;
	ButtonRect button;
	void (*callback)();
	void (*hover)();
public:
	Button(const char* textureName, SDL_Rect rect, void (*callbackFunction)(), void (*hoverFunction)());
	void handleEvents(SDL_Event& buttonEvent);
	bool mouseInArea(int x, int y, int w, int h);
};


class Keyboard
{
private:
	bool keys[SDL_NUM_SCANCODES];
public:
	Keyboard();
	void handleEvents(SDL_Event &keyboardEvent);
};