#include "Player.h"
#include "GameObject.h"

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

void Player::Update()
{
	SDL_Event eventMovePlayer;
	SDL_PollEvent(&eventMovePlayer);
	switch (eventMovePlayer.type)
	{
	case SDL_KEYDOWN:
		switch (eventMovePlayer.key.keysym.sym)
		{
		case SDLK_w:
			inputMovePlayer->pressW();
			break;
		case SDLK_s:
			inputMovePlayer->pressS();
			break;
		case SDLK_a:
			inputMovePlayer->pressA();
			break;
		case SDLK_d:
			inputMovePlayer->pressD();
			break;
		default:
			break;
		}
	}
}
