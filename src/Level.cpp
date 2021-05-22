#include "Game.h"
#include "Level.h"
#include "Managers.h"
#include <ctime>
#include <vector>
#include <iostream>
#include "EntityPosition.h"
#include <cmath>
#include <algorithm>
#include <typeinfo>

Level::Level(SDL_Renderer* renderer, int playerClass) : ren (renderer), pClass(playerClass)
{
    GameTextures = TextureBase::Instance();
    LevelMap = new Map();
    Gulag = new Map();
    Gulag->TileSet = 5;
    Gulag->GulagChoose(1);
    pLCK = 1;
    TileTextures[0] = GameTextures->GetTexture("CaveTiles");
    TileTextures[1] = GameTextures->GetTexture("JungleTiles");
    TileTextures[2] = GameTextures->GetTexture("CastleTiles");
    TileTextures[3] = GameTextures->GetTexture("CastleTiles2");
    TileTextures[4] = GameTextures->GetTexture("ArcaneTiles");
    TileTextures[5] = GameTextures->GetTexture("Gulag");
    PlayBackground = textureManager::LoadTexture("data/images/Playback.png", ren);
    player = new Player(ren);
    UiEnemy = new UIEnemy(ren, StandartEnemyTurtle);
    uiInfo = new UIInfo(ren);
    uiItem = new UIItem(ren);
    uiSpec = new UISpecifications(ren);
    uiInv = new UIInventory(ren);
    hp = new HpInfo(ren);
    mana = new ManaInfo(ren);
    exp = new ExpInfo(ren);
    uiEquiped = new UIEquipedItem(ren);
    uiTrader = new UiTrader(ren);
    timer = 0;
    timeB = false;
    PlayerDeath = false;
    PlayerDead = false;
    auto pressW{
        [this]()
        {
            Map* CurrentMap;
            if (!PlayerDeath) CurrentMap = LevelMap;
            else CurrentMap = Gulag;
            bool wFlag = true;
            for (Enemy* enemy : enemies)
            {
                if (EntityPosition::Coords[1] == 32)
                {
                    //остановка при упоре в стену
                    wFlag = false;
                }
                else if (EntityPosition::Coords[0] == enemy->Rect.x &&
                         (EntityPosition::Coords[1] - 32) == enemy->Rect.y && !PlayerDeath)
                {
                    wFlag = false;
                    //остановка при попытке пройти сквозь enemy
                }
            }
            if (wFlag == true)
            {
                if (CurrentMap->Location[(EntityPosition::Coords[1]) / 32 - 1][(EntityPosition::Coords[0]) / 32] == 8)
                {
                    PlayerInGulagHole();
                }
                if (CurrentMap->Location[(EntityPosition::Coords[1]) / 32 - 1][(EntityPosition::Coords[0]) / 32] == 4)
                {
                    Start();
                }
                if (CurrentMap->Location[(EntityPosition::Coords[1]) / 32 - 1][(EntityPosition::Coords[0]) / 32] == 0)
                {
                    EntityPosition::Coords[1] -= 32;
                    FlagManager::flagTurn = 1;
                }
                if (CurrentMap->Location[(EntityPosition::Coords[1]) / 32 - 1][(EntityPosition::Coords[0]) / 32] == 3)
                {
                    FlagManager::flagChest = 1;
                }
            }
        }
    };
    keyW = new Keyboard(SDL_SCANCODE_W, pressW);
    buttonW = new Button("left", NULL, ren, {EntityPosition::Coords[0], EntityPosition::Coords[1] - 32, 32, 32}, pressW, NULL, NULL);
    auto pressA{
        [this]()
        {
            Map* CurrentMap;
            if (!PlayerDeath) CurrentMap = LevelMap;
            else CurrentMap = Gulag;
            bool AFlag = true;
            for (Enemy* enemy : enemies)
            {
                if (EntityPosition::Coords[0] == 32)
                {
                    //остановка при упоре в стену
                    AFlag = false;
                }
                else if ((EntityPosition::Coords[0] - 32) == enemy->Rect.x &&
                         EntityPosition::Coords[1] == enemy->Rect.y && !PlayerDeath)
                {
                    AFlag = false;
                    //остановка при попытке пройти сквозь enemy
                }
            }
            if (AFlag == true)
            {
                if (CurrentMap->Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 - 1] == 8)
                {
                    PlayerInGulagHole();
                }
                if (CurrentMap->Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 - 1] == 4)
                {
                    Start();
                }
                if (CurrentMap->Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 - 1] == 0)
                {
                    EntityPosition::Coords[0] -= 32;
                    FlagManager::flagTurn = 1;
                }
                if (CurrentMap->Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 - 1] == 3)
                {
                    FlagManager::flagChest = 2;
                }
            }
        }
    };
    keyA = new Keyboard(SDL_SCANCODE_A, pressA);
    buttonA = new Button("left", NULL, ren, {EntityPosition::Coords[0] - 32, EntityPosition::Coords[1], 32, 32}, pressA, NULL, NULL);
    auto pressS{
        [this]()
        {
            Map* CurrentMap;
            if (!PlayerDeath) CurrentMap = LevelMap;
            else CurrentMap = Gulag;
            bool sFlag = true;
            for (Enemy* enemy : enemies)
            {
                if (EntityPosition::Coords[1] == 640)
                {
                    sFlag = false;
                    //остановка при упоре в стену
                }
                else if (EntityPosition::Coords[0] == enemy->Rect.x &&
                         (EntityPosition::Coords[1] + 32) == enemy->Rect.y && !PlayerDeath)
                {
                    sFlag = false;
                    //остановка при попытке пройти сквозь enemy
                }
            }
            if(sFlag == true)
            {
                if (CurrentMap->Location[(EntityPosition::Coords[1]) / 32 + 1][(EntityPosition::Coords[0]) / 32] == 8)
                {
                    PlayerInGulagHole();
                }
                if (CurrentMap->Location[(EntityPosition::Coords[1]) / 32 + 1][(EntityPosition::Coords[0]) / 32] == 4)
                {
                    Start();
                }
                if (CurrentMap->Location[(EntityPosition::Coords[1]) / 32 + 1][(EntityPosition::Coords[0]) / 32] == 0)
                {
                    EntityPosition::Coords[1] += 32;
                    FlagManager::flagTurn = 1;
                }
                if (CurrentMap->Location[(EntityPosition::Coords[1]) / 32 + 1][(EntityPosition::Coords[0]) / 32] == 3)
                {
                    FlagManager::flagChest = 3;
                }
            }
        }
    };
    keyS = new Keyboard(SDL_SCANCODE_S, pressS);
    buttonS = new Button("left", NULL, ren, {EntityPosition::Coords[0], EntityPosition::Coords[1] + 32, 32, 32}, pressS, NULL, NULL);
    auto pressD{
        [this]()
        {
            Map* CurrentMap;
            if (!PlayerDeath) CurrentMap = LevelMap;
            else CurrentMap = Gulag;
            bool dFlag = true;
            for(Enemy* enemy : enemies)
            {
                if (EntityPosition::Coords[0] == 960)
                {
                    dFlag = false;
                    //остановка при упоре в стену
                }
                else if ((EntityPosition::Coords[0] + 32) == enemy->Rect.x &&
                         EntityPosition::Coords[1] == enemy->Rect.y && !PlayerDeath)
                {
                    dFlag = false;
                    //остановка при попытке пройти сквозь enemy
                }
            }
            if(dFlag == true)
            {
                if (CurrentMap->Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 + 1] == 8)
                {
                    PlayerInGulagHole();
                }
                if (CurrentMap->Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 + 1] == 4)
                {
                    Start();
                }
                if (CurrentMap->Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 + 1] == 0)
                {
                    EntityPosition::Coords[0] += 32;
                    FlagManager::flagTurn = 1;
                }
                if (CurrentMap->Location[(EntityPosition::Coords[1]) / 32][(EntityPosition::Coords[0]) / 32 + 1] == 3)
                {
                    FlagManager::flagChest = 4;
                }
            }
        }
    };
    keyD = new Keyboard(SDL_SCANCODE_D, pressD);
    buttonD = new Button("left", NULL, ren, {EntityPosition::Coords[0] + 32, EntityPosition::Coords[1], 32, 32}, pressD, NULL, NULL);
    auto playerAttack{
        [this]()
        {
            player->playerTurn();
            if(!player->playerEscaping)
            {
                Attack();
            }
        }
    };
    buttonForPlayerAttack = new Button("left", NULL, ren, {0, 0, 32, 32}, playerAttack, NULL, NULL);
    auto Escape {
        [this]()
        {
            player->playerEscaping = !player->playerEscaping;
        }
    };
    keyH = new Keyboard(SDL_SCANCODE_H, Escape);
}

