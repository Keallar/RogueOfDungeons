#include "Graphics.h"
#include <iostream>
using namespace N;
using namespace std;
int N::Graphics::CreateWindow()
{

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { return 1; }//проверка на инициализацию
    SDL_Window* win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);//создание окна
    if (win == nullptr) { return 1; }
    SDL_Delay(2000);//время жизни окна(тест)
    return 0;
};
