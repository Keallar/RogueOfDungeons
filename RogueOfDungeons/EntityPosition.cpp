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
	1024, /*InfoBlock x position 4*/
	32,  /*InfoBLock y postion 5*/
	1024, /*InventoryBlock x position 6*/
	480, /*InventoryBlock y position 7*/
	0, 
	0 
};


