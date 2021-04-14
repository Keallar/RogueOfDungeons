#include "Animation.h"
#include "EntityPosition.h"

Animation::Animation(SDL_Renderer* renderer, SDL_Texture* texture) : ren(renderer), animTexture(texture)
{
	xanim = 0;
	yanim = 0;
}

Animation::~Animation()
{
	
}

void Animation::Render()
{
	RenderManager::CopyToRender(animTexture, ren, EntityPosition::Coords[2], EntityPosition::Coords[3], 32, 32, xanim, yanim, 32, 32);
}

int Animation::animationInstrForX(SDL_Texture* texture, int numOfFrames, bool complete)
{
	if (xanim != 32 * numOfFrames)
	{
		xanim += 32;
	}
	else
	{
		xanim = 0;
	}
	return xanim;
}

int Animation::animationInstrForY(SDL_Texture* texture, int numOfFrames, bool complete)
{
	if (yanim != 32 * numOfFrames)
	{
		yanim += 32;
	}
	else
	{
		yanim = 0;
	}
	return yanim;
}

bool Animation::animationInstrForXCoord(int numOfFrames, bool complete)
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

void Animation::animationInstrForYCoord(SDL_Texture* texture, int numOfFrames, bool complete)
{

}

