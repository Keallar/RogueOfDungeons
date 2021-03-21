#pragma once

#include <string>
#include <vector>
#include "SDL.h"
#include <map>

enum type {
	weapon,
	rWeapon,
	armor,
	other
};

class Inventory {
public:
	Inventory();
	int inventory[16];
	static int inventoryFace[16];
	static std::map <int, InventoryItem> ExistingItems;
	void AddItem(int id);
	void Update();
};









class InventoryItem {
public:
	std::string name;
	SDL_Texture* ItemTexture;
	SDL_Renderer* ren;
	type Type;
	std::string Description;
};

class meleeWeapon : public InventoryItem {
private:
	int DMG;
	int RNG;
public:
	meleeWeapon(int Damage, int range, type type, const char* WeapTex);
};
class rangeWeapon : public InventoryItem 
{
private:
	int DMG;
	int RNG;
	int CHNS;
	int DCHNS;
public:
	rangeWeapon(int Damage, int Range, int Chanse, int deltaChanse, type type, const char* WeapTex);
};