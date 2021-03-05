#include "Level.h"

bool Level::Start()
{
	for (int i = 0; i < 22; i++) 
	{
		for (int j = 0; j < 32; j++) 
		{
			if ((i == 0) || (j == 0) || (i == 21) || (j == 31))
			{
				TileSet(0);
			}
			else
			{
				TileSet(1);
			}
		}
	}
}
void Level::TileSet(int num) 
{
	switch (num)
	{
	case 0:

		break;
	case 1:
		break;
	default:
		break;
	}
}
int Level::Random(int min, int max) 
{
	return min + rand() % (max - min);
}