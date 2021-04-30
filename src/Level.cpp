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
#include "Map.h"
#include <cmath>

Level::Level(SDL_Renderer* renderer) : ren (renderer)
{
    LevelMap = new Map();
    TileTextures[0] = textureManager::LoadTexture("data/images/Tiles.png", ren);
    TileTextures[1] = textureManager::LoadTexture("data/images/CaslteTiles.png", ren);
    PlayBackground = textureManager::LoadTexture("data/images/Playback.png", ren);
    player = new Player(ren);
    //enemyTurtle = new Enemy();
    SecondEnemyTurtle = new Enemy("data/images/Turtle.png", 4, ren, 10, 10, 3, 4);
    uiEnemyInfo = new UIEnemyInfo(ren, SecondEnemyTurtle);
    //enemies.push_back(enemyTurtle);
    enemies.push_back(SecondEnemyTurtle);

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
            bool wFlag = true;
            for (Enemy* enemy : enemies)
            {
                if (EntityPosition::Coords[1] == 32)
                {
                    //остановка при упоре в стену
                    wFlag = false;
                }
                else if (EntityPosition::Coords[0] == enemy->Rect.x &&
                         (EntityPosition::Coords[1] - 32) == enemy->Rect.y)
                {
                    wFlag = false;
                    //остановка при попытке пройти сквозь enemy
                }
            }
            if (wFlag == true)
            {
                if (LevelMap->Location[(EntityPosition::Coords[1]) / 32 - 1][(EntityPosition::Coords[0]) / 32] == 0)
                {
                    EntityPosition::Coords[1] -= 32;
                    FlagManager::flagPlayer = 0;
                    FlagManager::flagEnemy = 1;
                }
                if (LevelMap->Location[(EntityPosition::Coords[1]) / 32 - 1][(EntityPosition::Coords[0]) / 32] == 3)
                {
                    FlagManager::flagChest = 1;
                }
                if (LevelMap->Location[(EntityPosition::Coords[1]) / 32 - 1][(EntityPosition::Coords[0]) / 32] == 4)
                {
                    Start();
                }
            }
        }
    };
    keyW = new Keyboard(SDL_SCANCODE_W, pressW);
    buttonW = new Button("left", NULL, ren, {EntityPosition::Coords[0], EntityPosition::Coords[1] - 32, 32, 32}, pressW, NULL);
    auto pressA{
        [=]()
        {
            bool AFlag = true;
            for (Enemy* enemy : enemies)
            {
                if (EntityPosition::Coords[0] == 32)
                {
                    //остановка при упоре в стену
                    AFlag = false;
                }
                else if ((EntityPosition::Coords[0] - 32) == enemy->Rect.x &&
                         EntityPosition::Coords[1] == enemy->Rect.y)
                {
                    AFlag = false;
                    //остановка при попытке пройти сквозь enemy
                }
            }
            if (AFlag == true)
            {
                if (LevelMap->Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 - 1] == 0)
                {
                    EntityPosition::Coords[0] -= 32;
                    FlagManager::flagPlayer = 0;
                    FlagManager::flagEnemy = 1;
                }
                if (LevelMap->Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 - 1] == 3)
                {
                    FlagManager::flagChest = 2;
                }
                if (LevelMap->Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 - 1] == 4)
                {
                    Start();
                }
            }
        }
    };
    keyA = new Keyboard(SDL_SCANCODE_A, pressA);
    buttonA = new Button("left", NULL, ren, {EntityPosition::Coords[0] - 32, EntityPosition::Coords[1], 32, 32}, pressA, NULL);
    auto pressS{
        [=]()
        {
            bool sFlag = true;
            for (Enemy* enemy : enemies)
            {
                if (EntityPosition::Coords[1] == 640)
                {
                    sFlag = false;
                    //остановка при упоре в стену
                }
                else if (EntityPosition::Coords[0] == enemy->Rect.x &&
                         (EntityPosition::Coords[1] + 32) == enemy->Rect.y)
                {
                    sFlag = false;
                    //остановка при попытке пройти сквозь enemy
                }
            }
            if(sFlag == true)
            {
                if (LevelMap->Location[(EntityPosition::Coords[1]) / 32 + 1][(EntityPosition::Coords[0]) / 32] == 0)
                {
                    EntityPosition::Coords[1] += 32;
                    FlagManager::flagPlayer = 0;
                    FlagManager::flagEnemy = 1;
                }
                if (LevelMap->Location[(EntityPosition::Coords[1]) / 32 + 1][(EntityPosition::Coords[0]) / 32] == 3)
                {
                    FlagManager::flagChest = 3;
                }
                if (LevelMap->Location[(EntityPosition::Coords[1]) / 32 + 1][(EntityPosition::Coords[0]) / 32] == 4)
                {
                    Start();
                }
            }
        }
    };
    keyS = new Keyboard(SDL_SCANCODE_S, pressS);
    buttonS = new Button("left", NULL, ren, {EntityPosition::Coords[0], EntityPosition::Coords[1] + 32, 32, 32}, pressS, NULL);
    auto pressD{
        [=]()
        {
            bool dFlag = true;
            for(Enemy* enemy : enemies)
            {
                if (EntityPosition::Coords[0] == 960)
                {
                    dFlag = false;
                    //остановка при упоре в стену
                }
                else if ((EntityPosition::Coords[0] + 32) == enemy->Rect.x &&
                         EntityPosition::Coords[1] == enemy->Rect.y)
                {
                    dFlag = false;
                    //остановка при попытке пройти сквозь enemy
                }
            }
            if(dFlag == true)
            {
                if (LevelMap->Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 + 1] == 0)
                {
                    EntityPosition::Coords[0] += 32;
                    FlagManager::flagPlayer = 0;
                    FlagManager::flagEnemy = 1;
                }
                if (LevelMap->Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 + 1] == 3)
                {
                    FlagManager::flagChest = 4;
                }
                if (LevelMap->Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 + 1] == 4)
                {
                    Start();
                }
            }
        }
    };
    keyD = new Keyboard(SDL_SCANCODE_D, pressD);
    buttonD = new Button("left", NULL, ren, {EntityPosition::Coords[0] + 32, EntityPosition::Coords[1], 32, 32}, pressD, NULL);
    auto playerAttack{
        [=]()
        {
            player->playerTurn();
            Attack();
        }
    };
    buttonForPlayerAttack = new Button("left", NULL, ren, {0, 0, 32, 32}, playerAttack, NULL);
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
   // delete uiEnemyInfo;
    delete uiSpec;
    delete hp;
    delete mana;
    delete exp;
    delete uiEquiped;
    delete animation;
    delete keyW;
    delete keyA;
    delete keyS;
    delete keyW;
    delete keyD;
    delete buttonW;
    delete buttonA;
    delete buttonS;
    delete buttonD;
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
    for(Enemy* enemy : enemies)
    {
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
    if (enemies.size() == 0)
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
        player->GetLevel(LevelMap->Location);

    for(Enemy* enemy : enemies)
    {
        //std::cout << enemies.size();
        if (enemy != nullptr &&
                FlagManager::flagPlayer == 0 && FlagManager::flagEnemy == 1)
        {
            enemy->Update();
            // std::cout << enemies.size();
            enemy->GetLoc(LevelMap->Location);
            player->playerTurn();//UNDONE Я уверен, что он не должен передавать здесь ход, но это пока что все фиксит, потому пусть пока поюудет
        }
        //удаление player (enemy) при hp <= 0
        if (enemy->CheckHpEnemy() <= 0 && enemy != nullptr)
        {
            //std::cout << enemy->CheckHpEnemy();
            Level::deleteEnemy();
            std::cout << enemies.size() << std::endl;
            if (enemies.size() == 0) {
                LevelMap->Location[LevelMap->portal.x][LevelMap->portal.y] = 4;
                LevelMap->textureLocation[LevelMap->portal.x][LevelMap->portal.y] = 15;
            }
        }

        if (enemy != nullptr)
            enemy->GetLoc(LevelMap->Location);

        //buttonForPlayerAttack->updateCoords(enemy->Rect.x, enemy->Rect.y);

    }

    //удаление player при hp <= 0
    if (Player::GetHP(0) <= 0 && player != nullptr)
    {
        player->Update();
        Level::deletePlayer();
    }
    buttonW->updateCoords(EntityPosition::Coords[0], EntityPosition::Coords[1] - 32);
    buttonA->updateCoords(EntityPosition::Coords[0] - 32, EntityPosition::Coords[1]);
    buttonS->updateCoords(EntityPosition::Coords[0], EntityPosition::Coords[1] + 32);
    buttonD->updateCoords(EntityPosition::Coords[0] + 32, EntityPosition::Coords[1]);  

}

