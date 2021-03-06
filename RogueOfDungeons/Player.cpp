#include "Player.h"
#include "GameObject.h"

InputManager* inputMovePlayer;
const Uint8* state;

Player::Player(const char* texturesheet, SDL_Renderer* renderer)
{
	ren = renderer;
	PlayerTexture = textureManager::LoadTexture(texturesheet, ren);
}

Player::~Player()
{
	if (HP == 0)
	{
		SDL_DestroyTexture(PlayerTexture);
	}
}
void Player::UpdateCoord() {
	playerCoordx += 32;
	std::cout << playerCoordx;
}

void Player::Render()
{
	RenderManager::CopyToRender(PlayerTexture, ren, playerCoordx, playerCoordy, 64, 64, 0, 0, 32, 32);
}

void Player::Update()
{
	Player::UpdateCoord();
	
	/*switch (eventMovePlayer.type)
	{
	case SDL_KEYDOWN:
		switch (eventMovePlayer.key.keysym.sym)
		{
		case SDL_SCANCODE_W:
			inputMovePlayer->pressW(ypos);
			std::cout << "PP//";
			Player::Render();
			std::cout << "PP\n";
			break;
		case SDL_SCANCODE_S:
			inputMovePlayer->pressS(xpos);
			Player::Render();
			break;
		case SDLK_a:
			
			inputMovePlayer->pressA(ypos);
			Player::Render();
			break;
		case SDLK_d:
			
			inputMovePlayer->pressD(xpos);
			Player::Render();
			break;
		default:
			break;
		}
	}*/

}
