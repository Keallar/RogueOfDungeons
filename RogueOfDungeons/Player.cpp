#include "Player.h"
#include "GameObject.h"

Player::Player(const char* texturesheet, SDL_Renderer* ren, int x, int y)
{

}

Player::~Player()
{

}
void Player::Update()
{
    while (EXP >= EXPFORLVL)
    {
        ChargePTS++;
        EXP -= EXPFORLVL;
        EXPFORLVL += 5;
        maxHP += 2;
        HP = maxHP;
    }
    if (HP == 0) 
    {
        ///
    }
    while (Mov == 0)
    {
        SDL_PollEvent(&PlayerEvent);
        switch (PlayerEvent.type)
        {
        case SDL_KEYDOWN:
            if (PlayerEvent.key.keysym.sym == SDLK_w) 
            {
                srcRect.y -= 32;
            }
            else if (PlayerEvent.key.keysym.sym == SDLK_s) 
            {
                srcRect
            }
            
        default:
            break;
        }
    }
}

void Player::clean()
{

}
