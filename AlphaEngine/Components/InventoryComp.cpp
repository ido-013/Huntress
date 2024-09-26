#include "InventoryComp.h"

void InventoryComp::InitInventory()
{
	items.insert({ Item::Big, 0 });
	items.insert({ Item::Stun, 0 });
	items.insert({ Item::Straight, 0 });
	items.insert({ Item::Orbit, 0 });
}
