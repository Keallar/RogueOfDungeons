#pragma once

#include <string>
#include <vector>
#include "SDL.h"
#include <map>
enum type 
{
	weapon,
	rWeapon,
	armor,
	other
};

class InventoryItem 
{	
public:
	std::string name;
	const char* ItemTexture;
	SDL_Renderer* ren;
	type Type;
	std::string Description;
};

class meleeWeapon : public InventoryItem 
{
private:
	
public:
	int DMG;
	int RNG;
	meleeWeapon(int Damage, int range, type type, const char* WeapTex, std::string Name);
};
class rangeWeapon : public InventoryItem 
{
private:
	
public:
	int DMG;
	int RNG;
	int CHNS;
	int DCHNS;
	rangeWeapon(int Damage, int Range, int Chanse, int deltaChanse, type type, const char* WeapTex, std::string Name);
};

class armorItem : public InventoryItem
{
private:

public:
	armorItem(int Defence, type type, const char* WeapTex, std::string Name);
	int DEF;
};

class Inventory
{
	//InventoryItem EquipedArmor;
	//InventoryItem EquipedWeapon;
public:
	Inventory();
	~Inventory();
	int inventory[16]; // хранит в себе вcе айтемы и они лежат в inventoryFace ещё (он не static)
	static int inventoryFace[16];
	void AddItem(int id);
	void EquipItem(int i, int j);
	void Update();
	meleeWeapon* GetRealMelee(int id);
	rangeWeapon* GetRealRange(int id);
	armorItem* GetRealArmor(int id);
	static std::map <int, InventoryItem*> ExistingItems;
	static std::map <int, InventoryItem*>::iterator it;
};
/*class EquipedItems 
{
private:
public:
	int Equiped[3];
	EquipedItems();
	void EquipItem();
};*/
//static std::map <int, InventoryItem>::iterator it;
