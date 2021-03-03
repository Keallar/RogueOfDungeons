#include "Game.h"
#include <SDL_image.h>
#include "textureManager.h"
SDL_Texture* playerTex;
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
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}
		isRunning = true;
	}
	else 
	{
		isRunning = false;
	}
	playerTex = textureManager::LoadTexture("", renderer);
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
	SDL_Delay(300);
}
void Game::render()
{
	SDL_RenderClear(renderer);
	texture = IMG_LoadTexture(renderer, "images/ABOBA.png");
	if (tex_RECT.x + 69 < 340) {
		tex_RECT.x = tex_RECT.x + 69;
	}
	else
	{
		tex_RECT.x = 0;
	}
	tex_RECT.y = 10;
	tex_RECT.w = 67;
	tex_RECT.h = 81;
	if (tex_posRect.x + 50 < 751) {
		tex_posRect.x = tex_posRect.x + 50;
	}
	else {
		tex_posRect.x = 0;
	}
	if (tex_posRect.y + 50 < 551) {
		tex_posRect.y = tex_posRect.y + 50;
	}
	else {
		tex_posRect.y = 0;
	}
	tex_posRect.w = 67;
	tex_posRect.h = 81;
	SDL_RenderCopy(renderer, texture, &tex_RECT, &tex_posRect);
	SDL_RenderPresent(renderer);
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
