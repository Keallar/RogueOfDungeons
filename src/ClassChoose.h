#pragma once
#include "Managers.h"
#include "Buttons.h"
#include "TextureBase.h"

class ClassChoose
{
private:
    TextureBase* GameTextures;
    SDL_Texture* Text;
    SDL_Renderer* ren;
    Button* warriorB;
    Button* archerB;
    Button* mageB;
    int textW;
    int textH;
public:
    int flag;
    int choosedClass;
    bool haveClass;
    ClassChoose(SDL_Renderer* ren);
    void handleEvents(SDL_Event event);
    void Render();
};
