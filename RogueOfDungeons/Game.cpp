#pragma once
#include "Game.h"
#include <SDL_image.h>
#include "SDL_ttf.h"
#include "Managers.h"
#include "Level.h"
#include "GameObject.h"
#include "Player.h"
#include "UI.h"
#include "Enemy.h"


Game::Game() 
{
	level = 0;
	uiMenu = 0;
}

Game::~Game()
{
	delete Menu;
	if (!level) 
	{
		delete level;
	}
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
	if ((SDL_Init(SDL_INIT_EVERYTHING) == 0)||(TTF_Init == 0))
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
				if (InputManager::MouseInArea(640, 361, 250, 100,  mouseCoord.x, mouseCoord.y))
				{
					Menu->flag = 0;
					level = new Level(renderer);
					uiMenu = new UIMenu(renderer);
					level->Start();
					break;
				}
				if (InputManager::MouseInArea(640, 471, 420, 100,  mouseCoord.x, mouseCoord.y)) 
				{
					break;
				}
				if (InputManager::MouseInArea(640, 581, 250, 100,  mouseCoord.x, mouseCoord.y))
				{
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
	if (Menu->flag == 1)
	{
		//Menu->Update();
	}
	else if (FlagManager::flagPlayer == 1 && level->flagTB == 1)
		{
			level->Update();
		}
	
}
	
void Game::render()
{
	SDL_RenderClear(renderer);
	if (Menu->flag == 1)
	{
		Menu->Render();
	}
	else if (FlagManager::flagPlayer == 1 && level->flagTB == 1)
	{
		level->Render();
		uiMenu->Render();
	}

	SDL_RenderPresent(renderer);
}
void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
	std::cout << "GG" << std::endl;
}

bool Game::running() 
{ 
	return isRunning; 
}
