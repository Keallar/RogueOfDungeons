#include "Graphics.h"
#include <iostream>
using namespace std;
int Graphics::CreateWindow()
{

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { return 1; }//проверка на инициализацию
    win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);//создание окна
    if (win == nullptr) { return 1; }

    return 0;
};