void Level::Start()
{
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            LevelMap->textureLocation[i][j] = 1;
            LevelMap->Location[i][j] = 1;
            LevelMap->Dark[i][j] = 0;
        }
    }
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            if (i == 0 || i == 21 || j == 0 || j == 31)
            {
                LevelMap->Dark[i][j] = 1;
            }
        }
    }
    for(int i = 0; i<1; i++)
    {
        //delete enemy;
        Enemy* enemy = new Enemy("data/images/Turtle.png", 4, ren, 8, 8, 3, 4);
        enemies.push_back(enemy);
    }
    LevelMap->GenerateMap();
    player->generate = LevelMap->generateChoose;
    for(Enemy* enemy : enemies)
    {
        enemy->generate = LevelMap->generateChoose;
    }
    player->GetLevel(LevelMap->Location);
    player->GetPlayerFirstCoords();
    for(Enemy* enemy : enemies)
    {
        enemy->GetLoc(LevelMap->Location);
        enemy->GetEnemyFirstCoords();
    }
}

void Level::ChangeDark(int i, int j) 
{
    if (i >= 0 && i < 22 && j >= 0 && j < 32)
    {
        LevelMap->Dark[i][j] = 1;
    }
}

void Level::Render()
{
    RenderManager::CopyToRender(PlayBackground, ren);
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 32; j++)
        {
            if (LevelMap->Dark[i][j] == 1)
            {
                RenderManager::SetTile(j * 32, i * 32, LevelMap->textureLocation[i][j], ren, TileTextures[LevelMap->TileSet]);
            }
            else
            {
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
            if (LevelMap->Dark[enemy->Rect.y/32][enemy->Rect.x/32] == 0)
            {
                RenderManager::SetTile(enemy->Rect.x, enemy->Rect.y, 12, ren, TileTextures[0]);
            }
            else
            {
                //по-моему тут надо не одного врага проверять...
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
//                for (UIEnemyInfo* info : uiEnemyInfo)
//                {
//                    info->Update();
//                }
            }

            if (FlagManager::flagUiEnemy == 1)
            {
                uiEnemyInfo->Render();
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
                    LevelMap->textureLocation[(EntityPosition::Coords[1]) / 32 - 1][(EntityPosition::Coords[0]) / 32] = 0;
                    LevelMap->Location[(EntityPosition::Coords[1]) / 32 - 1][(EntityPosition::Coords[0]) / 32] = 0;
                    player->GetItemOnLvl(LevelMap->itemsOnLvl[LevelMap->itemsHave]);
                    LevelMap->itemsHave--;
                    FlagManager::flagChest = 0;
                    break;
                case 2:
                    LevelMap->textureLocation[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 - 1] = 0;
                    LevelMap->Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 - 1] = 0;
                    player->GetItemOnLvl(LevelMap->itemsOnLvl[LevelMap->itemsHave]);
                    LevelMap->itemsHave--;
                    FlagManager::flagChest = 0;
                    break;
                case 3:
                    LevelMap->textureLocation[(EntityPosition::Coords[1]) / 32 + 1][(EntityPosition::Coords[0]) / 32] = 0;
                    LevelMap->Location[(EntityPosition::Coords[1]) / 32 + 1][(EntityPosition::Coords[0]) / 32] = 0;
                    player->GetItemOnLvl(LevelMap->itemsOnLvl[LevelMap->itemsHave]);
                    LevelMap->itemsHave--;
                    FlagManager::flagChest = 0;
                    break;
                case 4:
                    LevelMap->textureLocation[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 + 1] = 0;
                    LevelMap-> Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 + 1] = 0;
                    player->GetItemOnLvl(LevelMap->itemsOnLvl[LevelMap->itemsHave]);
                    LevelMap->itemsHave--;
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
    LevelMap->Location[x][y] = LocationChange;
    LevelMap->textureLocation[x][y] = TextureChange;
}

