#include "Graphics.h"
#include <iostream>
using namespace N;
using namespace std;
int N::Graphics::CreateWindow()
{

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { return 1; }//�������� �� �������������
    SDL_Window* win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);//�������� ����
    if (win == nullptr) { return 1; }
    SDL_Delay(2000);//����� ����� ����(����)
    return 0;
};
