#include "UI.h"

UI::UI(SDL_Renderer* renderer) {
	ren = renderer;
	Font1 = FontManager::renderText("rogue of dungeons", "fonts/manaspc.ttf", 255, 255, 255, 255, 16, ren);
	Font2 = FontManager::renderText("maybe dungeons of rogue&", "fonts/manaspc.ttf", 255, 255, 255, 255, 16, ren);
}
void UI::start() {
	RenderManager::CopyToRender(Font1, ren, 1024, 10, 256, 21);
	RenderManager::CopyToRender(Font2, ren, 1024, 30, 256, 21);
}