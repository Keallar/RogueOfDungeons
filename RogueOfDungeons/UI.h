#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"


//class UIMenu 
//{
//private:
//	SDL_Renderer* ren;
//	SDL_Texture* Font1;
//	SDL_Texture* Font2;
//public:
//	UIMenu();
//	UIMenu(SDL_Renderer* renderer);
//	void Render();
//};

class UILevel
{
private:
	const char* pathInFont;
	SDL_Renderer* ren;
	SDL_Texture* versionBLock;
	SDL_Texture* infoBlock;
	SDL_Texture* inventoryBlock;
	SDL_Texture* info;
	SDL_Texture* inventory;
	SDL_Texture* hpBar;
	SDL_Texture* hpText;
	SDL_Texture* hpInfo;

public:
	UILevel( SDL_Renderer* renderer);
	void Render();
};