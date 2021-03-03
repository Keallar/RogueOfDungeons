#pragma once
#include "Game.h"
#include "textureManager.h"

class MainMenu
{
private:
	SDL_Texture* MainMenuTexture;
	SDL_Renderer* renderer;
	
public:
	int flag = 1;
	MainMenu();
	~MainMenu();
	void MainMenuTextureSetter(const char* texturesheet, SDL_Renderer* ren);
	void Render();
	void RenderButtons();
	void Update();
	void UpdateButtons();
	void clear();
	void clearButtons();
	

};

