#pragma once
#include <string>
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Window;


class Graphics {
private:
	SDL_Texture* _texture;
	SDL_Renderer* _renderer;
	SDL_Window* _window;
public:
	Graphics(SDL_Window* window, SDL_Renderer* renderer);
	~Graphics() {};
	void OutputTexture(int x,int y,int w,int h, std::string file);
	void CreateFrame();
	void Destroy();
};