#include "UI.h"
#include "Managers.h"
#include "EntityPosition.h"
#include <iostream>
#include "inventory.h"
#include "Player.h"

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

//UNDONE (изменить конструкторы для HpInfo, ManaInfo, ExpInfo)
HpInfo::HpInfo(SDL_Renderer* renderer, int changeTextValue) :TextInfo(renderer, changeTextValue)
{
	ren = renderer;
	PATH_IN_FONT = "fonts/manaspc.ttf";
	std::string stringValue = std::to_string(changeTextValue);
	const char* TEXT_VALUE = stringValue.c_str();
	hpText = FontManager::renderText(TEXT_VALUE, PATH_IN_FONT, color, 32, ren);
	hpMax = FontManager::renderText("10", PATH_IN_FONT, color, 32, ren);
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

void HpInfo::UpdateMax()
{
	std::string stringTemp = std::to_string(Player::GetHP(2));
	const char* CHAR_VALUE = stringTemp.c_str();
	hpMax = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);
}

void HpInfo::Render()
{
	RenderManager::CopyToRender(hpText, ren, 1120, 72, 32, 20);
	RenderManager::CopyToRender(hpMax, ren, 1180, 72, 32, 20);
}

ManaInfo::ManaInfo(SDL_Renderer* renderer, int changeTextValue) : TextInfo(renderer, changeTextValue)
{
	ren = renderer;
	PATH_IN_FONT = "fonts/manaspc.ttf";
	std::string stringValue = std::to_string(changeTextValue);
	const char* TEXT_VALUE = stringValue.c_str();
	manaText = FontManager::renderText(TEXT_VALUE, PATH_IN_FONT, color, 32, ren);
	manaMax = FontManager::renderText("50", PATH_IN_FONT, color, 32, ren);
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

void ManaInfo::UpdateMax()
{

}

void ManaInfo::Render()
{
	RenderManager::CopyToRender(manaText, ren, 1120, 122, 32, 20);
	RenderManager::CopyToRender(manaMax, ren, 1180, 122, 32, 20);
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

void ExpInfo::UpdateMax()
{

}

void ExpInfo::Render()
{
	RenderManager::CopyToRender(expText, ren, 1120, 175, 32, 20);
}

UIInfo::UIInfo(SDL_Renderer* renderer)
{
	PATH_IN_FONT = "fonts/manaspc.ttf";
	ren = renderer;

	//Version
	versionBLock = FontManager::renderText("ROGUE OF DUNGEONS V-0.0.5", PATH_IN_FONT, color, 32, ren);

	infoBlock = textureManager::LoadTexture("images/InfoBlock.png", ren);
	info = FontManager::renderText("Info", PATH_IN_FONT, color, 32, ren);

	slashhhhhhhhh = FontManager::renderText("/", PATH_IN_FONT, color, 32, ren);

	//HP
	hpBar = textureManager::LoadTexture("images/hp.png", ren);
	hpText = FontManager::renderText("HP", PATH_IN_FONT, color, 64, ren);

	//Mana
	mnBar = textureManager::LoadTexture("images/ManaBar.png", ren);
	mnText = FontManager::renderText("MN", PATH_IN_FONT, color, 64, ren);

	//XP
	xpBar = textureManager::LoadTexture("images/XP.png", ren);
	xpText = FontManager::renderText("XP", PATH_IN_FONT, color, 64, ren);

	//Buttons
	specButton = textureManager::LoadTexture("images/Button.png", ren);
}

void UIInfo::Render()
{
	RenderManager::CopyToRender(infoBlock, ren, 1024, 0, 256, 480);
	RenderManager::CopyToRender(info, ren, 1116, 13, 64, 32);
	RenderManager::CopyToRender(slashhhhhhhhh, ren, 1152, 72, 32, 20);
	RenderManager::CopyToRender(slashhhhhhhhh, ren, 1152, 122, 32, 20);
	RenderManager::CopyToRender(slashhhhhhhhh, ren, 1152, 175, 32, 20);

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
	RenderManager::CopyToRender(specButton, ren, 1230, 240, 32, 32);

}

void UIInfo::RenderVersion()
{
	RenderManager::CopyToRender(versionBLock, ren, 0, 705, 170, 9);
}

UISpecifications::UISpecifications(SDL_Renderer* renderer)
{
	PATH_IN_FONT = "fonts/manaspc.ttf";
	color = { 255, 255, 255, 255 };
	ren = renderer;

	//Specifications
	specBlock = textureManager::LoadTexture("images/InfoBlock.png", ren);
	specifcation = FontManager::renderText("Specifications", PATH_IN_FONT, color, 64, ren);
	plus = FontManager::renderText("+", PATH_IN_FONT, color, 32, ren);
	button = textureManager::LoadTexture("images/Button.png", ren);
	STR = FontManager::renderText("STR", PATH_IN_FONT, color, 64, ren);
	valueSTR = FontManager::renderText("1", PATH_IN_FONT, color, 32, ren);
	DEX = FontManager::renderText("DEX", PATH_IN_FONT, color, 64, ren);
	valueDEX = FontManager::renderText("1", PATH_IN_FONT, color, 32, ren);
	INT = FontManager::renderText("INT", PATH_IN_FONT, color, 64, ren);
	valueINT = FontManager::renderText("1", PATH_IN_FONT, color, 32, ren);
	PHS = FontManager::renderText("PHS", PATH_IN_FONT, color, 64, ren);
	valuePHS = FontManager::renderText("1", PATH_IN_FONT, color, 32, ren);
	LCK = FontManager::renderText("LCK", PATH_IN_FONT, color, 64, ren);
	valueLCK = FontManager::renderText("1", PATH_IN_FONT, color, 32, ren);
	one = FontManager::renderText("(1)", PATH_IN_FONT, color, 64, ren);
	two = FontManager::renderText("(2)", PATH_IN_FONT, color, 64, ren);
	three = FontManager::renderText("(3)", PATH_IN_FONT, color, 64, ren);
	four = FontManager::renderText("(4)", PATH_IN_FONT, color, 64, ren);
	five = FontManager::renderText("(5)", PATH_IN_FONT, color, 64, ren);

}

void UISpecifications::Render()
{
	//Specifications
	RenderManager::CopyToRender(specBlock, ren, 1024, 0, 256, 480);
	RenderManager::CopyToRender(specifcation, ren, 1075, 13, 160, 32);
	RenderManager::CopyToRender(button, ren, 1230, 240, 32, 32);
	//STR
	RenderManager::CopyToRender(STR, ren, 1050, 80, 64, 20);
	RenderManager::CopyToRender(plus, ren, 1230, 80, 16, 20);
	RenderManager::CopyToRender(valueSTR, ren, 1180, 80, 16, 20);
	RenderManager::CopyToRender(one, ren, 1250, 80, 16, 20);
	//DEX
	RenderManager::CopyToRender(DEX, ren, 1050, 110, 64, 20);
	RenderManager::CopyToRender(plus, ren, 1230, 110, 16, 20);
	RenderManager::CopyToRender(valueDEX, ren, 1180, 110, 16, 20);
	RenderManager::CopyToRender(two, ren, 1250, 110, 16, 20);
	//INT
	RenderManager::CopyToRender(INT, ren, 1050, 140, 64, 20);
	RenderManager::CopyToRender(plus, ren, 1230, 140, 16, 20);
	RenderManager::CopyToRender(valueINT, ren, 1180, 140, 16, 20);
	RenderManager::CopyToRender(three, ren, 1250, 140, 16, 20);
	//PHS
	RenderManager::CopyToRender(PHS, ren, 1050, 170, 64, 20);
	RenderManager::CopyToRender(plus, ren, 1230, 170, 16, 20);
	RenderManager::CopyToRender(valuePHS, ren, 1180, 170, 16, 20);
	RenderManager::CopyToRender(four, ren, 1250, 170, 16, 20);
	//LCK
	RenderManager::CopyToRender(LCK, ren, 1050, 200, 64, 20);
	RenderManager::CopyToRender(plus, ren, 1230, 200, 16, 20);
	RenderManager::CopyToRender(valueLCK, ren, 1180, 200, 16, 20);
	RenderManager::CopyToRender(five, ren, 1250, 200, 16, 20);
}

void UISpecifications::UpdateSpec(int value, int num)
{
	switch (num)
	{
	case 1:
	{
		std::string stringTemp = std::to_string(value);
		const char* CHAR_VALUE = stringTemp.c_str();
		valueSTR = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);
		break;
	}
	case 2:
	{
		std::string stringTemp = std::to_string(value);
		const char* CHAR_VALUE = stringTemp.c_str();
		valueDEX = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);
		break;
	}
	case 3:
	{
		std::string stringTemp = std::to_string(value);
		const char* CHAR_VALUE = stringTemp.c_str();
		valueINT = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);
		break;
	}
	case 4:
	{
		std::string stringTemp = std::to_string(value);
		const char* CHAR_VALUE = stringTemp.c_str();
		valuePHS = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);
		break;
	}
	case 5: 
	{
		std::string stringTemp = std::to_string(value);
		const char* CHAR_VALUE = stringTemp.c_str();
		valueLCK = FontManager::renderText(CHAR_VALUE, PATH_IN_FONT, color, 32, ren);
		break;
	}
	default:
		break;
	}
}


UIItem::UIItem(SDL_Renderer* renderer)
{
	PATH_IN_FONT = "fonts/manaspc.ttf";
	color = { 255, 255, 255, 255 };
	ren = renderer;

	itemBlock = textureManager::LoadTexture("images/InfoBlock.png", ren);
	item = FontManager::renderText("Items", PATH_IN_FONT, color, 32, ren);
	buttonForInv = textureManager::LoadTexture("images/Button.png", ren);
}

void UIItem::Render()
{
	RenderManager::CopyToRender(itemBlock, ren, 1024, 480, 256, 225);
	RenderManager::CopyToRender(item, ren, 1085, 490, 128, 32);
	RenderManager::CopyToRender(buttonForInv, ren, 1050, 665, 25, 22);
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
			item = textureManager::LoadTexture((Inventory::it->second).ItemTexture, ren);
			RenderManager::CopyToRender(item, ren, (780 + 36 * (i % 4)), (100 + ((i / 4) * 50)), 32, 32);
			SDL_DestroyTexture(item);
			item = 0;
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