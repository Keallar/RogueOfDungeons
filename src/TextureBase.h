#pragma once
#include <SDL.h>
#include <map>
#include <string>

class TextureBase
{
private:
    static TextureBase* res;
    TextureBase();
    TextureBase(const TextureBase &) = delete;
    TextureBase & operator = (const TextureBase&) = delete;
    ~TextureBase();
public:
    static TextureBase* Instance()
    {
        TextureBase* res = new TextureBase();
        return res;
    }
    std::map<std::string, SDL_Texture*> Textures;
    SDL_Texture* GetTexture(std::string Name);
};