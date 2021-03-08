#include "UI.h"
#include "Managers.h"

//UIMenu::UIMenu(SDL_Renderer* renderer) 
//{
//	ren = renderer;
//	
//}
//void UIMenu::Render()
//{
//	RenderManager::CopyToRender(Font1, ren, 1024, 10, 256, 21);
//	RenderManager::CopyToRender(Font2, ren, 1024, 30, 256, 21);
//}

UILevel::UILevel(SDL_Renderer* renderer)
{
	SDL_Color color = { 255, 255, 255, 255 };
	ren = renderer;
	infoBLock = FontManager::renderText("rogue of dungeons", "fonts/manaspc.ttf", color,64, ren);
	inventoryBlock = FontManager::renderText("maybe dungeons of rogue&", "fonts/manaspc.ttf",  color,64, ren);
}

void UILevel::Render()
{
	RenderManager::CopyToRender(infoBLock, ren);
	RenderManager::CopyToRender(inventoryBlock, ren);
}

