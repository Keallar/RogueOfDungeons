#include "Player.h"
#include "GameObject.h"
#include "Managers.h"
#include <iostream>
#include "EntityPosition.h"
#include "UI.h"
#include "Inventory.h"
#include "Enemy.h"
#include "Buttons.h"
#include "TextureBase.h"
#include <iostream>

Equiped Player::EqItems = { -1, nullptr, nullptr, -1};

int Player::HP[3] = {
					 10, /*hp  now*/
					 10, /*hp  previous*/
					 10	 /*hp max*/
					};

int Player::mana[3] = {
						50, /*mana  now*/
						0, /*mana  previous*/
						50 /*mana max */
					  };

int Player::exp[3] = { 
                       0,  /*exp  now*/
					   0,  /*exp  previous*/
					   100   /*exp max */
					 };

int Player::STR[2] = {
						1, /*STR  now*/
						1, /*STR  previous*/
					 };

int Player::DEX[2] = {
						1, /*DEX  now*/
						1, /*DEX  previous*/
					 };

int Player::INT[2] = {
						1, /*INT  now*/
						1, /*INT  previous*/
					 };

int Player::WSD[2] = {
						1, /*WSD  now*/
						1, /*WSD  previous*/
					 };

int Player::PHS[2] = {
						1, /*PHS  now*/
						1, /*PHS  previous*/
					 };

int Player::LCK[2] = {
						1, /*LCK  now*/
						1, /*LCK  previous*/
					 };

int Player::VIS = 16;

Player::Player(SDL_Renderer* renderer)
{
    GameTextures = TextureBase::Instance();
	ren = renderer;
    PlayerTexture = GameTextures->GetTexture("Hero");
	playerAnimation = new Animation(ren, PlayerTexture);
	generate = -1;
	for (int i = 0; i < 22; i++) 
	{
		for (int j = 0; j < 32; j++)
		{
			Location[i][j] = 0;
		}
	}

	inventory = new Inventory;
	
	inventory->AddItem(1);
	inventory->AddItem(2);
	inventory->AddItem(5);
	inventory->AddItem(3);
    inventory->AddItem(4);
	inventory->AddItem(6);
	inventory->AddItem(7);
	inventory->Update();
	EqItems.WeaponId = 0;
	EqItems.equipedMeleeW = inventory->GetRealMelee(0);
}

Player::~Player()
{
	if (HP[0] <= 0)
	{
		SDL_DestroyTexture(PlayerTexture);
	}
}

int Player::GetHP(int numOfArr)
{
    int temp = 0;
	switch (numOfArr)
	{
	case 0:
        temp = HP[0];
        break;
	case 1:
        temp = HP[1];
        break;
	case 2:
        temp = HP[2];
        break;
	default:
		break;
	}
    return temp;
}

int Player::GetEXP(int numOfArr)
{
    int temp = 0;
	switch (numOfArr)
	{
	case 0:
        temp = exp[0];
        break;
	case 1:
        temp = exp[1];
        break;
	case 2:
        temp = exp[2];
        break;
	default:
		break;
	}
return temp;
}

int Player::GetMana(int numOfArr)
{
    int temp = 0;
	switch (numOfArr)
	{
	case 0:
        temp = mana[0];
        break;
	case 1:
        temp = mana[1];
        break;
	case 2:
        temp = mana[2];
        break;
	default:
		break;
	}
    return temp;
}

//Получение значения характеристик (STR, DEX, INT, WSD, PHS, LCK)
int Player::GetSpecValue(int numSpec)
{
    int temp = 0;
	switch (numSpec)
	{
	case 1:
        temp = STR[0];
		break;
	case 2:
        temp = DEX[0];
		break;
	case 3:
        temp = INT[0];
		break;
	case 4:
        temp = WSD[0];
		break;
	case 5:
        temp = PHS[0];
		break;
	case 6:
        temp = LCK[0];
		break;
	default:
		std::cout << "Error in GetSpecValue!" << std::endl;
		break;
    }
    return temp;
}