//Обновление данных объектов
void Level::handleEvents(SDL_Event eventInLvl)
{
    if (uiInfo)
    {
        switch (eventInLvl.type)
        {
        case SDL_MOUSEBUTTONDOWN:
        case SDL_KEYDOWN:
            //Взаимодействие с Items в Inventory
            uiInv->clickForItemsInInv();

            //Взаимодействие с Equiped Items
            uiEquiped->clickForItemsInInv();
            break;
            break;
        }

        //Вызов окна Spec по нажатию мыши
        uiInfo->handleEvents(eventInLvl);

        //Увеличение значения характеристик по нажатию мыши
        uiSpec->handleEvents(eventInLvl);

        //Вызов окна Inventory по нажатию мыши
        uiInv->handleEvents(eventInLvl);

        //Вызов InfoEnemy
        uiEnemyInfo->handleEvents(eventInLvl);

    }


    //Передача event в Player
    if (player && FlagManager::flagPlayer == 1)
    {
        keyW->handleEvents(eventInLvl);
        keyA->handleEvents(eventInLvl);
        keyS->handleEvents(eventInLvl);
        keyD->handleEvents(eventInLvl);

        buttonForPlayerAttack->handleEvents(eventInLvl);
        buttonW->handleEvents(eventInLvl);
        buttonA->handleEvents(eventInLvl);
        buttonS->handleEvents(eventInLvl);
        buttonD->handleEvents(eventInLvl);
    }
    for (Enemy* enemy : enemies)
    {
        int mouseX = 0, mouseY = 0;
        SDL_GetMouseState(&mouseX, &mouseY);
        if((mouseX<=enemy->Rect.x+32)&&(mouseX>=enemy->Rect.x)&&
                (mouseY<=enemy->Rect.y+32)&&(mouseY>=enemy->Rect.y))
        {
            buttonForPlayerAttack->updateCoords(enemy->Rect.x, enemy->Rect.y);
            uiEnemyInfo->Update(enemy);
            break;
        }
    }
}

