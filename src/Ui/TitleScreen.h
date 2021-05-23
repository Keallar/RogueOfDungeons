#pragma once
#include "Managers.h"
#include "Buttons.h"
#include "TextureBase.h"

class TitleScreen
{
private:
    TextureBase*  GameTextures;
    SDL_Texture* titleTextTexture;
    SDL_Renderer* ren;
    Button* SkipButton;
    int textW;
    int textH;
public:
    bool flag;
    TitleScreen(const char* titleText, SDL_Renderer* ren);
    ~TitleScreen();
    void Render();
    void handleEvents(SDL_Event& event);

};