void Level::PlayerInGulagHole()
{
    if(!(rand()%(12-pLCK)))
    {
        PlayerDeath = false;
        player->ChangeHpValue(player->GetHP(2)-1);
        EntityPosition::Coords[0] = pCOORDS.x;
        EntityPosition::Coords[1] = pCOORDS.y;
    }
    else
    {
        PlayerDead = true;
        player->ChangeHpValue(-10);
    }
}

Level::~Level()
{
    //WTF нельзя делитнуть инвентарь (вылезает ошибка линковщика)
    //delete player;
    for (Enemy* enemy : enemies)
    {
        delete enemy;
    }
    for (Enemy* enemy : StandartEnemies)
    {
        delete enemy;
    }
    delete uiInfo;
    delete uiItem;
    delete UiEnemy;
    delete uiSpec;
    delete uiTrader;
    delete hp;
    delete mana;
    delete exp;
    delete uiEquiped;
    delete keyW;
    delete keyA;
    delete keyS;
    delete keyD;
    delete buttonW;
    delete buttonA;
    delete buttonS;
    delete buttonD;
    delete buttonForPlayerAttack;
    delete LevelMap;
    delete Gulag;
    SDL_DestroyTexture(PlayBackground);
    for (Coins* coin : coins)
    {
        if (coin != nullptr)
        {
            delete coin;
            coin = nullptr;
        }
    }
    //delete uiTrader;
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
            coins.push_back(enemy->GetCoin());
            enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy));
            std::cout << "Delete enemy" << std::endl;
            FlagManager::flagUiEnemy = 0;
            player->ChangeExpValue(100);
            FlagManager::flagInAreaOfAnemy = 0;
        }
    }
}

