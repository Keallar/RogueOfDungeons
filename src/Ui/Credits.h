#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "TextureBase.h"

class Credits
{
public:
    Credits();
    ~Credits();
    void render();
private:
    const SDL_Color COLOR = {255, 255, 255, 255};
    const char* PATH_IN_FONT = "data/fonts/manaspc.ttf";
    TextureBase* GameTextures;
    SDL_Texture* background;
    SDL_Texture* firstName;
    SDL_Texture* secondName;
    SDL_Texture* thirdName;
    SDL_Texture* fourthName;
    SDL_Texture* fifthName;
};