//Изменение значения характеристики (STR, DEX, INT, PHS, LCK) на +1
void Player::ChangeValueSpecs(int numOfSpec)
{
	switch (numOfSpec)
	{
	case 1: //STR
		STR[0] += 1;
		break;
	case 2: //DEX
		DEX[0] += 1;
		break;
	case 3: //INT
		INT[0] += 1;
		break;
	case 4:
		WSD[0] += 1;
		break;
	case 5: //PHS
		PHS[0] += 1;
		break;
	case 6: //LCK
		LCK[0] += 1;
		break;
	default:
		break;
	}
}

//Изменение текущего значения hp
void Player::ChangeHpValue(int valueOfChangingHp)
{	if (HP[0] != 0 && HP[0] <= HP[2])
        HP[0] += valueOfChangingHp;
}

//Изменение текущего значения mana
void Player::ChangeManaValue(int valueOfChangingMana)
{
    if (mana[0] != 0)
        mana[0] += valueOfChangingMana;
}

//Изменение текущего значения exp
void Player::ChangeExpValue(int valueOfChangingExp)
{
	exp[0] += valueOfChangingExp;
}

//Изменение максимального значения hp
void Player::ChangeMaxHpValue()
{
	HP[2] += 1;
	HP[0] += 1;
}

//Изменение максимального значения маны
void Player::ChangeMaxManaValue()
{
	mana[2] += 10;
	mana[0] += 10;
}

//Изменение максимального значения exp
void Player::ChangeMaxExpValue()
{
	exp[2] += 100;
}

//Проверка изменения HP
void Player::CheckHP()
{
	if (Player::HP[0] != Player::HP[1] && FlagManager::flagCheckHP == 0)
	{
		FlagManager::flagCheckHP = 1;
		Player::HP[1] = Player::HP[0];
	}
	else if (Player::HP[0] == Player::HP[1] && FlagManager::flagCheckHP == 1)
	{
		FlagManager::flagCheckHP = 0;
	}
}

//Проверка изменения MANA
void Player::CheckMANA()
{
	if (Player::mana[0] != Player::mana[1] && FlagManager::flagCheckMana == 0)
	{
		FlagManager::flagCheckMana = 1;
		Player::mana[1] = Player::mana[0];
	}
	else if (Player::mana[0] == Player::mana[1] && FlagManager::flagCheckMana == 1)
	{
		FlagManager::flagCheckMana = 0;
	}
}

//Проверка изменения EXP
void Player::CheckEXP()
{
	if (Player::exp[0] != Player::exp[1] && FlagManager::flagCheckExp == 0)
	{
		FlagManager::flagCheckExp = 1;
		Player::exp[1] = Player::exp[0];
	}
	else if (Player::exp[0] == Player::exp[1] && FlagManager::flagCheckExp == 1)
	{
		FlagManager::flagCheckExp = 0;
	}
}

//Проверка изменения значений характеристик (STR, DEX, INT, PHS, LCK)
void Player::CheckSpecVaue(int numSpec)
{
	switch (numSpec)
	{
	case 1://Check STR
		if (Player::STR[0] != Player::STR[1] && FlagManager::flagSTR == 0)
		{
			FlagManager::flagSTR = 1;
			Player::STR[1] = Player::STR[0];
		}
		else if (Player::STR[0] == Player::STR[1] && FlagManager::flagSTR == 1)
		{
			FlagManager::flagSTR = 0;
		}
		break;
	case 2://Check DEX
		if (Player::DEX[0] != Player::DEX[1] && FlagManager::flagDEX == 0)
		{
			FlagManager::flagDEX = 1;
			Player::DEX[1] = Player::DEX[0];
		}
		else if (Player::DEX[0] == Player::DEX[1] && FlagManager::flagDEX == 1)
		{
			FlagManager::flagDEX = 0;
		}
		break;
	case 3://Check INT
		if (Player::INT[0] != Player::INT[1] && FlagManager::flagINT == 0)
		{
			FlagManager::flagINT = 1;
			Player::INT[1] = Player::INT[0];
		}
		else if (Player::INT[0] == Player::INT[1] && FlagManager::flagINT == 1)
		{
			FlagManager::flagINT = 0;
		}
		break;
	case 4: //Check WSD
		if (Player::WSD[0] != Player::WSD[1] && FlagManager::flagWSD == 0)
		{
			FlagManager::flagWSD = 1;
			Player::WSD[1] = Player::WSD[0];
		}
		else if (Player::WSD[0] == Player::WSD[1] && FlagManager::flagWSD == 1)
		{
			FlagManager::flagWSD = 0;
		}
		break;
	case 5://Check PHS
		if (Player::PHS[0] != Player::PHS[1] && FlagManager::flagPHS == 0)
		{
			FlagManager::flagPHS = 1;
			Player::PHS[1] = Player::PHS[0];
		}
		else if (Player::PHS[0] == Player::PHS[1] && FlagManager::flagPHS == 1)
		{
			FlagManager::flagPHS = 0;
		}
		break;
	case 6://Check LCK
		if (Player::LCK[0] != Player::LCK[1] && FlagManager::flagLCK == 0)
		{
			FlagManager::flagLCK = 1;
			Player::LCK[1] = Player::LCK[0];
		}
		else if (Player::LCK[0] == Player::LCK[1] && FlagManager::flagLCK == 1)
		{
			FlagManager::flagLCK = 0;
		}
		break;
	default:
		std::cout << "Error in CheckSpecValue" << std::endl;
		break;
	}
}


