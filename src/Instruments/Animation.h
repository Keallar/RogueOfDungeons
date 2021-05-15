#pragma once
#include "Managers.h"
#include "SDL.h"
#include "SDL_image.h"
#include "TextureBase.h"
#include <string>

class Animation
{
private:
	SDL_Renderer* ren;
	SDL_Texture* animTexture;
	int xanim, yanim;
	int xpos, ypos;
    TextureBase* GameTexture;

public:
	Animation(SDL_Renderer* renderer, SDL_Texture* texture);
	~Animation();
	void Render(int xposition, int yposition);
    void UpdateTexture(std::string newTexture); //Добавлять этот метод всегда, когда меняете текстуру чего-то
    int animationPlusForX(int numOfFrames);
    int animationPlusForY(int numOfFrames);
    int animationMinusForX(int numOfFrames);
    int animationMinusForY(int numOfFrames);
};

