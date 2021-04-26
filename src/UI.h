#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "string"
#include "Buttons.h"

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
	Keyboard* keyForIncSTR;
	Keyboard* keyForIncDEX;
	Keyboard* keyForIncINT;
	Keyboard* keyForIncWSD;
	Keyboard* keyForIncPHS;
	Keyboard* keyForIncLCK;
public:
	UIInfo(SDL_Renderer* renderer);
	~UIInfo();
	void Render();
	void AlwaysRender();
	void handleEvents(SDL_Event& eventInUiInfo);
};

//Interface
class TextInfo
{
protected:
	const char* PATH_IN_FONT;
	SDL_Color color = { 255, 255, 255, 255 };
public:
	TextInfo();
	virtual ~TextInfo();
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual void UpdateMax() = 0;
};

class HpInfo : public TextInfo
{
private:
	SDL_Renderer* ren;
	SDL_Texture* hpText;
	SDL_Texture* hpMax;
public:
	HpInfo(SDL_Renderer* renderer);
	~HpInfo();
	void Render() override;
	void Update() override;
	void UpdateMax() override;
};

class ManaInfo :public TextInfo
{
private:
	SDL_Renderer* ren;
	SDL_Texture* manaText;
	SDL_Texture* manaMax;
public:
	ManaInfo(SDL_Renderer* renderer);
	~ManaInfo();
	void Render() override;
	void Update() override;
	void UpdateMax() override;
};

class ExpInfo : public TextInfo
{
private:
	SDL_Renderer* ren;
	SDL_Texture* expText;
	SDL_Texture* expMax;
public:
	ExpInfo(SDL_Renderer* renderer);
	~ExpInfo();
	void Render()override;
	void Update()override;
	void UpdateMax() override;
};

class UISpecifications : public TextInfo
{
private:
	SDL_Renderer* ren;
	SDL_Color color;
	SDL_Texture* specBlock;
	SDL_Texture* specifcation;
	//STR
	SDL_Texture* STR;
	SDL_Texture* valueSTR;
	//DEX
	SDL_Texture* DEX;
	SDL_Texture* valueDEX;
	//INT
	SDL_Texture* INT;
	SDL_Texture* valueINT;
	//WSD (WISDOM)
	SDL_Texture* WSD;
	SDL_Texture* valueWSD;
	//PHS (Physical Strength)
	SDL_Texture* PHS; 
	SDL_Texture* valuePHS;
	//LCK
	SDL_Texture* LCK;
	SDL_Texture* valueLCK;
	//buttons
	Button* buttonForCallInfoWin;
	Button* buttonForIncPlayerSTR;
	Button* buttonForIncPlayerDEX;
	Button* buttonForIncPlayerINT;
	Button* buttonForIncPlayerWSD;
	Button* buttonForIncPlayerPHS;
	Button* buttonForIncPlayerLCK;
	//other
	SDL_Texture* one;
	SDL_Texture* two;
	SDL_Texture* three;
	SDL_Texture* four;
	SDL_Texture* five;
	SDL_Texture* six;

public:
	UISpecifications(SDL_Renderer* renderer);
	~UISpecifications();
	void Render() override;
	void Update() override;
	void Update(int value, int num);
	void UpdateMax() override;
	void handleEvents(SDL_Event &eventInSpec);
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
public:
	UIInventory(SDL_Renderer* renderer);
	~UIInventory();
	void Render();
	void handleEvents(SDL_Event &eventInInv);
	void clickForItemsInInv();
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

class UiHpEnemyInfo : public TextInfo
{
private:
	SDL_Renderer* ren;
	SDL_Texture* hpTextEnemy;
	SDL_Texture* hpCurrentTextEnemy;
	SDL_Texture* hpMaxEnemy;
	SDL_Texture* slashhhhhhhhh;
public:
    UiHpEnemyInfo(SDL_Renderer* renderer);
	~UiHpEnemyInfo();
	void Render();
    void Update();
	void UpdateMax();
	void callEnemyInfo();
};
