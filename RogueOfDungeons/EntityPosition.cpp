#include "EntityPosition.h"
void EntityPosition::ChangeCoords(int i, int changePosition)
{
	EntityPosition::Coords[i] += changePosition;
}

int EntityPosition::Coords[10] =
{ 
	32,   /*Player x position 0*/
	32,   /*Player y position 1*/
	256,  /*Enemy x position 2*/
	256,  /*Enemy y position 3*/
	0,
	0,
	0,
	0,
	0,
	0
};


