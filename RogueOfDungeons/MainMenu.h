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
	void MainMenuTextureSeater();
	void Render();
	void RenderButtons();
	void Update();
	void UpdateButtons();
	void clear();
	void clearButtons();

};

