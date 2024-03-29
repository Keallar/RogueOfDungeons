#include "Game.h"
#include <SDL_image.h>
#include "SDL_ttf.h"
#include "Managers.h"
#include "Level.h"
#include "GameObject.h"
#include "Player.h"
#include "UiMain.h"
#include "Enemy.h"
#include "Buttons.h"
#include "TextureBase.h"

Game::Game() 
{
	level = 0;
	uiLevel = 0;
}

Game::~Game()
{
	delete Menu;
	if (!level) 
	{
		delete level;
	}
    TextureBase::Destroy();
}

SDL_Renderer* Game::renderer;

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}
    if ((SDL_Init(SDL_INIT_EVERYTHING) == 0))
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
		if (TTF_Init() != 0)
		{
			std::cout << "TTF lib init error: " << TTF_GetError()<<std::endl;
		}
		isRunning = true;
	}
	else
	{
		isRunning = false;
	}
	
    Menu = new MainMenu("data/images/BackgroundMenu.png", "data/images/Play.png", "data/images/Settings.png", "data/images/Exit.png", "data/images/Credits.png", renderer);
    classChoose = new ClassChoose(renderer);
    credits = new Credits(Menu);
    TextureBase* GameTextures = TextureBase::Instance();
    winnerScreen = new TitleScreen("you did it",GameTextures->GetTexture("PapaDead") , renderer);
    gameOverScreen = new TitleScreen("Game Over",GameTextures->GetTexture("RIP") , renderer);
    story = new TitleScreen("Story", GameTextures->GetTexture("Story"), renderer);
}

void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
        if (classChoose->flag == 1)
        {
            classChoose->handleEvents(event);
        }
        if (gameOverScreen->flag) {
            gameOverScreen->handleEvents(event);
        }
        if (story->flag) {
            story->handleEvents(event);
        }
        if (winnerScreen->flag) {
            winnerScreen->handleEvents(event);
        }
        if (level)
        {
            level->handleEvents(event);
        }
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&mouseCoord.x, &mouseCoord.y);
			if (Menu->flag == 1) 
			{
				if (InputManager::MouseInArea(640, 361, 250, 100, mouseCoord.x, mouseCoord.y))
				{
                    Menu->flag = 0;
                    classChoose->flag = 1;
                    break;
				}
				if (InputManager::MouseInArea(640, 471, 420, 100, mouseCoord.x, mouseCoord.y))
				{
                    story->flag = true;
					break;
				}
				if (InputManager::MouseInArea(640, 581, 250, 100, mouseCoord.x, mouseCoord.y))
				{
                    isRunning = false;
					break;
				}
                if (InputManager::MouseInArea(10, 630, 210, 60, mouseCoord.x, mouseCoord.y))
                {
                    credits->flag = 1;
                    Menu->flag = 2;
                    break;
                }

			}
            if (Menu->flag == 2)
            {
                credits->handleEvent(event);
            }
		default:
			break;
		}
	}
}

void Game::update()
{
	if (Menu->flag == 1)
	{
		//Menu->Update();
	}
    else
	{
        if (classChoose->flag == 0) {
            classChoose->flag = 3;
            level = new Level(renderer, classChoose->choosedClass);
            level->Start();
        }
        if (level)
        {
            level->Update();
            if(level->PlayerDead) {
                delete level;
                level = nullptr;
                Menu->flag = 1;
                classChoose->choosedClass = 0;
                gameOverScreen->flag = true;
            }
        }
        if(level) {
            if(level->BossDead) {
                delete level;
                level = nullptr;
                Menu->flag = 1;
                classChoose->choosedClass = 0;
                winnerScreen->flag = true;
            }
        }
	}	
}
	
void Game::render()
{
	if (Menu->flag == 1)
	{
		Menu->Render();
	}
	else if (Menu->flag == 0)
    {
        if (classChoose->flag == 1) {
            classChoose->Render();
        }
        else if (level) {
            level->Render();
        }
	}
    else if (Menu->flag == 2)
    {
        credits->render();
    }
    if (gameOverScreen->flag) {
        gameOverScreen->Render();
    }
    if (winnerScreen->flag) {
        winnerScreen->Render();
    }
    if (story->flag) {
        story->Render();
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
