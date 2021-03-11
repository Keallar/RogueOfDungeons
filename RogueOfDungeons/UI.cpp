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

UIInfo::UIInfo(SDL_Renderer* renderer)
{
	pathInFont = "fonts/manaspc.ttf";
	SDL_Color color = { 255, 255, 255, 255 };
	ren = renderer;

	//Version
	versionBLock = FontManager::renderText("ROGUE OF DUNGEONS V-0.0.2", pathInFont, color, 32, ren);
	
	infoBlock = textureManager::LoadTexture("images/InfoBlock.png", ren);
	inventoryBlock = textureManager::LoadTexture("images/InfoBlock.png", ren);
	info = FontManager::renderText("Info", "fonts/manaspc.ttf", color, 32, ren);
	inventory = FontManager::renderText("Inventory", pathInFont, color, 32, ren);
	
	//HP
	hpBar = textureManager::LoadTexture("images/hp.png", ren);
	hpText = FontManager::renderText("HP", pathInFont, color, 64, ren);
	hpInfo = FontManager::renderText("10/10", pathInFont, color, 32, ren);
	
	//Mana
	mnBar = textureManager::LoadTexture("images/ManaBar.png", ren);
	mnText = FontManager::renderText("MN", pathInFont, color, 64, ren);
	mnInfo = FontManager::renderText("50/50", pathInFont, color, 32, ren);

	//XP
	xpBar = textureManager::LoadTexture("images/XP.png", ren);
	xpText = FontManager::renderText("XP", pathInFont, color, 64, ren);
	xpInfo = FontManager::renderText("99/100", pathInFont, color, 32, ren);

	//Buttons
	specButton = textureManager::LoadTexture("images/Button.png", ren);

	//Specifications
	STR = FontManager::renderText("STR", pathInFont, color, 64, ren);
	DEX = FontManager::renderText("DEX", pathInFont, color, 64, ren);
	INT = FontManager::renderText("INT", pathInFont, color, 64, ren);
	PHS = FontManager::renderText("INT", pathInFont, color, 64, ren);
	LCK = FontManager::renderText("LCK", pathInFont, color, 64, ren);
}

void UIInfo::Render()
{
	RenderManager::CopyToRender(versionBLock, ren, 0, 705, 170, 9 );
	RenderManager::CopyToRender(infoBlock, ren, 1024, 0, 256, 480);
	RenderManager::CopyToRender(inventoryBlock, ren, 1024, 480, 256, 225);
	RenderManager::CopyToRender(info, ren, 1116, 13, 64, 32);
	RenderManager::CopyToRender(inventory, ren, 1085, 490, 128, 32);
	
	//HP
	RenderManager::CopyToRender(hpBar, ren, 1080, 40, 160, 32, 0, 0, 128, 16);
	RenderManager::CopyToRender(hpText, ren, 1050, 47, 25, 22);
	RenderManager::CopyToRender(hpInfo, ren, 1116, 72, 64, 20);

	//Mana
	RenderManager::CopyToRender(mnBar, ren, 1080, 95, 230, 32, 21, 10, 128, 16);
	RenderManager::CopyToRender(mnText, ren, 1050, 99, 25, 22);
	RenderManager::CopyToRender(mnInfo, ren, 1116, 122, 64, 20);
	
	//XP
	RenderManager::CopyToRender(xpBar, ren, 1080, 150, 200, 32, 21, 10, 128, 16);
	RenderManager::CopyToRender(xpText, ren, 1050, 152, 25, 22);
	RenderManager::CopyToRender(xpInfo, ren, 1116, 175, 64, 20);

	//Buttons
	RenderManager::CopyToRender(specButton, ren, 1230, 200, 32, 32);

	//Specifications
	//RenderManager::CopyToRender(STR, ren, 1050, 160, 64, 20);
}