void Level::deleteCoin()
{
    for (Coins* coin : coins)
    {
        if (coin != nullptr)
        {
            if (coin->GetRect().x == EntityPosition::Coords[0] &&
                    coin->GetRect().y == EntityPosition::Coords[1])
            {
                coins.erase(std::remove(coins.begin(), coins.end(), coin));
                coins.shrink_to_fit();
                std::cout << "Delete coin\n";
                player->ChangeCoins(coin->GetValueCoins());
                delete coin;
                coin = nullptr;
            }
        }
    }
}

void Level::Update()
{
    if(PlayerDead)
    {
        delete player;
        player = nullptr;
    }
    if (player != nullptr && player->GetSpecValue(6) != pLCK)
    {
        pLCK = player->GetSpecValue(6);
        Gulag->GulagChoose(pLCK);
    }
    if(player != nullptr && player->GetHP(0) <= 0)
    {
        PlayerDeath = true;
        for (Coins* coin : coins)
        {
            if (coin != nullptr)
            {
                coins.erase(std::remove(coins.begin(), coins.end(), coin));
                coins.shrink_to_fit();
                delete coin;
                coin = nullptr;
                std::cout << "Start coin delete" << std::endl;
            }
        }
        pCOORDS.x = EntityPosition::Coords[0];
        pCOORDS.y = EntityPosition::Coords[1];
        EntityPosition::Coords[0] = 32*13; EntityPosition::Coords[1] = 32*13;
        while (Gulag->Location[EntityPosition::Coords[1]/32][EntityPosition::Coords[0]/32] == 4)
        {
            EntityPosition::Coords[0] = rand()%30+1; EntityPosition::Coords[1] = rand()%20 + 1;
        }
        player->ChangeHpValue((1-(player->GetHP(0))));
    }

    Level::TimerTurn();

    if(player!= nullptr && (player->playerEscaping || PlayerDeath))
        FlagManager::flagTurn = 0;

    int n = Player::VIS;

    if (!PlayerDeath)
    {
        for (int i = (EntityPosition::Coords[1] / 32) - n; i <= (EntityPosition::Coords[1] / 32) + n; i++)
        {
            for (int j = (EntityPosition::Coords[0] / 32) - n; j <= (EntityPosition::Coords[0] / 32) + n; j++)
            {
                ChangeDark(i, j);
            }
        }
    }

    if (enemies.size() == 0)
    {
        FlagManager::flagTurn = 0;
    }

    if (player != nullptr)
    {
        if (!PlayerDeath) player->GetLevel(LevelMap->Location);
        if (PlayerDeath) player->GetLevel(Gulag->Location);
    }

    if (player != nullptr &&
            FlagManager::flagTurn == 0)
    {
        player->Update();
    }

    if (!PlayerDeath)
    {
        if (StandartBossSkeleton->GetHpEnemy(0) > 0 && LevelMap->floorLvl == 20 && FlagManager::flagTurn != 0 && enemies.size() < 15)
        {
            Enemy* enemy = new Enemy(StandartEnemySkeletonMinion);
            enemies.push_back(enemy);
            enemy->GetLoc(LevelMap->Location);
            enemy->GetEnemyFirstCoords();
        }
        for(Enemy* enemy : enemies)
        {
            if (enemy != nullptr &&
                    FlagManager::flagTurn != 0)
            {
                enemy->Update();
                enemy->GetLoc(LevelMap->Location);
            }
            //удаление player (enemy) при hp <= 0
            if (enemy->GetHpEnemy(0) <= 0 && enemy != nullptr)
            {
                Level::deleteEnemy();
                std::cout << enemies.size() << std::endl;
                if (enemies.size() == 0)
                {
                    LevelMap->Location[LevelMap->portal.x][LevelMap->portal.y] = 4;
                    LevelMap->textureLocation[LevelMap->portal.x][LevelMap->portal.y] = 15;
                }
                if(!(rand()%3))
                {
                    while(true) {
                        int item = rand()%(Inventory::ExistingItems.size());
                        if (Inventory::ExistingItems[item]->Type == potion) {
                            if(LevelMap->TileSet == 0 || LevelMap->TileSet == 1) {
                                if (Inventory::ExistingItems[item]->spawnLoc == loc::cave) {
                                    player->GetItemOnLvl((item));
                                    break;
                                }
                            }
                            if(LevelMap->TileSet == 2 || LevelMap->TileSet == 3 || LevelMap->TileSet == 4) {
                                if (Inventory::ExistingItems[item]->spawnLoc == loc::castle) {
                                    player->GetItemOnLvl((item));
                                    break;
                                }
                            }
                        }
                    }
                }
            }

            if (enemy != nullptr)
                enemy->GetLoc(LevelMap->Location);
        }
        //BOSS
    }

    if (FlagManager::flagInAreaOfAnemy == 0)
        player->playerTurn();

    //удаление player при hp <= 0
    if (Player::GetHP(0) <= 0 && player != nullptr)
    {
        player->Update();
    }

    for (Coins* coin : coins)
    {
        if (coin != nullptr)
            deleteCoin();
    }

    buttonW->updateCoords(EntityPosition::Coords[0], EntityPosition::Coords[1] - 32);
    buttonA->updateCoords(EntityPosition::Coords[0] - 32, EntityPosition::Coords[1]);
    buttonS->updateCoords(EntityPosition::Coords[0], EntityPosition::Coords[1] + 32);
    buttonD->updateCoords(EntityPosition::Coords[0] + 32, EntityPosition::Coords[1]);

    //Update значений hp, mana и exp у playera
    if (FlagManager::flagCheckHP == 1)
    {
        hp->Update();
        //hp->UpdateMax(); //WTF
    }

    if (FlagManager::flagCheckMana == 1)
    {
        mana->Update();
        //mana->UpdateMax(); //WTF
    }

    if (FlagManager::flagCheckExp == 1)
    {
        exp->Update();
        exp->UpdateMax();
    }
    if (FlagManager::flagPointOfSpec == 1)
    {
        uiSpec->Update();
    }
    if (FlagManager::flagLevelOfPlayer == 1)
    {
        uiInfo->Update();
    }
    if (FlagManager::flagCoin == 1)
    {
        uiInfo->Update();
    }

    if (FlagManager::flagUiTrader == 1 && player != nullptr)
    {
        uiTrader->Update(player);
    }

    if (FlagManager::flagUiTrader == 0)
    {
        uiTrader->Check();
    }
}

