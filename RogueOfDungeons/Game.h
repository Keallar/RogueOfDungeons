#pragma once
#include <SDL.h>
#include <iostream>
#include "Graphics.h"
#include <string>
#include <SDL_image.h>
	class Game
	{
	private:
		bool isRunning;
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Texture* textureBackground;
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
