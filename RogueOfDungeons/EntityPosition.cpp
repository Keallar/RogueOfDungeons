#include "EntityPosition.h"
void EntityPosition::ChangeCoords(int i, int changePosition)
{
	EntityPosition::Coords[i] += changePosition;
}
int EntityPosition::Coords[10] =
{ 
	32,  /*Player x position 0*/
	32,  /*Player y position 1*/
	512, /*Enemy x position 2*/
	512, /*Enemy y position 3*/
	0,    /*VersionBlock x position 4*/
	705,  /*VersionBLock y postion 5*/
	1116, /*Info x position 6*/
	20,   /*Info y position 7*/
	1024, /*InfoBlock x position 8*/
	0,     /*InfoBlock y position 9*/
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0
};


