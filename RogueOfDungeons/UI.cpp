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
	pathInFont = "fonts/manaspc.ttf";
	SDL_Color color = { 255, 255, 255, 255 };
	ren = renderer;
	versionBLock = FontManager::renderText("ROGUE OF DUNGEONS V-0.0.2", pathInFont, color, 32, ren);
	infoBlock = textureManager::LoadTexture("images/InfoBlock.png", ren);
	inventoryBlock = textureManager::LoadTexture("images/InfoBlock.png", ren);
	info = FontManager::renderText("Info", "fonts/manaspc.ttf", color, 32, ren);
	inventory = FontManager::renderText("Inventory", pathInFont, color, 32, ren);
	hpBar = textureManager::LoadTexture("images/hp.png", ren);
	hpText = FontManager::renderText("HP", pathInFont, color, 64, ren);
	hpInfo = FontManager::renderText("20/20", pathInFont, color, 32, ren);
}

void UILevel::Render()
{
	RenderManager::CopyToRender(versionBLock, ren, 0, 705, 170, 9 );
	RenderManager::CopyToRender(infoBlock, ren, 1024, 0, 256, 480);
	RenderManager::CopyToRender(inventoryBlock, ren, 1024, 480, 256, 225);
	RenderManager::CopyToRender(info, ren, 1116, 15, 64, 32);
	RenderManager::CopyToRender(inventory, ren, 1085, 490, 128, 32);
	RenderManager::CopyToRender(hpBar, ren, 1080, 40, 140, 32, 0, 0, 128, 16);
	RenderManager::CopyToRender(hpText, ren, 1050, 47, 25, 22);
	RenderManager::CopyToRender(hpInfo, ren, 1116, 72, 64, 20);
}

