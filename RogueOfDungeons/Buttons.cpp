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
Button::Button(const char* textureName, SDL_Renderer* renderer, SDL_Rect rect, 
	void (*callbackFunction)(), void (*hoverFunction)()):
	nameOftexture(textureName), ren(renderer), callback(callbackFunction), hover(hoverFunction)
{
	button.x = rect.x;
	button.y = rect.y;
	button.w = rect.w;
	button.h = rect.h;

	stateOfClip[CLIP_MOUSEOVER].x = 0;
	stateOfClip[CLIP_MOUSEOVER].y = 0;
	stateOfClip[CLIP_MOUSEOVER].w = button.w;
	stateOfClip[CLIP_MOUSEOVER].h = button.h;

	stateOfClip[CLIP_MOUSEOUT].x = button.w;
	stateOfClip[CLIP_MOUSEOUT].y = 0;
	stateOfClip[CLIP_MOUSEOUT].w = button.w;
	stateOfClip[CLIP_MOUSEOUT].h = button.h;

	stateOfClip[CLIP_MOUSEDOWN].x = 0;
	stateOfClip[CLIP_MOUSEDOWN].y = button.h;
	stateOfClip[CLIP_MOUSEDOWN].w = button.w;
	stateOfClip[CLIP_MOUSEDOWN].h = button.h;

	stateOfClip[CLIP_MOUSEUP].x = button.w;
	stateOfClip[CLIP_MOUSEUP].y = button.h;
	stateOfClip[CLIP_MOUSEUP].w = button.w;
	stateOfClip[CLIP_MOUSEUP].h = button.h;

	clip = &stateOfClip[CLIP_MOUSEOUT];

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
	if (buttonEvent.type == SDL_MOUSEBUTTONDOWN)
	{
		if (buttonEvent.button.clicks == 1)
		{
			if (buttonEvent.button.button == SDL_BUTTON_LEFT)
			{
				mouse.x = buttonEvent.button.x;
				mouse.y = buttonEvent.button.y;
				if (Button::mouseInArea(button.x, button.y, button.w, button.h))
				{
					clip = &stateOfClip[CLIP_MOUSEDOWN];
					callback();
				}
				else
				{
					clip = &stateOfClip[CLIP_MOUSEUP];
				}
			}
		}
	}
	else if (buttonEvent.type == SDL_MOUSEMOTION)
	{
		std::cout << "I'm here! In Motion" << std::endl;
		mouse.x = buttonEvent.motion.x;
		std::cout << mouse.x << std::endl;
 		mouse.y = buttonEvent.motion.y;
		std::cout << mouse.y << std::endl;
		if (Button::mouseInArea(button.x, button.y, button.w, button.h))
		{
			clip = &stateOfClip[CLIP_MOUSEOVER];
			hover();
			std::cout << "hover" << std::endl;
		}
		else
		{
			clip = &stateOfClip[CLIP_MOUSEOUT];
		}
	} 
}

bool Button::mouseInArea(int x, int y, int w, int h)
{
	bool validity;
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

void Button::updateCoords(int newx, int newy)
{
	button.x = newx;
	button.y = newy;
}

Keyboard::Keyboard(SDL_Scancode code, void (*callbackFunction)()):
	callback(callbackFunction)
{
	keys[code];
	if (callback == NULL)
		std::cout << "callback in Keyboard isn't ready" << std::endl;
}

Keyboard::~Keyboard()
{

}

void Keyboard::handleEvents(SDL_Event& keyboardEvent)
{
	if (buttonIsPressed(keyboardEvent))
		callback();
}

bool Keyboard::buttonIsPressed(SDL_Event& keyboardEvent)
{
	bool validity = false;
	if (keyboardEvent.type = SDL_KEYDOWN)
	{
		keys[keyboardEvent.key.keysym.scancode] = true;
		validity = keys[keyboardEvent.key.keysym.scancode];
	}
	else if (keyboardEvent.type == SDL_KEYUP)
	{
		keys[keyboardEvent.key.keysym.scancode] = false;
		validity = keys[keyboardEvent.key.keysym.scancode];
	}
	return validity;
}


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

Mouse MouseButtonsPlayer::mouseCoordsPlayer;

void MouseButtonsPlayer::buttonsForAttack(int x, int y)
{
	SDL_GetMouseState(&mouseCoordsPlayer.x, &mouseCoordsPlayer.y);

	if (InputManager::MouseInArea(x, y, 32, 32, mouseCoordsPlayer.x, mouseCoordsPlayer.y))
	{
		FlagManager::flagMeleeAttackPlayer = 1;
		//level->Attack();
	}
}

void MouseButtonsPlayer::buttonForRangeAttack(int x, int y)
{
	SDL_GetMouseState(&mouseCoordsPlayer.x, &mouseCoordsPlayer.y);

	if (InputManager::MouseInArea(x, y, 32, 32, mouseCoordsPlayer.x, mouseCoordsPlayer.y))
	{
		FlagManager::flagRangeAttack = 1;
		//Level::Attack();
	}
}

