#include "Player.h"
#include "GameObject.h"

InputManager* inputMovePlayer;

Player::Player(const char* texturesheet, SDL_Renderer* renderer)
{
	ren = renderer;
	PlayerTexture = textureManager::LoadTexture(texturesheet, ren);
}

Player::~Player()
{

}

void Player::Render()
{
	RenderManager::CopyToRender(PlayerTexture, ren, 32, 32, 32, 32, 0, 0, 32, 32);
}

void Player::Update(int x, int y)
{
	SDL_Event eventMovePlayer;
	SDL_PollEvent(&eventMovePlayer);
	switch (eventMovePlayer.type)
	{
	case SDL_KEYDOWN:
		switch (eventMovePlayer.key.keysym.sym)
		{
		case SDLK_w:
			ypos = y;
			inputMovePlayer->pressW(ypos);
			break;
		case SDLK_s:
			xpos = x;
			inputMovePlayer->pressS(xpos);
			break;
		case SDLK_a:
			ypos = y;
			inputMovePlayer->pressA(ypos);
			break;
		case SDLK_d:
			xpos = x;
			inputMovePlayer->pressD(xpos);
			break;
		default:
			break;
		}
	}
}
