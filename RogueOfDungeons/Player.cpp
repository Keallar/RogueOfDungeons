#include "Player.h"
#include "GameObject.h"
#include "Managers.h"
#include <iostream>
#include "EntityPosition.h"
#include "UI.h"
#include "inventory.h"

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

int Player::GetHP()
{
	return HP[0];
}

int Player::GetEXP()
{
	return exp[0];
}

int Player::GetMana()
{
	return mana[0];
}

int Player::GetSTR()
{
	return STR[0];
}

void Player::ChangeSTR()
{
	STR[0] += 1;
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

void Player::CheckHP()
{
	if (Player::HP[0] != Player::HP[1] && FlagManager::flagCheckHP ==  0)
	{
		//std::cout << "Check HP 1" << std::endl;
		FlagManager::flagCheckHP = 1;
		Player::HP[1] = Player::HP[0];
	}
	else if (Player::HP[0] == Player::HP[1] && FlagManager::flagCheckHP == 1)
	{
		//std::cout << "Check HP 0" << std::endl;
		FlagManager::flagCheckHP = 0;
	}
}

void Player::CheckMANA()
{
	if (Player::mana[0] != Player::mana[1] && FlagManager::flagCheckMana == 0)
	{
		//std::cout << "Check HP 1" << std::endl;
		FlagManager::flagCheckMana = 1;
		Player::mana[1] = Player::mana[0];
	}
	else if (Player::mana[0] == Player::mana[1] && FlagManager::flagCheckMana == 1)
	{
		//std::cout << "Check HP 0" << std::endl;
		FlagManager::flagCheckMana = 0;
	}
}

void Player::CheckEXP()
{
	if (Player::exp[0] != Player::exp[1] && FlagManager::flagCheckExp == 0)
	{
		//std::cout << "Check HP 1" << std::endl;
		FlagManager::flagCheckExp = 1;
		Player::exp[1] = Player::exp[0];
	}
	else if (Player::exp[0] == Player::exp[1] && FlagManager::flagCheckExp == 1)
	{
		//std::cout << "Check HP 0" << std::endl;
		FlagManager::flagCheckExp = 0;
	}
}

void Player::CheckSTR()
{
	if (Player::STR[0] != Player::STR[1] && FlagManager::flagSTR == 1)
	{
		//std::cout << "Check HP 1" << std::endl;
		FlagManager::flagSTR = 1;
		Player::STR[1] = Player::STR[0];
	}
	else if (Player::STR[0] == Player::STR[1] && FlagManager::flagSTR == 0)
	{
		//std::cout << "Check HP 0" << std::endl;
		FlagManager::flagSTR = 0;
	}
}



void Player::Render()
{
	RenderManager::CopyToRender(PlayerTexture, ren, EntityPosition::Coords[0], EntityPosition::Coords[1], 32, 32, 0, 0, 32, 32);
}

void Player::Update()
{
	//inventory->Update();
	Player::CheckHP();
	Player::CheckMANA();
	Player::CheckEXP();
	Player::CheckSTR();
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
				//��������� ��� ����� � �����
			}
			else
			{
				if (Location[(EntityPosition::Coords[1]) / 32 - 1][(EntityPosition::Coords[0]) / 32] == 0) 
				{
					EntityPosition::Coords[1] -= 32;
					if (Player::HP[0] != 0)
						Player::HP[0] -= 1;
					FlagManager::flagPlayer = 0;
					//std::cout << "w" << EntityPosition::Coords[0] << EntityPosition::Coords[1] << std::endl;
					//SDL_Delay(100);
				}
			}
		}

		else if (keys[SDL_SCANCODE_A])
		{
			if (EntityPosition::Coords[0] == 32)
			{
				//остановка при упоре в стену
			}
			else
			{
				if (Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 - 1] == 0) 
				{
					EntityPosition::Coords[0] -= 32;
					Player::mana[0] += 1;
					FlagManager::flagPlayer = 0;
					//sdt::cout << "a" << std::endl;
					//SDL_Delay(100);
				}
			}
		}

		else if (keys[SDL_SCANCODE_S])
		{
			if (EntityPosition::Coords[1] == 640)
			{
				//остановка при упоре в стену
			}
			else
			{
				if (Location[(EntityPosition::Coords[1]) / 32 + 1][(EntityPosition::Coords[0]) / 32] == 0) 
				{
					EntityPosition::Coords[1] += 32;
					Player::exp[0] -= 1;
					FlagManager::flagPlayer = 0;
					//std::cout << "s" << std::endl;
					//SDL_Delay(100);
				}
			}
		}

		else if (keys[SDL_SCANCODE_D])
		{
			if (EntityPosition::Coords[0] == 960)
			{
				//остановка при упоре в стену
			}
			else
			{
				if (Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 + 1] == 0)
				{
					EntityPosition::Coords[0] += 32;
					FlagManager::flagPlayer = 0;
					//std::cout << "d" << std::endl;
					//SDL_Delay(100);
				}
			}
		}
	default:
		break;
	}
}

/*void Player::Attack()
{
	if (ITEMTYPE.... = 0 ���� ������� ���) {}
	else if (ITEMTYPE.... = 1 ���� ������� ���)
	{
		
	}
}*/