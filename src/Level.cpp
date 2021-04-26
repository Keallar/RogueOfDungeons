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
#include <cmath>

Level::Level(SDL_Renderer* renderer) : ren (renderer)
{
	TileSet = 0;
	floorLvl = 0;
    TileTextures[0] = textureManager::LoadTexture("data/images/Tiles.png", ren);
    TileTextures[1] = textureManager::LoadTexture("data/images/CaslteTiles.png", ren);
    PlayBackground = textureManager::LoadTexture("data/images/Playback.png", ren);
	player = new Player(ren);
    enemyTurtle = new Enemy("data/images/Turtle.png", 4, ren, 8, 8, 3, 4);
    SecondEnemyTurtle = new Enemy("data/images/Turtle.png", 4, ren, 10, 10, 3, 4);
    enemies.push_back(enemyTurtle);
    enemies.push_back(SecondEnemyTurtle);

    //uiEnemyHpInfo = new UiHpEnemyInfo(ren, enemy);
	uiInfo = new UIInfo(ren);
    uiItem = new UIItem(ren);
    uiSpec = new UISpecifications(ren);
    uiInv = new UIInventory(ren);
	hp = new HpInfo(ren);
	mana = new ManaInfo(ren);
	exp = new ExpInfo(ren);
    uiEquiped = new UIEquipedItem(ren);
	auto pressW{
		[=]()
		{
            bool wFlag = 1;
            for(Enemy* enemy : enemies){
			if (EntityPosition::Coords[1] == 32)
			{
				//остановка при упоре в стену
                wFlag = 0;
			}
            else if (EntityPosition::Coords[0] == enemy->Rect.x &&
                (EntityPosition::Coords[1] - 32) == enemy->Rect.y)
			{
				//остановка при попытке пройти сквозь enemy
                wFlag = 0;
			}
            }
            if (wFlag == true)
			{
				if (Location[(EntityPosition::Coords[1]) / 32 - 1][(EntityPosition::Coords[0]) / 32] == 0)
				{
					EntityPosition::Coords[1] -= 32;
					FlagManager::flagPlayer = 0;
					FlagManager::flagEnemy = 1;
				}
            }
            if (Location[(EntityPosition::Coords[1]) / 32 - 1][(EntityPosition::Coords[0]) / 32] == 3)
				{
					FlagManager::flagChest = 1;
				}

		}
	};
	keyW = new Keyboard(SDL_SCANCODE_W, pressW);

	auto pressA{
		[=]()
		{
            bool aFlag = true;
            for(Enemy* enemy : enemies){
			if (EntityPosition::Coords[0] == 32)
			{
				//остановка при упоре в стену
                aFlag = 0;
			}
            else if ((EntityPosition::Coords[0] - 32) == enemy->Rect.x &&
                EntityPosition::Coords[1] == enemy->Rect.y)
			{
				//остановка при попытке пройти сквозь enemy
                aFlag = 0;
			}
            }
            if(aFlag == true)
			{
				if (Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 - 1] == 0)
				{
					EntityPosition::Coords[0] -= 32;
                    std::cout << "A\n";
					FlagManager::flagPlayer = 0;
					FlagManager::flagEnemy = 1;
				}
            }
            if (Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 - 1] == 3)
				{
					FlagManager::flagChest = 2;
				}

		}
	};
	keyA = new Keyboard(SDL_SCANCODE_A, pressA);
	auto pressS{
		[=]()
		{
            bool sFlag = true;
            for(Enemy* enemy : enemies){
			if (EntityPosition::Coords[1] == 640)
			{
				//остановка при упоре в стену
                sFlag = 0;
			}
            else if (EntityPosition::Coords[0] == enemy->Rect.x &&
                (EntityPosition::Coords[1] + 32) == enemy->Rect.y)
			{
				//остановка при попытке пройти сквозь enemy
                sFlag = 0;
			}
            }
            if (sFlag == true)
			{
				if (Location[(EntityPosition::Coords[1]) / 32 + 1][(EntityPosition::Coords[0]) / 32] == 0)
				{
					EntityPosition::Coords[1] += 32;
					FlagManager::flagPlayer = 0;
					FlagManager::flagEnemy = 1;
				}
                }
            if (Location[(EntityPosition::Coords[1]) / 32 + 1][(EntityPosition::Coords[0]) / 32] == 3)
				{
					FlagManager::flagChest = 3;
				}
		}
	};
	keyS = new Keyboard(SDL_SCANCODE_S, pressS);

	auto pressD{
			[=]()
		{
            bool dFlag = true;
            for(Enemy* enemy : enemies){
			if (EntityPosition::Coords[0] == 960)
			{
				//остановка при упоре в стену
                dFlag = 0;
			}
            else if ((EntityPosition::Coords[0] + 32) == enemy->Rect.x &&
                EntityPosition::Coords[1] == enemy->Rect.y)
			{
                dFlag = 0;
				//остановка при попытке пройти сквозь enemy
			}
            }
            if(dFlag == true)
			{
				if (Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 + 1] == 0)
				{
					EntityPosition::Coords[0] += 32;
					FlagManager::flagPlayer = 0;
					FlagManager::flagEnemy = 1;
				}
            }
            if (Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 + 1] == 3)
				{
					FlagManager::flagChest = 4;
				}
		}
	};
	keyD = new Keyboard(SDL_SCANCODE_D, pressD);

	for (int i = 0; i < 22; i++) 
	{
		for (int j = 0; j < 32; j++)
		{
			textureLocation[i][j] = 1;
			Location[i][j] = 1;
			Dark[i][j] = 0;
		}
	}
	for (int i = 0; i < 22; i++) 
	{
		for (int j = 0; j < 32; j++) 
		{
			if (i == 0 || i == 21 || j == 0 || j == 31)
			{
				Dark[i][j] = 1;
			}
		}
    }
 }

