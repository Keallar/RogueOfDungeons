#include "Game.h"
#include "Graphics.h"

Game::Game()
{}
Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) 
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "ABOBA";

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Win created" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			std::cout << "Renderer created!" << std::endl;
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		isRunning = true;
	}
	else 
	{
		isRunning = false;
	}
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{ case SDL_QUIT:
		isRunning = false;
		break;
	  default:
		break;
	}
}
void Game::update()
{
	Background->OutputTexture(0, 0, 1280, 720, "image/BackgroundMenu.png");
	Play->OutputTexture(0, 0, 350, 100, "image/Play.png");
}
void Game::render() 
{
	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);
	SDL_Delay(16);
}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "GG" << std::endl;
}
bool Game::running() 
{ 
	return isRunning; 
}