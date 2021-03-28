#include "Inventory.h"
#include "Managers.h"
#include <iostream>

int Inventory::inventoryFace[16]; //хранит в себе всЄ, что хранит inventory, но в static
std::map <int, InventoryItem> Inventory::ExistingItems;
std::map <int, InventoryItem>::iterator Inventory::it;

Inventory::Inventory()
{
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
			break;
		}
		count++;
		if (count == 16) 
		{
			std::cout << "Ќ≈“ ћ≈—“јјјјјјј!!!" << std::endl;
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

meleeWeapon* Inventory::GetRealMelee(int id) {
	switch (id) {
	case 0:
		return ShortSword;
	case 2:
		return Spear;
	}
}

rangeWeapon* Inventory::GetRealRange(int id) {
	switch (id) {
	case 1:
		return ShortBow;
	}
}

rangeWeapon::rangeWeapon(int Damage, int Range, int Chanse, int deltaChanse, type type, const char* WeapTex)
{
	DMG = Damage;
	RNG = Range;
	CHNS = Chanse;
	DCHNS = deltaChanse;
	ItemTexture = WeapTex;
}

meleeWeapon::meleeWeapon(int Damage, int range, type type, const char* WeapTex)
{
	DMG = Damage;
	RNG = range;
	ItemTexture = WeapTex;
}

/*void EquipedItems::EquipItem() 
{
	
}*/