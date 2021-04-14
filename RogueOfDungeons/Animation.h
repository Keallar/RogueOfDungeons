#pragma once
#include "Managers.h"
#include "SDL.h"
#include "SDL_image.h"

class Animation
{
private:
	SDL_Renderer* ren;
	SDL_Texture* animTexture;
	int xanim, yanim;
public:
	Animation(SDL_Renderer* renderer, SDL_Texture* texture);
	~Animation();
	void Render();
	int animationInstrForX(SDL_Texture* texture, int numOfFrames, bool complete);
	int animationInstrForY(SDL_Texture* texture, int numOfFrames, bool complete);
	bool animationInstrForXCoord(int numOfFrames, bool complete);
	void animationInstrForYCoord(SDL_Texture* texture, int numOfFrames, bool complete);
};

