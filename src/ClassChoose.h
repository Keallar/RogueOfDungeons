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
    void SetClass(int chooseClass);
public:
    int flag;
    int choosedClass;
    ClassChoose(SDL_Renderer* ren);
    ~ClassChoose();
    void handleEvents(SDL_Event& event);
    void Render();
};
