#include "EntityPosition.h"
void EntityPosition::ChangeCoords(int i, int changePosition)
{
	EntityPosition::Coords[i] += changePosition;
}
int EntityPosition::Coords[20] =
{ 
	32,   /*Player x position 0*/
	32,   /*Player y position 1*/
	512,  /*Enemy x position 2*/
	512,  /*Enemy y position 3*/
	0,    /*VersionBlock x position 4*/
	705,  /*VersionBLock y postion 5*/
	1116, /*Info x position 6*/
	20,   /*Info y position 7*/
	1024, /*InfoBlock x position 8*/
	0,    /*InfoBlock y position 9*/
	1024, /*InventoryBlock x position 10*/
	480,  /*InventoryBlock y position 11*/
	1085,    /*Inventory x position 12*/
	490,    /*Inventory y position 13*/
	0,
	0,
	0,
	0,
	0,
	0
};


