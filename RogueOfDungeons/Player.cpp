#include "Player.h"
#include "GameObject.h"
#include "Managers.h"
#include <iostream>
#include "EntityPosition.h"
#include "UI.h"
#include "inventory.h"

int Player::HP[2] = {
					 10, /*hp  now*/
					 10  /*hp  previous*/
					};
int Player::exp[2] = { 
					   0, /*exp  now*/
					   0  /*exp  previous*/
					 };

int Player::mana[2] = { 
					    0, /*mana  now*/
						0  /*mana  previous*/
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
	EntityPosition::Coords[0] = (rand() % 2 +1) * 32;
	EntityPosition::Coords[1] = (rand() % 20 +1) * 32;
	while ((Location[EntityPosition::Coords[1] / 32][EntityPosition::Coords[0] / 32] == 1)||
		((Location[EntityPosition::Coords[1] / 32][EntityPosition::Coords[0] / 32 - 1] != 0)&&
		(Location[EntityPosition::Coords[1] / 32][EntityPosition::Coords[0] / 32 + 1] != 0)&&
		(Location[EntityPosition::Coords[1] / 32 - 1][EntityPosition::Coords[0] / 32] != 0)&&
		(Location[EntityPosition::Coords[1] / 32 + 1][EntityPosition::Coords[0] / 32] != 0)))
	{
		EntityPosition::Coords[0] = (rand() % 2 + 1) * 32;
		EntityPosition::Coords[1] = (rand() % 20 + 1) * 32;
	}
}

void Player::Render()
{
	RenderManager::CopyToRender(PlayerTexture, ren, EntityPosition::Coords[0], EntityPosition::Coords[1], 32, 32, 0, 0, 32, 32);
}

void Player::Update()
{

	if (keys[SDL_SCANCODE_W])
	{
		if (EntityPosition::Coords[1] == 32)
		{
			//остановка при упоре в стену
		}
		else
		{
			if (Location[(EntityPosition::Coords[1]) / 32 - 1][(EntityPosition::Coords[0])/ 32] == 0) {
				EntityPosition::Coords[1] -= 32;
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
			if (Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 - 1] == 0) {
				EntityPosition::Coords[0] -= 32;
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
			if (Location[(EntityPosition::Coords[1]) / 32 + 1][(EntityPosition::Coords[0]) / 32] == 0) {
				EntityPosition::Coords[1] += 32;
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
	inventory->Update();
	Player::CheckHP();
}

/*void Player::Attack()
{
	if (ITEMTYPE.... = 0 типо ближний бой) {}
	else if (ITEMTYPE.... = 1 типо дальний бой)
	{
		
	}
}*/