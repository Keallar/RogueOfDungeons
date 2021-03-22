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


//UNDONE (сделать общим классом для всех изменяемых текстов)
class TextInfo
{
private:
	SDL_Renderer* ren;
	SDL_Texture* infoText;
protected:
	const char* PATH_IN_FONT;
	SDL_Color color = { 255, 255, 255, 255 };
public:
	TextInfo(SDL_Renderer* renderer, int changeTextValue);
	~TextInfo();
	virtual void Render() = 0;
};

class HpInfo : public TextInfo
{
private:
	/*const char* PATH_IN_FONT;
	SDL_Color color = { 255, 255, 255, 255 };*/
	SDL_Renderer* ren;
	SDL_Texture* hpText;
public:
	HpInfo(SDL_Renderer* renderer, int changeTextValue);
	~HpInfo();
	void Render();
};

class ManaInfo :public TextInfo
{
private:
	/*const char* PATH_IN_FONT;
	SDL_Color color = { 255, 255, 255, 255 };*/
	SDL_Renderer* ren;
	SDL_Texture* manaText;
public:
	ManaInfo(SDL_Renderer* renderer, int changeTextValue);
	~ManaInfo();
	void Render();
};

class ExpInfo : public TextInfo
{
private:
	const char* PATH_IN_FONT;
	SDL_Color color = { 255, 255, 255, 255 };
	SDL_Renderer* ren;
	SDL_Texture* expText;
public:
	ExpInfo(SDL_Renderer* renderer, int changeTextValue);
	~ExpInfo();
	void Render();
};

class UIInfo
{
private:
	const char* pathInFont;
	SDL_Color color = { 255, 255, 255, 255 };
	SDL_Renderer* ren;
	SDL_Texture* versionBLock;
	SDL_Texture* infoBlock;
	SDL_Texture* info;
	//HP
	SDL_Texture* hpBar;
	SDL_Texture* hpText;
	SDL_Texture* hpInfo;
	SDL_Texture* updatedHP;
	//static int healthInfo;
	//XP
	SDL_Texture* xpBar;
	SDL_Texture* xpText;
	SDL_Texture* xpInfo;
	//static int expInfo;
	//MANA
	SDL_Texture* mnBar;
	SDL_Texture* mnText;
	SDL_Texture* mnInfo;
	//static int manaInfo;
	//Buttons
	SDL_Texture* specButton;
public:
	UIInfo(SDL_Renderer* renderer);
	void Render();
};

class Spec
{
private:
	SDL_Texture* spec;
public:
	Spec();
};

class UISpecifications
{
private:
	const char* pathInFont;
	const Uint32 MOUSE_CHECK = SDL_GetMouseState(NULL, NULL);
	SDL_Renderer* ren;
	bool flag;
	SDL_Texture* specBlock;
	SDL_Texture* specifcation;
	SDL_Texture* state;
	SDL_Texture* STR;
	SDL_Texture* DEX;
	SDL_Texture* INT;
	SDL_Texture* PHS; //Physical Strength
	SDL_Texture* LCK;
	SDL_Texture* button;
	SDL_Texture* plus;
	SDL_Texture* one;
	SDL_Texture* two;
	SDL_Texture* three;
	SDL_Texture* four;
	SDL_Texture* five;

public:
	UISpecifications(SDL_Renderer* renderer);
	void Render();
};


class UIItem
{
private:
	const char* pathInFont;
	SDL_Renderer* ren;
	SDL_Texture* itemBlock;
	SDL_Texture* item;
public:
	UIItem(SDL_Renderer* renderer);
	void Render();
};

class UIInventory
{

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