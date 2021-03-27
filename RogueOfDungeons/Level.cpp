#pragma once
#include "Game.h"
#include "Level.h"
#include "Managers.h"
#include <ctime>
#include "UI.h"
#include "EntityPosition.h"
#include <vector>
#include <iostream>
#include "EntityPosition.h"

Level::Level(SDL_Renderer* renderer) : ren (renderer)
{
	floorLvl = 0;
	TileTexture = textureManager::LoadTexture("images/Tiles.png", ren);
	TileTextureCastle = textureManager::LoadTexture("images/CaslteTiles.png", ren);
	PlayBackground = textureManager::LoadTexture("images/Playback.png", ren);
	player = new Player("images/Hero.png", ren);
	enemy = new Enemy("images/Turtle.png", ren, 10, 3, 4);
	uiInfo = new UIInfo(ren);
	uiItem = new UIItem(ren);
	uiEnemy = new UIEnemyInfo(ren);
	uiSpec = new UISpecifications(ren);
	uiInv = new UIInventory(ren);
	hp = new HpInfo(ren, Player::GetHP(0));
	mana = new ManaInfo(ren, Player::GetMana());
	exp = new ExpInfo(ren, Player::GetEXP());
	/*changeState[0] = hp;
	changeState[1] = mana;
	changeState[2] = exp;*/
	
	for (int i = 0; i < 22; i++) 
	{
		for (int j = 0; j < 32; j++)
		{
			textureLocation[i][j] = 1;
		}
	}
}

Level::~Level()
{
	delete player;
	delete enemy;
	delete uiInfo;
	delete uiItem;
	delete uiEnemy;
	delete uiSpec;
}
void Level::Update()
{
	if (FlagManager::flagPlayer == 1)
	{
		player->Update();	
	}
	if (FlagManager::flagPlayer == 0)
	{
		enemy->Update();
		enemy->GetLoc(Location);
		SDL_Delay(150);
	}
	player->GetLevel(Location);
	enemy->GetLoc(Location);
}

void Level::Start()
{
	FlagManager::flagUI = 1;
	//Level::flagTB = 1;
	FlagManager::flagPlayer = 1;
	Generate();
	FlagManager::flagEnemy = 0;
	FlagManager::flagUiSpec = 0;
	FlagManager::flagCheckHP = 0;
	FlagManager::flagCheckMana = 0;
	FlagManager::flagCheckExp = 0;
	FlagManager::flagUiEnemy = 0;
	player->GetLevel(Location);
	player->GetPlayerFirstCoords();
	enemy->GetLoc(Location);
	enemy->GetEnemyFirstCoords();
}

