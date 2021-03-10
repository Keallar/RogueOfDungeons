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
	versionBLock = FontManager::renderText("ROGUE OF DUNGEONS V-0.0.1", "fonts/manaspc.ttf", 255, 255, 255, 255, 32, ren);
	infoBlock = textureManager::LoadTexture("images/InfoBlock.png", ren);
	inventoryBlock = FontManager::renderText("Info", "fonts/manaspc.ttf", 255, 255, 255, 255, 32, ren);
}

void UILevel::Render()
{
	RenderManager::CopyToRender(versionBLock, ren, EntityPosition::Coords[4], EntityPosition::Coords[5], 170, 10 );
	RenderManager::CopyToRender(infoBlock, ren, EntityPosition::Coords[8], EntityPosition::Coords[9], 256, 480);
	RenderManager::CopyToRender(inventoryBlock, ren, EntityPosition::Coords[6], EntityPosition::Coords[7], 64, 32);
}

