#include "ColliderComp.h"
#include "TransformComp.h"
#include "RigidbodyComp.h"
#include "../CollisionManager/CollisionManager.h"
#include "../EventManager/EventManager.h"

ColliderComp::ColliderComp(GameObject* _owner) : EngineComponent(_owner), pos(), scale(), rot(0), vertices()
{
	CollisionManager::GetInstance().AddCollider(this);
	EventManager::GetInstance().AddEntity(this);

	SetCollider();
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
		RigidbodyComp* r = owner->GetComponent<RigidbodyComp>();

		if (r)
		{
			r->oppoCollider.push(static_cast<ColliderComp*>(e->src));
			r->colliderType[static_cast<ColliderComp*>(e->src)->GetOwner()->type] = true;
		}
	}
}

void ColliderComp::SetPos(const AEVec2& otherPos)
{
	this->pos = otherPos;

	SetVertices();
}

void ColliderComp::SetScale(const AEVec2& otherScale)
{
	this->scale = otherScale;

	SetVertices();
}

void ColliderComp::SetRot(const float& otherRot)
{
	this->rot = otherRot;
}

void ColliderComp::SetCollider()
{
	TransformComp* t = owner->GetComponent<TransformComp>();
	if (!t) return;

	pos.x = t->GetPos().x;
	pos.y = t->GetPos().y;

	scale.x = t->GetScale().x;
	scale.y = t->GetScale().y;

	rot = t->GetRot();

	SetVertices();
}

void ColliderComp::SetCollider(float posX, float posY, float scaleX, float scaleY, float _rot)
{
	pos.x = posX;
	pos.y = posY;

	scale.x = scaleX;
	scale.y = scaleY;

	rot = _rot;

	SetVertices();
}

void ColliderComp::SetVertices()
{
	float x = pos.x;
	float y = pos.y;
	float w = scale.x / 2;
	float h = scale.y / 2;

	vertices[0] = { x - w, y + h, 1.f };
	vertices[1] = { x + w, y + h, 1.f };
	vertices[2] = { x + w, y - h, 1.f };
	vertices[3] = { x - w, y - h, 1.f };

	const AEMtx33& mat = owner->GetComponent<TransformComp>()->GetMatrix();

	for (int i = 0; i < 4; i++)
	{
		vertices[i] = mat * vertices[i];
	}
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

