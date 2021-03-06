#include "Player.h"
#include "GameObject.h"

Player::Player(const char* texturesheet, SDL_Renderer* renderer)
{
	ren = renderer;
	PlayerTexture = textureManager::LoadTexture(texturesheet, renderer);
}

Player::~Player()
{

}

void Player::Render()
{
	RenderManager::CopyToRender(PlayerTexture, ren, 0, 0, 32, 32, 32, 32, 32, 32);
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

			break;
		case SDLK_s:
			break;
		case SDLK_a:
			break;
		case SDLK_d:
			break;
		default:
			break;
		}
}
