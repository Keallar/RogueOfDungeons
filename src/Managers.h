#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <chrono>
#include <functional>

class textureManager
{
public:
    static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren = nullptr);
};

namespace RenderManager
{
    void CopyToRender(SDL_Texture* texture, SDL_Renderer* ren, int x, int y, int w, int h, int dx, int dy, int dw, int dh);
    void CopyToRender(SDL_Texture* texture, SDL_Renderer* ren, SDL_Rect rect);
    void CopyToRender(SDL_Texture* texture, SDL_Renderer* ren);
    void SetTile(int x, int y, int tile, SDL_Renderer* renderer, SDL_Texture* tiles);
    void CopyToRender(SDL_Texture *texture, SDL_Renderer *ren, int x, int y, int w, int h);
};

namespace InputManager
{
    bool MouseInArea(int x, int y, int w, int h, int MouseX, int MouseY);
};

namespace FontManager
{
    SDL_Texture* renderText(const char* text, const char * fontFile, SDL_Color textColor, int fontSize, SDL_Renderer* renderer);
};

class FlagManager
{
public:
    //Turn
    static int flagTurn;
    static int flagInAreaOfAnemy;
    static bool flagTimerTurn;
    //UI
    static bool flagUI;
    static bool flagUiSpec;
    static bool flagCheckHP;
    static bool flagCheckMana;
    static bool flagCheckExp;
    static bool flagInv;
    static int flagChest;
    static bool flagUiEnemy;
    static bool flagPointOfSpec;
    static bool flagLevelOfPlayer;
    static bool flagCoin;
    static bool flagUiTrader;
    static int flagBuy;
    static bool flagSell;
    //Specs
    static bool flagSTR;
    static bool flagDEX;
    static bool flagINT;
    static bool flagWSD;
    static bool flagPHS;
    static bool flagLCK;
    //Equip Inv
    static int flagInvHover;
    static int flagEquip;
    static int flagUnEquip;
    static int flagDrop;
    static bool flagHaveDrop;
    //Attack
    static int flagMeleeAttackPlayer;
    static int flagMeleeAttackEnemy;
    static bool flagCheckHpEnemy;
    static bool flagRangeAttackPlayer;
    //Button
    static bool flagHover;
};


