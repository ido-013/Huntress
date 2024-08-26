#pragma once
#include <list>
#include <string>
#include "../GameObject/GameObject.h"

class GameObjectManager
{
private:
	std::list<GameObject*> objects;

	GameObjectManager();
	~GameObjectManager();

	GameObjectManager(const GameObjectManager&) = delete;
	GameObjectManager& operator =(const GameObjectManager&) = delete;

	static GameObjectManager* ptr;

public:
	std::list<GameObject*>& GetAllObjects() { return objects; }

	static GameObjectManager& GetInstance()
	{
		static GameObjectManager instance;
		return instance;
	}

	void AddObject(GameObject* obj);
	void RemoveObject(GameObject* obj);
	void RemoveAllObject();
};