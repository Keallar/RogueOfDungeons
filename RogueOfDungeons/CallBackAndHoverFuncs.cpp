#include "CallBackAndHoverFuncs.h"

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
		std::cout << "Spec" << std::endl;
	}
	else if (FlagManager::flagUiSpec == 1)
	{
		FlagManager::flagUI = 1;
		FlagManager::flagUiSpec = 0;
		std::cout << "Info" << std::endl;
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
	if (FlagManager::flagDEX == 0)
	{
		Player::ChangeValueSpecs(2);
	}
}

void callbackFunctions::incPlayerINT()
{
	//INT
	if (FlagManager::flagINT == 0)
	{
		Player::ChangeValueSpecs(3);
	}
}

void callbackFunctions::incPlayerWSD()
{
	//WSD
	if (FlagManager::flagWSD == 0)
	{
		Player::ChangeValueSpecs(4);
	}
}

void callbackFunctions::incPlayerPHS()
{
	//PHS
	if (FlagManager::flagPHS == 0)
	{
		Player::ChangeValueSpecs(5);
	}
}

void callbackFunctions::incPlayerLCK()
{
	//LCK
	if (FlagManager::flagLCK == 0)
	{
		Player::ChangeValueSpecs(6);
	}
}

void hoverFunctions::callSpecWin()
{

}
