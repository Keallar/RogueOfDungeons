#pragma once
class EntityPosition
{
public:
	static int Coords[20];
	// В ПРАЙВАТЕ НЕ РАБОТАЕТ ОТСТАНЬТЕ
	// 1 - y коорда перса
	// 2 - x коорда первого енеми
	// 3 - y коорда первого енеми
	static void ChangeCoords(int i, int Change);
};

