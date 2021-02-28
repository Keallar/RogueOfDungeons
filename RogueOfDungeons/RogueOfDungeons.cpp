#include "Graphics.h"
#include <SDL.h>
#include <iostream>

using namespace N;
using namespace std;
int SDL_main(int argc, char* argv[]) /* Замена для main, поскольку SDL требует собственного 
main легче будет работать в SDL_main чем создавать доп main*/
{
	Graphics graphics;//создание объекта класса
	graphics.CreateWindow();//функция создания окна
	return 0;
};