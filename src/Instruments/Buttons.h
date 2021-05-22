#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <functional>
#include <iostream>
#include "TextureBase.h"
#include "string"

struct Mouse
{
    int x;
    int y;
};

class Button
{
private:
    TextureBase* GameTextures;
    std::string buttonText;
    SDL_Renderer* ren;
    SDL_Texture* buttonTexture;
    Mouse mouse;
    SDL_Rect button;
    std::function <void()> callback;
    std::function <void()> hover;
    std::function <void()> leaveHover;
    bool mouseInArea(int x, int y, int w, int h);
public:
    Button(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect rect);
    Button(std::string textButton, SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect rect, std::function <void()> callbackFunction, std::function <void()>hoverFunction, std::function <void()>leaveHoverFunction);
    void handleEvents(SDL_Event& buttonEvent);
    void Render();
    void updateCoords(int newx, int newy);
    void updateScaleButton(int newx, int newy, int neww, int newh);
    void updateTexture(SDL_Texture* tex);
    void deleteTexture();
    SDL_Rect GetCoords();
    SDL_Texture* GetTexture() {return buttonTexture;}
    void SetTexture(SDL_Texture* tex) {buttonTexture = tex;}
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






