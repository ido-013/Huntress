#include "Inventory.h"
#include <iostream>
#include <string>

void Inventory::InitInventory()
{
	items.insert({ Item::Big,		0 });
	items.insert({ Item::Stun,		0 });
	items.insert({ Item::Straight,	0 });
	items.insert({ Item::Orbit,		0 }); 
}
int Inventory::GetItemCount(Item item)
{
	if (items.empty())
		return 0;
	return items.find(item)->second;
}
void Inventory::SetItemCount(Item item, int itemCount)
{
	if (items.empty())
		return;
	items.find(item)->second = itemCount;
}


bool Inventory::UseItem(Item item)
{
	if (GetItemCount(item) > 0)
	{
		//Item 썻다는 자막
		std::cout << subtitleOfItem[item] << std::endl;
		SetItemCount(item, GetItemCount(item) - 1);
		return true;
	}
	//Item 없다는 자막
	std::cout << subtitleOfItem[4] << std::endl;
	return false;
}

bool Inventory::AddItem(Item item)
{
	if (GetItemCount(item) >= ITEM_LIMIT)
	{
		//이미 최대 한도 만큼 가지고 있다는 뜻
		std::cout << subtitleOfItem[9] << std::endl;
		return false;
	}
	//Item 을 추가했다는 자막
	SetItemCount(item, GetItemCount(item) + 1);
	std::cout << subtitleOfItem[item + 5] << std::endl;
	return true;
}

void Inventory::RemoveInventory()
{
	items.clear();
}
