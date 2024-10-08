#pragma once
#include <map>
#include <list>
#include <string>

#define ITEM_LIMIT 3

static std::string subtitleOfItem[12] {
	"Using Bigger and Bigger", 
	"Uses Stun Arrow",
	"Uses Straight Arrow",
	"Uses Show orbit",
	"This item is not enough",
	"Purchases Bigger and Bigger",
	"Purchases Stun Arrow",
	"Purchases Straight Arrow",
	"Purchases Show orbit",
	"Items has reached its limit",
	"This item is already used",
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