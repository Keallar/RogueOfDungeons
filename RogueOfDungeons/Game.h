#pragma once
#include <SDL.h>
#include <iostream>
#include "Graphics.h"
#include <string>
#include <SDL_image.h>
	
using namespace std;

class Game
	{
	private:
		bool isRunning;
		SDL_Window* window;
		SDL_Renderer* renderer;
		Graphics* Background = new Graphics(window, renderer);
		Graphics* Play = new Graphics(window, renderer);
	public:
		Game();
		~Game();
		void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
		void handleEvents();
		void update();
		void render();
		void clean();
		bool running();
	};
