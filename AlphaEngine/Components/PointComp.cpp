#include "PointComp.h"
#include <string>
#include "TransformComp.h"
#include "RigidbodyComp.h"
#include "SpriteComp.h"
#include "../Event/CollisionEvent.h"
#include "../Utils/Utils.h"
#include "../GSM/GameStateManager.h"
#include "../Prefab/Prefab.h"
#include "../GameObjectManager/GameObjectManager.h"

PointComp::PointComp(GameObject* _owner) : LogicComponent(_owner)
{

}

PointComp::~PointComp()
{
	
}

void PointComp::Update()
{
	TransformComp* t = owner->GetComponent<TransformComp>();
	if (!t) return;

	RigidbodyComp* r = owner->GetComponent<RigidbodyComp>();
	if (!r) return;

	SpriteComp* s = owner->GetComponent<SpriteComp>();
	if (!s) return;

	speed = 200;

	r->SetVelocityX(0);

	if (AEInputCheckCurr(AEVK_A))
	{
		r->SetVelocityX(-speed);
	}

	if (AEInputCheckCurr(AEVK_D))
	{
		r->SetVelocityX(speed);
	}

	/*r->SetVelocityY(0);

	if (AEInputCheckCurr(AEVK_W))
	{
		r->SetVelocityY(speed);
	}

	if (AEInputCheckCurr(AEVK_S))
	{
		r->SetVelocityY(-speed);
	}*/
}

void PointComp::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		auto it = compData->find("speed");
		speed = it.value();
	}
}

json PointComp::SaveToJson()
{
	json data;
	data["type"] = TypeName;

	json compData;
	compData["speed"] = speed;
	data["compData"] = compData;

	return data;
}

BaseRTTI* PointComp::CreatePointComponent(GameObject* owner)
{
	BaseRTTI* p = new PointComp(owner);
	owner->AddComponent<PointComp>(static_cast<BaseComponent*>(p));
	return p;
}
