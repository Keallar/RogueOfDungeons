#include "EntityPosition.h"
void EntityPosition::ChangeCoords(int i, int changePosition)
{
	EntityPosition::Coords[i] += changePosition;
}
int EntityPosition::Coords[10] =
{ 
	32, /*Player x position*/
	32, /*Player y position*/
	512, /*Enemy x position*/
	512, /*Enemy y position*/
	0,
	0, 
	0, 
	0,
	0, 
	0 
};


