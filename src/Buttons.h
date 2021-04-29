#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <functional>
#include <iostream>

struct Mouse
{
	int x;
	int y;
};

class Button
{
private:
    std::string buttonText ;
	const char* nameOftexture;
	SDL_Renderer* ren;
	SDL_Texture* buttonTexture;
	Mouse mouse;
	SDL_Rect button;
    std::function <void()> callback;
    std::function <void()> hover;
	bool mouseInArea(int x, int y, int w, int h);
public:
    Button(const char* textureName, SDL_Renderer* renderer, SDL_Rect rect);
    Button(std::string textButton, const char* textureName, SDL_Renderer* renderer, SDL_Rect rect, std::function <void()> callbackFunction, std::function <void()>hoverFunction);
	void handleEvents(SDL_Event& buttonEvent);
	void Render();
    void updateCoords(int newx, int newy);
    SDL_Rect GetCoords();
};

class Keyboard
{
private:
	SDL_Scancode code;
    std::function <void()> callback;
	bool buttonIsPressed(SDL_Event& keyboardEvent);
public:
	Keyboard(SDL_Scancode scancode, std::function <void()> callbackFunction);
	~Keyboard();
	void handleEvents(SDL_Event &keyboardEvent);
};

class MouseButtonsPlayer
{
private:
    static Mouse mouseCoordsPlayer;
public:
    static void buttonsForAttack(int x, int y);
    static void buttonForRangeAttack(int x, int y);
};





