#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <chrono>
#include <functional>

class textureManager
{
public:
	static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);
};

class RenderManager 
{
public:
	static void CopyToRender(SDL_Texture* texture, SDL_Renderer* ren, int x, int y, int w, int h, int dx, int dy, int dw, int dh);
	static void CopyToRender(SDL_Texture* texture, SDL_Renderer* ren, int x, int y, int w, int h);
	static void CopyToRender(SDL_Texture* texture, SDL_Renderer* ren);
	static void SetTile(int x, int y, int tile, SDL_Renderer* renderer, SDL_Texture* tiles);
};

class InputManager
{
public:
	static bool MouseInArea(int x, int y, int w, int h, int MouseX, int MouseY);	
};

class FontManager 
{
public:
	static SDL_Texture* renderText(const char* text, const char * fontFile, SDL_Color textColor, int fontSize, SDL_Renderer* renderer);
};

class FlagManager
{
public:
    static int flagTurn;
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
	static bool flagSTR;
	static bool flagDEX;
	static bool flagINT;
	static bool flagWSD;
	static bool flagPHS;
	static bool flagLCK;
	static int flagEquip;
	static int flagUnEquip;
	static int flagMeleeAttackPlayer;
	static int flagMeleeAttackEnemy;
	static bool flagCheckHpEnemy;
	static bool flagRangeAttack;
	static int flagDrop;
	static bool flagHaveDrop;
	static bool flagHover;
};


