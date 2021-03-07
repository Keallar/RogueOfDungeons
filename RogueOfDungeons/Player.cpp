#include "Player.h"
#include "GameObject.h"
#include "textureManager.h"
#include <iostream>

Player::Player(const char* texturesheet, SDL_Renderer* renderer)
{
	PlayerRect.x = 32;
	PlayerRect.y = 32;
	PlayerRect.h = 32;
	PlayerRect.w = 32;
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
	if (keys[SDL_SCANCODE_W])
	{
		
	}

	if (keys[SDL_SCANCODE_A])
	{
		
		std::cout << "a" << std::endl;
	}

	if (keys[SDL_SCANCODE_S])
	{
		move_RIGHT(ren, PlayerTexture, PlayerRect);
		std::cout << "s" << std::endl;
	}

	if (keys[SDL_SCANCODE_D])
	{

	}

	//SDL_Event eventMovePlayer;
	//while (SDL_PollEvent(&eventMovePlayer))
	//{
	//	switch (eventMovePlayer.type)
	//	{
	//	case SDL_KEYDOWN:
	//		switch (eventMovePlayer.key.keysym.sym)
	//		{
	//		case SDL_SCANCODE_W:
	//			playerCoordy -= 32;
	//			std::cout << "W" << std::endl;
	//			//playerCoordy = InputManager::pressW(playerCoordy);
	//			break;
	//		case SDL_SCANCODE_A:
	//			playerCoordx -= 32;
	//			std::cout << "A" << std::endl;
	//			//playerCoordx = InputManager::pressA(playerCoordx);
	//			break;
	//		case SDL_SCANCODE_S:
	//			playerCoordy += 32;
	//			std::cout << "S" << std::endl;
	//			//playerCoordy = InputManager::pressS(playerCoordy);
	//			break;
	//		case SDL_SCANCODE_D:
	//			playerCoordx += 32;
	//			std::cout << "D" << std::endl;
	//			//playerCoordx = InputManager::pressD(playerCoordx);
	//			break;
	//		default:
	//			std::cout << "Nothing" << std::endl;
	//			break;
	//		}
	//	}
	//}
}
