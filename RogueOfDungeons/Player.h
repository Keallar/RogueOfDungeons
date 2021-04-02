#pragma once
#include "SDL.h"
#include "inventory.h"

struct Equiped 
{
	int WeaponId;
	meleeWeapon* equipedMeleeW;
	rangeWeapon* equipedRangeW;
	int ArmorId;
	armorItem* equipedArmor;
};

class Player
{
private:
	Inventory* inventory;
    int Location[22][32];
    SDL_Texture* PlayerTexture;
    SDL_Renderer* ren;
    static int HP[3];
    static int exp[3];
    static int mana[3];
    static int STR[2];
    static int DEX[2];
    static int INT[2];
    static int PHS[2];
    static int LCK[2];
    int damageInput;

    const Uint8* keys = SDL_GetKeyboardState(NULL);
public: 
    static int damage;
    static Equiped EqItems;
    //static int Id; // UNDONE ������� getid
    Player(SDL_Renderer* ren);
    ~Player();
    void Render();
    void Update();
    void handleEvents(SDL_Event playerEvent);

	void GetLevel(int arr[22][32]);
	void GetPlayerFirstCoords();
    static void Attack();
	void GetItemOnLvl(int id);
	void GetItemEquip(int id);
    //static void meleeAttackPlayer();

    static int GetHP(int numOfArr);
    static int GetEXP(int numOfArr);
    static int GetMana(int numOfArr);
    static int GetSpecValue(int numSpec);

    static void ChangeHpValue(int valueOfChangingHp);
    static void ChangeManaValue(int valueOfChangingMana);
    static void ChangeExpValue(int valueOfChangingExp);
    static void ChangeValueSpecs(int numOfSpec);
    static void ChangeMaxHpValue();
    static void ChangeMaxManaValue();
    static void ChangeMaxExpValue();

    static void CheckHP();
    static void CheckEXP();
    static void CheckMANA();
    static void CheckSpecVaue(int numSpec);	
};
