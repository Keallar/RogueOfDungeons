#include "Animation.h"
#include "EntityPosition.h"

Animation::Animation(SDL_Renderer* renderer, SDL_Texture* texture) : 
	ren(renderer), animTexture(texture)
{
	xanim = 0;
	yanim = 0;
}

Animation::~Animation()
{
	
}

void Animation::Render(int xposition, int yposition)
{
	RenderManager::CopyToRender(animTexture, ren, xposition, yposition, 32, 32, xanim, yanim, 32, 32);
}

void Animation::UpdateTexture(const char* newTexture)
{
	SDL_DestroyTexture(animTexture);
	animTexture = 0;
	animTexture = textureManager::LoadTexture(newTexture, ren);
}

bool Animation::animationPlusForX(int numOfFrames, bool complete)
{
	if (xanim != 32 * numOfFrames)
	{
		xanim += 32;
		complete = 0;
	}
	else
	{
		xanim = 0;
		complete = 1;
	}

	return complete;
}

bool Animation::animationPlusForY(int numOfFrames, bool complete)
{
	if (yanim != 32 * numOfFrames)
	{
		yanim += 32;
		complete = 0;
	}
	else
	{
		yanim = 0;
		complete = 1;
	}

	return complete;
}

bool Animation::animationMinusForX(int numOfFrames, bool complete)
{
	if (xanim != -32 * numOfFrames)
	{
		xanim -= 32;
		complete = 0;
	}
	else
	{
		xanim = 0;
		complete = 1;
	}

	return complete;
}

bool Animation::animationMinusForY(int numOfFrames, bool complete)
{
	if (yanim != -32 * numOfFrames)
	{
		yanim -= 32;
		complete = 0;
	}
	else
	{
		yanim = 0;
		complete = 1;
	}

	return complete;
}

