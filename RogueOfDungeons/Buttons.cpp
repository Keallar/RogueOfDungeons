#include "Buttons.h"
#include "Managers.h"
#include "Inventory.h"
#include <iostream>
#include "EntityPosition.h"
#include "Player.h"

//конструктор без callback и hover
Button::Button(const char* textureName, SDL_Renderer* renderer, SDL_Rect rect)
	:nameOftexture(textureName), ren(renderer)
{
	button.x = rect.x;
	button.y = rect.y;
	button.w = rect.w;
	button.h = rect.h;

	if (nameOftexture != NULL)
		buttonTexture = textureManager::LoadTexture(nameOftexture, ren);
	else
		buttonTexture = NULL;
}
//конструктор c callback и hover
Button::Button(const char* textureName, SDL_Renderer* renderer, SDL_Rect rect, 
	void (*callbackFunction)(), void (*hoverFunction)()):
	nameOftexture(textureName), ren(renderer), callback(callbackFunction), hover(hoverFunction)
{
	button.x = rect.x;
	button.y = rect.y;
	button.w = rect.w;
	button.h = rect.h;

	//UNDONE call of name callback
	if (callback == NULL)
		std::cout << "callback isn't ready " << "name of callback" << std::endl;

	if (nameOftexture != NULL)
		buttonTexture = textureManager::LoadTexture(nameOftexture, ren);
	else
		buttonTexture = NULL;
}

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
			if (hover != NULL)
				hover();
		}
	} 
}

bool Button::mouseInArea(int x, int y, int w, int h)
{
	bool validity;
	SDL_GetMouseState(&mouse.x, &mouse.y);
	if ((mouse.x >= x) && (mouse.y >= y) && (mouse.x <= x + w) && (mouse.y <= y + h))
	{
		validity = true;
	}
	else
	{
		validity = false;
	}

	return validity;
}

void Button::Render()
{
	if (buttonTexture != NULL)
		RenderManager::CopyToRender(buttonTexture, ren, button.x, button.y, button.w, button.h);
	else
		std::cout << "Error in Button::Render" << std::endl;
}

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

void buttonsForItemsInInv()
{
	for (int i = 0; i < 16; i++)
	{
		if (Inventory::inventoryFace[i] != -1 && FlagManager::flagInv == 1)
		{
			std::cout << "Item " + i << std::endl;
			FlagManager::flagEquip = i;
		}
	}
}

void callbackFunctions::callInvWin()
{
	if (FlagManager::flagInv == 0)
	{
		FlagManager::flagInv = 1;
	}
	else if (FlagManager::flagInv == 1)
	{
		FlagManager::flagInv = 0;
	}
}

void callbackFunctions::callSpecOrInfoWin()
{
	if (FlagManager::flagUiSpec == 0)
	{
		FlagManager::flagUiSpec = 1;
		FlagManager::flagUI = 0;
		std::cout << "Spec" << std::endl;
	}
	else if (FlagManager::flagUiSpec == 1)
	{
		FlagManager::flagUI = 1;
		FlagManager::flagUiSpec = 0;
		std::cout << "Info" << std::endl;
	}
}

//void callbackFunctions::callInfoWin()
//{
//	
//}

void callbackFunctions::incPlayerSTR()
{
	//STR
	if (FlagManager::flagSTR == 0 && FlagManager::flagUiSpec == 1)
	{
		Player::ChangeValueSpecs(1);
	}
}

void callbackFunctions::incPlayerDEX()
{
	//DEX
	if (FlagManager::flagDEX == 0)
	{
		Player::ChangeValueSpecs(2);
	}
}

void callbackFunctions::incPlayerINT()
{
	//INT
	if (FlagManager::flagINT == 0)
	{
		Player::ChangeValueSpecs(3);
	}
}

void callbackFunctions::incPlayerWSD()
{
	//WSD
	if (FlagManager::flagWSD == 0)
	{
		Player::ChangeValueSpecs(4);
	}
}

void callbackFunctions::incPlayerPHS()
{
	//PHS
	if (FlagManager::flagPHS == 0)
	{
		Player::ChangeValueSpecs(5);
	}
}

void callbackFunctions::incPlayerLCK()
{
	//LCK
	if (FlagManager::flagLCK == 0)
	{
		Player::ChangeValueSpecs(6);
	}
}

void callbackFunctions::callEnemyInfo()
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
