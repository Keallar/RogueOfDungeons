#pragma once
#include <vector>
#include "Enemy.h"
#include "Player.h"
#include "UI.h"
#include "GameObject.h"
#include "Buttons.h"

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
	//int Location2[22][32];
	SDL_Texture* TileTexture;
	SDL_Texture* TileTextureCastle;
	SDL_Texture* PlayBackground;
	SDL_Renderer* ren;
	Player* player;
	Enemy* enemyTurtle;
	UiHpEnemyInfo* uiEnemyHpInfo;
	UIInfo* uiInfo;
	UIItem* uiItem;
	UIEnemyInfo* uiEnemy;
	UISpecifications* uiSpec;
	UIEquipedItem* uiEquiped;
	Keyboard* keyboard;
	Button* buttonForCallSpecInfo;
	Button* buttonForCallInvWin;
	Animation* animation;
	std::vector <Enemy> enemies;
	UIInventory* uiInv;
	//std::vector <GameObject> textures; 
	MouseCoords mouseCoords;
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	//std::vector<std::pair<int, int>> pop_front(std::vector<std::pair<int, int>> vec);
	//void OtherGeneration(int startX, int startY, int endX, int endY);
	//bool Search(std::vector<std::pair<int, int>> vector, int x, int y);
	//int SearchNum(std::vector<std::pair<int, int>> vector, int x, int y);
	void CaveRender(int y, int x);
	void CastleRender(int y, int x);
	void ChangeDark(int i, int j);
	void ChunkGenerationMethod();
	void ChunkGenerationMethod2();
	void LabGeneration();
	void CastleLabGeneration();
	void RoomGenerationMethod2();
	void CreateChunk(int x, int y);
	void CreateChunk2(int x, int y);
public:
	int GetGeneration();
	bool flagTB;
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



