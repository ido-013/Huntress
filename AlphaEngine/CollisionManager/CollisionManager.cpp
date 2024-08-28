#include "CollisionManager.h"
#include "AEEngine.h"
#include "../Utils/Utils.h"

CollisionManager::CollisionManager() 
{

}

CollisionManager::~CollisionManager()
{

}

bool CollisionManager::isCollisionPointTri(ColliderComp* a, ColliderComp* b) const
{ 
	if (!isCollisionPointAABB(a, b)) return false;

	float aX = a->GetPos().x;
	float aY = a->GetPos().y;

	float bX = b->GetPos().x;
	float bY = b->GetPos().y;
	float bW = b->GetScale().x / 2;
	float bH = b->GetScale().y / 2;

	float grad;

	if (b->GetOwner()->type == GameObject::RightTri)
		grad = bH / bW;
	else
		grad = -bH / bW;

	if ((grad * aX) + bY - (grad * bX) < aY) return false;

	return true;
}

bool CollisionManager::isCollisionPointAABB(ColliderComp* a, ColliderComp* b) const
{
	float aX = a->GetPos().x;
	float aY = a->GetPos().y;

	float bX = b->GetPos().x;
	float bY = b->GetPos().y;
	float bW = b->GetScale().x / 2;
	float bH = b->GetScale().y / 2;

	if (aX > bX + bW) return false;
	if (aX < bX - bW) return false;
	if (aY > bY + bH) return false;
	if (aY < bY - bH) return false;

	return true;
}

bool CollisionManager::isCollisionAABBAABB(ColliderComp* a, ColliderComp* b) const
{
	float aX = a->GetPos().x;
	float aY = a->GetPos().y;
	float aW = a->GetScale().x / 2;
	float aH = a->GetScale().y / 2;

	float bX = b->GetPos().x;
	float bY = b->GetPos().y;
	float bW = b->GetScale().x / 2;
	float bH = b->GetScale().y / 2;

	if (aX - aW > bX + bW) return false;
	if (bX - bW > aX + aW) return false;
	if (aY - aH > bY + bH) return false;
	if (bY - bH > aY + aH) return false;

	return true;
}

bool CollisionManager::isCollisionCircleCircle(ColliderComp* a, ColliderComp* b) const
{
	float aX = a->GetPos().x;
	float aY = a->GetPos().y;
	float aR = a->GetScale().x / 2;

	float bX = b->GetPos().x;
	float bY = b->GetPos().y;
	float bR = b->GetScale().y / 2;

	return ((aR + bR) * (aR + bR)) >= GetSqDistance(aX, aY, bX, bY);
}

bool CollisionManager::PointTriCheck(ColliderComp* a, ColliderComp* b)
{
	EventManager& em = EventManager::GetInstance();

	if (a->GetOwner()->type == GameObject::Point && (b->GetOwner()->type == GameObject::LeftTri || b->GetOwner()->type == GameObject::RightTri))
	{
		if (isCollisionPointTri(a, b))
		{
			em.AddEvent<CollisionEvent>(a, b);
			em.AddEvent<CollisionEvent>(b, a);
		}

		return true;
	}

	else if (b->GetOwner()->type == GameObject::Point && (a->GetOwner()->type == GameObject::LeftTri || a->GetOwner()->type == GameObject::RightTri))
	{
		if (isCollisionPointTri(b, a))
		{
			em.AddEvent<CollisionEvent>(a, b);
			em.AddEvent<CollisionEvent>(b, a);
		}

		return true;
	}

	return false;
}

bool CollisionManager::PointAABBCheck(ColliderComp* a, ColliderComp* b)
{
	EventManager& em = EventManager::GetInstance();

	if (a->GetOwner()->type == GameObject::Point && b->GetOwner()->type == GameObject::Square)
	{
		if (isCollisionPointAABB(a, b))
		{
			em.AddEvent<CollisionEvent>(a, b);
			em.AddEvent<CollisionEvent>(b, a);
		}

		return true;
	}

	else if (b->GetOwner()->type == GameObject::Point && a->GetOwner()->type == GameObject::Square)
	{
		if (isCollisionPointAABB(b, a))
		{
			em.AddEvent<CollisionEvent>(a, b);
			em.AddEvent<CollisionEvent>(b, a);
		}

		return true;
	}

	return false;
}

bool CollisionManager::AABBAABBCheck(ColliderComp* a, ColliderComp* b)
{
	EventManager& em = EventManager::GetInstance();

	if (a->GetOwner()->type == GameObject::Square && b->GetOwner()->type == GameObject::Square)
	{
		if (isCollisionAABBAABB(a, b))
		{
			em.AddEvent<CollisionEvent>(a, b);
			em.AddEvent<CollisionEvent>(b, a);
		}

		return true;
	}

	return false;
}

void CollisionManager::AddCollider(ColliderComp* trans)
{
	colliderList.push_back(trans);
}

void CollisionManager::DelCollider(ColliderComp* trans)
{
	for (auto it = colliderList.begin(); it != colliderList.end(); it++)
	{
		if (*it == trans)
		{
			colliderList.erase(it);
			break;
		}
	}
}

void CollisionManager::Update()
{
	if (colliderList.empty())
		return;

	EventManager& em = EventManager::GetInstance();

	for (int i = 0; i < colliderList.size() - 1; i++)
	{
		for (int j = i + 1; j < colliderList.size(); j++)
		{
			ColliderComp* a = colliderList[i];
			ColliderComp* b = colliderList[j];

			if (PointTriCheck(a, b)) continue;
			if (PointAABBCheck(a, b)) continue;
			if (AABBAABBCheck(a, b)) continue;
		}
	}
}
