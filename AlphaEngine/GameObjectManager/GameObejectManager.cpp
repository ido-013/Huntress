#include "GameObjectManager.h"

int GameObjectManager::counter = 0;

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	for (auto it : objects)
	{
		if (it.first)
			delete it.first;
	}
}

void GameObjectManager::InsertObject(GameObject* obj, std::string str)
{
	objects.insert({ obj, str });
}

void GameObjectManager::AddObject(GameObject* obj)
{
	objects.insert({ obj, std::to_string(GameObjectManager::counter++) });
}

GameObject* GameObjectManager::GetObj(const std::string& id) {
	// my_Obj의 모든 요소를 순회하며 ID를 찾음
	for (const auto& pair : objects) {
		if (pair.second == id) {
			return pair.first;
		}
	}
	// 일치하는 ID가 없을 경우 nullptr 반환
	return nullptr;
}

GameObject* GameObjectManager::GetLastObject()
{
	if (!objects.empty())
	{
		auto it = objects.end();
		--it;
		auto key = it->first;
		return key;
	}
	return nullptr;
}
void GameObjectManager::RemoveObject(GameObject* obj)
{
	for (auto it = objects.begin()->first; it != objects.end()->first; it++)
	{
		if (it == obj)
		{
			delete it;
			objects.erase(it);
			return;
		}
	}
}

void GameObjectManager::RemoveAllObject()
{
	for (auto it = objects.begin()->first; it != objects.end()->first; it++)
	{
		delete it;
	}
	objects.clear();
}
