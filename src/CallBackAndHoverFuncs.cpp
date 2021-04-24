#include "CallBackAndHoverFuncs.h"
#include "Game.h"

using namespace std;

void callbackFunctions::callInvWin()
{
	if (FlagManager::flagInv == 0)
	{
		FlagManager::flagInv = 1;
	}
	else if (FlagManager::flagInv == 1)
	{
		FlagManager::flagInv = 0;
	}
}

void callbackFunctions::callSpecOrInfoWin()
{
	if (FlagManager::flagUiSpec == 0)
	{
		FlagManager::flagUiSpec = 1;
		FlagManager::flagUI = 0;
	}
	else if (FlagManager::flagUiSpec == 1)
	{
		FlagManager::flagUI = 1;
		FlagManager::flagUiSpec = 0;
	}
}

void callbackFunctions::incPlayerSTR()
{
	//STR
	if (FlagManager::flagSTR == 0 && FlagManager::flagUiSpec == 1)
	{
		Player::ChangeValueSpecs(1);
	}
}

void callbackFunctions::incPlayerDEX()
{
	//DEX
	if (FlagManager::flagDEX == 0 && FlagManager::flagUiSpec == 1)
	{
		Player::ChangeValueSpecs(2);
	}
}

void callbackFunctions::incPlayerINT()
{
	//INT
	if (FlagManager::flagINT == 0 && FlagManager::flagUiSpec == 1)
	{
		Player::ChangeValueSpecs(3);
	}
}

void callbackFunctions::incPlayerWSD()
{
	//WSD
	if (FlagManager::flagWSD == 0 && FlagManager::flagUiSpec == 1)
	{
		Player::ChangeValueSpecs(4);
	}
}

void callbackFunctions::incPlayerPHS()
{
	//PHS
	if (FlagManager::flagPHS == 0 && FlagManager::flagUiSpec == 1)
	{
		Player::ChangeValueSpecs(5);
	}
}

void callbackFunctions::incPlayerLCK()
{
	//LCK
	if (FlagManager::flagLCK == 0 && FlagManager::flagUiSpec == 1)
	{
		Player::ChangeValueSpecs(6);
	}
}

void callbackFunctions::callDrop()
{
	if (FlagManager::flagHaveDrop == false) 
	{
		FlagManager::flagHaveDrop = true;
	}
	else 
	{
		FlagManager::flagHaveDrop = false;
	}
}

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