#pragma once

#include <map>

#define ITEM_LIMIT 3

class InventoryComp
{
public:
	enum Item
	{
		Big,
		Stun,
		Straight,
		Orbit
	};
	std::map<Item, int> items;
	void InitInventory();
};