void Player::GetLevel(int arr[22][32])
{
	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 32; j++) 
		{
			Location[i][j] = arr[i][j];
		}
	}
}

void Player::GetPlayerFirstCoords()
{
	EntityPosition::Coords[0] = (rand() % 2 + 1) * 32;
	EntityPosition::Coords[1] = (rand() % 20 + 1) * 32;
	if (generate != 4 && generate != 5) {
		while ((Location[EntityPosition::Coords[1] / 32][EntityPosition::Coords[0] / 32] == 1) ||
			((Location[EntityPosition::Coords[1] / 32][EntityPosition::Coords[0] / 32 - 1] != 0) &&
			(Location[EntityPosition::Coords[1] / 32][EntityPosition::Coords[0] / 32 + 1] != 0) &&
				(Location[EntityPosition::Coords[1] / 32 - 1][EntityPosition::Coords[0] / 32] != 0) &&
				(Location[EntityPosition::Coords[1] / 32 + 1][EntityPosition::Coords[0] / 32] != 0)))
		{
			EntityPosition::Coords[0] = (rand() % 2 + 1) * 32;
			EntityPosition::Coords[1] = (rand() % 20 + 1) * 32;
		}
	}
	else {
		while ((Location[EntityPosition::Coords[1] / 32][EntityPosition::Coords[0] / 32] == 1))
		{
			EntityPosition::Coords[0] = (rand() % 2 + 1) * 32;
			EntityPosition::Coords[1] = (rand() % 20 + 1) * 32;
		}
	}
}

void Player::GetItemDrop(int id) {
	if (id != -1) {
		inventory->inventory[id] = -1;
	}
	FlagManager::flagDrop = -1;
}

void Player::GetItemEquip(int id) 
{
	if (id != -1)
	{
		int ItemId = inventory->inventory[id];
		if (Inventory::ExistingItems[ItemId]->Type == weapon) 
		{
			if (EqItems.WeaponId > 0) 
			{
				inventory->inventory[id] = EqItems.WeaponId;
			}
			else
			{
				inventory->inventory[id] = -1;
			}
			EqItems.WeaponId = ItemId;
			EqItems.equipedMeleeW = inventory->GetRealMelee(ItemId);
			EqItems.equipedRangeW = nullptr;
		}
		if (Inventory::ExistingItems[ItemId]->Type == rWeapon) 
		{
			if (EqItems.WeaponId > 0) 
			{
				inventory->inventory[id] = EqItems.WeaponId;
			}
			else 
			{
				inventory->inventory[id] = -1;
			}
			EqItems.WeaponId = ItemId;
			
			EqItems.equipedRangeW = inventory->GetRealRange(ItemId);
			EqItems.equipedMeleeW = nullptr;
		}
		if (Inventory::ExistingItems[ItemId]->Type == armor) 
		{
			if (EqItems.ArmorId > 0) {
				inventory->inventory[id] = EqItems.ArmorId;
			}
			else 
			{
				inventory->inventory[id] = -1;
			}
			EqItems.ArmorId = ItemId;

			EqItems.equipedArmor = inventory->GetRealArmor(ItemId);
			if (EqItems.equipedArmor->name == "LetherArmor")
			{
				SDL_DestroyTexture(PlayerTexture);
				PlayerTexture = 0;
				PlayerTexture = textureManager::LoadTexture("data/images/HeroLether.png", ren);
				playerAnimation->UpdateTexture("data/images/HeroLether.png");
			}
		}
		if (Inventory::ExistingItems[ItemId]->Type == potion) {
			ChangeHpValue(static_cast<Potion*>(Inventory::ExistingItems[ItemId])->HEAL);
			ChangeManaValue(static_cast<Potion*>(Inventory::ExistingItems[ItemId])->MpHEAL);
			inventory->inventory[id] = -1;
		}
	}
	FlagManager::flagEquip = -1;
}

