#pragma once
struct SDL_Window;
struct SDL_Renderer;

class Graphics {
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
public:
	Graphics();
	~Graphics() {};
	void SimpleWindow();
	void Destroy();
};