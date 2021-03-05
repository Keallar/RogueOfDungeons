#include "Player.h"
#include "GameObject.h"

Player::Player()
{}


Player::Player(const char* texturesheet, SDL_Renderer* renderer)
{
	PlayerTexture = textureManager::LoadTexture(texturesheet, renderer);
}

Player::~Player()
{

}

void Player::Render()
{
	SDL_RenderCopy(ren, PlayerTexture, NULL, NULL);
}

void Player::Update()
{

}

void Player::clean()
{

}