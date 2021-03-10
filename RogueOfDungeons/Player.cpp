#include "Player.h"
#include "GameObject.h"
#include "Managers.h"
#include <iostream>
#include "EntityPosition.h"

Player::Player(const char* texturesheet, SDL_Renderer* renderer)
{
	ren = renderer;
	PlayerTexture = textureManager::LoadTexture(texturesheet, ren);
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 32; j++) {
			Location[i][j] = 0;
		}
	}
}

Player::~Player()
{
	if (HP == 0)
	{
		SDL_DestroyTexture(PlayerTexture);
	}
}

void Player::GetLevel(int arr[22][32]) 
{
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 32; j++) {
			Location[i][j] = arr[i][j];
		}
	}
}

void Player::GetPlayerFirstCoords() 
{
	EntityPosition::Coords[0] = (rand() % 1 +1) * 32;
	EntityPosition::Coords[1] = (rand() % 20 +1) * 32;
	while (Location[EntityPosition::Coords[0]][EntityPosition::Coords[1]] == 1) 
	{
		EntityPosition::Coords[0] = (rand() % 1 + 1) * 32;
		EntityPosition::Coords[1] = (rand() % 20 + 1) * 32;
	}
}

void Player::Render()
{
	RenderManager::CopyToRender(PlayerTexture, ren, EntityPosition::Coords[0], EntityPosition::Coords[1], 32, 32, 0, 0, 32, 32);
}

void Player::Update()
{
		if (keys[SDL_SCANCODE_W])
		{
			if (EntityPosition::Coords[1] == 32)
			{
				//остановка при упоре в стену
			}
			else
			{
				if (Location[(EntityPosition::Coords[1]) / 32 - 1][(EntityPosition::Coords[0])/ 32] == 0) {
					EntityPosition::Coords[1] -= 32;
					FlagManager::flagPlayer = 0;
					//std::cout << "w" << EntityPosition::Coords[0] << EntityPosition::Coords[1] << std::endl;
					//SDL_Delay(100);
				}
			}
		}

		else if (keys[SDL_SCANCODE_A])
		{
			if (EntityPosition::Coords[0] == 32)
			{
				//остановка при упоре в стену
			}
			else
			{
				if (Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 - 1] == 0) {
					EntityPosition::Coords[0] -= 32;
					FlagManager::flagPlayer = 0;
					//sdt::cout << "a" << std::endl;
					//SDL_Delay(100);
				}
			}
		}

		else if (keys[SDL_SCANCODE_S])
		{
			if (EntityPosition::Coords[1] == 640)
			{
				//остановка при упоре в стену
			}
			else
			{
				if (Location[(EntityPosition::Coords[1]) / 32 + 1][(EntityPosition::Coords[0]) / 32] == 0) {
					EntityPosition::Coords[1] += 32;
					FlagManager::flagPlayer = 0;
					//std::cout << "s" << std::endl;
					//SDL_Delay(100);
				}
			}
		}

		else if (keys[SDL_SCANCODE_D])
		{
			if (EntityPosition::Coords[0] == 960)
			{
				//остановка при упоре в стену
			}
			else
			{
				if (Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 + 1] == 0) {
					EntityPosition::Coords[0] += 32;
					FlagManager::flagPlayer = 0;
					//std::cout << "d" << std::endl;
					//SDL_Delay(100);
				}
			}
		}
}

