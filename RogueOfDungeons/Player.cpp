#include "Player.h"
#include "GameObject.h"

InputManager* inputMovePlayer;
const Uint8* state = SDL_GetKeyboardState(0);

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
	RenderManager::CopyToRender(PlayerTexture, ren, xpos, ypos, 64, 64, 0, 0, 32, 32);
}

void Player::Update(int xpos, int ypos)
{
	SDL_Event eventMovePlayer;
	SDL_PollEvent(&eventMovePlayer);
	switch (eventMovePlayer.type)
	{
	case SDL_KEYDOWN:
		switch (eventMovePlayer.key.keysym.sym)
		{
		case SDL_SCANCODE_W:
			inputMovePlayer->pressW(ypos);
			Player::Render();
			std::cout << "PP\n";
			break;
		case  SDL_SCANCODE_S:
			inputMovePlayer->pressS(xpos);
			Player::Render();
			break;
		case  SDL_SCANCODE_A:
			inputMovePlayer->pressA(ypos);
			Player::Render();
			break;
		case  SDL_SCANCODE_D:
			inputMovePlayer->pressD(xpos);
			Player::Render();
			break;
		default:
			break;
		}
	}
}