void Level::SetLevelLoot() {
    loc CurrentSpawn = static_cast<loc>(LevelMap->TileSet);
    for (int i = 0; i < 3; i++) {
        while(true) {
            LevelMap->itemsOnLvl[i] = (rand() % (Inventory::ExistingItems.size()-1)) + 1;
            if (Inventory::ExistingItems[LevelMap->itemsOnLvl[i]]->spawnLoc == CurrentSpawn) {
                break;
            }
        }
    }
    LevelMap->itemsHave = 2;
}

void Level::Start()
{
    for (Coins* coin : coins)
    {
        if (coin != nullptr)
        {
            delete coin;
            coin = nullptr;
            std::cout << "Start coin delete" << std::endl;
        }
    }
    coins.clear();

    if (FlagManager::flagUiTrader == 0 && LevelMap->floorLvl != 1)
        FlagManager::flagUiTrader = 1;

    if (LevelMap->floorLvl == 1)
    {
        player->PushItemsToInventory(4);
    }
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
    LevelMap->GenerateMap();

    SetLevelLoot();

    for(int i = 0; i<((LevelMap->floorLvl)%4+1)+(LevelMap->floorLvl/4); i++)
    {
        std::cout<<LevelMap->floorLvl << "F";
        //int MobTypeChoose = ((LevelMap->floorLvl)/4)*2+(rand()%2);
        //if (MobTypeChoose > 4) MobTypeChoose = 4;
         //ВАЖНО
         //ВАЖНО
         //ВАЖНО я здесь добавил условие потому что нет мобов на 4 и 5 локу. Текстурки я добавил их осталось настроить, я
         //не совсем понял как. Текстурки на них есть, кста джунгли теперь 2 лока, не замок, придется подвигать. Сумимасе.
        if(LevelMap->floorLvl != 20)
        {
            int MobTypeChoose = (LevelMap->floorLvl/4)*2+(rand()%2);
            if(StandartEnemies[MobTypeChoose]->GetTypeName() == 1)
            {
                Enemy* enemy = new Enemy(StandartEnemies[MobTypeChoose]);
                enemies.push_back(enemy);
            }
            else if(StandartEnemies[MobTypeChoose]->GetTypeName() == 2)
            {
                RangeEnemy* enemy1 = new RangeEnemy(StandartEnemies[MobTypeChoose]);
                enemies.push_back(enemy1);
            }
        }
        else
        {
            enemies.push_back(StandartBossSkeleton);
            break;
        }
    }
    player->generate = LevelMap->generateChoose;
    for(Enemy* enemy : enemies)
    {
        enemy->generate = LevelMap->generateChoose;
        std::cout << LevelMap->generateChoose;
    }
    player->GetLevel(LevelMap->Location);
    player->GetPlayerFirstCoords();
    for(Enemy* enemy : enemies)
    {
        enemy->GetLoc(LevelMap->Location);
        enemy->GetEnemyFirstCoords();
    }
    player->playerTurn();
}

