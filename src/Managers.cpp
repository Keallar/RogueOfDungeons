#include "Managers.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <string>
#include <thread>
SDL_Texture* textureManager::LoadTexture(const char* texName, SDL_Renderer* ren) 
{
    SDL_Texture* tex = IMG_LoadTexture(ren, texName);
    return tex;
}

bool InputManager::MouseInArea(int x, int y, int w, int h, int MouseX, int MouseY) 
{
    bool temp;
    if ((MouseX >= x) && (MouseX <= x + w) && (MouseY >= y) && (MouseY <= y + h))
    {
        temp = true;
    }
    else
    {
        temp = false;
    }
    return  temp;
}

void RenderManager::CopyToRender(SDL_Texture* texture, SDL_Renderer* ren, int x, int y, int w, int h, int dx, int dy, int dw, int dh) 
{
    SDL_Rect COORD; SDL_Rect dCOORD;
    COORD.x = x; COORD.y = y; COORD.w = w; COORD.h = h;
    dCOORD.x = dx; dCOORD.y = dy; dCOORD.w = dw; dCOORD.h = dh;
    SDL_RenderCopy(ren, texture, &dCOORD, &COORD);
}
void RenderManager::CopyToRender(SDL_Texture* texture, SDL_Renderer* ren, int x, int y, int w, int h) 
{	
    SDL_Rect COORD; //SDL_Rect dCOORD;
    COORD.x = x; COORD.y = y; COORD.w = w; COORD.h = h;
    SDL_RenderCopy(ren, texture, NULL, &COORD);
}	
void RenderManager::CopyToRender(SDL_Texture* texture, SDL_Renderer* ren) 
{
    SDL_RenderCopy(ren, texture, NULL, NULL);
}

void RenderManager::SetTile(int x, int y, int tile, SDL_Renderer* renderer, SDL_Texture* TileTexture)
{
    RenderManager::CopyToRender(TileTexture, renderer, x, y, 32, 32, (tile / 4) * 32, (tile % 4) * 32, 32, 32);
}

SDL_Texture* FontManager::renderText(const char* text, const char* fontFile, SDL_Color textColor, int fontSize, SDL_Renderer* renderer) 
{
    SDL_Surface* surf;
    SDL_Color fontColor;
    TTF_Font* font;
    SDL_Texture* fontTexture;
    fontColor = textColor;
    font = TTF_OpenFont(fontFile, fontSize);
    if (font == NULL)
    {
        std::cout << "Error TTF_OpenFont"<< std::endl;
        std::cout << TTF_GetError() << std::endl;
        return nullptr;
    }
    surf = TTF_RenderText_Blended(font, text, fontColor);

    fontTexture = SDL_CreateTextureFromSurface(renderer, surf);

    SDL_FreeSurface(surf);
    TTF_CloseFont(font);
    return fontTexture;
}

//Turn
int FlagManager::flagTurn = 1;
int FlagManager::flagInAreaOfAnemy = 0;
bool FlagManager::flagTimerTurn = 0;
//UI
bool FlagManager::flagUI = 1;
bool FlagManager::flagUiSpec = 0;
bool FlagManager::flagUiEnemy = 0;
bool FlagManager::flagInv = 0;
bool FlagManager::flagHover = 0;
bool FlagManager::flagCoin = 0;
//Checks of main characters
bool FlagManager::flagCheckHP = 0;
bool FlagManager::flagCheckMana = 0;
bool FlagManager::flagCheckExp = 0;
bool FlagManager::flagHaveDrop = 0;
//Items and other
int FlagManager::flagChest = 0;
int FlagManager::flagEquip = -1;
int FlagManager::flagUnEquip = -1;
int FlagManager::flagDrop = -1;
//Specs and level of player
bool FlagManager::flagPointOfSpec = 0;
bool FlagManager::flagLevelOfPlayer = 0;
bool FlagManager::flagSTR = 0;
bool FlagManager::flagDEX = 0;
bool FlagManager::flagINT = 0;
bool FlagManager::flagWSD = 0;
bool FlagManager::flagPHS = 0;
bool FlagManager::flagLCK = 0;
//Fight system enemy and player
int FlagManager::flagMeleeAttackPlayer = 0;
int FlagManager::flagMeleeAttackEnemy = 0;
bool FlagManager::flagRangeAttackPlayer = 0;
//Check HP enemy
bool FlagManager::flagCheckHpEnemy = 0;




