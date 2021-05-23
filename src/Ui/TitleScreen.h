#pragma once
#include "Managers.h"
#include "Buttons.h"
#include "TextureBase.h"

class TitleScreen
{
private:
    TextureBase*  GameTextures;
    SDL_Texture* titleTextTexture;
    SDL_Texture* textureUnderTitle;
    SDL_Renderer* ren;
    Button* SkipButton;
    int textW;
    int textH;
    int textWunder;
    int textHunder;
public:
    bool flag;
    TitleScreen(const char* titleText,SDL_Texture* texture, SDL_Renderer* ren);
    ~TitleScreen();
    void Render();
    void handleEvents(SDL_Event& event);

};

