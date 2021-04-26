#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "string"
#include "Buttons.h"
#include "Enemy.h"

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
	SDL_Texture* SPEC;
	
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
	Button* buttonForCallSpecInfo;
	Button* buttonForCallInvWin;

	//Keyboard
	Keyboard* keyForCallSpecInfo;
	Keyboard* keyForcCallInvWin;
public:
	UIInfo(SDL_Renderer* renderer);
	~UIInfo();
	void Render();
	void AlwaysRender();
	void handleEvents(SDL_Event& eventInUiInfo);
};

class UIItem
{
private:
	const char* PATH_IN_FONT;
	SDL_Color color;
	SDL_Renderer* ren;
	SDL_Texture* itemBlock;
	SDL_Texture* item;
	SDL_Texture* INV;
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
	int xMouseCoord;
	int yMouseCoord;
	Button* buttonForCallDpor;
    Button* buttonForInvItems;
public:
	UIInventory(SDL_Renderer* renderer);
	~UIInventory();
	void Render();
	void handleEvents(SDL_Event &eventInInv);
	void clickForItemsInInv();
};


class UIEquipedItem 
{
private:
	SDL_Texture* EquipedItem;
	SDL_Renderer* ren;
public:
	UIEquipedItem(SDL_Renderer* renderer);
	UIEquipedItem();
	void Render();
	void clickForItemsInInv();
};

class UIEnemyInfo
{
private:
    const char* PATH_IN_FONT;
    SDL_Color color;
    Enemy* tempEnemy;
	SDL_Renderer* ren;
    SDL_Texture* enemyTex;
    SDL_Texture* hpEnemyBar;
	SDL_Texture* hpTextEnemy;
	SDL_Texture* hpCurrentTextEnemy;
	SDL_Texture* hpMaxEnemy;
	SDL_Texture* slashhhhhhhhh;
    Button* buttonForCallEnemyInfo;
public:
    UIEnemyInfo(SDL_Renderer* renderer, Enemy* enemy);
    void Render();
    void Update();
    void Update(Enemy* enemy);
    void UpdateMax();
    void handleEvents(SDL_Event &eventInUiEnemyInfo);
};