void Level::TimerTurn()
{
    if (FlagManager::flagTimerTurn == 1)
    {
        if (timeB == false)
        {
            timer = SDL_GetTicks();
            timeB = true;
        }
        Uint32 timer2 = SDL_GetTicks();
        if (timer2 - timer >= 200 && timeB == true)
        {
            std::cout << "TimerTurn" << std::endl;
            timer = timer2;
            FlagManager::flagTimerTurn = 0;
            FlagManager::flagTurn = 1;
        }
        else
        {
            FlagManager::flagTimerTurn = 1;
            FlagManager::flagTurn = 0;
        }
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
            if (PlayerDeath) {
                RenderManager::SetTile(j * 32, i * 32, Gulag->textureLocation[i][j], ren, TileTextures[Gulag->TileSet]);
            }
            if (!PlayerDeath) {
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
    }
    if (player != nullptr)
    {
        player->Render();
    }
    if (!PlayerDeath) {
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
                    enemy->Render();
                }
            }
        }
    }

    for (Coins* coin : coins)
    {
        if (coin != nullptr)
            coin->Render();
    }

    if (FlagManager::flagUiTrader == 1 && LevelMap->floorLvl != 1)
        uiTrader->Render();

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
        }
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
        }
        if (FlagManager::flagWSD == 1)
        {
            uiSpec->Update(Player::GetSpecValue(4), 4);
            mana->UpdateMax();
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
        if (FlagManager::flagUI == 1)
        {
            uiInfo->Render();
            hp->Render();
            mana->Render();
            exp->Render();

            if (FlagManager::flagUiEnemy == 1)
            {
                UiEnemy->Render();
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
            if (eventInLvl.button.button == SDL_BUTTON_LEFT)
            {
                //Взаимодействие с Items в Inventory
                uiInv->clickForItemsInInv();

                //Взаимодействие с Equiped Items
                uiEquiped->clickForItemsInInv();
                break;
            }
        }

        //Вызов окна Spec по нажатию мыши
        uiInfo->handleEvents(eventInLvl);

        //Увеличение значения характеристик по нажатию мыши
        uiSpec->handleEvents(eventInLvl);

        //Вызов окна Inventory по нажатию мыши
        uiInv->handleEvents(eventInLvl);

        //Вызов InfoEnemy
        UiEnemy->handleEvents(eventInLvl);
        if (FlagManager::flagUiTrader == 1)
        {
            //Work with UiTrader
            uiTrader->handleEvents(eventInLvl);
        }
    }

    if (FlagManager::flagUiTrader == 0)
    {
        //Передача event в Player
        if (player && FlagManager::flagTurn == 0)
        {
            keyW->handleEvents(eventInLvl);
            keyA->handleEvents(eventInLvl);
            keyS->handleEvents(eventInLvl);
            keyD->handleEvents(eventInLvl);
            keyH->handleEvents(eventInLvl);

            buttonForPlayerAttack->handleEvents(eventInLvl);
            buttonW->handleEvents(eventInLvl);
            buttonA->handleEvents(eventInLvl);
            buttonS->handleEvents(eventInLvl);
            buttonD->handleEvents(eventInLvl);
        }
        CheckButton(eventInLvl);
    }
}

