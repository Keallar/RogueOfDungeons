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
#include "Buttons.h"

Level::Level(SDL_Renderer* renderer) : ren (renderer)
{
	floorLvl = 0;
	TileTexture = textureManager::LoadTexture("images/Tiles.png", ren);
	TileTextureCastle = textureManager::LoadTexture("images/CaslteTiles.png", ren);
	PlayBackground = textureManager::LoadTexture("images/Playback.png", ren);
	player = new Player("images/Hero.png", ren);
	enemy = new Enemy("images/Turtle.png", ren, 5, 5, 3, 4);
	enemyHpInfo = new UiHpEnemyInfo(ren, Enemy::GetHpEnemy(0));
	uiInfo = new UIInfo(ren);
	uiItem = new UIItem(ren);
	uiEnemy = new UIEnemyInfo(ren);
	uiSpec = new UISpecifications(ren, 1);
	uiInv = new UIInventory(ren);
	hp = new HpInfo(ren, Player::GetHP(0));
	mana = new ManaInfo(ren, Player::GetMana(0));
	exp = new ExpInfo(ren, Player::GetEXP());
	uiEquiped = new UIEquipedItem(ren);
	keyboardButtonsInLevel = new KeyboardButtonsInLevel();
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
	delete uiInv;
	delete hp;
	delete mana;
	delete exp;
	delete uiEquiped;
	delete keyboardButtonsInLevel;
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
	FlagManager::flagPlayer = 1;
	FlagManager::flagEnemy = 0;
	Generate();
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
	uiEquiped->Render();

	if (FlagManager::flagInv == 1)
	{
		uiInv->Render();
	}

	if (FlagManager::flagUiSpec == 1)
	{
		uiSpec->Render();

		if (FlagManager::flagSTR == 1)
		{
			uiSpec->Update(Player::GetSpecValue(1), 1);
		}
		if (FlagManager::flagDEX == 1)
		{
			uiSpec->Update(Player::GetSpecValue(2), 2);
		}
		if (FlagManager::flagINT == 1)
		{
			uiSpec->Update(Player::GetSpecValue(3), 3);
			mana->UpdateMax();
		}
		if (FlagManager::flagPHS == 1)
		{
			uiSpec->Update(Player::GetSpecValue(4), 4);
			hp->UpdateMax();
		}
		if (FlagManager::flagLCK == 1)
		{
			uiSpec->Update(Player::GetSpecValue(5), 5);
		}
	}
	if (FlagManager::flagUI == 1)
	{
		uiInfo->Render();
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
			hp->Update();
		}

		if (FlagManager::flagCheckMana == 1)
		{
			mana->Update();
		}

		if (FlagManager::flagCheckExp == 1)
		{
			exp->Update();
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
void Level::handleEvents(SDL_Event eventInLvl)
{
	switch (eventInLvl.type)
	{
	case SDL_MOUSEBUTTONDOWN:

		//Взаимодействие с Items в Inventory
		MouseButtonsInLevel::buttonsForItemsInInv();

		//Вызов окна Spec по нажатию мыши
		MouseButtonsInLevel::buttonForCallSpecWin();
		
		//Вызов окна Inventory по нажатию мыши
		MouseButtonsInLevel::buttonForCallInvWin();

		//Вызов infoEnemy по нажатию мыши
		MouseButtonsInLevel::buttonForCallEnemyInfo();

		//Увеличение значения характеристик по нажатию мыши
		MouseButtonsInLevel::buttonForIncPlayerSpec();
		
	case SDL_KEYDOWN:

		//Смена окон (с Spec на Info и наоборот) на Q
		KeyboardButtonsInLevel::keyForCallSpecWin(keys);

		//Вызов окна Inventory на I
		KeyboardButtonsInLevel::keyForCallInvWin(keys);

		//Увеличение характеристик Spec с помощью клавиш
		KeyboardButtonsInLevel::keyForIncPlayerSpec(keys);

	default:
		break;
	}

	//Передача event в Player
	if (player)
	{
		player->handleEvents(eventInLvl);
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