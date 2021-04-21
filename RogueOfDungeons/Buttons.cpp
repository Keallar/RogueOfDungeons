#include "Buttons.h"
#include "Managers.h"
#include "Inventory.h"
#include <iostream>
#include "EntityPosition.h"
#include "Player.h"
#include "Level.h"
#include "Game.h"

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
Button::Button(const char* textureName, SDL_Renderer* renderer, const SDL_Rect rect, 
	void (*callbackFunction)(), void (*hoverFunction)()):
	nameOftexture(textureName), ren(renderer), callback(callbackFunction), hover(hoverFunction)
{
	button.x = rect.x;
	button.y = rect.y;
	button.w = rect.w;
	button.h = rect.h;

	if (callback == NULL)
		std::cout << "callback isn't ready " << std::endl;
	
	if (hover == NULL)
		std::cout << "hover isn't ready" << std::endl;

	if (nameOftexture != NULL)
		buttonTexture = textureManager::LoadTexture(nameOftexture, ren);
	else
		buttonTexture = NULL;
}

void Button::handleEvents(SDL_Event& buttonEvent)
{
	switch (buttonEvent.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (buttonEvent.button.clicks == 1)
		{
			if (buttonEvent.button.button == SDL_BUTTON_LEFT)
			{
				mouse.x = buttonEvent.button.x;
				mouse.y = buttonEvent.button.y;
				if (Button::mouseInArea(button.x, button.y, button.w, button.h))
				{
					callback();
				}
			}
		}
		break;

	case SDL_MOUSEMOTION:
		mouse.x = buttonEvent.motion.x;
		mouse.y = buttonEvent.motion.y;
		if (Button::mouseInArea(button.x, button.y, button.w, button.h) && 
			FlagManager::flagHover == 1 && 
			hover != NULL)
		{
			hover();
		}
		break;

	default:
		break;
	}
}

bool Button::mouseInArea(int x, int y, int w, int h)
{
	bool validity;
	if ((mouse.x >= x) && (mouse.y >= y) && (mouse.x <= x + w) && (mouse.y <= y + h))
	{
		validity = true;
		FlagManager::flagHover = 1;
	}
	else
	{
		validity = false;
		FlagManager::flagHover = 0;
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

void Button::updateCoords(int newx, int newy)
{
	button.x = newx;
	button.y = newy;
}

Keyboard::Keyboard(SDL_Scancode scancode, void (*callbackFunction)()):
	code (scancode), callback(callbackFunction)
{
	if (callback == NULL)
		std::cout << "callback in Keyboard isn't ready" << std::endl;
}

Keyboard::~Keyboard()
{

}

void Keyboard::handleEvents(SDL_Event& keyboardEvent)
{
	if (buttonIsPressed(keyboardEvent) == 1 && callback != NULL)
	{
		//std::cout << code << std::endl;
		callback();
	}
}

bool Keyboard::buttonIsPressed(SDL_Event& keyboardEvent)
{
	SDL_Scancode codeB = keyboardEvent.key.keysym.scancode;
	bool validity = false;
	switch (keyboardEvent.type)
	{
	case SDL_KEYDOWN:
		if (code == codeB)
		validity = true;
		break;
	case SDL_KEYUP:
		validity = false;
		break;
	default:
		break;
	}
	return validity;
}


//void KeyboardButtonsInLevel::keyForIncPlayerSpec(const Uint8* keys)
//{
//	if (keys[SDL_SCANCODE_1] && FlagManager::flagUiSpec == 1 && FlagManager::flagSTR == 0)
//	{
//		Player::ChangeValueSpecs(1);
//	}
//	if (keys[SDL_SCANCODE_2] && FlagManager::flagUiSpec == 1 && FlagManager::flagDEX == 0)
//	{
//		Player::ChangeValueSpecs(2);
//	}
//	if (keys[SDL_SCANCODE_3] && FlagManager::flagUiSpec == 1 && FlagManager::flagINT == 0)
//	{
//		Player::ChangeValueSpecs(3);
//	}
//	if (keys[SDL_SCANCODE_4] && FlagManager::flagUiSpec == 1 && FlagManager::flagPHS == 0)
//	{
//		Player::ChangeValueSpecs(4);
//	}
//	if (keys[SDL_SCANCODE_5] && FlagManager::flagUiSpec == 1 && FlagManager::flagLCK == 0)
//	{
//		Player::ChangeValueSpecs(5);
//	}
//}

Mouse MouseButtonsPlayer::mouseCoordsPlayer;

void MouseButtonsPlayer::buttonsForAttack(int x, int y)
{
	SDL_GetMouseState(&mouseCoordsPlayer.x, &mouseCoordsPlayer.y);

	if (InputManager::MouseInArea(x, y, 32, 32, mouseCoordsPlayer.x, mouseCoordsPlayer.y))
	{
		FlagManager::flagMeleeAttackPlayer = 1;
	}
}

void MouseButtonsPlayer::buttonForRangeAttack(int x, int y)
{
	SDL_GetMouseState(&mouseCoordsPlayer.x, &mouseCoordsPlayer.y);

	if (InputManager::MouseInArea(x, y, 32, 32, mouseCoordsPlayer.x, mouseCoordsPlayer.y))
	{
		FlagManager::flagRangeAttack = 1;
	}
}

