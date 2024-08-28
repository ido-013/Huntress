#pragma once
#include <vector>
#include "../Components/ColliderComp.h"
#include "../EventManager/EventManager.h"
#include "../Event/CollisionEvent.h"

class CollisionManager
{
private:
	CollisionManager();

	CollisionManager(const CollisionManager& other) = delete;
	const CollisionManager& operator=(const CollisionManager& other) = delete;
	~CollisionManager();

	static CollisionManager* ptr;

	std::vector<ColliderComp*> colliderList;

	bool isCollisionPointTri(ColliderComp*, ColliderComp*) const;
	bool isCollisionPointAABB(ColliderComp*, ColliderComp*) const;
	bool isCollisionAABBAABB(ColliderComp*, ColliderComp*) const;
	bool isCollisionCircleCircle(ColliderComp*, ColliderComp*) const;

	bool PointTriCheck(ColliderComp*, ColliderComp*);
	bool PointAABBCheck(ColliderComp*, ColliderComp*);
	bool AABBAABBCheck(ColliderComp*, ColliderComp*);

public:
	static CollisionManager& GetInstance()
	{
		static CollisionManager instance;
		return instance;
	}

	void AddCollider(ColliderComp* trans);
	void DelCollider(ColliderComp* trans);

	void Update();
};