#include "UI.h"
#include "Managers.h"
#include "EntityPosition.h"

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
	//SDL_Color color = { 255, 255, 255, 255 };
	ren = renderer;
	infoBLock = FontManager::renderText("Rogue of dungeons", "fonts/manaspc.ttf", 255, 255, 255, 255, 32, ren);
	inventoryBlock = FontManager::renderText("Maybe dungeons of rogue", "fonts/manaspc.ttf", 255, 255, 255, 255, 32, ren);
}

void UILevel::Render()
{
	RenderManager::CopyToRender(infoBLock, ren, EntityPosition::Coords[4], EntityPosition::Coords[5], 32, 32 );
	RenderManager::CopyToRender(inventoryBlock, ren, EntityPosition::Coords[6], EntityPosition::Coords[7], 32, 32);
}

