#pragma once
#include "SDL.h"
#include "Inventory.h"
#include "GameObject.h"
#include "Animation.h"
#include "TextureBase.h"

struct Equiped 
{
	int WeaponId;
	meleeWeapon* equipedMeleeW;
	rangeWeapon* equipedRangeW;
    magicWeapon* equipedMagic;
	int ArmorId;
	armorItem* equipedArmor;
};

class Player : public GameObject
{
private:
    TextureBase* GameTextures;
	Inventory* inventory;
    int Location[22][32];
    SDL_Texture* PlayerTexture;
    SDL_Renderer* ren;
    int damageInput;
    Animation* playerAnimation;
    bool completePlayerAnimation;
    static int HP[3];
    static int exp[3];
    static int mana[3];
    static int STR[2];
    static int DEX[2];
    static int INT[2];
    static int WSD[2];
    static int PHS[2];
    static int LCK[2];
    static int pointOfSpec[3];
    static int levelOfPlayer[3];
    static int quantityOfCoins[3];
public:
    bool playerEscaping;
	bool InventoryBlock();
	int generate;
	static int VIS;
    static int damage;
    static Equiped EqItems;
    Player(const char* texturesheet, SDL_Renderer* ren);
    void Update() override;
    void Render() override;

	void GetLevel(int arr[22][32]);
	void GetPlayerFirstCoords();
    int MeleeAttack();
    int RangeAttack();
    int MagicAttack();
	void GetItemOnLvl(int id);
	void GetItemEquip(int id);
	void GetItemUnEquip(int id);
	void GetItemDrop(int id);

    static int GetHP(int numOfArr);
    static int GetEXP(int numOfArr);
    static int GetMana(int numOfArr);
    static int GetSpecValue(int numSpec);
    static int GetPointOfSpec(int numPoint);
    static int GetLevelOfPlayer(int numLvl);
    static int GetCoinsOfPlayer(int numCoins);

    static void ChangeHpValue(int valueOfChangingHp);
    static void ChangeManaValue(int valueOfChangingMana);
    static void ChangeExpValue(int valueOfChangingExp);
    static void ChangeValueSpecs(int numOfSpec);
    static void ChangeMaxHpValue();
    static void ChangeMaxManaValue();
    static void ChangeMaxExpValue();
    static void ChangeCoins(int value);

    void CheckHP();
    void CheckEXP();
    void CheckMANA();
    void CheckSpecValue(int numSpec);
    void CheckPointOfSpec();
    void CheckLevelOfPlayer();
    void CheckCoinsOfPlayer();

    static void playerTurn();
};
