﻿#pragma once
#include "Game.h"
#include "Level.h"
#include "Managers.h"
#include <ctime>
#include "UI.h"
#include "EntityPosition.h"
#include <vector>
#include <iostream>

Level::Level(SDL_Renderer* renderer) : ren (renderer)
{
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
			hp->Update(Player::GetHP());
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
		if (keys[SDL_SCANCODE_1] && FlagManager::flagUiSpec == 1)
		{
			break;
		}
		if (keys[SDL_SCANCODE_2] && FlagManager::flagUiSpec == 1)
		{
			break;
		}
		if (keys[SDL_SCANCODE_3] && FlagManager::flagUiSpec == 1)
		{
			break;
		}
		if (keys[SDL_SCANCODE_4] && FlagManager::flagUiSpec == 1)
		{
			break;
		}
		if (keys[SDL_SCANCODE_5] && FlagManager::flagUiSpec == 1)
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



void Level::CreateChunk(int x, int y) {
	for (int i = x; i < x + 2; i++) {
		for (int j = y; j < y + 4; j++) {
			if ((j <= 31) || (i <= 21)|| (j > 0) || (i > 0)) {
				textureLocation[i][j] = 0;
			}
		}
	}
}

//ф-я для безопасного получения инфы из массива
int Level::GetLocation(int x, int y) {
	if (x >= 0 && x < 32 && y >= 0 && y < 22) {
		return textureLocation[y][x];
	}
	else {
		return 1;
	}
}

//ф-я для безопасного измменения массива
void Level::ChangeLocation(int x, int y) {
	if (x >= 0, x < 32, y >= 0, y < 22) {
		textureLocation[y][x] = 0;
	}
}

//при данном методе генерации карт делится на 8*11 чанков

void Level::ChunkGenerationMethod() {
	for (int j = 0; j < 8; j++) { //делим карту на 8 столбцов по 11 чанков, обрабатываем каждый отдельно
		int i = rand() % 4 + rand() % 3; int count = 0;
		//задумка такая: в каждом столбце создаем какое-то количество пустых чанков (в которых можно хоидть)
		//начиная от какого-то чанка. После того, как мы совместим столбцы, мы получим, так сказать, угловатую пещеру
		//например, в 1 столбце пустые от 4 по 7 чанки, а во 2 стобце от 5 по 9 чанки, представьте в голове
		while (count < (5 + rand() % 3)) { //выбираем кол-во пустых чанков в столбце
			if (i + count < 11) {
				CreateChunk((i + count) * 2, j * 4);
			}
			count++;
		}
	}
	 //цикл для сглаживания, превращает угловатую пещеру в нормальную
	//для каждой клетки считаем пустые клетки- соседи. Если их больше 3, делаем клетку пустой
	for (int j = 0; j < 32; j++) {
		for (int i = 0; i < 22; i++) {
			int iteration = 0;
			while (iteration < 50) {
				int count = 0;
				if (GetLocation(j, i + 1) == 0) {
					count++;
				}
				if (GetLocation(j + 1, i + 1) == 0) {
					count++;
				}
				if (GetLocation(j + 1, i) == 0) {
					count++;
				}
				if (GetLocation(j + 1, i - 1) == 0) {
					count++;
				}
				if (GetLocation(j, i - 1) == 0) {
					count++;
				}
				if (GetLocation(j - 1, i - 1) == 0) {
					count++;
				}
				if (GetLocation(j - 1, i) == 0) {
					count++;
				}
				if (GetLocation(j - 1, i + 1) == 0) {
					count++;
				}
				if (count > 3) {
					textureLocation[i][j] = 0;
				}
				iteration++;
			}
		}
	}

	//далее рандомно выбираем клетки и меняем им тектурку, чтобы уровень был разнообразнее

	for (int j = 0; j < 32; j++) {
		for (int i = 0; i < 22; i++) {
			if (!(rand() % 16)) {
				textureLocation[i][j] = 3;
			}
			if (textureLocation[i][j] == 1) {
				if (rand() % 2) {
					textureLocation[i][j] = 5;
				}
			}
			if (textureLocation[i][j] == 0) {
				switch (rand() % 3) {
				case 0:
					break;
				case 1:
					textureLocation[i][j] = 4;
					break;
				case 2:
					textureLocation[i][j] = 6;
					break;
				}
			}
			//стены вокруг уровня
			if ((j == 31) || (i == 21) || (j == 0) || (i == 0)) {
				textureLocation[i][j] = 2;
			}
		}
	}

	//заполяем массив, которых хранит инфу, где стены, а где можно ходить

	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 32; j++) {
			if ((textureLocation[i][j] == 0) || (textureLocation[i][j] == 4) || (textureLocation[i][j] == 6)) {
				Location[i][j] = 0;
			}
			if ((textureLocation[i][j] == 1) || (textureLocation[i][j] == 3) || (textureLocation[i][j] == 5)) {
				Location[i][j] = 1;
			}
			if (textureLocation[i][j] == 2) {
				Location[i][j] = 2;
			}
		}
	}
}

