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

}

void Player::Update()
{

}

void Player::clean()
{

}