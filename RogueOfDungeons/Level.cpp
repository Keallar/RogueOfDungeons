#pragma once
#include "Game.h"
#include "Level.h"
#include "Managers.h"
#include <ctime>
#include "UI.h"
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
	hp = new HpInfo(ren, Player::GetHP());
	mana = new ManaInfo(ren, Player::GetMana());
	exp = new ExpInfo(ren, Player::GetEXP());
	changeState[0] = hp;
	changeState[1] = mana;
	changeState[2] = exp;
	
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
	uiEnemy->Render();
	

	if (FlagManager::flagInv == 1)
	{
		uiInv->Render();
	}

	if (FlagManager::flagUiSpec == 1)
	{
		uiSpec->Render();
	}
	if (FlagManager::flagUI == 1)
	{
		uiInfo->Render();
		changeState[0]->Render();
		changeState[1]->Render();
		changeState[2]->Render();

		if (FlagManager::flagCheckHP == 1)
		{
			//WTF (сделать лучше метод Update)
			//std::cout << "Throw HP" << std::endl;
			delete changeState[0];
			changeState[0] = nullptr;
			changeState[0] = new HpInfo(ren, Player::GetHP());

		}

		if (FlagManager::flagCheckMana == 1)
		{
			//std::cout << "Throw Mana" << std::endl;
			delete changeState[1];
			changeState[1] = nullptr;
			changeState[1] = new ManaInfo(ren, Player::GetMana());
		}

		if (FlagManager::flagCheckExp == 1)
		{
			//std::cout << "Throw Exp" << std::endl;
			delete changeState[2];
			changeState[2] = nullptr;
			changeState[2] = new ExpInfo(ren, Player::GetEXP());
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
		if (InputManager::MouseInArea(1230, 200, 64, 64, mouseCoords.x, mouseCoords.y) && 
			FlagManager::flagUiSpec == 0)
		{
			//std::cout << "Mouse spec" << std::endl;
			FlagManager::flagUiSpec = 1;
			FlagManager::flagUI = 0;
			SDL_Delay(200);
			break;
		}
		else if (InputManager::MouseInArea(1230, 200, 32, 32, mouseCoords.x, mouseCoords.y) && 
			FlagManager::flagUiSpec == 1)
		{
			//std::cout << "Mouse info" << std::endl;
			FlagManager::flagUI = 1;
			FlagManager::flagUiSpec = 0;
			SDL_Delay(200);
			break;
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

		if (keys[SDL_SCANCODE_1] && FlagManager::flagUiSpec == 1)
		{
			break;
		}
		else if (keys[SDL_SCANCODE_2] && FlagManager::flagUiSpec == 1)
		{
			break;
		}
		else if (keys[SDL_SCANCODE_3] && FlagManager::flagUiSpec == 1)
		{
			break;
		}
		else if (keys[SDL_SCANCODE_4] && FlagManager::flagUiSpec == 1)
		{
			break;
		}
		else if (keys[SDL_SCANCODE_5] && FlagManager::flagUiSpec == 1)
		{
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