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
//	virtual void Update(int value) = 0;
};

class HpInfo : public TextInfo
{
private:
	/*const char* PATH_IN_FONT;
	SDL_Color color = { 255, 255, 255, 255 };*/
	SDL_Renderer* ren;
	SDL_Texture* hpText;
	SDL_Texture* hpMax;
public:
	HpInfo(SDL_Renderer* renderer, int changeTextValue);
	~HpInfo();
	void Render();
	void Update(int value);
	void UpdateMax();
};

class ManaInfo :public TextInfo
{
private:
	/*const char* PATH_IN_FONT;
	SDL_Color color = { 255, 255, 255, 255 };*/
	SDL_Renderer* ren;
	SDL_Texture* manaText;
	SDL_Texture* manaMax;
public:
	ManaInfo(SDL_Renderer* renderer, int changeTextValue);
	~ManaInfo();
	void Render();
	void Update(int value);
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
	void Update(int value);
};

class UIInfo
{
private:
	const char* PATH_IN_FONT;
	SDL_Color color = { 255, 255, 255, 255 };
	SDL_Renderer* ren;
	SDL_Texture* versionBLock;
	SDL_Texture* infoBlock;
	SDL_Texture* info;
	SDL_Texture* slashhhhhhhhh;
	//HP
	SDL_Texture* hpBar;
	SDL_Texture* hpText;

	//XP
	SDL_Texture* xpBar;
	SDL_Texture* xpText;

	//MANA
	SDL_Texture* mnBar;
	SDL_Texture* mnText;

	//Buttons
	SDL_Texture* specButton;
public:
	UIInfo(SDL_Renderer* renderer);
	void Render();
	void RenderVersion();
};

class Spec
{
private:
	SDL_Texture* spec;
	SDL_Texture* STR;
	SDL_Texture* DEX;
	SDL_Texture* INT;
	SDL_Texture* PHS; //Physical Strength
	SDL_Texture* LCK;
	SDL_Texture* button;
	SDL_Texture* plus;
public:
	Spec();
	void Update(int value);
};

class UISpecifications
{
private:
	const char* PATH_IN_FONT;
	SDL_Renderer* ren;
	SDL_Color color;
	SDL_Texture* specBlock;
	SDL_Texture* specifcation;
	SDL_Texture* STR;
	SDL_Texture* valueSTR;
	SDL_Texture* DEX;
	SDL_Texture* valueDEX;
	SDL_Texture* INT;
	SDL_Texture* valueINT;
	SDL_Texture* PHS; //Physical Strength
	SDL_Texture* valuePHS;
	SDL_Texture* LCK;
	SDL_Texture* valueLCK;
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
	void UpdateSpec(int value, int num);
};


class UIItem
{
private:
	const char* PATH_IN_FONT;
	SDL_Color color;
	SDL_Renderer* ren;
	SDL_Texture* itemBlock;
	SDL_Texture* item;
	SDL_Texture* buttonForInv;
public:
	UIItem(SDL_Renderer* renderer);
	void Render();
};

class UIInventory
{
private:
	SDL_Renderer* ren;
	SDL_Texture* inventoryBlock;
	SDL_Texture* inventoryText;
	SDL_Texture* inventory;
	SDL_Texture* item;
public:
	UIInventory(SDL_Renderer* renderer);
	~UIInventory();
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