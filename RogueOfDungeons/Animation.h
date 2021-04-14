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
	int xpos, ypos;
public:
	Animation(SDL_Renderer* renderer, SDL_Texture* texture);
	~Animation();
	void Render(int xposition, int yposition);
	void UpdateTexture(const char* newTexture); //��������� ���� ����� ������, ����� ������� �������� ����-��
	bool animationPlusForX(int numOfFrames, bool complete);
	bool animationPlusForY(int numOfFrames, bool complete);
	bool animationMinusForX(int numOfFrames, bool complete);
	bool animationMinusForY(int numOfFrames, bool complete);
};

