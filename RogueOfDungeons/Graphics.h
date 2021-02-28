#ifndef GRAPHICS_H
#define GRAPHICS_H

struct SDL_Window;
struct SDL_Renderer;

class Graphics {
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
public:
	Graphics() {
	SDL_Init(SDL_INIT_EVERYTHING);
	_window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1272, 720, SDL_WINDOW_SHOWN);
	_renderer = SDL_CreateRenderer(_window, -1, 0);
	}
	~Graphics() {};
	void SimpleWindow() {
		SDL_SetRenderDrawColor(_renderer, 117, 187, 253, 255);
		SDL_RenderClear(_renderer);
		SDL_RenderPresent(_renderer);
		SDL_Delay(3000);
	}
};
#endif