Level::~Level()
{
	//WTF нельзя делитнуть инвентарь (вылезает ошибка линковщика)
	delete player;
    for (Enemy* enemy : enemies)
    {
    delete enemy;
    }
	delete uiInfo;
	delete uiItem;
  //delete uiEnemy;
	delete uiSpec;
	delete hp;
	delete mana;
	delete exp;
	delete uiEquiped;
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

int Level::GetGeneration()
{
	return 0;
}



void Level::deleteEnemy()
{
    for(Enemy* enemy : enemies){
    if (enemy->GetHpEnemy(0) <= 0)
	{
        enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy));
		std::cout << "Delete enemy" << std::endl;
		FlagManager::flagUiEnemy = 0;
		player->ChangeExpValue(5);
	}
    }
}

void Level::Update()
{
	int n = Player::VIS;
	for (int i = (EntityPosition::Coords[1] / 32) - n; i <= (EntityPosition::Coords[1] / 32) + n; i++) 
	{
		for (int j = (EntityPosition::Coords[0] / 32) - n; j <= (EntityPosition::Coords[0] / 32) + n; j++) 
		{
			ChangeDark(i, j);
		}
	}
	if (enemyTurtle == nullptr)
	{
		FlagManager::flagEnemy = 0;
		FlagManager::flagPlayer = 1;
	}
	if (player != nullptr && 
		FlagManager::flagPlayer == 1 && FlagManager::flagEnemy == 0)
	{
		player->Update();
	}
    if (player != nullptr)
        player->GetLevel(Location);
    if (Player::GetHP(0) <= 0 && player != nullptr)
    {
        Level::deletePlayer();
    }
    for(Enemy* enemy : enemies)
    {
        if (enemy != nullptr &&
		FlagManager::flagPlayer == 0 && FlagManager::flagEnemy == 1)
        {
        enemy->Update();
        enemy->GetLoc(Location);
		//SDL_Delay(100); //UNDONE перенести delay в Animation
        }

        if (enemy != nullptr)
        enemy->GetLoc(Location);

	//удаление player (enemy) при hp <= 0
        if (enemy->CheckHpEnemy() <= 0 && enemy != nullptr)
        {
        std::cout << enemy->CheckHpEnemy();
		Level::deleteEnemy();
        }
    }
}

void Level::Start()
{
	Generate();
	player->GetLevel(Location);
	player->GetPlayerFirstCoords();
    for(Enemy* enemy : enemies)
    {
    enemy->GetLoc(Location);
    enemy->GetEnemyFirstCoords();
    }
}

void Level::ChangeDark(int i, int j) 
{
	if (i >= 0 && i < 22 && j >= 0 && j < 32) 
	{
		Dark[i][j] = 1;
	}
}

