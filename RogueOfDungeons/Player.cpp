#include "Player.h"
#include "GameObject.h"
#include "Managers.h"
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
	RenderManager::CopyToRender(PlayerTexture, ren, playerCoordx, playerCoordy, 64, 64, 0, 0, 32, 32);
}

void Player::Update()
{
	if (flag == 0)
	{
		if (keys[SDL_SCANCODE_W])
		{
			playerCoordy -= 32;
			std::cout << "w" << std::endl;
			flag = 1;
		}

		if (keys[SDL_SCANCODE_A])
		{
			playerCoordx -= 32;
			std::cout << "a" << std::endl;
			flag = 1;
		}

		if (keys[SDL_SCANCODE_S])
		{
			playerCoordy += 32;
			std::cout << "s" << std::endl;
			flag = 1;
		}

		if (keys[SDL_SCANCODE_D])
		{
			playerCoordx += 32;
			std::cout << "d" << std::endl;
			flag = 1;
		}
	}
}
