#include "Player.h"
#include "GameObject.h"
#include "Managers.h"
#include <iostream>
#include "EntityPosition.h"

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
	RenderManager::CopyToRender(PlayerTexture, ren, playerCoordx, playerCoordy, 32, 32, 0, 0, 32, 32);
}

void Player::Update()
{
		if (keys[SDL_SCANCODE_W])
		{
			EntityPosition::Coords[1] -= 32;
			//std::cout << "w" << EntityPosition::Coords[0] << EntityPosition::Coords[1] << std::endl;
			SDL_Delay(100);
		}

		else if (keys[SDL_SCANCODE_A])
		{
			EntityPosition::Coords[0] -= 32;
			//sdt::cout << "a" << std::endl;
			SDL_Delay(100);
		}

		else if (keys[SDL_SCANCODE_S])
		{
			EntityPosition::Coords[1] += 32;
			//std::cout << "s" << std::endl;
			SDL_Delay(100);
		}

		else if (keys[SDL_SCANCODE_D])
		{
			EntityPosition::Coords[0] += 32;
			//std::cout << "d" << std::endl;
			SDL_Delay(100);
		}
}

