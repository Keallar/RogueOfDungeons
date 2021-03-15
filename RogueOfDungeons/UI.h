#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "string"


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

class UIInfo
{
private:
	static const char* pathInFont;
	SDL_Renderer* ren;
	SDL_Texture* versionBLock;
	SDL_Texture* infoBlock;
	SDL_Texture* info;
	//HP
	SDL_Texture* hpBar;
	
	SDL_Texture* hpText;
	SDL_Texture* hpInfo;
	static int healthInfo;
	static char* HP;
	//XP
	SDL_Texture* xpBar;
	SDL_Texture* xpText;
	SDL_Texture* xpInfo;
	static int expInfo;
	static std::string XP;
	//MANA
	SDL_Texture* mnBar;
	SDL_Texture* mnText;
	SDL_Texture* mnInfo;
	static int manaInfo;
	static std::string MANA;
	//Buttons
	SDL_Texture* specButton;
public:
	UIInfo( SDL_Renderer* renderer);
	void Render();
	static void Update(int hp, int mana, int exp, SDL_Renderer* renderer);
};

class UISpecifications
{
private:
	const char* pathInFont;
	SDL_Renderer* ren;
	SDL_Texture* specBlock;
	SDL_Texture* STR;
	SDL_Texture* DEX;
	SDL_Texture* INT;
	SDL_Texture* PHS; //Physical Strength
	SDL_Texture* LCK;
	SDL_Texture* button;
public:
	UISpecifications(SDL_Renderer* renderer);
	void Render();
	//void Start();
	//void Close();
};


class UIInventory
{
private:
	const char* pathInFont;
	SDL_Renderer* ren;
	SDL_Texture* inventoryBlock;
	SDL_Texture* inventory;
public:
	UIInventory(SDL_Renderer* renderer);
	void Render();
};

class UIEnemyInfo
{
private:
	const char* pathInFont;
	SDL_Renderer* ren;
	SDL_Texture* enemy;
	SDL_Texture* hpEmenyBar;
	SDL_Texture* hpEnemyText;
	SDL_Texture* hpEnemyInfo;
	SDL_Texture* specfifcationsEnemy;
public:
	UIEnemyInfo(SDL_Renderer* rendrerer);
	void Render();
};