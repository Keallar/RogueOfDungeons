#include "Buttons.h"
#include "Managers.h"
#include "Inventory.h"
#include <iostream>
#include "EntityPosition.h"
#include "Player.h"

Mouse MouseButtonsPlayer::mouseCoordsPlayer;

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

Button::Button(const char* textureName, SDL_Rect rect, void (*callbackFunction)(), void (*hoverFunction)()):
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
				callback();
			}
		}
	}
	else
	{
		if (Button::mouseInArea(button.x, button.y, button.w, button.h))
		{
			hover();
		}
	}
}

//да-да, знаю, что уже есть такая функция, но надо было её сделать, просто надо!
bool Button::mouseInArea(int x, int y, int w, int h)
{
	bool validity;
	SDL_GetMouseState(&mouse.x, &mouse.y);
	if ((mouse.x >= x) && (mouse.y >= y) && (mouse.x <= x + w) && (mouse.y <= y + h))
	{
		validity = true;
		//std::cout << "True validity" << std::endl;
	}
	else
	{
		validity = false;
		//std::cout << "False validity" << std::endl;
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


namespace buttons
{
	

	void buttonForCallEnemyInfoL()
	{
		if (FlagManager::flagUiEnemy == 0)
		{
			FlagManager::flagUiEnemy = 1;
		}
		else if (FlagManager::flagUiEnemy == 1)
		{
			FlagManager::flagUiEnemy = 0;
		}
	}

	void buttonForIncPlayerSpecL()
	{
		//STR
		if (FlagManager::flagSTR == 0)
		{
			Player::ChangeValueSpecs(1);
		}
		//DEX
		if (FlagManager::flagDEX == 0)
		{
			Player::ChangeValueSpecs(2);
		}
		//INT
		if (FlagManager::flagINT == 0)
		{
			Player::ChangeValueSpecs(3);
		}
		//WSD
		if (FlagManager::flagWSD == 0)
		{
			Player::ChangeValueSpecs(4);
		}
		//PHS
		if (FlagManager::flagPHS == 0)
		{
			Player::ChangeValueSpecs(5);
		}
		//LCK
		if (FlagManager::flagLCK == 0)
		{
			Player::ChangeValueSpecs(6);
		}
	}
}
