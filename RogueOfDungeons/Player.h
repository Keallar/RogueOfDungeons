#pragma once
#include "SDL.h"


class Player
{
private:
	int Location[22][32];
    SDL_Texture* PlayerTexture;
    SDL_Renderer* ren;
    static int HP;
    static int exp;
    static int mana;
    int damageInput;
    UIInfo* uiInfo;
    const Uint8* keys = SDL_GetKeyboardState(NULL);
public:
    Player() = default;
    Player(const char* texturesheet, SDL_Renderer* ren);
    ~Player();
    void Render();
    void Update();
    void clean();
	void GetLevel(int arr[22][32]);
	void GetPlayerFirstCoords();
};
