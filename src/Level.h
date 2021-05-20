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
    Enemy* StandartEnemyTurtle = new Enemy("data/images/Turtle.png", 4, ren, 10, 10, 5, 4, 5, 1);
    RangeEnemy* StandartRangeEnemyTurtle = new RangeEnemy("data/images/TurtleR.png", 4, ren, 7, 7, 4, 4, 5, 2);
    Enemy* StandartEnemyBear = new Enemy("data/images/Bear.png", 4, ren, 12, 12, 2, 5, 6, 1);
    RangeEnemy* StandartDragonEnemy =  new RangeEnemy("data/images/Gragon.png", 4, ren, 3, 3, 8, 10, 6, 2);
    RangeEnemy* StandartBigDragonEnemy = new RangeEnemy("data/images/MDragon.png", 4, ren, 5, 5, 13, 15, 8, 2);
    Enemy* StandartEnemySlime = new Enemy("data/images/Slime.png", 4, ren, 8, 8, 1, 3, 2, 1);
    Enemy* StandartEnemySkeletonMinion = new Enemy("data/images/HeroEscape.png", 4, ren, 5, 5, 2, 1, 0, 1);
    BossSummoner* StandartBossSkeleton = new BossSummoner("data/images/Boss.png", 4, ren, 25, 25, 0, 100, 20, 3);
    RangeEnemy* StandartEnemyBee = new RangeEnemy("data/images/Bee.png", 4, ren, 8, 8, 2, 6, 6, 2);
    Enemy* StandartEnemyJungleSlime = new Enemy("data/images/JungleSlime.png", 4, ren, 9, 9, 3, 7, 7, 1);
    RangeEnemy* StandartEnemyRangeGhost = new RangeEnemy("data/images/MageGhost.png", 4, ren, 10, 10, 6, 10, 10, 2);
    Enemy* StandartEnemyGhost = new Enemy("data/images/MeleeGhost", 4, ren, 14, 14, 8, 14, 14, 1);
    std::array<Enemy*, 12> StandartEnemies = { StandartEnemySlime, StandartEnemyBear,
                                             StandartEnemyBee, StandartEnemyJungleSlime,
                                             StandartEnemyTurtle, StandartRangeEnemyTurtle,
                                            StandartDragonEnemy, StandartBigDragonEnemy,
                                             StandartEnemyRangeGhost, StandartEnemyGhost,
                                            StandartBossSkeleton, StandartEnemySkeletonMinion};
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
    void TimerTurn();
};


