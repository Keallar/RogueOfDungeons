#include "Buttons.h"
#include "Managers.h"
#include "Inventory.h"
#include <iostream>
#include "EntityPosition.h"
#include "Player.h"

//UNDONE ��������� ���������� ����� BUTTONS
KeyboardButtonsInLevel::KeyboardButtonsInLevel()
{

}

void KeyboardButtonsInLevel::keyForCallSpecWin(const Uint8* keys)
{
	if (keys[SDL_SCANCODE_Q] && FlagManager::flagUiSpec == 0)
	{
		FlagManager::flagUiSpec = 1;
		FlagManager::flagUI = 0;
	}
	else if (keys[SDL_SCANCODE_Q] && FlagManager::flagUI == 0)
	{
		FlagManager::flagUiSpec = 0;
		FlagManager::flagUI = 1;
	}
}

void KeyboardButtonsInLevel::keyForCallInvWin(const Uint8* keys)
{
	if (keys[SDL_SCANCODE_I] && FlagManager::flagInv == 0)
	{
		FlagManager::flagInv = 1;
	}
	else if (keys[SDL_SCANCODE_I] && FlagManager::flagInv == 1)
	{
		FlagManager::flagInv = 0;
	}

}

void KeyboardButtonsInLevel::keyForIncPlayerSpec(const Uint8* keys)
{
	if (keys[SDL_SCANCODE_1] && FlagManager::flagUiSpec == 1 && FlagManager::flagSTR == 0)
	{
		Player::ChangeValueSpecs(1);
	}
	if (keys[SDL_SCANCODE_2] && FlagManager::flagUiSpec == 1 && FlagManager::flagDEX == 0)
	{
		Player::ChangeValueSpecs(2);
	}
	if (keys[SDL_SCANCODE_3] && FlagManager::flagUiSpec == 1 && FlagManager::flagINT == 0)
	{
		Player::ChangeValueSpecs(3);
	}
	if (keys[SDL_SCANCODE_4] && FlagManager::flagUiSpec == 1 && FlagManager::flagPHS == 0)
	{
		Player::ChangeValueSpecs(4);
	}
	if (keys[SDL_SCANCODE_5] && FlagManager::flagUiSpec == 1 && FlagManager::flagLCK == 0)
	{
		Player::ChangeValueSpecs(5);
	}
}

MCoord MouseButtonsInLevel::mouseCoords;

MouseButtonsInLevel::MouseButtonsInLevel()
{

}

void MouseButtonsInLevel::buttonsForItemsInInv()
{
	SDL_GetMouseState(&mouseCoords.x, &mouseCoords.y);

	for (int i = 0; i < 16; i++)
	{
		if (InputManager::MouseInArea((780 + 36 * (i % 4)), (100 + ((i / 4) * 50)), 32, 32, mouseCoords.x, mouseCoords.y) &&
			Inventory::inventoryFace[i] != -1 && FlagManager::flagInv == 1)
		{
			std::cout << "Item " + i << std::endl;
			FlagManager::flagEquip = i;
		}
	}
}

void MouseButtonsInLevel::buttonForCallSpecWin()
{
	SDL_GetMouseState(&mouseCoords.x, &mouseCoords.y);

	if (InputManager::MouseInArea(1230, 240, 64, 64, mouseCoords.x, mouseCoords.y) &&
		FlagManager::flagUiSpec == 0)
	{
		FlagManager::flagUiSpec = 1;
		FlagManager::flagUI = 0;
	}
	else if (InputManager::MouseInArea(1230, 240, 32, 32, mouseCoords.x, mouseCoords.y) &&
		FlagManager::flagUiSpec == 1)
	{
		FlagManager::flagUI = 1;
		FlagManager::flagUiSpec = 0;
	}
}

void MouseButtonsInLevel::buttonForCallInvWin()
{
	SDL_GetMouseState(&mouseCoords.x, &mouseCoords.y);

	if (InputManager::MouseInArea(1050, 665, 25, 22, mouseCoords.x, mouseCoords.y) &&
		FlagManager::flagInv == 0)
	{
		FlagManager::flagInv = 1;
	}
	else if (InputManager::MouseInArea(1050, 665, 25, 22, mouseCoords.x, mouseCoords.y) &&
		FlagManager::flagInv == 1)
	{
		FlagManager::flagInv = 0;
	}
}

void MouseButtonsInLevel::buttonForCallEnemyInfo()
{
	SDL_GetMouseState(&mouseCoords.x, &mouseCoords.y);
	if (InputManager::MouseInArea(EntityPosition::Coords[2], EntityPosition::Coords[3], 32, 32, mouseCoords.x, mouseCoords.y) &&
		FlagManager::flagUiEnemy == 0)
	{
		FlagManager::flagUiEnemy = 1;
	}
	else if (InputManager::MouseInArea(EntityPosition::Coords[2], EntityPosition::Coords[3], 32, 32, mouseCoords.x, mouseCoords.y) &&
		FlagManager::flagUiEnemy == 1)
	{
		FlagManager::flagUiEnemy = 0;
	}
}

void MouseButtonsInLevel::buttonForIncPlayerSpec()
{
	SDL_GetMouseState(&mouseCoords.x, &mouseCoords.y);
	//STR
	if (FlagManager::flagUiSpec == 1 && InputManager::MouseInArea(1230, 80, 16, 20, mouseCoords.x, mouseCoords.y) &&
		FlagManager::flagSTR == 0)
	{
		Player::ChangeValueSpecs(1);
	}
	//DEX
	if (FlagManager::flagUiSpec == 1 && InputManager::MouseInArea(1230, 110, 16, 20, mouseCoords.x, mouseCoords.y) &&
		FlagManager::flagDEX == 0)
	{
		Player::ChangeValueSpecs(2);
	}
	//INT
	if (FlagManager::flagUiSpec == 1 && InputManager::MouseInArea(1230, 140, 16, 20, mouseCoords.x, mouseCoords.y) &&
		FlagManager::flagINT == 0)
	{
		Player::ChangeValueSpecs(3);
	}
	//PHS
	if (FlagManager::flagUiSpec == 1 && InputManager::MouseInArea(1230, 170, 16, 20, mouseCoords.x, mouseCoords.y) &&
		FlagManager::flagPHS == 0)
	{
		Player::ChangeValueSpecs(4);
	}
	//LCK
	if (FlagManager::flagUiSpec == 1 && InputManager::MouseInArea(1230, 200, 16, 20, mouseCoords.x, mouseCoords.y) &&
		FlagManager::flagLCK == 0)
	{
		Player::ChangeValueSpecs(5);
	}
}

MouseButtonsPlayer::MouseButtonsPlayer()
{

}

MouseButtonsPlayer::~MouseButtonsPlayer()
{

}

void MouseButtonsPlayer::buttonsForAttack()
{
	FlagManager::flagMeleeAttackPlayer = 1;
	Player::Attack();
}

void MouseButtonsPlayer::buttonForRangeAttack()
{
	SDL_GetMouseState(&mouseCoordsPlayer.x, &mouseCoordsPlayer.y);

	if (InputManager::MouseInArea(EntityPosition::Coords[2], EntityPosition::Coords[3], 32, 32, mouseCoordsPlayer.x, mouseCoordsPlayer.y))
	{
		FlagManager::flagRangeAttack = 1;
		Player::Attack();
	}
}

MCoord MouseButtonsPlayer:: mouseCoordsPlayer;