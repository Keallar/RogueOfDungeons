#include "SDL.h"
#include "Player.h"
#include <iostream>
#include "MainMenu.h"

	class Game
	{
	private:
		bool isRunning;
		SDL_Window* window;
		SDL_Renderer* renderer;
		SDL_Texture* texture;
		SDL_Rect tex_RECT;
		SDL_Rect tex_posRect;
		MainMenu MainMenu;
		

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
