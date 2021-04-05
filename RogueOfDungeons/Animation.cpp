#include "Animation.h"


Animation::Animation(SDL_Renderer* renderer) : ren(renderer)
{
	xanimPlayer = 0;
	yanimPlayer = 0;
	xanimTurtle = 0;
	yanimTurtle = 0;
	xanimAboba = 0;
	yanimAboba = 0;
	playerAnimation = textureManager::LoadTexture("images/Player.png", ren);
	enemyTurtleAnimation = textureManager::LoadTexture("images/Turtle..png", ren);
	enemyAbobaAnimation = textureManager::LoadTexture("images/ABOBA.png", ren);
}

Animation::~Animation()
{
	SDL_DestroyTexture(playerAnimation);
	SDL_DestroyTexture(enemyTurtleAnimation);
	SDL_DestroyTexture(enemyAbobaAnimation);
}

void Animation::animationForPlayer()
{
	if (xanimPlayer != 96)
	{
		xanimPlayer += 32;
	}
	else if (xanimPlayer == 96)
	{
	
	}
}

void Animation::animationForTurtle()
{
	if (xanimTurtle != 96)
	{

	}
	else if (xanimTurtle == 96)
	{

	}
}

void Animation::animationForAboba()
{
	if (xanimAboba != 96)
	{

	}
	else if (xanimAboba == 96)
	{

	}
}