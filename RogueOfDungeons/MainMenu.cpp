#include "MainMenu.h"
#include "Game.h"
#include "textureManager.h"

MainMenu::MainMenu(const char* texturesheetMenu, const char* texturesheetPlay,
	const char* texturesheetSettings, const char* texturesheetExit, SDL_Renderer* ren) {
	renderer = ren;
	MainMenuTexture = textureManager::LoadTexture(texturesheetMenu, ren);
	PlayButton = textureManager::LoadTexture(texturesheetPlay, ren);
	SettingsButton = textureManager::LoadTexture(texturesheetSettings, ren);
	ExitButton = textureManager::LoadTexture(texturesheetExit, ren);
}
void MainMenu::Render() {
	RenderManager::CopyToRender(MainMenuTexture, renderer, 0, 0, 1280, 720);
	RenderManager::CopyToRender(PlayButton, renderer, 640, 361, 250, 100);
	RenderManager::CopyToRender(SettingsButton, renderer, 640, 471, 420, 100);
	RenderManager::CopyToRender(ExitButton, renderer, 640, 581, 250, 100);
	SDL_RenderPresent(renderer);
}



