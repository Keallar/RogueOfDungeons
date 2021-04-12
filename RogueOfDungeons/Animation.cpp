#include "Animation.h"
#include "EntityPosition.h"

Animation::Animation(SDL_Renderer* renderer) : ren(renderer)
{
	xanim = 0;
	yanim = 0;
}

Animation::~Animation()
{
	
}

//void Animation::Render()
//{
//	RenderManager::CopyToRender(enemyTexture, ren, EntityPosition::Coords[2], EntityPosition::Coords[3], 32, 32, xanim, yanim, 32, 32);
//}

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

void Animation::animationInstrForXCoord(SDL_Texture* texture, int numOfFrames, bool complete)
{
	if (xanim != 32 * numOfFrames)
	{
		xanim += 32;
	}
	else
	{
		xanim = 0;
	}

	RenderManager::CopyToRender(texture, ren, EntityPosition::Coords[2], EntityPosition::Coords[3], 32, 32, xanim, yanim, 32, 32);
}

void Animation::animationInstrForYCoord(SDL_Texture* texture, int numOfFrames, bool complete)
{

}

