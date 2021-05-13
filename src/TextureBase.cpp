#include "TextureBase.h"
#include <fstream>
#include "Managers.h"

TextureBase* TextureBase::res = nullptr;

TextureBase::TextureBase()
{
   std::ifstream file;
   file.open("data/Textures.txt");
   while (file)
   {
       std::string Name;
       file >> Name;
       std::string Path;
       file >> Path;
       Textures[Name] = textureManager::LoadTexture(Path.c_str());
   }
}
TextureBase::~TextureBase()
{
    for (auto& i : Textures)
    {
        SDL_DestroyTexture(i.second);
    }
}

TextureBase *TextureBase::Instance()
{
    if(!res)
        res = new TextureBase();
    return res;
}

void TextureBase::Destroy()
{
    if(res)
    {
        delete res;
        res = 0;
    }
}

SDL_Texture* TextureBase::GetTexture(std::string Name)
{
    return Textures[Name];
}
