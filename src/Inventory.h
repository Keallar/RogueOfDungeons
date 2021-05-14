#pragma once

#include <string>
#include <vector>
#include "SDL.h"
#include <map>

#define INVENTORY_SIZE 60

enum type 
{
	weapon,
	rWeapon,
    magic,
	armor,
    potion,
    artifact
};

class InventoryItem 
{	
public:
    int COST;
	std::string name;
	const char* ItemTexture;
	SDL_Renderer* ren;
	type Type;
	std::string Description;
    int GetCost();
};

class meleeWeapon : public InventoryItem 
{
private:
	
public:
	int DMG;
	int RNG;
    meleeWeapon(int Damage, int range, int Cost, type type, const char* WeapTex, std::string Name);
	~meleeWeapon();
};
class rangeWeapon : public InventoryItem 
{
private:
	
public:
	int DMG;
	int RNG;
	int CHNS;
	int DCHNS;
    rangeWeapon(int Damage, int Range, int Chanse, int deltaChanse, int Cost, type type, const char* WeapTex, std::string Name);
	~rangeWeapon();
};

enum class magicEl {
    ice,
    fire,
    thunder
};

enum class magicType {
    field,
    point
};

class magicWeapon: public InventoryItem
{
private:

public:
    int DMG;
    int RNG;
    int SPL;
    magicEl WeaponEl;
    magicType WeaponType;
    magicWeapon(int Damage, int range, int splash, int Cost, type type, magicEl ElType, magicType WeaponType, const char* WeapTex, std::string Name);
    ~magicWeapon();
};

class Artifact : public InventoryItem
{
private:

public:
    int specs[6];
    Artifact(int STR, int DEX, int INT, int WSD, int PHS, int LCK, type type, const char* WeapTex, std::string Name);
};

class armorItem : public InventoryItem
{
private:

public:
	armorItem(int Defence, type type, const char* WeapTex, std::string Name);
	~armorItem();
	int DEF;
};

class Potion : public InventoryItem
{
public:
	int HEAL;
	int MpHEAL;
    int Cost;
	Potion(int Heal, int MpHeal, type type, const char* WeapTex, std::string Name);
};

class Inventory
{
	//InventoryItem EquipedArmor;
	//InventoryItem EquipedWeapon;
public:
	Inventory();
	~Inventory();
    int inventory[INVENTORY_SIZE];
    static int inventoryFace[INVENTORY_SIZE];
	int InventoryCount();
	void AddItem(int id);
	void EquipItem(int i, int j);
	void Update();
	meleeWeapon* GetRealMelee(int id);
	rangeWeapon* GetRealRange(int id);
	armorItem* GetRealArmor(int id);
    magicWeapon* GetRealMagic(int id);
    Artifact* GetRealArtifact(int id);
	static std::map <int, InventoryItem*> ExistingItems;
	static std::map <int, InventoryItem*>::iterator it;
};
