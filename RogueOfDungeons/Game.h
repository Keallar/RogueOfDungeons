#pragma once
#include "Graphics.h"
#include <conio.h>
#include <iostream>
namespace std {
	class Game : public Graphics
	{
	private:
		
	public:
		char button;
		int quit();
	};
}
