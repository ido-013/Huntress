#include "ColliderComp.h"
#include "TransformComp.h"
#include "../CollisionManager/CollisionManager.h"
#include "../EventManager/EventManager.h"

ColliderComp::ColliderComp(GameObject* _owner) : EngineComponent(_owner), pos(), scale(), rot(0), isCollision(false)
{
	TransformComp* t = _owner->GetComponent<TransformComp>();

	if (t)
	{
		pos.x = t->GetPos().x;
		pos.y = t->GetPos().y;

		scale.x = t->GetScale().x;
		scale.y = t->GetScale().y;
	}

	else
	{
		pos.x = 0;
		pos.y = 0;

		scale.x = 1;
		scale.y = 1;
	}

	CollisionManager::GetInstance().AddCollider(this);
	EventManager::GetInstance().AddEntity(this);
}

ColliderComp::~ColliderComp()
{
	CollisionManager::GetInstance().DelCollider(this);
	EventManager::GetInstance().DelEntity(this);
}

void ColliderComp::Update()
{

}

void ColliderComp::OnEvent(Event* e)
{
	if (dynamic_cast<CollisionEvent*>(e) != nullptr)
	{
		isCollision = true;
		//colliderList.push_back(e->src);
	}
}

void ColliderComp::SetPos(const AEVec2& otherPos)
{
	this->pos = otherPos;
}

void ColliderComp::SetScale(const AEVec2& otherScale)
{
	this->scale = otherScale;
}

void ColliderComp::SetRot(const float& otherRot)
{
	this->rot = otherRot;
}

void ColliderComp::LoadFromJson(const json& data)
{
	// Check how you saved, load from there
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		auto p = compData->find("position");
		pos.x = p->begin().value();
		pos.y = (p->begin() + 1).value();

		auto s = compData->find("scale");
		scale.x = s->begin().value();
		scale.y = (s->begin() + 1).value();

		auto r = compData->find("rotation");
		rot = r.value();
	}
}

json ColliderComp::SaveToJson()
{
	json data;

	data["type"] = TypeName;

	json compData;
	compData["position"] = { pos.x, pos.y };
	compData["scale"] = { scale.x, scale.y };
	compData["rotation"] = rot;

	data["compData"] = compData;
	return data;
}

BaseRTTI* ColliderComp::CreateColliderComponent(GameObject* owner)
{
	BaseRTTI* p = new ColliderComp(owner);

	owner->AddComponent<ColliderComp>(static_cast<BaseComponent*>(p));

	return p;
}