void Level::CheckButton(SDL_Event& eventInLvl) {
    if (player->EqItems.equipedMagic != nullptr) {
        if(player->EqItems.equipedMagic->WeaponType == magicType::field) {
            int mouseX = 0, mouseY = 0;
            SDL_GetMouseState(&mouseX, &mouseY);
            int temp = mouseX % 32; mouseX -= temp; temp = mouseY % 32; mouseY -= temp;
            buttonForPlayerAttack->updateCoords(mouseX, mouseY);
            for (Enemy* enemy : enemies) {
                if(enemy->Rect.x == mouseX && enemy->Rect.y == mouseY) {
                    UiEnemy->Update(enemy);
                    UiEnemy->UpdateMax(enemy);
                }
            }
        }
    }
    if((player->EqItems.equipedMagic == nullptr)||(player->EqItems.equipedMagic != nullptr && (static_cast<magicWeapon*>(Inventory::ExistingItems[Player::EqItems.WeaponId]))->WeaponType != magicType::field)) {
        for (Enemy* enemy : enemies)
        {
            int mouseX = 0, mouseY = 0;
            SDL_GetMouseState(&mouseX, &mouseY);
            if((mouseX<=enemy->Rect.x+32)&&(mouseX>=enemy->Rect.x)&&
                    (mouseY<=enemy->Rect.y+32)&&(mouseY>=enemy->Rect.y) &&
                    eventInLvl.button.clicks == 1)
            {
                UiEnemy->Update(enemy);
                UiEnemy->UpdateMax(enemy);
                if (eventInLvl.button.button == SDL_BUTTON_LEFT)
                {
                    buttonForPlayerAttack->updateCoords(enemy->Rect.x, enemy->Rect.y);
                }
                break;
            }
        }
    }
}

