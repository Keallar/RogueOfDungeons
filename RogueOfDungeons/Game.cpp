#include "Game.h"
#include <SDL_image.h>
#include "textureManager.h"
#include "Level.h"
MainMenu* Menu;

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
			SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}
		isRunning = true;
	}
	
	else
	{
		isRunning = false;
	}
	Menu = new MainMenu("images/BackgroundMenu.png", "images/Play.png", "images/Settings.png","images/Exit.png", renderer);
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{ 
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&mouseCoord.x, &mouseCoord.y);
			if(Menu->flag == 1) {
				if (InputManager::MouseInArea(640, 361, 250, 100, mouseCoord.x, mouseCoord.y)) {
					isRunning = false;
					break;
				}
				if (InputManager::MouseInArea(640, 471, 420, 100, mouseCoord.x, mouseCoord.y)) {
					isRunning = false;
					break;
				}
				if (InputManager::MouseInArea(640, 581, 250, 100, mouseCoord.x, mouseCoord.y)) {
					isRunning = false;
					break;
				}
			}
		default:
			break;
	}
}
void Game::update()
{
	if (Menu->flag == 1) {
		Menu->Render();
	}
	
}
void Game::render()
{
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
