#pragma once
#include <map>
#include <list>
#include <string>

#define ITEM_LIMIT 3

static std::string subtitleOfItem[12] {
	"Using Bigger and Bigger", 
	"Using Stun Arrow",
	"Using Straight Arrow",
	"Using Show orbit",
	"Can't use it now",
	"Purchasing Bigger and Bigger",
	"Purchasing Stun Arrow",
	"Purchasing Straight Arrow",
	"Purchasing Show orbit",
	"Items has reached its limit",
	"Already buy it now",
	"Already used items"
};

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