//здесь описан алгоритм поиска в ширину, я его сделал, потом понял, что он мне не нужен

/*
std::vector<std::pair<int, int>> Level::pop_front(std::vector<std::pair<int, int>> vec)
{
	for (int i = 0; i < vec.size() - 1; i++) {
		vec[i] = vec[i + 1];
	}
	vec.pop_back();
	return vec;
}

bool Level::Search(std::vector<std::pair<int, int>> vector, int x, int y) {
	std::pair<int, int> coords = { x ,y };
	bool result = false;
	for (int i = 0; i < vector.size(); i++) {
		if (vector[i] == coords) {
			result = true;
		}
	}
	return result;
}

int Level::SearchNum(std::vector<std::pair<int, int>> vector, int x, int y) {
	std::pair<int, int> coords = { x ,y };
	bool result = false;
	for (int i = 0; i < vector.size(); i++) {
		if (vector[i] == coords) {
			return i;
		}
	}
	return -1;
}

void Level::OtherGeneration(int startX, int startY, int endX, int endY) {
	COORDS startPoint = {startX, startY };
	COORDS endPoint = { endX, endY };
	bool HaveWay = false;
	std::vector< std::pair<int, int> > used (1);
	std::vector< std::pair<int, int> > queue (1);
	queue.push_back({ startPoint.x, startPoint.y });
	used.push_back({ startPoint.x, startPoint.y });
	std::pair <int, int> current = { 0, 0 };
	while ((!queue.empty())) {
		current = queue.front();
		queue = pop_front(queue);
		if ((current.first == endPoint.x)&&(current.second == endPoint.y)) {
			HaveWay = true;
			break;
		}
		if (textureLocation[current.first][current.second + 1] != 2) {
			if (!(Search(used, current.first, current.second + 1))) {
				queue.push_back({ current.first, current.second + 1 });
				used.push_back({ current.first, current.second + 1 });
			}
		}
		if (textureLocation[current.first - 1][current.second] != 2) {
			if (!(Search(used, current.first - 1, current.second ))) {
				queue.push_back({ current.first - 1, current.second });
				used.push_back({ current.first - 1, current.second });
			}
		}
		if (textureLocation[current.first][current.second - 1] != 2) {
			if (!(Search(used, current.first, current.second - 1))) {
				queue.push_back({ current.first, current.second - 1 });
				used.push_back({ current.first, current.second - 1 });
			}
		}
		if (textureLocation[current.first + 1][current.second] != 2) {
			if (!(Search(used, current.first + 1, current.second))) {
				queue.push_back({ current.first + 1, current.second });
				used.push_back({ current.first + 1, current.second });
			}
		}
	}
	std::vector< std::pair<int, int> > Way (1);
	Way.push_back({endPoint.x, endPoint.y});
	current = { endPoint.x, endPoint.y };
	int min;
	int minNum;
	int Numbers[] = { -1, -1, -1, -1 };
	while ((current.first != startPoint.x)||(current.second != startPoint.y)) {
		minNum = 0;
		min = 0;
		int counter = 0;
		Numbers[0] = SearchNum(used, current.first, current.second + 1);
		Numbers[1] = SearchNum(used, current.first - 1, current.second);
		Numbers[2] = SearchNum(used, current.first, current.second - 1);
		Numbers[3] = SearchNum(used, current.first + 1, current.second);
		for (int k = 0; k < 4; k++) {
			if (Numbers[k] != -1) {
				min = Numbers[k];
				counter = k;
				break;
			}
		}
		for (int k = counter; k < 3; k++) {
			if ((min > Numbers[k + 1])&&(Numbers[k + 1] != -1)) {
				min = Numbers[k + 1];
				minNum = k + 1;
			}
		}
		switch (minNum) {
		case 0:
			current = { current.first, current.second + 1 };
			Way.push_back(current);
			break;
		case 1:
			current = { current.first - 1, current.second };
			Way.push_back(current);
			break;
		case 2:
			current = { current.first, current.second - 1 };
			Way.push_back(current);
			break;
		case 3:
			current = { current.first + 1, current.second };
			Way.push_back(current);
			break;
		}
	}
	std::cout << Way.size() << std::endl;
	for (int i = 0; i < Way.size(); i++) {
		textureLocation[Way[i].first][Way[i].second] = 0;
	}
}*/

