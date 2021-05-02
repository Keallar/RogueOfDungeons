#include "TextureBase.h"
#include "fstream"
#include "Managers.h"
#include "Game.h"

TextureBase* TextureBase::res = nullptr;

TextureBase::TextureBase() {
   std::ifstream file;
   file.open("data/Textures.txt");
   while (file) {
       std::string Name;
       file >> Name;
       char* Path;
       file >> Path;
       Textures[Name] = textureManager::LoadTexture(Path, Game::renderer);
   }
}
TextureBase::~TextureBase() {
    while(Textures.size() != 0) {
        SDL_DestroyTexture(Textures.begin()->second);
        Textures.erase(Textures.begin());
    }
}

SDL_Texture* TextureBase::GetTexture(std::string Name) {
    return Textures[Name];
}
