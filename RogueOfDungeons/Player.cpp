#include "Player.h"
#include "GameObject.h"
#include "textureManager.h"
#include <iostream>

Player::Player(const char* texturesheet, SDL_Renderer* renderer)
{
	ren = renderer;
	PlayerTexture = textureManager::LoadTexture(texturesheet, ren);
}

Player::~Player()
{
	if (HP == 0)
	{
		SDL_DestroyTexture(PlayerTexture);
	}
}


void Player::Render()
{
	RenderManager::CopyToRender(PlayerTexture, ren, playerCoordx, playerCoordy, 64, 64, 32, 0, 32, 32);
}

void Player::Update()
{
	SDL_Event eventMovePlayer;
	while (SDL_PollEvent(&eventMovePlayer))
	{
		switch (eventMovePlayer.type)
		{
		case SDL_KEYDOWN:
			switch (eventMovePlayer.key.keysym.sym)
			{
			case SDL_SCANCODE_W:
				playerCoordy = InputManager::pressW(playerCoordy);
				break;
			case SDL_SCANCODE_A:
				playerCoordx = InputManager::pressA(playerCoordx);
				break;
			case SDL_SCANCODE_S:
				playerCoordy = InputManager::pressS(playerCoordy);
				break;
			case SDLK_d:
				playerCoordx = InputManager::pressD(playerCoordx);
				break;
			default:
				break;
			}
		}
	}
}
