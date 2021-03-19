#include "UI.h"
#include "Managers.h"
#include "EntityPosition.h"
#include <iostream>

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

TextInfo::TextInfo(SDL_Renderer* renderer, int changeTextValue) : ren(renderer)
{
	PATH_IN_FONT = "fonts/manaspc.ttf";
	std::string stringValue = std::to_string(changeTextValue);
	const char* TEXT_VALUE = stringValue.c_str();
	infoText = FontManager::renderText(TEXT_VALUE, PATH_IN_FONT, color, 32, ren);
}

TextInfo::~TextInfo()
{

}

void TextInfo::Render()
{
	RenderManager::CopyToRender(infoText, ren, 1116, 72, 32, 20);
}


UIInfo::UIInfo(SDL_Renderer* renderer)
{
	pathInFont = "fonts/manaspc.ttf";
	ren = renderer;

	//Version
	versionBLock = FontManager::renderText("ROGUE OF DUNGEONS V-0.0.4", pathInFont, color, 32, ren);

	infoBlock = textureManager::LoadTexture("images/InfoBlock.png", ren);
	info = FontManager::renderText("Info", "fonts/manaspc.ttf", color, 32, ren);

	//HP
	hpBar = textureManager::LoadTexture("images/hp.png", ren);
	hpText = FontManager::renderText("HP", pathInFont, color, 64, ren);
	//hpInfo = FontManager::renderText("10/10", pathInFont, color, 32, ren);

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
}

void UIInfo::Render()
{
	RenderManager::CopyToRender(versionBLock, ren, 0, 705, 170, 9);
	RenderManager::CopyToRender(infoBlock, ren, 1024, 0, 256, 480);
	RenderManager::CopyToRender(info, ren, 1116, 13, 64, 32);

	//HP
	RenderManager::CopyToRender(hpBar, ren, 1080, 40, 160, 32, 0, 0, 128, 16);
	RenderManager::CopyToRender(hpText, ren, 1050, 47, 25, 22);
	//RenderManager::CopyToRender(hpInfo, ren, 1116, 72, 64, 20);

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

}

void UIInfo::Update()
{
	if (keys[SDL_SCANCODE_Q] && FlagManager::flagUI == 0)
	{
		std::cout << "Check Info" << std::endl;
		FlagManager::flagUiSpec = 0;
		FlagManager::flagUI = 1;
	}
}

UISpecifications::UISpecifications(SDL_Renderer* renderer)
{
	pathInFont = "fonts/manaspc.ttf";
	SDL_Color color = { 255, 255, 255, 255 };
	ren = renderer;

	//Specifications
	specBlock = textureManager::LoadTexture("images/InfoBlock.png", ren);
	specifcation = FontManager::renderText("Specifications", pathInFont, color, 64, ren);
	plus = FontManager::renderText("+", pathInFont, color, 32, ren);
	state = FontManager::renderText("1", pathInFont, color, 32, ren);
	STR = FontManager::renderText("STR", pathInFont, color, 64, ren);
	DEX = FontManager::renderText("DEX", pathInFont, color, 64, ren);
	INT = FontManager::renderText("INT", pathInFont, color, 64, ren);
	PHS = FontManager::renderText("PHS", pathInFont, color, 64, ren);
	LCK = FontManager::renderText("LCK", pathInFont, color, 64, ren);
}

void UISpecifications::Render()
{
	//Specifications
	RenderManager::CopyToRender(specBlock, ren, 1024, 0, 256, 480);
	RenderManager::CopyToRender(specifcation, ren, 1075, 13, 160, 32);

	RenderManager::CopyToRender(STR, ren, 1050, 80, 64, 20);
	RenderManager::CopyToRender(plus, ren, 1230, 80, 16, 20);
	RenderManager::CopyToRender(state, ren, 1180, 80, 16, 20);

	RenderManager::CopyToRender(DEX, ren, 1050, 110, 64, 20);
	RenderManager::CopyToRender(plus, ren, 1230, 110, 16, 20);
	RenderManager::CopyToRender(state, ren, 1180, 110, 16, 20);

	RenderManager::CopyToRender(INT, ren, 1050, 140, 64, 20);
	RenderManager::CopyToRender(plus, ren, 1230, 140, 16, 20);
	RenderManager::CopyToRender(state, ren, 1180, 140, 16, 20);

	RenderManager::CopyToRender(PHS, ren, 1050, 170, 64, 20);
	RenderManager::CopyToRender(plus, ren, 1230, 170, 16, 20);
	RenderManager::CopyToRender(state, ren, 1180, 170, 16, 20);

	RenderManager::CopyToRender(LCK, ren, 1050, 200, 64, 20);
	RenderManager::CopyToRender(plus, ren, 1230, 200, 16, 20);
	RenderManager::CopyToRender(state, ren, 1180, 200, 16, 20);
}

void UISpecifications::Update()
{
	//UNDONE (to do bundle with mouse)
	if ((keys[SDL_SCANCODE_C] && FlagManager::flagUiSpec == 0))
	{
		std::cout << "Check Spec" << std::endl;
		FlagManager::flagUiSpec = 1;
		FlagManager::flagUI = 0;
	}
}

UIInventory::UIInventory(SDL_Renderer* renderer)
{
	pathInFont = "fonts/manaspc.ttf";
	SDL_Color color = { 255, 255, 255, 255 };
	ren = renderer;

	inventoryBlock = textureManager::LoadTexture("images/InfoBlock.png", ren);
	inventory = FontManager::renderText("Inventory", pathInFont, color, 32, ren);
}

void UIInventory::Render()
{

	RenderManager::CopyToRender(inventoryBlock, ren, 1024, 480, 256, 225);
	RenderManager::CopyToRender(inventory, ren, 1085, 490, 128, 32);
}

//EnemyInfo
UIEnemyInfo::UIEnemyInfo(SDL_Renderer* renderer)
{
	pathInFont = "fonts/manaspc.ttf";
	SDL_Color color = { 255, 255, 255, 255 };
	ren = renderer;

	enemy = FontManager::renderText("Enemy", pathInFont, color, 32, ren);
	hpEmenyBar = textureManager::LoadTexture("images/EnemyBar.png", ren);
	hpEnemyText = FontManager::renderText("HP", pathInFont, color, 64, ren);
	hpEnemyInfo = FontManager::renderText("5/5", pathInFont, color, 32, ren);
}

void UIEnemyInfo::Render()
{
	RenderManager::CopyToRender(enemy, ren, 1116, 250, 64, 32);
	RenderManager::CopyToRender(hpEmenyBar, ren, 1080, 290, 190, 45, 20, 5, 256, 32);
	RenderManager::CopyToRender(hpEnemyText, ren, 1050, 300, 25, 22);
	RenderManager::CopyToRender(hpEnemyInfo, ren, 1130, 325, 32, 20);
}