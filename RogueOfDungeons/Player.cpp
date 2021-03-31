#include "Player.h"
#include "GameObject.h"
#include "Managers.h"
#include <iostream>
#include "EntityPosition.h"
#include "UI.h"
#include "inventory.h"
#include "Enemy.h"
#include "Buttons.h"

int Player::Id = -2;
Equiped Player::EqItems = { -1, nullptr, nullptr };

int Player::HP[3] = {
					 10, /*hp  now*/
					 10, /*hp  previous*/
					 10	 /*hp max*/
					};
int Player::exp[3] = { 
					   99, /*exp  now*/
					   99,  /*exp  previous*/
					   0   /*exp max */
					 };

int Player::mana[3] = { 
					    0, /*mana  now*/
						0, /*mana  previous*/
						50 /*mana max */
					  };

int Player::STR[2] = {
						1, /*STR  now*/
						1, /*STR  previous*/
					 };

int Player::DEX[2] = {
						1, /*STR  now*/
						1, /*STR  previous*/
					 };

int Player::INT[2] = {
						1, /*STR  now*/
						1, /*STR  previous*/
					 };

int Player::PHS[2] = {
						1, /*STR  now*/
						1, /*STR  previous*/
					 };

int Player::LCK[2] = {
						1, /*STR  now*/
						1, /*STR  previous*/
					 };

Player::Player(const char* texturesheet, SDL_Renderer* renderer)
{
	//EqItems = { -1, nullptr, nullptr };
	ren = renderer;
	PlayerTexture = textureManager::LoadTexture(texturesheet, ren);
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 32; j++) {
			Location[i][j] = 0;
		}
	}
	inventory = new Inventory;
	
	inventory->AddItem(0);
	inventory->AddItem(1);
	inventory->AddItem(0);
	inventory->Update();
}

Player::~Player()
{
	if (HP == 0)
	{
		SDL_DestroyTexture(PlayerTexture);
	}
}

int Player::GetHP(int numOfArr)
{
	switch (numOfArr)
	{
	case 0:
		return HP[0];
	case 1:
		return HP[1];
	case 2:
		return HP[2];
	default:
		break;
	}
}

int Player::GetEXP()
{
	return exp[0];
}

int Player::GetMana(int numOfArr)
{
	switch (numOfArr)
	{
	case 0:
		return mana[0];
	case 1:
		return mana[1];
	case 2:
		return mana[2];
	default:
		break;
	}

}

//Получение значения характеристик (STR, DEX, INT, PHS, LCK)
int Player::GetSpecValue(int numSpec)
{
	switch (numSpec)
	{
	case 1:
		return STR[0];
		break;
	case 2:
		return DEX[0];
		break;
	case 3:
		return INT[0];
		break;
	case 4:
		return PHS[0];
		break;
	case 5:
		return LCK[0];
		break;
	default:
		std::cout << "Error in GetSpecValue!" << std::endl;
		break;
	}
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
	case 4: //PHS
		PHS[0] += 1;
		break;
	case 5: //LCK
		LCK[0] += 1;
		break;
	default:
		break;
	}
}

void Player::GetLevel(int arr[22][32])
{
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 32; j++) {
			Location[i][j] = arr[i][j];
		}
	}
}

