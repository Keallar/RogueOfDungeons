#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "Buttons.h"
#include "TextureBase.h"

//Interface
class TextInfo
{
protected:
    const char* PATH_IN_FONT;
    SDL_Color color = { 255, 255, 255, 255 };
    TextureBase* GameTextures;
public:
    TextInfo();
    virtual ~TextInfo();
    virtual void Render() = 0;
    virtual void Update() = 0;
    virtual void UpdateMax() = 0;
};

class HpInfo : public TextInfo
{
private:
    SDL_Renderer* ren;
    //HP
    SDL_Texture* hpBar;
    SDL_Texture* hpText;
    SDL_Texture*  hpCurrent;
    SDL_Texture* hpMax;
public:
    HpInfo(SDL_Renderer* renderer);
    ~HpInfo();
    void Render() override;
    void Update() override;
    void UpdateMax() override;
};

class ManaInfo :public TextInfo
{
private:
    SDL_Texture* mnBar;
    SDL_Texture* mnText;
    SDL_Renderer* ren;
    SDL_Texture* manaCurrent;
    SDL_Texture* manaMax;
public:
    ManaInfo(SDL_Renderer* renderer);
    ~ManaInfo();
    void Render() override;
    void Update() override;
    void UpdateMax() override;
};

class ExpInfo : public TextInfo
{
private:
    SDL_Texture* xpBar;
    SDL_Texture* xpText;
    SDL_Renderer* ren;
    SDL_Texture* expCurrent;
    SDL_Texture* expMax;
public:
    ExpInfo(SDL_Renderer* renderer);
    ~ExpInfo();
    void Render()override;
    void Update()override;
    void UpdateMax() override;
};

class UISpecifications : public TextInfo
{
private:
    TextureBase* GameTextures;

    SDL_Renderer* ren;
    SDL_Color color;
    SDL_Texture* specBlock;
    SDL_Texture* specifcation;
    //STR
    SDL_Texture* STR;
    SDL_Texture* valueSTR;
    //DEX
    SDL_Texture* DEX;
    SDL_Texture* valueDEX;
    //INT
    SDL_Texture* INT;
    SDL_Texture* valueINT;
    //WSD (WISDOM)
    SDL_Texture* WSD;
    SDL_Texture* valueWSD;
    //PHS (Physical Strength)
    SDL_Texture* PHS;
    SDL_Texture* valuePHS;
    //LCK
    SDL_Texture* LCK;
    SDL_Texture* valueLCK;
    //Points
    SDL_Texture* textPointOfSpec;
    SDL_Texture* pointOfSpec;
    //buttons
    Button* buttonForCallInfoWin;
    Button* buttonForIncPlayerSTR;
    Button* buttonForIncPlayerDEX;
    Button* buttonForIncPlayerINT;
    Button* buttonForIncPlayerWSD;
    Button* buttonForIncPlayerPHS;
    Button* buttonForIncPlayerLCK;

    //keys
    Keyboard* keyForIncSTR;
    Keyboard* keyForIncDEX;
    Keyboard* keyForIncINT;
    Keyboard* keyForIncWSD;
    Keyboard* keyForIncPHS;
    Keyboard* keyForIncLCK;
    //other
    SDL_Texture* one;
    SDL_Texture* two;
    SDL_Texture* three;
    SDL_Texture* four;
    SDL_Texture* five;
    SDL_Texture* six;

public:
    UISpecifications(SDL_Renderer* renderer);
    ~UISpecifications();
    void Render() override;
    void Update() override;
    void Update(int value, int num);
    void UpdateMax() override;
    void handleEvents(SDL_Event &eventInSpec);
};


