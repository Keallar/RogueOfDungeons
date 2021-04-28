#pragma once
#include <vector>
#include "Enemy.h"
#include "Player.h"
#include "UI.h"
#include "GameObject.h"
#include "Buttons.h"
#include "UiPlayer.h"

struct MouseCoords
{
	int x;
	int y;
}; 

class Level 
{
private:
	TextInfo* changeState[3];
	int itemsOnLvl[3];
	int itemsHave;
	int chests[3][2];
	int floorLvl;
	HpInfo* hp;
	ManaInfo* mana;
	ExpInfo* exp;
	int generateChoose;
	int textureLocation[22][32];
	int Location[22][32];
	int Dark[22][32];
	int TileSet;
	SDL_Texture* TileTextures[5];
	SDL_Texture* PlayBackground;
	SDL_Renderer* ren;
	Player* player;
	Enemy* enemyTurtle;
    Enemy* SecondEnemyTurtle;
    UIEnemyInfo* uiEnemyInfo;
	UIInfo* uiInfo;
	UIItem* uiItem;
	UISpecifications* uiSpec;
	UIEquipedItem* uiEquiped;
	Animation* animation;
    std::vector <Enemy*> enemies;
	UIInventory* uiInv;
	MouseCoords mouseCoords;
	const Uint8* keys = SDL_GetKeyboardState(NULL);
    Keyboard* keyW = 0;
    Button* buttonW = 0;
    Keyboard* keyA = 0;
    Button* buttonA = 0;
    Keyboard* keyS = 0;
    Button* buttonS = 0;
    Keyboard* keyD = 0;
    Button* buttonD = 0;
    Button* buttonForPlayerAttack;

	void ChangeDark(int i, int j);
	void ChunkGenerationMethod();
	void ChunkGenerationMethod2();
	void LabGeneration();
	void CastleLabGeneration();
	void RoomGenerationMethod2();
	void CreateChunk(int x, int y);
	void CreateChunk2(int x, int y);
	MouseCoords Mouse;
public:
	bool CheckPositionToMeleeAttack(SDL_Rect rect, int x, int y);
	int GetGeneration();
	bool flagTB;
	void Attack();
	Level(SDL_Renderer* renderer);
	~Level();
	void deletePlayer();
	void deleteEnemy();
	void Update();
	void Start();
	void Render();
	void handleEvents(SDL_Event eventInLvl);
	void Generate();
	int GetLocation(int x, int y);
	void ChangeLocation(int x, int y);
	void ChangeLevel(int x, int y, int LocationChange, int TextureChange);
};


