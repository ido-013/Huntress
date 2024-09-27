#pragma once
#include <map>

#define ITEM_LIMIT 3

struct Inventory
{
	enum Item { Big, Stun, Straight, Orbit };
	bool isGBY;
	std::map<Item, int> items;
	void InitInventory();
	int GetItemCount(Item item);
	void SetItemCount(Item item, int itemCount);
	bool UseItem(Item item);
	bool AddItem(Item item);
	void RemoveInventory();
};