#include "Player.h"
#include "GameObject.h"
#include "Level.h"
Player::Player()
{}


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
	RenderManager::CopyToRender(PlayerTexture, ren, 32, 32, 32, 32, 0, 0, 32, 32);
	
}

void Player::Update()
{

}

void Player::clean()
{

}