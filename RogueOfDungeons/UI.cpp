#include "UI.h"
#include "Managers.h"
#include "EntityPosition.h"
#include <iostream>
#include "inventory.h"

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
}

TextInfo::~TextInfo()
{
	
}

HpInfo::HpInfo(SDL_Renderer* renderer, int changeTextValue) :TextInfo(renderer, changeTextValue)
{
	ren = renderer;
	PATH_IN_FONT = "fonts/manaspc.ttf";
	std::string stringValue = std::to_string(changeTextValue);
	const char* TEXT_VALUE = stringValue.c_str();
	hpText = FontManager::renderText(TEXT_VALUE, PATH_IN_FONT, color, 32, ren);
}

HpInfo::~HpInfo()
{

}

void HpInfo::Update(int value)
{
	std::string stringTemp = std::to_string(value);
	const char* CHAR_VALUE = stringTemp.c_str();
	hpText = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);
}

void HpInfo::Render()
{
	RenderManager::CopyToRender(hpText, ren, 1120, 72, 32, 20);
}

ManaInfo::ManaInfo(SDL_Renderer* renderer, int changeTextValue) : TextInfo(renderer, changeTextValue)
{
	ren = renderer;
	PATH_IN_FONT = "fonts/manaspc.ttf";
	std::string stringValue = std::to_string(changeTextValue);
	const char* TEXT_VALUE = stringValue.c_str();
	manaText = FontManager::renderText(TEXT_VALUE, PATH_IN_FONT, color, 32, ren);
}

ManaInfo::~ManaInfo()
{

}

void ManaInfo::Update(int value)
{
	std::string stringTemp = std::to_string(value);
	const char* CHAR_VALUE = stringTemp.c_str();
	manaText = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);
}

void ManaInfo::Render()
{
	RenderManager::CopyToRender(manaText, ren, 1120, 122, 32, 20);
}

ExpInfo::ExpInfo(SDL_Renderer* renderer, int changeTextValue) : TextInfo(renderer, changeTextValue)
{
	ren = renderer;
	PATH_IN_FONT = "fonts/manaspc.ttf";
	std::string stringValue = std::to_string(changeTextValue);
	const char* TEXT_VALUE = stringValue.c_str();
	expText = FontManager::renderText(TEXT_VALUE, PATH_IN_FONT, color, 32, ren);
}

ExpInfo::~ExpInfo()
{
	
}

void ExpInfo::Update(int value)
{
	std::string stringTemp = std::to_string(value);
	const char* CHAR_VALUE = stringTemp.c_str();
	expText = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);
}

void ExpInfo::Render()
{
	RenderManager::CopyToRender(expText, ren, 1120, 175, 64, 20);
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

	//Mana
	mnBar = textureManager::LoadTexture("images/ManaBar.png", ren);
	mnText = FontManager::renderText("MN", pathInFont, color, 64, ren);

	//XP
	xpBar = textureManager::LoadTexture("images/XP.png", ren);
	xpText = FontManager::renderText("XP", pathInFont, color, 64, ren);

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

	//Mana
	RenderManager::CopyToRender(mnBar, ren, 1080, 95, 230, 32, 21, 10, 128, 16);
	RenderManager::CopyToRender(mnText, ren, 1050, 99, 25, 22);

	//XP
	RenderManager::CopyToRender(xpBar, ren, 1080, 150, 200, 32, 21, 10, 128, 16);
	RenderManager::CopyToRender(xpText, ren, 1050, 152, 25, 22);

	//Buttons
	RenderManager::CopyToRender(specButton, ren, 1230, 200, 32, 32);

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
	one = FontManager::renderText("(1)", pathInFont, color, 64, ren);
	two = FontManager::renderText("(2)", pathInFont, color, 64, ren);
	three = FontManager::renderText("(3)", pathInFont, color, 64, ren);
	four = FontManager::renderText("(4)", pathInFont, color, 64, ren);
	five = FontManager::renderText("(5)", pathInFont, color, 64, ren);

}

void UISpecifications::Render()
{
	//Specifications
	RenderManager::CopyToRender(specBlock, ren, 1024, 0, 256, 480);
	RenderManager::CopyToRender(specifcation, ren, 1075, 13, 160, 32);

	RenderManager::CopyToRender(STR, ren, 1050, 80, 64, 20);
	RenderManager::CopyToRender(plus, ren, 1230, 80, 16, 20);
	RenderManager::CopyToRender(state, ren, 1180, 80, 16, 20);
	RenderManager::CopyToRender(one, ren, 1250, 80, 16, 20);

	RenderManager::CopyToRender(DEX, ren, 1050, 110, 64, 20);
	RenderManager::CopyToRender(plus, ren, 1230, 110, 16, 20);
	RenderManager::CopyToRender(state, ren, 1180, 110, 16, 20);
	RenderManager::CopyToRender(two, ren, 1250, 110, 16, 20);

	RenderManager::CopyToRender(INT, ren, 1050, 140, 64, 20);
	RenderManager::CopyToRender(plus, ren, 1230, 140, 16, 20);
	RenderManager::CopyToRender(state, ren, 1180, 140, 16, 20);
	RenderManager::CopyToRender(three, ren, 1250, 140, 16, 20);

	RenderManager::CopyToRender(PHS, ren, 1050, 170, 64, 20);
	RenderManager::CopyToRender(plus, ren, 1230, 170, 16, 20);
	RenderManager::CopyToRender(state, ren, 1180, 170, 16, 20);
	RenderManager::CopyToRender(four, ren, 1250, 170, 16, 20);

	RenderManager::CopyToRender(LCK, ren, 1050, 200, 64, 20);
	RenderManager::CopyToRender(plus, ren, 1230, 200, 16, 20);
	RenderManager::CopyToRender(state, ren, 1180, 200, 16, 20);
	RenderManager::CopyToRender(five, ren, 1250, 200, 16, 20);
}

UIItem::UIItem(SDL_Renderer* renderer)
{
	pathInFont = "fonts/manaspc.ttf";
	SDL_Color color = { 255, 255, 255, 255 };
	ren = renderer;

	itemBlock = textureManager::LoadTexture("images/InfoBlock.png", ren);
	item = FontManager::renderText("Inventory", pathInFont, color, 32, ren);
}

void UIItem::Render()
{
	RenderManager::CopyToRender(itemBlock, ren, 1024, 480, 256, 225);
	RenderManager::CopyToRender(item, ren, 1085, 490, 128, 32);
}

UIInventory::UIInventory(SDL_Renderer* renderer) : ren(renderer)
{
	SDL_Color color = { 255, 255, 255, 255 };
	const char* PATH_IN_FONT = "fonts/manaspc.ttf";
	inventoryBlock = textureManager::LoadTexture("images/InfoBlock.png", ren);
	inventoryText = FontManager::renderText("Inventory", PATH_IN_FONT, color, 64, ren);
}

void UIInventory::Render()
{
	RenderManager::CopyToRender(inventoryBlock, ren, 730, 0, 300, 710);
	RenderManager::CopyToRender(inventoryText, ren, 780, 50, 160, 32);
	for (int i = 0; i < 16; i++) {
		if (Inventory::inventoryFace[i] != -1) {
			Inventory::it = Inventory::ExistingItems.find(Inventory::inventoryFace[i]);
			std::cout << (Inventory::it->second).ItemTexture;
			item = textureManager::LoadTexture((Inventory::it->second).ItemTexture, ren);
		}
		else {
			std::cout << 0;
		}
	}
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