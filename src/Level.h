#pragma once
#include <vector>
#include <memory>
#include "Enemy.h"
#include "Player.h"
#include "UiMain.h"
#include "GameObject.h"
#include "Buttons.h"
#include "UiPlayer.h"
#include "Map.h"
#include "UiEnemy.h"
#include "rangeenemy.h"
#include "Coins.h"
#include "TextureBase.h"
#include "bosssummoner.h"
#include "UiTrader.h"
#include "bosssummoner.h"

struct MouseCoords
{
	int x;
	int y;
}; 

class Level 
{
private:
    TextureBase* GameTextures;
    //TextInfo* changeState[3];
	HpInfo* hp;
	ManaInfo* mana;
	ExpInfo* exp;
    SDL_Texture* TileTextures[6];
	SDL_Texture* PlayBackground;
	SDL_Renderer* ren;
	Player* player;
    Enemy* StandartEnemyTurtle = new Enemy("data/images/Turtle.png", 4, ren, 28, 28, 5, 4, 5, 1, 10);
    RangeEnemy* StandartRangeEnemyTurtle = new RangeEnemy("data/images/TurtleR.png", 4, ren, 24, 24, 5, 4, 5, 2, 7);
    Enemy* StandartEnemyBear = new Enemy("data/images/Bear.png", 4, ren, 23, 23, 2, 5, 6, 1, 10);
    RangeEnemy* StandartDragonEnemy =  new RangeEnemy("data/images/Gragon.png", 4, ren, 24, 24, 6, 10, 6, 2, 7);
    Enemy* StandartBigDragonEnemy = new Enemy("data/images/MDragon.png", 4, ren, 36, 36, 7, 15, 8, 2, 10);
    Enemy* StandartEnemySlime = new Enemy("data/images/Slime.png", 4, ren, 12, 12, 2, 3, 2, 1, 10);
    Enemy* StandartEnemySkeletonMinion = new Enemy("data/images/HeroEscape.png", 4, ren, 5, 5, 2, 1, 0, 1, 10);
    BossSummoner* StandartBossSkeleton = new BossSummoner("data/images/Boss.png", 4, ren, 25, 25, 0, 100, 20, 3, 10);
    RangeEnemy* StandartEnemyBee = new RangeEnemy("data/images/Bee.png", 3, ren, 18, 20, 3, 6, 6, 2, 5);
    Enemy* StandartEnemyJungleSlime = new Enemy("data/images/JungleSlime.png", 4, ren, 23, 30, 3, 7, 7, 1, 10);
    RangeEnemy* StandartEnemyRangeGhost = new RangeEnemy("data/images/MageGhost.png", 4, ren, 42, 42, 8, 10, 10, 2, 8);
    Enemy* StandartEnemyGhost = new Enemy("data/images/MeleeGhost", 4, ren, 42, 42, 8, 14, 14, 1, 10);
    RangeEnemy* StandartRangeSkeletonMinion = new RangeEnemy("data/images/PAPAABOBA", 4, ren, 8, 8, 6, 10, 10, 2, 10);
    std::array<Enemy*, 13> StandartEnemies = { StandartEnemySlime, StandartEnemyBear,
                                             StandartEnemyBee, StandartEnemyJungleSlime,
                                             StandartEnemyTurtle, StandartRangeEnemyTurtle,
                                            StandartDragonEnemy, StandartBigDragonEnemy,
                                             StandartEnemyRangeGhost, StandartEnemyGhost,
                                            StandartBossSkeleton, StandartEnemySkeletonMinion,
                                               StandartRangeSkeletonMinion};
    UIEnemy* UiEnemy;
	UIInfo* uiInfo;
	UIItem* uiItem;
	UISpecifications* uiSpec;
	UIEquipedItem* uiEquiped;
    std::vector <Enemy*> enemies;
	UIInventory* uiInv;
	MouseCoords mouseCoords;
    Keyboard* keyW = 0;
    Button* buttonW = 0;
    Keyboard* keyA = 0;
    Button* buttonA = 0;
    Keyboard* keyS = 0;
    Button* buttonS = 0;
    Keyboard* keyD = 0;
    Button* buttonD = 0;
    Keyboard* keyH = 0;
    Button* buttonForPlayerAttack;
    Keyboard* keyE;
    Map* LevelMap;
    Map* Gulag;
    std::vector<Coins*> coins;
    UiTrader* uiTrader;

    bool PlayerDeath;
    int pClass;
    int pLCK;
    struct pCOORDS {
        int x;
        int y;
    } pCOORDS;

    void PlayerInGulagHole();
	void ChangeDark(int i, int j);
	MouseCoords Mouse;
    void CheckButton(SDL_Event& eventInLvl);
    bool FindWallsOnWay(int x1, int y1, int x2, int y2);
    Uint32 timer;
    bool timeB;
    void SetLevelLoot();
public:
    bool PlayerDead;
	bool CheckPositionToMeleeAttack(SDL_Rect rect, int x, int y);
	int GetGeneration();
	bool flagTB;
	void Attack();
    Level(SDL_Renderer* renderer, int playerClass);
	~Level();
	void deletePlayer();
	void deleteEnemy();
    void deleteCoin();
	void Update();
	void Start();
	void Render();
	void handleEvents(SDL_Event eventInLvl);
	int GetLocation(int x, int y);
	void ChangeLocation(int x, int y);
	void ChangeLevel(int x, int y, int LocationChange, int TextureChange);
//    void TimerTurn();
};


