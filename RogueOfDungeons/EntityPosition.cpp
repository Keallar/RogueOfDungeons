#include "EntityPosition.h"
void EntityPosition::ChangeCoords(int i, int Change)
{
	EntityPosition::Coords[i] += Change;
}
int EntityPosition::Coords[10] = { 32, 32, 512, 512, 0, 0, 0, 0, 0, 0 };


