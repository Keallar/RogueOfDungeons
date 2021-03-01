#pragma once
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Window;

class Graphics {
private:
	SDL_Texture* _backgroundMenu;
	SDL_Window* _window;
	SDL_Renderer* _renderer;
public:
	Graphics();
	~Graphics() {};
	void SimpleWindow();
	void Destroy();
};