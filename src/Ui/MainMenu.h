#pragma once
#include "Managers.h"

class MainMenu
{
private:
	SDL_Texture* MainMenuTexture;
	SDL_Renderer* renderer;
	SDL_Texture* PlayButton;
	SDL_Texture* SettingsButton;
	SDL_Texture* ExitButton;
public:
	int flag = 1;
	MainMenu(const char* texturesheetMenu, const char* texturesheetPlay,
		const char* texturesheetSettings, const char* texturesheetExit, SDL_Renderer* ren);
	~MainMenu();
	void Render();
};

