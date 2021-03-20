#pragma once

#include <string>
#include <vector>
#include <SDL.h>
#include <map>

enum type {
	weapon,
	armor,
	other
};

class Inventory {
	std::map <int, InventoryItem> inventory;
	std::map <int, InventoryItem> ExistingItems;

};

class InventoryItem {
public:
	std::string name;
	SDL_Texture* ItemTexture;
	type Type;
	std::string Description;
};

class Weapon : public InventoryItem {
public:
	int STR;
	int AGI;
	int INT;
	int DMG;
	bool rangeDamage;
	int range;
};