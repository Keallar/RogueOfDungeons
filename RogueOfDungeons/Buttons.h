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
	SDL_Rect stateOfClip[4];
	SDL_Rect* clip;
	const int CLIP_MOUSEOVER = 0;
	const int CLIP_MOUSEOUT = 1;
	const int CLIP_MOUSEDOWN = 2;
	const int CLIP_MOUSEUP = 3;
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
	static void buttonsForAttack();
	static void buttonForRangeAttack();
};

class Keyboard
{
private:
	bool keys[SDL_NUM_SCANCODES];
	void (*callback)();
	bool buttonIsPressed(SDL_Event& keyboardEvent);
public:
	Keyboard(SDL_Scancode* code, void (*callbackFunction)());
	~Keyboard();
	void handleEvents(SDL_Event &keyboardEvent);
};






