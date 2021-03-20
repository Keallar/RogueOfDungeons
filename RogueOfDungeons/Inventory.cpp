#include "Inventory.h"
#include "Managers.h"

meleeWeapon::meleeWeapon(int Damage, int range, type type, const char* WeapTex)
{
	DMG = Damage;
	RNG = range;
	Type = type;
	ItemTexture = textureManager::LoadTexture(WeapTex, ren);
}

Inventory::Inventory()
{
	meleeWeapon *ShortSword = new meleeWeapon(2, 1, weapon, "ABOBA.png");
	meleeWeapon* Spear = new meleeWeapon(3, 0, weapon, "ABOBA.png");
	rangeWeapon* ShortBow = new rangeWeapon(1, 4, 60, 15, rWeapon, "ABOBA.png");
	std::map <int, InventoryItem> ExistingItems
	{ {0, *ShortSword},
	  {1, *Spear},
	  {101, *ShortBow} };
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