//метод плохо работает на данный момент, не юзайте

void Level::RoomGenerationMethod1() {
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 32; j++) {
			if ((j == 31) || (i == 21) || (j == 0) || (i == 0)) {
				textureLocation[i][j] = 2;
			}
		}
	}
	COORDS RoomPoints[9] = { {-1, -1},{-1, -1},{-1, -1},{-1, -1},{-1, -1},{-1, -1},{-1, -1},{-1, -1},{-1, -1} };
	for (int i = 0; i < 9; i++) {
		bool near = true;
		int counter = 0;
		while (near) {
			near = false;
			RoomPoints[i] = { rand() % 20 + 1, rand() % 30 + 1 };
			if ((RoomPoints[i].x < 4) || (RoomPoints[i].x > 17) || (RoomPoints[i].y < 4) || (RoomPoints[i].y > 27)) {
				near = true;
			}
			for (int k = 0; k < i; k++) {
				if ((((RoomPoints[k].x - RoomPoints[i].x < 7) && (RoomPoints[k].x - RoomPoints[i].x > -7)) &&
					((RoomPoints[k].y - RoomPoints[i].y < 7) && (RoomPoints[k].y - RoomPoints[i].y > -7)))) {
					near = true;
				}
			}
			counter++;
			if (counter > 150) {
				near = false;
				RoomPoints[i].x = -1;
				RoomPoints[i].y = -1;
			}
		}
	}
	for (int m = 0; m < 9; m++) {
		if ((RoomPoints[m].x != -1) && (RoomPoints[m].y != -1)) {
			textureLocation[RoomPoints[m].x][RoomPoints[m].y] = 0;
			for (int j = 0; j < 6; j++) {
				for (int k = 0; k < 6; k++) {
					textureLocation[RoomPoints[m].x - 2 + j][RoomPoints[m].y - 2 + k] = 0;
				}
			}
		}
	}
	for (int i = 0; i < 8; i++) {
		if ((RoomPoints[i].x != -1) && (RoomPoints[i].y != -1)&&(RoomPoints[i+1].x != -1) && (RoomPoints[i+1].y != -1)) {
			int deltaX = abs(RoomPoints[i].x - RoomPoints[i + 1].x);
			int deltaY = abs(RoomPoints[i].y - RoomPoints[i + 1].y);
			if (RoomPoints[i].x < RoomPoints[i + 1].x) {
				for (int j = 0; j < deltaX; j++) {
					textureLocation[RoomPoints[i].x + 1 + j][RoomPoints[i].y] = 0;
				}
				if (RoomPoints[i].y < RoomPoints[i + 1].y) {
					for (int j = 0; j < deltaY; j++) {
						textureLocation[RoomPoints[i + 1].x][RoomPoints[i].y + 1 + j] = 0;
					}
				}
				else {
					for (int j = 0; j < deltaY; j++) {
						textureLocation[RoomPoints[i + 1].x][RoomPoints[i + 1].y + 1 + j] = 0;
					}
				}
			}
			else {
				for (int j = 0; j < deltaX; j++) {
					textureLocation[RoomPoints[i + 1].x + 1 + j][RoomPoints[i].y] = 0;
				}
				if (RoomPoints[i].y < RoomPoints[i + 1].y) {
					for (int j = 0; j < deltaY; j++) {
						textureLocation[RoomPoints[i].x][RoomPoints[i].y + 1 + j] = 0;
					}
				}
				else {
					for (int j = 0; j < deltaY; j++) {
						textureLocation[RoomPoints[i].x][RoomPoints[i + 1].y + 1 + j] = 0;
					}
				}
			}
		}
	}
}

//метод для генерации комнат, 2 вариант генерации

