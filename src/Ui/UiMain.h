#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "string"
#include "Buttons.h"
#include "Enemy.h"
#include "TextureBase.h"

class UIInfo
{
private:
    TextureBase* GameTextures;
	const char* PATH_IN_FONT;
	SDL_Color color = { 255, 255, 255, 255 };
	SDL_Renderer* ren;
	SDL_Texture* versionBLock;
	SDL_Texture* infoBlock;
	SDL_Texture* info;
	SDL_Texture* slashhhhhhhhh;
	SDL_Texture* SPEC;
    SDL_Texture* INV;

    //Level
    SDL_Texture* textLevelOfPlayer;
    SDL_Texture* levelOfPlayer;

    //flags
    bool flagHoverSpec = 0;
    bool flagHoverInv = 0;

    //Coins
    SDL_Texture* coinText;
    SDL_Texture* coins;

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
    void Update();
	void handleEvents(SDL_Event& eventInUiInfo);
};

class UIItem
{
private:
    TextureBase* GameTextures;
	const char* PATH_IN_FONT;
	SDL_Color color;
	SDL_Renderer* ren;
	SDL_Texture* itemBlock;
    SDL_Texture* item;
public:
	UIItem(SDL_Renderer* renderer);
    ~UIItem();
	void Render();
};

class UIInventory
{
private:
    TextureBase* GameTextures;
	SDL_Renderer* ren;
	SDL_Texture* inventoryBlock;
	SDL_Texture* inventoryText;
	SDL_Texture* inventory;
	SDL_Texture* item;
	int xMouseCoord;
	int yMouseCoord;
	Button* buttonForCallDpor;
    Button* buttonForInvItems;
    SDL_Texture* hoverTexture;
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



