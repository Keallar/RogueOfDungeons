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

class Timer
{
public:
	Timer();
	void add(std::chrono::milliseconds delay, std::function<void()> callback, bool asynchronous = true);
};

class FlagManager
{
public:
	static int flagPlayer;
	static int flagEnemy;
	static bool flagUI;
	static bool flagUiSpec;
	static bool flagCheckHP;
	static bool flagCheckMana;
	static bool flagCheckExp;
	static bool flagInv;
	static int flagChest;
	static bool flagUiEnemy;
	static bool flagSTR;
	static bool flagDEX;
	static bool flagINT;
	static bool flagPHS;
	static bool flagLCK;
	static int flagEquip;
	static int flagMeleeAttackPlayer;
	static int flagMeleeAttackEnemy;
	static bool flagCheckHpEnemy;
};