void Player::GetItemUnEquip(int id) 
{
	if (inventory->InventoryCount() != 16) 
	{
		if (id == 0) 
		{
			inventory->AddItem(EqItems.WeaponId);
			EqItems.WeaponId = 0;
			EqItems.equipedMeleeW = inventory->GetRealMelee(0);
			EqItems.equipedRangeW = nullptr;
		}
		if (id == 1) 
		{
			inventory->AddItem(EqItems.ArmorId);
			EqItems.ArmorId = -1;
			EqItems.equipedArmor = nullptr;
			SDL_DestroyTexture(PlayerTexture);
			PlayerTexture = 0;
			PlayerTexture = textureManager::LoadTexture("data/images/Hero.png", ren);
			playerAnimation->UpdateTexture("data/images/Hero.png");
		}
	}
	FlagManager::flagUnEquip = -1;
}

bool Player::InventoryBlock() {
	int count = inventory->InventoryCount();
	if (count == 16) {
		return true;
	}
	else {
		return false;
	}
}

void Player::GetItemOnLvl(int id) 
{
	inventory->AddItem(id);
}

void Player::Render()
{
	playerAnimation->Render(EntityPosition::Coords[0], EntityPosition::Coords[1]);
}

void Player::Update()
{
	Player::GetItemDrop(FlagManager::flagDrop);
	Player::GetItemEquip(FlagManager::flagEquip);
	Player::GetItemUnEquip(FlagManager::flagUnEquip);
	inventory->Update();
	Player::CheckHP();
	Player::CheckMANA();
	Player::CheckEXP();
	Player::CheckSpecVaue(1); //STR
	Player::CheckSpecVaue(2); //DEX
	Player::CheckSpecVaue(3); //INT
	Player::CheckSpecVaue(4); //WSD
	Player::CheckSpecVaue(5); //PHS
	Player::CheckSpecVaue(6); //LCK
}

void Player::handleEvents(SDL_Event playerEvent)
{
	
}

void Player::clean()
{
	SDL_DestroyTexture(PlayerTexture);
}

int Player::damage = 0;

void Player::playerTurn()
{
	FlagManager::flagPlayer = 1;
	FlagManager::flagMeleeAttackPlayer = 1;
	FlagManager::flagRangeAttack = 1;
	FlagManager::flagEnemy = 0;
	FlagManager::flagMeleeAttackEnemy = 0;
}
int	Player::MeleeAttack() 
{
	if (Inventory::ExistingItems[Player::EqItems.WeaponId]->Type == weapon) 
	{
		std::cout << "Melee boy" << std::endl;
			damage = Player::EqItems.equipedMeleeW->DMG + Player::STR[0];
			std::cout << damage << std::endl;
	}
    return damage;
}
int Player::RangeAttack() 
{
	if ((Inventory::ExistingItems[Player::EqItems.WeaponId]->Type == rWeapon) &&
		FlagManager::flagRangeAttack == 1 &&
		Player::mana[0] != 0) 
	{
		damage = Player::EqItems.equipedRangeW->DMG + Player::DEX[0];
		std::cout << damage << "!" << std::endl;
	}
    return damage;
}
