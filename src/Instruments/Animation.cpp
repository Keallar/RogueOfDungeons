#include "Animation.h"
#include "EntityPosition.h"
#include <iostream>

Animation::Animation(SDL_Renderer* renderer, SDL_Texture* texture) : 
	ren(renderer), animTexture(texture)
{
    GameTexture = TextureBase::Instance();
    xanim = 0;
	yanim = 0;
}

Animation::~Animation()
{
\
}

void Animation::Render(int xposition, int yposition)
{
	RenderManager::CopyToRender(animTexture, ren, xposition, yposition, 32, 32, xanim, yanim, 32, 32);
}

void Animation::UpdateTexture(std::string newTexture)
{
	animTexture = 0;
    animTexture = GameTexture->GetTexture(newTexture);
}

int Animation::animationPlusForX(int numOfFrames)
{
    static int num = 1;
	if (xanim != 32 * (numOfFrames - 1))
	{
		xanim += 32;
        num++;
	}
	else
	{
		xanim = 0;
        num = 1;
	}

    return num;
}

int Animation::animationPlusForY(int numOfFrames)
{
    static int num = 1;
	if (yanim != 32 * (numOfFrames - 1))
	{
		yanim += 32;
        num++;
	}
	else
	{
		yanim = 0;
        num = 1;
	}

    return num;
}

int Animation::animationMinusForX(int numOfFrames)
{
    static int num = 1;
    if (xanim != -32 * (numOfFrames - 1))
	{
		xanim -= 32;
        num++;
	}
	else
	{
		xanim = 0;
        num = 1;
	}

    return num;
}

int Animation::animationMinusForY(int numOfFrames)
{
    static int num = 1;
	if (yanim != -32 * (numOfFrames - 1))
	{
		yanim -= 32;
        num++;
	}
	else
	{
		yanim = 0;
        num = 1;
	}

    return num;
}

