#include "Graphics.h"
#include <SDL.h>
#include <iostream>

using namespace N;
using namespace std;
int SDL_main(int argc, char* argv[]) /* ������ ��� main, ��������� SDL ������� ������������ 
main ����� ����� �������� � SDL_main ��� ��������� ��� main*/
{
	Graphics graphics;//�������� ������� ������
	graphics.CreateWindow();//������� �������� ����
	return 0;
};