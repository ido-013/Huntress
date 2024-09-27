#include "Inventory.h"
#include <iostream>
#include <string>
void Inventory::InitInventory()
{
	items.insert({ Item::Big, 0 });
	items.insert({ Item::Stun, 0 });
	items.insert({ Item::Straight, 0 });
	items.insert({ Item::Orbit, 0 });
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
std::string subtitleOfItem[10] =
{
	"Use Bigger and Bigger",
	"Use Stun Arrow",
	"Use Straight Arrow",
	"Use Show orbit",
	"This item is not enough",
	"Buy Bigger and Bigger",
	"Buy Stun Arrow",
	"Buy Straight Arrow",
	"Buy Show orbit",
	"This item is enough"
};

bool Inventory::UseItem(Item item)
{
	if (GetItemCount(item) > 0)
	{
		//Item ���ٴ� �ڸ�
		std::cout << subtitleOfItem[item] << std::endl;
		SetItemCount(item, GetItemCount(item) - 1);
		return true;
	}
	//Item ���ٴ� �ڸ�
	std::cout << subtitleOfItem[4] << std::endl;
	return true;
}

bool Inventory::AddItem(Item item)
{
	if (GetItemCount(item) >= ITEM_LIMIT)
	{
		//�̹� �ִ� �ѵ� ��ŭ ������ �ִٴ� ��
		std::cout << subtitleOfItem[9] << std::endl;
		return false;
	}
	//Item �� �߰��ߴٴ� �ڸ�
	SetItemCount(item, GetItemCount(item) + 1);
	std::cout << subtitleOfItem[item + 5] << std::endl;
	return true;
}

void Inventory::RemoveInventory()
{
	items.clear();
}
