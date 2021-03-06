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

void Player::Render()
{
	RenderManager::CopyToRender(PlayerTexture, ren, xpos, ypos, 64, 64, 0, 0, 32, 32);
}

void Player::Update(int xpos, int ypos)
{
	int x = xpos, y = ypos;
	SDL_Event eventMovePlayer;
	SDL_PollEvent(&eventMovePlayer);
	state = SDL_GetKeyboardState(NULL);
	while ((x == xpos)||(y == ypos))
	{
		if (state[SDL_SCANCODE_W])
			ypos -= 32;
		else if (state[SDL_SCANCODE_S])
			ypos += 32;
		else if (state[SDL_SCANCODE_A])
			xpos -= 32;
		else if (state[SDL_SCANCODE_D])
			xpos += 32;
	}
	Player::Render();
	/*switch (eventMovePlayer.type)
	{
	case SDL_KEYDOWN:
		switch (eventMovePlayer.key.keysym.sym)
		{
		case SDL_SCANCODE_W:
			inputMovePlayer->pressW(ypos);
			std::cout << "PP//";
			Player::Render();
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
