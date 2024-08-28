#include "GameObject.h"
#include "../ComponentManager/BaseComponent.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Event/CollisionEvent.h"
#include "../Components/PlayerComp.h"
#include "../Components/AudioComp.h"
#include "../EventManager/EventManager.h"


GameObject::GameObject()
{
	GameObjectManager::GetInstance().AddObject(this);
	EventManager::GetInstance().AddEntity(this);
}

GameObject::GameObject(std::string str)
{
	GameObjectManager::GetInstance().InsertObject(this, str);
	EventManager::GetInstance().AddEntity(this);
}

GameObject::~GameObject()
{
	for (auto it : component)
	{
		if (it.second)
			delete it.second;	
	}

	component.clear();
	EventManager::GetInstance().RemoveEntity(this);
}

void GameObject::OnEvent(Event* event)
{

}

BaseComponent* GameObject::GetBase(std::string typeName)
{
	auto it = component.find(typeName);
	if (it != component.end())
	{
		return it->second;
	}

	return nullptr;
}