void Level::Attack() 
{
    int mouseX , mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    //Дальний boy
    for (Enemy* enemy : enemies)
    {
        buttonForPlayerAttack->updateCoords(enemy->Rect.x, enemy->Rect.y);
        std::cout<<enemy->Rect.x<< " " << enemy->Rect.y << std::endl;
        if((mouseX<=enemy->Rect.x+32)&&(mouseX>=enemy->Rect.x)&&
                (mouseY<=enemy->Rect.y+32)&&(mouseY>=enemy->Rect.y))
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
                            if (LevelMap->Location[i][PlPosx] == 1)
                            {
                                blankflag = false;
                            }
                        }
                    }
                    else
                    {
                        for (int i = EnPosy; i > PlPosy; i--)
                        {
                            if (LevelMap->Location[i][PlPosx] == 1)
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
                            if (LevelMap->Location[PlPosy][i] == 1)
                            {
                                blankflag = false;
                            }
                        }
                    }
                    else
                    {
                        for (int i = EnPosy; i > PlPosy; i--)
                        {
                            if (LevelMap->Location[PlPosy][i] == 1)
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
                            if (LevelMap->Location[(int)(k * x + b)][x] == 1)
                            {
                                blankflag = false;
                            }
                        }
                    }
                    else if (PlPosx < EnPosx)
                    {
                        for (x = EnPosx; x > PlPosx; x--)
                        {
                            if (LevelMap->Location[(int)(k * x + b)][x] == 1)
                            {
                                blankflag = false;
                            }
                        }
                    }
                    if (PlPosy < EnPosy)
                    {
                        for (y = EnPosy; y > PlPosy; y--)
                        {
                            if (LevelMap->Location[y][(int)((y - b) / k)] == 1)
                            {
                                blankflag = false;
                            }
                        }
                    }
                    else if (PlPosy > EnPosy)
                    {
                        for (y = PlPosy; y > EnPosy; y--)
                        {
                            if (LevelMap->Location[y][(int)((y - b) / k)] == 1)
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
                enemies[0]->enemyTurn();// ВАЖНО
            }

            //Ближний boy
            else if (this->CheckPositionToMeleeAttack(enemy->Rect, EntityPosition::Coords[0], EntityPosition::Coords[1]) == true &&
                     FlagManager::flagMeleeAttackPlayer == 1 && FlagManager::flagMeleeAttackEnemy == 0 &&
                     FlagManager::flagPlayer == 1 && FlagManager::flagEnemy == 0)
            {
                enemy->ChahgeHpEnemy(-(player->MeleeAttack()));
                enemies[0]->enemyTurn(); // ТОЖЕ ВАЖНО
            }
        }
    }
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
