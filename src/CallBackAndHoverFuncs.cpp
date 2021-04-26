#include "CallBackAndHoverFuncs.h"
#include "Game.h"

using namespace std;

void hoverFunctions::callSpecWin()
{
	const char* PATH_IN_FONT = "data/fonts/manaspc.ttf";
	SDL_Color color = { 255, 255, 255, 255 };
	SDL_Texture* SPEC = FontManager::renderText("SPEC", PATH_IN_FONT, color, 32, Game::renderer);

	if (SPEC != nullptr)
	{
		RenderManager::CopyToRender(SPEC, Game::renderer, 1230, 220, 30, 25);
		std::cout << "Render Hover SPEC" << std::endl;
	}
}
