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
	RenderManager::CopyToRender(PlayerTexture, ren, Coords[0], Coords[1], 64, 64, 0, 0, 32, 32);
}

void Player::Update()
{
		if (keys[SDL_SCANCODE_W])
		{
			Coords[1] -= 32;
			std::cout << "w" << Coords[0] << Coords[1] << std::endl;
			SDL_Delay(400);
		}

		else if (keys[SDL_SCANCODE_A])
		{
			Coords[0] -= 32;
			std::cout << "a" << std::endl;
			SDL_Delay(400);
		}

		else if (keys[SDL_SCANCODE_S])
		{
			Coords[1] += 32;
			std::cout << "s" << std::endl;
			SDL_Delay(400);
		}

		else if (keys[SDL_SCANCODE_D])
		{
			Coords[0] += 32;
			std::cout << "d" << std::endl;
			SDL_Delay(400);
		}
}

