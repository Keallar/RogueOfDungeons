#include "Inventory.h"
#include "Managers.h"
#include <iostream>

int Inventory::inventoryFace[16];
std::map <int, InventoryItem> Inventory::ExistingItems;
std::map <int, InventoryItem>::iterator Inventory::it;

Inventory::Inventory()
{
	meleeWeapon *ShortSword = new meleeWeapon(2, 1, weapon, "images/ShortSword.png");
	meleeWeapon* Spear = new meleeWeapon(3, 0, weapon, "images/ShortSword.png");
	rangeWeapon* ShortBow = new rangeWeapon(1, 4, 60, 15, rWeapon, "images/ShortSword.png");
	ExistingItems = 
	{ 
		{0, *ShortSword},
		{1, *Spear},
		{2, *ShortBow} 
	};
	for (int i = 0; i < 16; i++) 
	{
		inventory[i] = -1;
	}
}
void Inventory::EquipItem(int i, int j) 
{
	//EquipedArmor = ExistingItems[i];
	//EquipedWeapon = ExistingItems[j];
}
void Inventory::AddItem(int id) 
{
	int count = 0;
	for (int i = 0; i < 16; i++) 
	{
		if (inventory[i] == -1) 
		{
			inventory[i] = id;
			count = -1;
		}
		count++;
		if (count == 16) 
		{
			std::cout << "ÍÅÒ ÌÅÑÒÀÀÀÀÀÀÀ!!!" << std::endl;
		}
	}
}

void Inventory::Update() 
{
	for (int i = 0; i < 16; i++) 
	{
		inventoryFace[i] = inventory[i];
	}
}


rangeWeapon::rangeWeapon(int Damage, int Range, int Chanse, int deltaChanse, type type, const char* WeapTex)
{
	DMG = Damage;
	RNG = Range;
	CHNS = Chanse;
	DCHNS = deltaChanse;
	Type = type;
	ItemTexture = WeapTex;
}

meleeWeapon::meleeWeapon(int Damage, int range, type type, const char* WeapTex)
{
	DMG = Damage;
	RNG = range;
	Type = type;
	ItemTexture = WeapTex;
}