void Level::Render()
{
	RenderManager::CopyToRender(PlayBackground, ren);
	//в зависимости от метода генерации выбираются нужные паки текстур
	if (generateChoose == 0) {
		for (int i = 0; i < 22; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				if (textureLocation[i][j] == 0)
				{
					RenderManager::SetTile(j * 32, i * 32, 2, ren, TileTexture);
				}
				else
				{
					RenderManager::SetTile(j * 32, i * 32, 6, ren, TileTexture);
				}
				if (textureLocation[i][j] == 2) {
					RenderManager::SetTile(j * 32, i * 32, 7, ren, TileTexture);
				}
				if (textureLocation[i][j] == 3) {
					RenderManager::SetTile(j * 32, i * 32, 3, ren, TileTexture);
				}
				if (textureLocation[i][j] == 4) {
					RenderManager::SetTile(j * 32, i * 32, 1, ren, TileTexture);
				}
				if (textureLocation[i][j] == 5) {
					RenderManager::SetTile(j * 32, i * 32, 9, ren, TileTexture);
				}
				if (textureLocation[i][j] == 6) {
					RenderManager::SetTile(j * 32, i * 32, 4, ren, TileTexture);
				}
				if (textureLocation[i][j] == 14) {
					RenderManager::SetTile(j * 32, i * 32, 13, ren, TileTexture);
				}
			}
		}
	}

	if ((generateChoose == 1)||(generateChoose == 2)) {
		for (int i = 0; i < 22; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				if (textureLocation[i][j] == 0)
				{
					RenderManager::SetTile(j * 32, i * 32, 6, ren, TileTextureCastle);
				}
				else
				{
					RenderManager::SetTile(j * 32, i * 32, 8, ren, TileTextureCastle);
				}
				if (textureLocation[i][j] == 2) {
					RenderManager::SetTile(j * 32, i * 32, 9, ren, TileTextureCastle);
				}
				if (textureLocation[i][j] == 3) {
					RenderManager::SetTile(j * 32, i * 32, 2, ren, TileTextureCastle);
				}
				if (textureLocation[i][j] == 4) {
					RenderManager::SetTile(j * 32, i * 32, 3, ren, TileTextureCastle);
				}
				if (textureLocation[i][j] == 5) {
					RenderManager::SetTile(j * 32, i * 32, 7, ren, TileTextureCastle);
				}
				if (textureLocation[i][j] == 6) {
					RenderManager::SetTile(j * 32, i * 32, 1, ren, TileTextureCastle);
				}
				if (textureLocation[i][j] == 7) {
					RenderManager::SetTile(j * 32, i * 32, 10, ren, TileTextureCastle);
				}
				if (textureLocation[i][j] == 8) {
					RenderManager::SetTile(j * 32, i * 32, 11, ren, TileTextureCastle);
				}
				if (textureLocation[i][j] == 14) {
					RenderManager::SetTile(j * 32, i * 32, 14, ren, TileTextureCastle);
				}
			}
		}
	}
	
	player->Render();
	enemy->Render();
	uiItem->Render();
	uiInfo->RenderVersion();
	

	if (FlagManager::flagInv == 1)
	{
		uiInv->Render();
	}

	if (FlagManager::flagUiSpec == 1)
	{
		uiSpec->Render();

		if (FlagManager::flagSTR == 1)
		{
			uiSpec->UpdateSpec(Player::GetSpecValue(1), 1);
		}
		if (FlagManager::flagDEX == 1)
		{
			uiSpec->UpdateSpec(Player::GetSpecValue(2), 2);
		}
		if (FlagManager::flagINT == 1)
		{
			uiSpec->UpdateSpec(Player::GetSpecValue(3), 3);
		}
		if (FlagManager::flagPHS == 1)
		{
			uiSpec->UpdateSpec(Player::GetSpecValue(4), 4);
			hp->UpdateMax();
		}
		if (FlagManager::flagLCK == 1)
		{
			uiSpec->UpdateSpec(Player::GetSpecValue(5), 5);
		}
	}
	if (FlagManager::flagUI == 1)
	{
		uiInfo->Render();
		//changeState[0]->Render();
		hp->Render();
		mana->Render();
		exp->Render();

		if (FlagManager::flagUiEnemy == 1)
		{
			uiEnemy->Render();
		}

		//Update значений hp, mana и  exp
		if (FlagManager::flagCheckHP == 1)
		{
			hp->Update(Player::GetHP(0));
		}

		if (FlagManager::flagCheckMana == 1)
		{
			mana->Update(Player::GetMana());
		}

		if (FlagManager::flagCheckExp == 1)
		{
			exp->Update(Player::GetEXP());
		}
	}
	if (FlagManager::flagChest != 0) {
		switch (FlagManager::flagChest) {
		case 1:
			textureLocation[(EntityPosition::Coords[1]) / 32 - 1][(EntityPosition::Coords[0]) / 32] = 0;
			Location[(EntityPosition::Coords[1]) / 32 - 1][(EntityPosition::Coords[0]) / 32] = 0;
			player->GetItemOnLvl(itemsOnLvl[itemsHave]);
			itemsHave--;
			FlagManager::flagChest = 0;
			break;
		case 2:
			textureLocation[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 - 1] = 0;
			Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 - 1] = 0;
			player->GetItemOnLvl(itemsOnLvl[itemsHave]);
			itemsHave--;
			FlagManager::flagChest = 0;
			break;
		case 3:
			textureLocation[(EntityPosition::Coords[1]) / 32 + 1][(EntityPosition::Coords[0]) / 32] = 0;
			Location[(EntityPosition::Coords[1]) / 32 + 1][(EntityPosition::Coords[0]) / 32] = 0;
			player->GetItemOnLvl(itemsOnLvl[itemsHave]);
			itemsHave--;
			FlagManager::flagChest = 0;
			break;
		case 4:
			textureLocation[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 + 1] = 0;
			Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 + 1] = 0;
			player->GetItemOnLvl(itemsOnLvl[itemsHave]);
			itemsHave--;
			FlagManager::flagChest = 0;
			break;
		}
	}
}

