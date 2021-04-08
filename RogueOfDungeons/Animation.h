#pragma once
#include "Managers.h"
#include "SDL.h"
#include "SDL_image.h"
#include <map>

class Animation
{
private:
	SDL_Renderer* ren;
	SDL_Texture* playerAnimation;
	int xanimPlayer, yanimPlayer;
	SDL_Texture* enemyTurtleAnimation;
	int xanimTurtle, yanimTurtle;
	SDL_Texture* enemyAbobaAnimation;
	int xanimAboba, yanimAboba;
public:
	Animation(SDL_Renderer* renderer);
	~Animation();
	void animationForPlayer();
	void animationForTurtle();
	void animationForAboba();
};

