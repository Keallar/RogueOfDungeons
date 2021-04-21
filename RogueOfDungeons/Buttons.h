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

class Button
{
private:
	const char* nameOftexture;
	SDL_Renderer* ren;
	SDL_Texture* buttonTexture;
	Mouse mouse;
	ButtonRect button;
	void (*callback)();
	void (*hover)();
	bool mouseInArea(int x, int y, int w, int h);
public:
	Button(const char* textureName, SDL_Renderer* renderer, SDL_Rect rect);
	Button(const char* textureName, SDL_Renderer* renderer, SDL_Rect rect, void (*callbackFunction)(), void (*hoverFunction)());
	void handleEvents(SDL_Event& buttonEvent);
	void Render();
	void updateCoords(int newx, int newy);
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

class MouseButtonsPlayer
{
private:
	static Mouse mouseCoordsPlayer;
public:
	static void buttonsForAttack(int x, int y);
	static void buttonForRangeAttack(int x, int y);
};