void Player::GetPlayerFirstCoords()
{
	EntityPosition::Coords[0] = (rand() % 2 + 1) * 32;
	EntityPosition::Coords[1] = (rand() % 20 + 1) * 32;
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

void Player::GetItemEquip(int id) {
	if (id != -1) {
		int ItemId = inventory->inventory[id];
		if (Inventory::ExistingItems[ItemId].Type == weapon) {
			if (EqItems.WeaponId != -1) {
				inventory->inventory[id] = EqItems.WeaponId;
			}
			else {
				inventory->inventory[id] = -1;
			}
			EqItems.WeaponId = ItemId;
			EqItems.equipedMeleeW = inventory->GetRealMelee(ItemId);
			EqItems.equipedRangeW = nullptr;
		}
		if (Inventory::ExistingItems[ItemId].Type == rWeapon) {
			if (EqItems.WeaponId != -1) {
				inventory->inventory[id] = EqItems.WeaponId;
			}
			else {
				inventory->inventory[id] = -1;
			}
			EqItems.WeaponId = ItemId;
			
			EqItems.equipedRangeW = inventory->GetRealRange(ItemId);
			EqItems.equipedMeleeW = nullptr;
		}
	}
	FlagManager::flagEquip = -1;
}

void Player::ChangeHpValue(int valueOfChangingHp)
{
	HP[0] -= valueOfChangingHp;
}

//Изменение максимального значения hp
void Player::ChangeMaxHpValue()
{
	HP[2] += 1;
}

//Изменение максимального значения маны
void Player::ChangeMaxManaValue()
{
	mana[2] += 10;
}

//Изменение максимального значения exp
void Player::ChangeMaxExpValue()
{
	exp[2] += 100;
}

//Проверка изменения HP
void Player::CheckHP()
{
	if (Player::HP[0] != Player::HP[1] && FlagManager::flagCheckHP ==  0)
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
	case 4://Check PHS
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
	case 5://Check LCK
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

void Player::GetItemOnLvl(int id) 
{
	inventory->AddItem(id);
}

void Player::Render()
{
	RenderManager::CopyToRender(PlayerTexture, ren, EntityPosition::Coords[0], EntityPosition::Coords[1], 32, 32, 0, 0, 32, 32);
	std::cout << EqItems.equipedMeleeW << " "<< EqItems.equipedRangeW << " "<<EqItems.WeaponId << std::endl;
	Player::Id = EqItems.WeaponId;
}

void Player::Update()
{
	Player::GetItemEquip(FlagManager::flagEquip);
	inventory->Update();
	Player::CheckHP();
	Player::CheckMANA();
	Player::CheckEXP();
	Player::CheckSpecVaue(1); //STR
	Player::CheckSpecVaue(2); //DEX
	Player::CheckSpecVaue(3); //INT
	Player::CheckSpecVaue(4); //PHS
	Player::CheckSpecVaue(5); //LCK
}

void Player::handleEvents(SDL_Event playerEvent)
{
	switch (playerEvent.type)
	{
	case SDL_KEYDOWN:
		if (keys[SDL_SCANCODE_W])
		{
			if (EntityPosition::Coords[1] == 32)
			{
				//остановка при упоре в стену
			}
			else if (EntityPosition::Coords[0] == EntityPosition::Coords[2] &&
				(EntityPosition::Coords[1] - 32) == EntityPosition::Coords[3])
			{
				std::cout << "Stop Enemy W" << std::endl;
				//остановка при попытке пройти сквозь enemy
			}
			else
			{
				if (Location[(EntityPosition::Coords[1]) / 32 - 1][(EntityPosition::Coords[0]) / 32] == 0) 
				{
					EntityPosition::Coords[1] -= 32;
					FlagManager::flagPlayer = 0;
					FlagManager::flagEnemy = 1;
				}
				if (Location[(EntityPosition::Coords[1]) / 32 - 1][(EntityPosition::Coords[0]) / 32] == 3) 
				{
					FlagManager::flagChest = 1;
				}
				if (EntityPosition::Coords[0] == EntityPosition::Coords[2] &&
					(EntityPosition::Coords[1] - 32) == EntityPosition::Coords[3])
				{
					//удар при определённой позиции Enemy
				}
			}
		}

		else if (keys[SDL_SCANCODE_A])
		{
			if (EntityPosition::Coords[0] == 32)
			{
				//остановка при упоре в стену
			}
			else if ((EntityPosition::Coords[0] - 32) == EntityPosition::Coords[2] &&
				EntityPosition::Coords[1] == EntityPosition::Coords[3])
			{
				std::cout << "Stop Enemy A" << std::endl;
				//остановка при попытке пройти сквозь enemy
			}
			else
			{
				if (Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 - 1] == 0) 
				{
					EntityPosition::Coords[0] -= 32;
					Player::mana[0] += 1;
					FlagManager::flagPlayer = 0;
					FlagManager::flagEnemy = 1;
				}
				if (Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 - 1] == 3)
				{
					FlagManager::flagChest = 2;
				}
				if ((EntityPosition::Coords[0] - 32) == EntityPosition::Coords[2] &&
					EntityPosition::Coords[1] == EntityPosition::Coords[3])
				{
					//удар при определённой позиции Enemy
				}
			}
		}

		else if (keys[SDL_SCANCODE_S])
		{
			if (EntityPosition::Coords[1] == 640)
			{
				//остановка при упоре в стену
			}
			else if (EntityPosition::Coords[0] == EntityPosition::Coords[2] && 
				(EntityPosition::Coords[1] + 32) == EntityPosition::Coords[3])
			{
				std::cout << "Stop Enemy S" << std::endl;
				//остановка при попытке пройти сквозь enemy
			}
			else
			{
				if (Location[(EntityPosition::Coords[1]) / 32 + 1][(EntityPosition::Coords[0]) / 32] == 0) 
				{
					EntityPosition::Coords[1] += 32;
					Player::exp[0] -= 1;
					FlagManager::flagPlayer = 0;
					FlagManager::flagEnemy = 1;
				}
				if (Location[(EntityPosition::Coords[1]) / 32 + 1][(EntityPosition::Coords[0]) / 32] == 3)
				{
					FlagManager::flagChest = 3;
				}
				if (EntityPosition::Coords[0] == EntityPosition::Coords[2] &&
					(EntityPosition::Coords[1] + 32) == EntityPosition::Coords[3])
				{
					//удар при определённой позиции Enemy
				}
			}
		}

		else if (keys[SDL_SCANCODE_D])
		{
			if (EntityPosition::Coords[0] == 960)
			{
				//остановка при упоре в стену
			}
			else if ((EntityPosition::Coords[0] + 32) == EntityPosition::Coords[2] &&
				EntityPosition::Coords[1] == EntityPosition::Coords[3])
			{
				std::cout << "Stop Enemy D" << std::endl;
				//остановка при попытке пройти сквозь enemy
			}
			else
			{
				if (Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 + 1] == 0)
				{
					EntityPosition::Coords[0] += 32;
					FlagManager::flagPlayer = 0;
					FlagManager::flagEnemy = 1;
				}
				if (Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 + 1] == 3) 
				{
					FlagManager::flagChest = 4;
				}
			}
		}
		case SDL_MOUSEBUTTONDOWN:

			//атака при нажатии мыши
			MouseButtonsPlayer::buttonsForAttack();


	default:
		break;
	}
}

