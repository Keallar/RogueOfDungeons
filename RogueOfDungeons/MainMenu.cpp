#include "MainMenu.h"
#include "Game.h"
#include "textureManager.h"
MainMenu::MainMenu(const char* texturesheet, SDL_Renderer* ren) {
	renderer = ren;
	MainMenuTexture = textureManager::LoadTexture(texturesheet, ren);
}
MainMenu::~MainMenu()
{}
void MainMenu::MainMenuTextureSeater()
{}
void MainMenu::Render() {
	SDL_RenderCopy(renderer, MainMenuTexture, NULL, NULL);
	SDL_RenderPresent(renderer);
}
void MainMenu::RenderButtons() {

}
void MainMenu::Update() {

}
void MainMenu::UpdateButtons() {

}
void MainMenu::clear() {

}
void MainMenu::clearButtons() {

}


