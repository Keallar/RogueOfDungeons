#include "Inventory.h"
#include "Managers.h"
#include <string>
#include <iostream>
#include <fstream>

int Inventory::inventoryFace[16]; //������ � ���� ��, ��� ������ inventory, �� � static
std::map <int, InventoryItem*> Inventory::ExistingItems;
std::map <int, InventoryItem*>::iterator Inventory::it;

Inventory::Inventory()
{
	std::ifstream file;
	file.open("Items.txt");
	int ItemNumber = 0;
	while (file) {
		std::string Type;
		int DMG;
		int RNG;
		std::string WeapTex;
		std::string Name;
		int CHS;
		int dCHS;
		int DEF;
		file >> Type;
		if (Type == "weapon") {
			file >> DMG;
			file >> RNG;
			file >> WeapTex;
			char* Tex = new char[WeapTex.length()+1];
			for (int i = 0; i <= WeapTex.length(); i++) {
				Tex[i] = WeapTex[i];
			}
			file >> Name;
			type ItemType = weapon;
			ExistingItems[ItemNumber] = new meleeWeapon(DMG, RNG, ItemType, Tex, Name);
		}
		if (Type == "rWeapon") {
			file >> DMG;
			file >> RNG;
			file >> CHS;
			file >> dCHS;
			file >> WeapTex;
			char* Tex = new char[WeapTex.length() + 1];
			for (int i = 0; i <= WeapTex.length(); i++) {
				Tex[i] = WeapTex[i];
			}
			file >> Name;
			type ItemType = rWeapon;
			ExistingItems[ItemNumber] = new rangeWeapon(DMG, RNG, CHS, dCHS, ItemType, Tex, Name);
		}
		if (Type == "armor") {
			file >> DEF;
			file >> WeapTex;
			char* Tex = new char[WeapTex.length() + 1];
			for (int i = 0; i <= WeapTex.length(); i++) {
				Tex[i] = WeapTex[i];
			}
			file >> Name;
			type ItemType = armor;
			ExistingItems[ItemNumber] = new armorItem(DEF, ItemType, Tex, Name);
		}
		ItemNumber++;
	}
	for (int i = 0; i < 16; i++) 
	{
		inventory[i] = -1;
	}
}

Inventory::~Inventory() {

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


rangeWeapon::rangeWeapon(int Damage, int Range, int Chance, int deltaChanse, type type, const char* WeapTex, std::string Name)
{
	DMG = Damage;
	RNG = Range;
	CHNS = Chance;
	DCHNS = deltaChanse;
	ItemTexture = WeapTex;
	Type = type;
	name = Name;
}

meleeWeapon::meleeWeapon(int Damage, int range, type type, const char* WeapTex, std::string Name)
{

	DMG = Damage;
	RNG = range;
	ItemTexture = WeapTex;
	Type = type;
	name = Name;
}

armorItem::armorItem(int Defence, type type, const char* WeapTex, std::string Name)
{
	DEF = Defence;
	ItemTexture = WeapTex;
	Type = type;
	name = Name;
}