void meleeAttackPlayer()
{
	if ((EntityPosition::Coords[0] + 32) == EntityPosition::Coords[2] &&
		EntityPosition::Coords[1] == EntityPosition::Coords[3] &&
		FlagManager::flagAttackPlayer == 1 &&
		FlagManager::flagAttackEnemy == 0 &&
		FlagManager::flagPlayer == 1 &&
		FlagManager::flagEnemy == 0)
	{
		std::cout << "Player attack enemy" << std::endl;
		Enemy::ChahgeHpEnemy(3);
	}
}

//void Player::Attack(Equiped typeOfEqItem)
//{
//	if (typeOfEqItem.equipedMeleeW = 1 && typeOfEqItem.equipedRangeW = 0)
//	{
//		//UNDONE сделать условие для всех позиций enemy
//		if ((EntityPosition::Coords[0] + 32) == EntityPosition::Coords[2] &&
//			EntityPosition::Coords[1] == EntityPosition::Coords[3] &&
//			FlagManager::flagAttackPlayer == 1 &&
//			FlagManager::flagAttackEnemy == 0 &&
//			FlagManager::flagPlayer == 1 &&
//			FlagManager::flagEnemy == 0)
//		{
//			std::cout << "Player attack enemy" << std::endl;
//			Enemy::ChahgeHpEnemy(3);
//		}
//	}
//	else if (typeOfEqItem.equipedMeleeW = 0 && typeOfEqItem.equipedRangeW = 1)
//	{
//		
//	}
//}

