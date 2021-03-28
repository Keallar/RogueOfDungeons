#include "Buttons.h"
#include "Managers.h"
#include "Inventory.h"
#include <iostream>

MouseButton::MouseButton()
{

}

void MouseButton::buttonsForItemsInInv(SDL_Event eventForItemsInInv)
{
	switch (eventForItemsInInv.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		SDL_GetMouseState(&mouseCoords.x, &mouseCoords.y);

		for (int i = 0; i < 16; i++)
		{
			if (InputManager::MouseInArea((780 + 36 * (i % 4)), (100 + ((i / 4) * 50)), 32, 32, mouseCoords.x, mouseCoords.y) &&
				Inventory::inventoryFace[i] != -1 && FlagManager::flagInv == 1)
			{
				std::cout << "Item " + i << std::endl;
				FlagManager::flagEquip = i;
			}
		}
	}
}