void Level::Render()
{
	RenderManager::CopyToRender(PlayBackground, ren);
	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			if (Dark[i][j] == 1) {
				RenderManager::SetTile(j * 32, i * 32, textureLocation[i][j], ren, TileTextures[TileSet]);
			}
			else {
				RenderManager::SetTile(j * 32, i * 32, 12, ren, TileTextures[0]);
			}
		}
	}
	if (player != nullptr)
	{
		player->Render();
	}		
    for(Enemy* enemy : enemies)
    {
    if (enemy != nullptr)
	{
        if (Dark[enemy->Rect.y/32][enemy->Rect.x/32] == 0)
		{
			RenderManager::SetTile(EntityPosition::Coords[2], EntityPosition::Coords[3], 12, ren, TileTextures[0]);
		}
		else
		{
            enemy->Render();
		}
	}
    }

	//ALL UI
	{
		uiItem->Render();
		uiInfo->AlwaysRender();
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
                //uiEnemyHpInfo->Update();
			}

			if (FlagManager::flagUiEnemy == 1)
			{
                //uiEnemy->Render();
				uiEnemyHpInfo->Render();
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

		if (FlagManager::flagChest != 0)
		{
			if (!player->InventoryBlock()) 
			{
				switch (FlagManager::flagChest) 
				{
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
			else 
			{
				FlagManager::flagChest = 0;
			}
		}
	}
}

//возможность изменять уровень из вне
void Level::ChangeLevel(int x, int y, int LocationChange, int TextureChange) 
{
	Location[x][y] = LocationChange;
	textureLocation[x][y] = TextureChange;
}

//Обновление данных объектов
void Level::handleEvents(SDL_Event eventInLvl)
{
	if (uiInfo)
	{
		//Взаимодействие с Items в Inventory
		uiInv->clickForItemsInInv();

		//Взаимодействие с Equiped Items
		uiEquiped->clickForItemsInInv();

		//Вызов окна Spec по нажатию мыши
		uiInfo->handleEvents(eventInLvl);

		//Увеличение значения характеристик по нажатию мыши
		uiSpec->handleEvents(eventInLvl);

		//Вызов окна Inventory по нажатию мыши
		uiInv->handleEvents(eventInLvl);

        if (eventInLvl.type == SDL_MOUSEBUTTONDOWN)
        {
            if (eventInLvl.button.button == SDL_BUTTON_RIGHT)
            {
                //Вызов infoEnemy по нажатию мыши
                uiEnemyHpInfo->callEnemyInfo();
            }
        }
    }
	//Передача event в Player
	if (player)
	{
		switch (eventInLvl.type)
		{
		case SDL_KEYDOWN:
			
            keyW->handleEvents(eventInLvl);
			keyA->handleEvents(eventInLvl);
			keyS->handleEvents(eventInLvl);
			keyD->handleEvents(eventInLvl);
			break;
		case SDL_MOUSEBUTTONDOWN:

			if (eventInLvl.button.button == SDL_BUTTON_LEFT)
			{
				SDL_GetMouseState(&Mouse.x, &Mouse.y);
                for(Enemy* enemy : enemies)
                {
                if (InputManager::MouseInArea(enemy->Rect.x, enemy->Rect.y, 32, 32, Mouse.x, Mouse.y))
				{
					FlagManager::flagRangeAttack = 1;
					Attack();
				}
                }
			}
			break;
		default:
			break;
		}
	}
}
//rand для рандомного выбора метода генерации
void Level::Attack() 
{
	//Дальний boy
    for (Enemy* enemy : enemies)
    {
	if (Inventory::ExistingItems[Player::EqItems.WeaponId]->Type == rWeapon)
	{
        int PlPosx = EntityPosition::Coords[0] / 32, PlPosy = EntityPosition::Coords[1] / 32, EnPosx = (enemy->Rect.x) / 32, EnPosy = (enemy->Rect.y) / 32;
		bool blankflag = true;
        if ((abs(EntityPosition::Coords[0] - enemy->Rect.x) == 0)) // разделил чтобы потом проверять на наличие стен
		{
			if (PlPosy > EnPosy)
			{
				for (int i = PlPosy; i > EnPosy; i--)
				{
					if (Location[i][PlPosx] == 1)
					{
						blankflag = false;
					}
				}
			}
			else
			{
				for (int i = EnPosy; i > PlPosy; i--)
				{
					if (Location[i][PlPosx] == 1)
					{
						blankflag = false;
					}
				}
			}
		}
        else if (/*abs*/(EntityPosition::Coords[1] - enemy->Rect.y == 0))
		{
			if (PlPosx > EnPosx)
			{
				for (int i = PlPosx; i > EnPosx; i--)
				{
					if (Location[PlPosy][i] == 1)
					{
						blankflag = false;
					}
				}
			}
			else
			{
				for (int i = EnPosy; i > PlPosy; i--)
				{
					if (Location[PlPosy][i] == 1)
					{
						blankflag = false;
					}
				}
			}
		}
		else
		{
			int x, y;
			float k = -(((float)(EnPosy - PlPosy) / (PlPosx - EnPosx)));
			float b = -((float)(EnPosx * PlPosy - PlPosx * EnPosy) / (PlPosx - EnPosx));
			if (PlPosx > EnPosx)
			{
				for (x = PlPosx; x > EnPosx; x--)
				{
					if (Location[(int)(k * x + b)][x] == 1)
					{
						blankflag = false;
					}
				}
			}
			else if (PlPosx < EnPosx)
			{
				for (x = EnPosx; x > PlPosx; x--)
				{
					if (Location[(int)(k * x + b)][x] == 1)
					{
						blankflag = false;
					}
				}
			}
			if (PlPosy < EnPosy)
			{
				for (y = EnPosy; y > PlPosy; y--)
				{
					if (Location[y][(int)((y - b) / k)] == 1)
					{
						blankflag = false;
					}
				}
			}
			else if (PlPosy > EnPosy)
			{
				for (y = PlPosy; y > EnPosy; y--)
				{
					if (Location[y][(int)((y - b) / k)] == 1)
					{
						blankflag = false;
					}
				}
			}
		}

		if (blankflag == true)
		{
                int x = (enemy->Rect.y - EntityPosition::Coords[1]) / 32;
                int y = (enemy->Rect.x - EntityPosition::Coords[0]) / 32;
				int i = rand() % 100;
				if (i < ((Player::EqItems.equipedRangeW->CHNS) -
					((Player::EqItems.equipedRangeW->DCHNS) *
						abs(((float)(sqrt(x * x + y * y))) - Player::EqItems.equipedRangeW->RNG))))
				{
					std::cout << ((Player::EqItems.equipedRangeW->CHNS) -
						((Player::EqItems.equipedRangeW->DCHNS) *
							abs(((float)(sqrt(x * x + y * y))) - Player::EqItems.equipedRangeW->RNG)));
                    enemy->ChahgeHpEnemy(-(player->RangeAttack()));
				}
        }
		player->ChangeManaValue(-5);
        enemyTurtle->enemyTurn();// ВАЖНО
	}

		//	Enemy::enemyTurn();
		//}
	//Ближний boy
    else if (this->CheckPositionToMeleeAttack(enemy->Rect, EntityPosition::Coords[0], EntityPosition::Coords[1]) == true &&
			FlagManager::flagMeleeAttackPlayer == 1 && FlagManager::flagMeleeAttackEnemy == 0 &&
			FlagManager::flagPlayer == 1 && FlagManager::flagEnemy == 0)
		{
            enemy->ChahgeHpEnemy(-(player->MeleeAttack()));
            enemyTurtle->enemyTurn(); // ТОЖЕ ВАЖНО
		}
    }
}
void Level::Generate() {
	srand(time(0));
    generateChoose = 5;
	player->generate = generateChoose;
    for(Enemy* enemy : enemies)
    {
        enemy->generate = generateChoose;
    }
	if (generateChoose == 0) {
		ChunkGenerationMethod();
	}
	if (generateChoose == 4) {
		LabGeneration();
	}
	if (generateChoose == 5) {
		CastleLabGeneration();
	}
	if (generateChoose == 1) {
		RoomGenerationMethod2();
	}
	if (generateChoose == 2) {
		ChunkGenerationMethod2();
	}
	for (int i = 0; i < 3; i++) {
		itemsOnLvl[i] = rand() % 4 + 1;
	}
	itemsHave = 2;
	floorLvl++;
}

bool Level::CheckPositionToMeleeAttack(SDL_Rect rect, int x, int y)
{
	if (((rect.x == x + 32) && (rect.y == y)) ||
		((rect.x == x - 32) && (rect.y == y)) ||
		((rect.x == x) && (rect.y == y + 32)) ||
		((rect.x == x) && (rect.y == y - 32))) 
	{
		return true;
	}
	return false;
}
