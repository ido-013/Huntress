#include "CollisionManager.h"
#include "AEEngine.h"
#include "../Utils/Utils.h"

CollisionManager::CollisionManager() {}

CollisionManager::~CollisionManager()
{

}

bool CollisionManager::isCollisionAABBAABB(TransformComp* a, TransformComp* b) const
{
	double aX = a->GetPos().x;
	double aY = a->GetPos().y;
	double aW = a->GetScale().x / 2;
	double aH = a->GetScale().y / 2;

	double bX = b->GetPos().x;
	double bY = b->GetPos().y;
	double bW = b->GetScale().x / 2;
	double bH = b->GetScale().y / 2;

	if (aX - aW > bX + bW) return false;
	if (bX - bW > aX + aW) return false;
	if (aY - aH > bY + bH) return false;
	if (bY - bH > aY + aH) return false;

	return true;
}

bool CollisionManager::isCollisionCircleCircle(TransformComp* a, TransformComp* b) const
{
	double aX = a->GetPos().x;
	double aY = a->GetPos().y;
	double aR = a->GetScale().x / 2;

	double bX = b->GetPos().x;
	double bY = b->GetPos().y;
	double bR = b->GetScale().y / 2;

	return ((aR + bR) * (aR + bR)) >= GetSqDistance(aX, aY, bX, bY);
}

void CollisionManager::AddTrans(TransformComp* trans)
{
	transformList.push_back(trans);
}

void CollisionManager::DelTrans(TransformComp* trans)
{
	for (auto it = transformList.begin(); it != transformList.end(); it++)
	{
		if (*it == trans)
		{
			transformList.erase(it);
			break;
		}
	}
}

void CollisionManager::Update()
{
	if (transformList.empty())
		return;

	EventManager& em = EventManager::GetInstance();

	for (int i = 0; i < transformList.size() - 1; i++)
	{
		for (int j = i + 1; j < transformList.size(); j++)
		{
			TransformComp* a = transformList[i];
			TransformComp* b = transformList[j];

			if (isCollisionAABBAABB(a, b))
			{
				em.AddEvent<CollisionEvent>(a->GetOwner(), b->GetOwner());
				em.AddEvent<CollisionEvent>(b->GetOwner(), a->GetOwner());
			}
		}
	}
}