//сначала делим карту на 8 чанков, 4 столбца по 2 чанка
//в первом столбце выбираем, какой из чанков будет стартовым
//в строке, в которой есть стартовый чанк, выбираем чанк номер 2 или 3, на котором произойдет поворот дороги
//в последнем столбце выбираем конечный чанк
//главная дорога идет от стартового чанка вправо, поворачивает наверх или вниз на чанке поворота
//(то есть меняет строку), далее дальше вправо до последнего столбца
//в каждом столбце есть дорога, которая соединяет чанки
//чанков 8, но комнат не 8, один из циклов выбирает чанки, в которых не будет комнаты
void Level::RoomGenerationMethod2() {
	int RoomSectors[2][4] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	//выбираем старт чанк
	switch (rand() % 2) {
	case 0:
		RoomSectors[0][0] = 1;
		break;
	case 1:
		RoomSectors[1][0] = 1;
		break;
	}
	//выбираем конечный чанк
	//p.s. в стартовом и конечном чанке всегда есть комната
	switch (rand() % 2) {
	case 0:
		RoomSectors[0][3] = 2;
		break;
	case 1:
		RoomSectors[1][3] = 2;
		break;
	}
	//выбираем чанк поворота. p.s. в нем тоже всегда есть комната
	switch (rand() % 2) {
	case 0:
		if (RoomSectors[0][0] == 1) {
			RoomSectors[0][1] = 3;
			break;
		}
		else {
			RoomSectors[1][1] = 3;
			break;
		}
	case 1:
		if (RoomSectors[0][0] == 1) {
			RoomSectors[0][2] = 3;
			break;
		}
		else {
			RoomSectors[1][2] = 3;
			break;
		}
	}
	//выбираем чанки, в которых не будет комнаты
	int count = 0;
	while (count < 1) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 4; j++) {
				if ((!(rand() % 4))&&(RoomSectors[i][j] == 0)) {
					RoomSectors[i][j] = -1;
					count++;
					break;
				}
			}
		}
	}
	//...
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << RoomSectors[i][j] << " ";
		}
	}
	//рисуем дороги, судя по инфе про чанки
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			if (RoomSectors[i][j] == 1) {
				for (int k = 0; k < 8; k++) {
					textureLocation[11 * i + 5][8 * j + 4 + k] = 0;
				}
			}
			if ((RoomSectors[i][j] == 0)|| (RoomSectors[i][j] == -1)) {
				if ((j == 2) && ((RoomSectors[1-i][1] == 3) || (RoomSectors[1 - i][2] == 3))) {
					for (int k = 0; k < 8; k++) {
						textureLocation[11 * i + 5][8 * j + 4 + k] = 0;
					}
				}
				if ((j == 1) && ((RoomSectors[i][0] == 1)||(RoomSectors[1-i][j] == 3))) {
					for (int k = 0; k < 8; k++) {
						textureLocation[11 * i + 5][8 * j + 4 + k] = 0;
					}
				}
			}
		}
	}
	//строим дороги между чанками в столюцах
	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 11; k++) {
			textureLocation[5 + k][8 * i + 4] = 0;
		}
	}
	//рисуем комнаты
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			int start = rand() % 2;
			int end = rand() % 2;
			if (RoomSectors[i][j] != -1) {
				for (int k = 0; k < 6; k++) {
					for (int m = 0+start; m < 7+end; m++) {
						textureLocation[11 * i +1 +m][8 * j + 1 + k] = 0;
					}
				}
			}
		}
	}
	//меняем текстурку центральных клеток комнат(мелочь, но приятно)
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			textureLocation[11 * i + 5][8 * j + 4] = 6;
		}
	}
	//рисуем границы мапы
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 32; j++) {
			if ((i == 0) || (j == 0) || (i == 21) || (j == 31)) {
				textureLocation[i][j] = 2;
			}
		}
	}
	//добавляем разнообразие в текстурки
	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 32; j++) {
			if ((textureLocation[i][j] == 1)&&(!(rand()%11))) {
				textureLocation[i][j] = 5;
			}
			if ((textureLocation[i][j] == 0) && (!(rand() % 16))) {
				if (rand() % 2) {
					textureLocation[i][j] = 3;
				}
				else {
					textureLocation[i][j] = 4;
				}
			}
			if ((textureLocation[i][j] == 0) && (!(rand() % 4))) {
				if (rand() % 2) {
					textureLocation[i][j] = 7;
				}
				else {
					textureLocation[i][j] = 8;
				}
			}
		}
	}

	//щагружаем инфу о том, где стены, а где можно ходить, в массив

	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < 32; j++) {
			if ((textureLocation[i][j] == 0) || (textureLocation[i][j] == 6)) {
				Location[i][j] = 0;
			}
			if ((textureLocation[i][j] == 1) || (textureLocation[i][j] == 5)) {
				Location[i][j] = 1;
			}
			if (textureLocation[i][j] == 2) {
				Location[i][j] = 2;
			}
		}
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

	//Здесь можно добавить 2 генератор, потом соединить их на одном массиве и получить их совместный результат, звучит перспективно
	/*for (int j = 0; j < 22; j++) {
		for (int i = 0; i < 32; i++) {
			Location2[j][i] = textureLocation[j][i];
		}
	}

	for (int j = 0; j < 22; j++) {
		for (int i = 0; i < 32; i++) {
			if (Location2[j][i] == 0) {
				textureLocation[j][i] = Location2[j][i];
			}
		}
	}*/
}
