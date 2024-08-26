#include "EventManager.h"
template<typename T>
inline void EventManager::AddEvent(Entity* _src, Entity* _dst)
{
	if (_dst != nullptr)
	{
		Event* event = new T(_src, _dst);
		allEvents.push(event);
	}
	else
	{
		for (auto& it : entityList)
		{
			Event* event = new T(_src, it);
			allEvents.push(event);
		}
	}
}

template<typename T>
inline void EventManager::AddEvent(Entity* _src, Entity::Type type)
{
	for (auto& it : entityList)
	{
		if (it->GetType() == type)
		{
			Event* event = new T(_src, it);
			allEvents.push(event);
		}
	}
}
