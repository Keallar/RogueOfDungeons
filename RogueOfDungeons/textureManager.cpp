#include "textureManager.h"
SDL_Texture* textureManager::LoadTexture(const char* texName, SDL_Renderer* ren) {
	SDL_Texture* tex = IMG_LoadTexture(ren, texName);
	return tex;
}