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

}

void Player::clean()
{

}