//Обновление данных объектов
void Level::handleEvents(SDL_Event eventWIthSpec)
{
	switch (eventWIthSpec.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		SDL_GetMouseState(&mouseCoords.x, &mouseCoords.y);

		//Вызов окна Spec по нажатию мыши
		if (InputManager::MouseInArea(1230, 240, 64, 64, mouseCoords.x, mouseCoords.y) && 
			FlagManager::flagUiSpec == 0)
		{
			//std::cout << "Mouse spec" << std::endl;
			FlagManager::flagUiSpec = 1;
			FlagManager::flagUI = 0;
			SDL_Delay(200);
			break;
		}
		else if (InputManager::MouseInArea(1230, 240, 32, 32, mouseCoords.x, mouseCoords.y) && 
			FlagManager::flagUiSpec == 1)
		{
			//std::cout << "Mouse info" << std::endl;
			FlagManager::flagUI = 1;
			FlagManager::flagUiSpec = 0;
			SDL_Delay(200);
			break;
		}
		
		//Вызов окна Inventory по нажатию мыши
		if (InputManager::MouseInArea(1050, 665, 25, 22, mouseCoords.x, mouseCoords.y) &&
			FlagManager::flagInv == 0)
		{
			FlagManager::flagInv = 1;
		}
		else if (InputManager::MouseInArea(1050, 665, 25, 22, mouseCoords.x, mouseCoords.y) && 
			FlagManager::flagInv == 1)
		{
			FlagManager::flagInv = 0;
		}

		//Вызов infoEnemy по нажатию мыши
		if (InputManager::MouseInArea(EntityPosition::Coords[2], EntityPosition::Coords[3], 32, 32, mouseCoords.x, mouseCoords.y) &&
			FlagManager::flagUiEnemy == 0)
		{
			FlagManager::flagUiEnemy = 1;
			SDL_Delay(200);
		}
		else if (InputManager::MouseInArea(EntityPosition::Coords[2], EntityPosition::Coords[3], 32, 32, mouseCoords.x, mouseCoords.y) &&
			FlagManager::flagUiEnemy == 1)
		{
			FlagManager::flagUiEnemy = 0;
			SDL_Delay(200);
		}

		//Увеличение значения характеристик по нажатию мыши
		//STR
		if (FlagManager::flagUiSpec == 1 && InputManager::MouseInArea(1230, 80, 16, 20, mouseCoords.x, mouseCoords.y) &&
			FlagManager::flagSTR == 0)
		{
			player->ChangeValueSpecs(1);
			SDL_Delay(200);
		}
		//DEX
		if (FlagManager::flagUiSpec == 1 && InputManager::MouseInArea(1230, 110, 16, 20, mouseCoords.x, mouseCoords.y) &&
			FlagManager::flagDEX == 0)
		{
			player->ChangeValueSpecs(2);
			SDL_Delay(200);
		}
		//INT
		if (FlagManager::flagUiSpec == 1 && InputManager::MouseInArea(1230, 140, 16, 20, mouseCoords.x, mouseCoords.y) &&
			FlagManager::flagINT == 0)
		{
			player->ChangeValueSpecs(3);
			SDL_Delay(200);
		}
		//PHS
		if (FlagManager::flagUiSpec == 1 && InputManager::MouseInArea(1230, 170, 16, 20, mouseCoords.x, mouseCoords.y) &&
			FlagManager::flagPHS == 0)
		{
			player->ChangeValueSpecs(4);
			SDL_Delay(200);
		}
		//LCK
		if (FlagManager::flagUiSpec == 1 && InputManager::MouseInArea(1230, 200, 16, 20, mouseCoords.x, mouseCoords.y) &&
			FlagManager::flagLCK == 0)
		{
			player->ChangeValueSpecs(5);
			SDL_Delay(200);
		}

	case SDL_KEYDOWN:

		//Смена окон (с Spec на Info и наоборот)
		if (keys[SDL_SCANCODE_Q] && FlagManager::flagUiSpec == 0)
		{
			//std::cout << "Check Spec" << std::endl;
			FlagManager::flagUiSpec = 1;
			FlagManager::flagUI = 0;
			SDL_Delay(200);
			break;
		}
		else if (keys[SDL_SCANCODE_Q] && FlagManager::flagUI == 0)
		{
			//std::cout << "Check Info" << std::endl;
			FlagManager::flagUiSpec = 0;
			FlagManager::flagUI = 1;
			SDL_Delay(200);
			break;
		}

		if (keys[SDL_SCANCODE_I] && FlagManager::flagInv == 0)
		{
			FlagManager::flagInv = 1;
			SDL_Delay(200);
			break;
		}
		else if (keys[SDL_SCANCODE_I] && FlagManager::flagInv == 1)
		{
			FlagManager::flagInv = 0;
			SDL_Delay(200);
			break;
		}

		//Увеличение характеристик Spec с помощью клавиш
		if (keys[SDL_SCANCODE_1] && FlagManager::flagUiSpec == 1 && FlagManager::flagSTR == 0)
		{
			player->ChangeValueSpecs(1);
			break;
		}
		if (keys[SDL_SCANCODE_2] && FlagManager::flagUiSpec == 1 && FlagManager::flagDEX == 0)
		{
			player->ChangeValueSpecs(2);
			break;
		}
		if (keys[SDL_SCANCODE_3] && FlagManager::flagUiSpec == 1 && FlagManager::flagINT == 0)
		{
			player->ChangeValueSpecs(3);
			break;
		}
		if (keys[SDL_SCANCODE_4] && FlagManager::flagUiSpec == 1 && FlagManager::flagPHS == 0)
		{
			player->ChangeValueSpecs(4);
			break;
		}
		if (keys[SDL_SCANCODE_5] && FlagManager::flagUiSpec == 1 && FlagManager::flagLCK == 0)
		{
			player->ChangeValueSpecs(5);
			break;
		}

	default:
		break;
	}

	if (player)
	{
		player->handleEvents(eventWIthSpec);
	}
}
//rand для рандомного выбора метода генерации

void Level::Generate() {
	srand(time(0));
	generateChoose = 1;
	if (generateChoose == 0) {
		ChunkGenerationMethod();
	}
	if (generateChoose == 3) {
		RoomGenerationMethod1();
	}
	if (generateChoose == 1) {
		RoomGenerationMethod2();
	}
	for (int i = 0; i < 3; i++) {
		itemsOnLvl[i] = rand() % 3;
	}
	itemsHave = 2;
	floorLvl++;

}