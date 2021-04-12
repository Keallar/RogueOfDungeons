#pragma once
#include "Managers.h"
#include "SDL.h"
#include "SDL_image.h"

class Animation
{
private:
	SDL_Renderer* ren;
	int xanim, yanim;
public:
	Animation(SDL_Renderer* renderer);
	~Animation();
	void Render();
	int animationInstrForX(SDL_Texture* texture, int numOfFrames, bool complete);
	int animationInstrForY(SDL_Texture* texture, int numOfFrames, bool complete);
	void animationInstrForXCoord(SDL_Texture* texture, int numOfFrames, bool complete);
	void animationInstrForYCoord(SDL_Texture* texture, int numOfFrames, bool complete);
};