//функция работает с пикселями

bool Level::FindWallsOnWay(int x1, int y1, int x2, int y2)
{
    int temp = 0;
    temp = x1 % 32; x1 = x1 - temp + 16; temp = x2 % 32; x2 = x2 - temp + 16;
    temp = y1 % 32; y1 = y1 - temp + 16; temp = y2 % 32; y2 = y2 - temp + 16;
    float k = 0;
    if (x1 != x2) k  = (float )(y2-y1)/(x2-x1);
    bool foundWalls = false;
    int i = 0; int x = (i+x1)/32;
    int y = ((k*i+16)/32) + (y1/32);
    while(!((x == x2/32)&&(y == y2/32)))
    {
        x = (i+x1)/32;
        if (x1 == x2) y += (y2-y1)/abs(y2-y1);
        if (x1 != x2) i+=(x2-x1)/abs(x2-x1);
        if(LevelMap->Location[y][x] != 0)
        {
            foundWalls = true;
        }
        if (x1 != x2) y =((k*i+16)/32)+(y1/32);
    }
    return foundWalls;
}

void Level::Attack()
{
    int mouseX , mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if (Inventory::ExistingItems[Player::EqItems.WeaponId]->Type == magic)
    {
        if (player->EqItems.equipedMagic->WeaponType == magicType::field)
        {
            mouseX/=32; mouseY/=32;
            int splash = Player::EqItems.equipedMagic->SPL;
            if (pow((mouseX-EntityPosition::Coords[0]/32), 2) + pow((mouseY-EntityPosition::Coords[1]/32), 2) <= pow(player->EqItems.equipedMagic->RNG, 2))
            {
                if(!FindWallsOnWay(EntityPosition::Coords[0], EntityPosition::Coords[1], mouseX*32, mouseY*32) ||
                        Player::EqItems.equipedMagic->WeaponEl == magicEl::thunder)
                {
                    for(int i = (mouseX - splash); i <= (mouseX + splash); i++)
                    {
                        for(int j = (mouseY - splash); j <= (mouseY + splash); j++)
                        {
                            for(Enemy* enemy : enemies) {
                                if(enemy->Rect.x/32 == i && enemy->Rect.y/32 == j) {
                                    enemy->ChahgeHpEnemy(-((player->MagicAttack())/2));
                                    if (enemy->Rect.x/32 == mouseX && enemy->Rect.y/32 == mouseY)
                                    {
                                        enemy->ChahgeHpEnemy(-((player->MagicAttack())/2));
                                    }
                                    if (player->EqItems.equipedMagic->WeaponEl == magicEl::fire)
                                    {
                                        enemy->ChahgeHpEnemy(-(player->GetSpecValue(3)));
                                    }
                                    if (player->EqItems.equipedMagic->WeaponEl == magicEl::ice)
                                    {
                                        //UNDONE
                                    }
                                }
                            }
                        }
                    }
                    enemies[0]->enemyTurn(); // ТОЖЕ ВАЖНО
                }
            }
        }
    }

    if ((Inventory::ExistingItems[Player::EqItems.WeaponId]->Type != magic)||
            (Inventory::ExistingItems[Player::EqItems.WeaponId]->Type == magic &&
             (static_cast<magicWeapon*>(Inventory::ExistingItems[Player::EqItems.WeaponId]))->WeaponType != magicType::field))
    {
        for (Enemy* enemy : enemies)
        {
            buttonForPlayerAttack->updateCoords(enemy->Rect.x, enemy->Rect.y);
            std::cout<<enemy->Rect.x<< " " << enemy->Rect.y << std::endl;
            if((mouseX<=enemy->Rect.x+32)&&(mouseX>=enemy->Rect.x)&&
                    (mouseY<=enemy->Rect.y+32)&&(mouseY>=enemy->Rect.y))
            {
                //magic
                if (Inventory::ExistingItems[Player::EqItems.WeaponId]->Type == magic)
                {
                    mouseX/=32; mouseY/=32;
                    if (pow((mouseX-EntityPosition::Coords[0]/32), 2) + pow((mouseY-EntityPosition::Coords[1]/32), 2) <= pow(player->EqItems.equipedMagic->RNG, 2))
                    {
                        if(!FindWallsOnWay(EntityPosition::Coords[0], EntityPosition::Coords[1], mouseX*32, mouseY*32) ||
                                Player::EqItems.equipedMagic->WeaponEl == magicEl::thunder)
                        {
                            enemy->ChahgeHpEnemy(-(player->MagicAttack()));
                            if (player->EqItems.equipedMagic->WeaponEl == magicEl::fire)
                            {
                                enemy->ChahgeHpEnemy(-(player->GetSpecValue(3)));
                            }
                            if (player->EqItems.equipedMagic->WeaponEl == magicEl::ice)
                            {
                                //UNDONE
                            }
                            player->ChangeManaValue(-5);
                            enemies[0]->enemyTurn(); // ТОЖЕ ВАЖНО
                            FlagManager::flagInAreaOfAnemy = 0;
                        }
                    }
                }

                //Range boy
                if (Inventory::ExistingItems[Player::EqItems.WeaponId]->Type == rWeapon)
                {
                    int PlPosx = EntityPosition::Coords[0] / 32, PlPosy =
                            EntityPosition::Coords[1] / 32, EnPosx = (enemy->Rect.x) / 32, EnPosy = (enemy->Rect.y) / 32;
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
                    FlagManager::flagInAreaOfAnemy = 0;
                }
                //Melee boy
                else if (this->CheckPositionToMeleeAttack(enemy->Rect, EntityPosition::Coords[0], EntityPosition::Coords[1]) == true &&
                         FlagManager::flagMeleeAttackPlayer == 1 && FlagManager::flagMeleeAttackEnemy == 0 &&
                         FlagManager::flagTurn == 0)
                {
                    enemy->ChahgeHpEnemy(-(player->MeleeAttack()));
                    enemies[0]->enemyTurn(); // ТОЖЕ ВАЖНО
                    FlagManager::flagInAreaOfAnemy = 0;
                }
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
