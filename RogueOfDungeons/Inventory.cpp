#include "Inventory.h"
#include "Managers.h"
#include <iostream>

int Inventory::inventoryFace[16]; //������ � ���� ��, ��� ������ inventory, �� � static
std::map <int, InventoryItem*> Inventory::ExistingItems;
std::map <int, InventoryItem*>::iterator Inventory::it;

Inventory::Inventory()
{
	meleeWeapon* ShortSword = new meleeWeapon(1, 1, weapon, "images/ShortSword.png");
	meleeWeapon* Spear = new meleeWeapon(2, 2, weapon, "images/Spear.png");
	meleeWeapon* Punch = new meleeWeapon(1, 1, weapon, "images/Punch.png");
	rangeWeapon* ShortBow = new rangeWeapon(1, 4, 60, 15, rWeapon, "images/ShortBow.png");
	rangeWeapon* FireBall = new rangeWeapon(2, 5, 50, 10, rWeapon, "images/FireBall.png");
	armorItem* LetherArmor = new armorItem(1, armor, "images/LetherArmor.png");
	ExistingItems = 
	{ 
		{0, ShortSword},
		{1, Spear},
		{2, ShortBow},
		{3,LetherArmor}
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
	return static_cast<meleeWeapon*>(ExistingItems[id]);
}

rangeWeapon* Inventory::GetRealRange(int id) {
	return static_cast<rangeWeapon*>(ExistingItems[id]);
}

armorItem* Inventory::GetRealArmor(int id) {
	return static_cast<armorItem*>(ExistingItems[id]);
}


rangeWeapon::rangeWeapon(int Damage, int Range, int Chance, int deltaChanse, type type, const char* WeapTex)
{
	DMG = Damage;
	RNG = Range;
	CHNS = Chance;
	DCHNS = deltaChanse;
	ItemTexture = WeapTex;
	Type = type;
}

meleeWeapon::meleeWeapon(int Damage, int range, type type, const char* WeapTex)
{
	DMG = Damage;
	RNG = range;
	ItemTexture = WeapTex;
	Type = type;
}

armorItem::armorItem(int Defence, type type, const char* WeapTex) 
{
	DEF = Defence;
	ItemTexture = WeapTex;
	Type = type;
}
