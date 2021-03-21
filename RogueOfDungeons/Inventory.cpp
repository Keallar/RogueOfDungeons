#include "Inventory.h"
#include "Managers.h"
#include <iostream>

int Inventory::inventoryFace[16];

Inventory::Inventory()
{
	meleeWeapon *ShortSword = new meleeWeapon(2, 1, weapon, "ShortSword.png");
	meleeWeapon* Spear = new meleeWeapon(3, 0, weapon, "ABOBA.png");
	rangeWeapon* ShortBow = new rangeWeapon(1, 4, 60, 15, rWeapon, "ABOBA.png");
	std::map <int, InventoryItem> ExistingItems
	{ 
		{0, *ShortSword},
		{1, *Spear},
		{101, *ShortBow} 
	};
	std::map <int, const char*> ItemTextureName
	{
		{0, "ShortSword.png"},
		{1, "Spear.png"},
		{101, "ShortBow.png"}
	};
	for (int i = 0; i < 16; i++) {
		inventory[i] = -1;
	}
}
void Inventory::EquipItem(int i, int j) 
{
	//EquipedArmor = ExistingItems[i];
	//EquipedWeapon = ExistingItems[j];
}
void Inventory::AddItem(int id) {
	int count = 0;
	for (int i = 0; i < 16; i++) {
		if (inventory[i] == -1) {
			inventory[i] = id;
			count = -1;
		}
		count++;
		if (count == 16) {
			std::cout << "ÍÅÒ ÌÅÑÒÀÀÀÀÀÀÀ!!!" << std::endl;
		}
	}
}

void Inventory::Update() {
	for (int i = 0; i < 16; i++) {
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
	ItemTexture = textureManager::LoadTexture(WeapTex, ren);
}

meleeWeapon::meleeWeapon(int Damage, int range, type type, const char* WeapTex)
{
	DMG = Damage;
	RNG = range;
	Type = type;
	ItemTexture = textureManager::LoadTexture(WeapTex, ren);
}
