#include "Graphics.h"
#include "Game.h"
#include <SDL.h>
#include <iostream>
#include <conio.h>


using namespace std;
int main(int argc, char* argv[])
{
	Game graphics;//�������� ������� ������
	graphics.CreateWindow();//������� �������� ����
	bool run = true;
	graphics.button = 'a';
	
	return graphics.quit();
};