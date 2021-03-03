#include "MainMenu.h"
#include "Game.h"
#include "textureManager.h"
MainMenu::MainMenu() {
	
};
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
void MainMenu::MainMenuTextureSetter(const char* texturesheet, SDL_Renderer* ren) {
	renderer = ren;
	MainMenuTexture = textureManager::LoadTexture(texturesheet, ren);
}
