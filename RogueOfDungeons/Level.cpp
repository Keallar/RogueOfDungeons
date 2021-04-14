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
#include "Enemy.h"
#include "Player.h"

Level::Level(SDL_Renderer* renderer) : ren (renderer)
{
	floorLvl = 0;
	TileTexture = textureManager::LoadTexture("images/Tiles.png", ren);
	TileTextureCastle = textureManager::LoadTexture("images/CaslteTiles.png", ren);
	PlayBackground = textureManager::LoadTexture("images/Playback.png", ren);
	//animation = new Animation(ren);
	player = new Player(ren);
	enemyTurtle = new Enemy("images/Turtle.png", 4, ren, 8, 8, 3, 4);
	enemyHpInfo = new UiHpEnemyInfo(ren);
	uiInfo = new UIInfo(ren);
	uiItem = new UIItem(ren);
	uiEnemy = new UIEnemyInfo(ren);
	uiSpec = new UISpecifications(ren);
	uiInv = new UIInventory(ren);
	hp = new HpInfo(ren);
	mana = new ManaInfo(ren);
	exp = new ExpInfo(ren);
	uiEquiped = new UIEquipedItem(ren);
	keyboardButtonsInLevel = new KeyboardButtonsInLevel();
	for (int i = 0; i < 22; i++) 
	{
		for (int j = 0; j < 32; j++)
		{
			textureLocation[i][j] = 1;
			Location[i][j] = 1;
			Dark[i][j] = 0;
		}
	}
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 32; j++) {
			if (i == 0 || i == 21 || j == 0 || j == 31) {
				Dark[i][j] = 1;
			}
		}
	}
}

Level::~Level()
{
	//WTF нельзя делитнуть инвентарь (вылезает ошибка линковщика)
	delete player;
	delete enemyTurtle;
	delete uiInfo;
	delete uiItem;
	delete uiEnemy;
	delete uiSpec;
	delete hp;
	delete mana;
	delete exp;
	delete uiEquiped;
	delete keyboardButtonsInLevel;
	delete animation;
}

void Level::deletePlayer()
{
	if (Player::GetHP(0) <= 0)
	{
		std::cout << "Delete player" << std::endl;
		delete player;
		player = nullptr;
	}
}

void Level::deleteEnemy()
{
	if (Enemy::HP <= 0)
	{
		std::cout << "Delete enemy" << std::endl;
		delete enemyTurtle;
		enemyTurtle = nullptr;
		FlagManager::flagUiEnemy = 0;
		player->ChangeExpValue(5);
	}
}

void Level::Update()
{
	int n = Player::VIS;
	for (int i = (EntityPosition::Coords[1] / 32) - n; i <= (EntityPosition::Coords[1] / 32) + n; i++) {
		for (int j = (EntityPosition::Coords[0] / 32) - n; j <= (EntityPosition::Coords[0] / 32) + n; j++) {
			ChangeDark(i, j);
		}
	}
	if (enemyTurtle == nullptr) {
		FlagManager::flagEnemy = 0;
		FlagManager::flagPlayer = 1;
	}
	if (player != nullptr && 
		FlagManager::flagPlayer == 1 && FlagManager::flagEnemy == 0)
	{
		player->Update();
	}
	if (enemyTurtle != nullptr &&
		FlagManager::flagPlayer == 0 && FlagManager::flagEnemy == 1)
	{
		enemyTurtle->Update();
		enemyTurtle->GetLoc(Location);
		SDL_Delay(150);
	}
	if (player != nullptr)
		player->GetLevel(Location);

	if (enemyTurtle != nullptr)
		enemyTurtle->GetLoc(Location);

	//удаление player (enemy) при hp <= 0
	if (Player::GetHP(0) <= 0 && player != nullptr)
	{
		Level::deletePlayer();
	}
	if (Enemy::HP <= 0 && enemyTurtle != nullptr)
	{
		Level::deleteEnemy();
		EntityPosition::Coords[2] = 0;
		EntityPosition::Coords[3] = 0;
	}
}

void Level::Start()
{
	Generate();
	player->GetLevel(Location);
	player->GetPlayerFirstCoords();
	enemyTurtle->GetLoc(Location);
	enemyTurtle->GetEnemyFirstCoords();
}

void Level::ChangeDark(int i, int j) {
	if (i >= 0 && i < 22 && j >= 0 && j < 32) {
		Dark[i][j] = 1;
	}
}

void Level::CaveRender(int y, int x) {
	int i = y;
	int j = x;
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
	if (Dark[i][j] == 0) {
		RenderManager::SetTile(j * 32, i * 32, 12, ren, TileTexture);
	}
}

void Level::CastleRender(int y, int x) {
	int i = y;
	int j = x;
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
	if (Dark[i][j] == 0) {
		RenderManager::SetTile(j * 32, i * 32, 12, ren, TileTexture);
	}
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
				CaveRender(i, j);
			}
		}
	}

	if ((generateChoose == 1)||(generateChoose == 2)) {
		for (int i = 0; i < 22; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				CastleRender(i, j);
			}
		}
	}
	if (player != nullptr) {
		player->Render();
	}		
	if (enemyTurtle != nullptr) {
		if (Dark[EntityPosition::Coords[3]/32][EntityPosition::Coords[2]/32] == 0) {
			RenderManager::SetTile(EntityPosition::Coords[2], EntityPosition::Coords[3], 12, ren, TileTexture);
		} else{
			enemyTurtle->Render();
		}
	}

	//ALL UI
	{
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
			if (FlagManager::flagWSD == 1)
			{
				uiSpec->Update(Player::GetSpecValue(4), 4);
			}
			if (FlagManager::flagPHS == 1)
			{
				uiSpec->Update(Player::GetSpecValue(5), 5);
				hp->UpdateMax();
			}
			if (FlagManager::flagLCK == 1)
			{
				uiSpec->Update(Player::GetSpecValue(6), 6);
			}
		}

		if (FlagManager::flagUI == 1)
		{
			uiInfo->Render();
			hp->Render();
			mana->Render();
			exp->Render();

			if (FlagManager::flagCheckHpEnemy == 1)
			{
				enemyHpInfo->Update();
			}

			if (FlagManager::flagUiEnemy == 1)
			{
				uiEnemy->Render();
				enemyHpInfo->Render();
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
}

//возможность изменять уровень из вне
void Level::ChangeLevel(int x, int y, int LocationChange, int TextureChange) {
	Location[x][y] = LocationChange;
	textureLocation[x][y] = TextureChange;
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

		if (eventInLvl.button.button == SDL_BUTTON_RIGHT)
		{
			//Вызов infoEnemy по нажатию мыши
			MouseButtonsInLevel::buttonForCallEnemyInfo();
		}

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
	generateChoose = rand()%2;
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
		itemsOnLvl[i] = rand() % 4;
	}
	itemsHave = 2;
	floorLvl++;
}
