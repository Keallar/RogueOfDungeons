#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "TextureBase.h"
#include "Buttons.h"
#define SCREEN_HEIGHT 1280
#define SCREEN_WEIGHT 720
#include "MainMenu.h"
class Credits
{
public:
    Credits();
    Credits(MainMenu* Menu);
    ~Credits();
    void render();
    void handleEvent(SDL_Event &e);
    bool flag = false;
    Button* buttonForBack;
private:
    int textW, textH;
    const SDL_Color COLOR = {255, 255, 255, 255};
    const char* PATH_IN_FONT = "data/fonts/manaspc.ttf";
    TextureBase* GameTextures;
    SDL_Texture* background;
    SDL_Texture* creators;
    SDL_Texture* firstName;
    SDL_Texture* secondName;
    SDL_Texture* thirdName;
    SDL_Texture* fourthName;
    SDL_Texture* fifthName;
};


