#pragma once
#include "SDL.h"
#include "inventory.h"

class Player
{
private:
	Inventory* inventory;
    int Location[22][32];
    SDL_Texture* PlayerTexture;
    SDL_Renderer* ren;
    static int HP[3];
    static int exp[3];
    static int mana[3];
    int damageInput;
    //UIInfo* uiInfo;
    const Uint8* keys = SDL_GetKeyboardState(NULL);
public:
    Player() = default;
    Player(const char* texturesheet, SDL_Renderer* ren);
    ~Player();
    void Render();
    void Update();
    void handleEvents(SDL_Event playerEvent);
    void clean();
	void GetLevel(int arr[22][32]);
	void GetPlayerFirstCoords();
    void Attack();
    static int GetHP();
    static int GetEXP();
    static int GetMana();
    static void CheckHP();
    static void CheckEXP();
    static void CheckMANA();
};
