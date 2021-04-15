#include "Buttons.h"
#include "Managers.h"
#include "Inventory.h"
#include <iostream>
#include "EntityPosition.h"
#include "Player.h"

Mouse MouseButtonsInLevel::mouseCoords;

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
	//SDL_GetMouseState(&mouseCoords.x, &mouseCoords.y);

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
	if (FlagManager::flagUiSpec == 1 && InputManager::MouseInArea(1230, 50, 16, 20, mouseCoords.x, mouseCoords.y) &&
		FlagManager::flagSTR == 0)
	{
		Player::ChangeValueSpecs(1);
	}
	//DEX
	if (FlagManager::flagUiSpec == 1 && InputManager::MouseInArea(1230, 80, 16, 20, mouseCoords.x, mouseCoords.y) &&
		FlagManager::flagDEX == 0)
	{
		Player::ChangeValueSpecs(2);
	}
	//INT
	if (FlagManager::flagUiSpec == 1 && InputManager::MouseInArea(1230, 110, 16, 20, mouseCoords.x, mouseCoords.y) &&
		FlagManager::flagINT == 0)
	{
		Player::ChangeValueSpecs(3);
	}
	//WSD
	if (FlagManager::flagUiSpec == 1 && InputManager::MouseInArea(1230, 140, 16, 20, mouseCoords.x, mouseCoords.y) &&
		FlagManager::flagWSD == 0) 
	{
		Player::ChangeValueSpecs(4);
	}
	//PHS
	if (FlagManager::flagUiSpec == 1 && InputManager::MouseInArea(1230, 170, 16, 20, mouseCoords.x, mouseCoords.y) &&
		FlagManager::flagPHS == 0)
	{
		Player::ChangeValueSpecs(5);
	}
	//LCK
	if (FlagManager::flagUiSpec == 1 && InputManager::MouseInArea(1230, 200, 16, 20, mouseCoords.x, mouseCoords.y) &&
		FlagManager::flagLCK == 0)
	{
		Player::ChangeValueSpecs(6);
	}
}

Mouse MouseButtonsPlayer::mouseCoordsPlayer;

MouseButtonsPlayer::MouseButtonsPlayer()
{

}

MouseButtonsPlayer::~MouseButtonsPlayer()
{

}

void MouseButtonsPlayer::buttonsForAttack()
{
	SDL_GetMouseState(&mouseCoordsPlayer.x, &mouseCoordsPlayer.y);

	if (InputManager::MouseInArea(EntityPosition::Coords[2], EntityPosition::Coords[3], 32, 32, mouseCoordsPlayer.x, mouseCoordsPlayer.y))
	{
		FlagManager::flagMeleeAttackPlayer = 1;
		Player::Attack();
	}
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

Button::Button(const char* textureName, SDL_Rect rect, void (*callbackFunction), void (*hoverFunction)):
	nameOftexture(textureName), callback(callbackFunction), hover(hoverFunction)
{
	button.x = rect.x;
	button.y = rect.y;
	button.w = rect.w;
	button.h = rect.h;
}

//UNDONE сделать SDL_BUTTON_RIGHT
void Button::handleEvents(SDL_Event& buttonEvent)
{
	if (buttonEvent.type == SDL_MOUSEBUTTONDOWN)
	{
		if (buttonEvent.button.button == SDL_BUTTON_LEFT)
		{
			if (Button::mouseInArea(button.x, button.y, button.w, button.h))
			{
				callback;
			}
		}
	}
	else
	{
		if (Button::mouseInArea(button.x, button.y, button.w, button.h))
		{
			hover;
		}
	}
}

//да-да, знаю, что уже есть такая функция, но надо было её сделать, просто надо!
bool Button::mouseInArea(int x, int y, int w, int h)
{
	bool validity;
	SDL_GetMouseState(&mouse.x, &mouse.y);
	if ((mouse.x >= x) && (mouse.y >= y) && (mouse.x >= x + w) && (mouse.y >= y + h))
	{
		validity = true;
	}
	else
	{
		validity = false;
	}

	return validity;
}

Keyboard::Keyboard()
{

}

void Keyboard::handleEvents(SDL_Event& keyboardEvent)
{
	//keyForCallSpecWin
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

	//keyForCallInvWin
	if (keys[SDL_SCANCODE_I] && FlagManager::flagInv == 0)
	{
		FlagManager::flagInv = 1;
	}
	else if (keys[SDL_SCANCODE_I] && FlagManager::flagInv == 1)
	{
		FlagManager::flagInv = 0;
	}

	//keyForIncPlayerSpec
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
	if (keys[SDL_SCANCODE_4] && FlagManager::flagUiSpec == 1 && FlagManager::flagWSD == 0)
	{
		Player::ChangeValueSpecs(4);
	}
	if (keys[SDL_SCANCODE_5] && FlagManager::flagUiSpec == 1 && FlagManager::flagPHS == 0)
	{
		Player::ChangeValueSpecs(5);
	}
	if (keys[SDL_SCANCODE_6] && FlagManager::flagUiSpec == 1 && FlagManager::flagLCK == 0)
	{
		Player::ChangeValueSpecs(6);
	}
}