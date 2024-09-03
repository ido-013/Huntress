#include "PlayerComp.h"
#include <string>
#include "TransformComp.h"
#include "RigidbodyComp.h"
#include "SpriteComp.h"
#include "../Event/CollisionEvent.h"
#include "../Utils/Utils.h"
#include "../GSM/GameStateManager.h"
#include "../Prefab/Prefab.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Particle/Particle.h"
#include "../Combat/Combat.h"
#include "../Combat/Projectile.h"

PlayerComp::PlayerComp(GameObject* _owner) : LogicComponent(_owner)
{
	
}

PlayerComp::~PlayerComp()
{
}

void PlayerComp::Update()
{
	TransformComp* t = owner->GetComponent<TransformComp>();
	if (!t) return;

	RigidbodyComp* r = owner->GetComponent<RigidbodyComp>();
	if (!r) return;

	SpriteComp* s = owner->GetComponent<SpriteComp>();
	if (!s) return;

	r->SetVelocityX(0);

	if (AEInputCheckCurr(AEVK_A) && movementGauge > 0)
	{
		t->SetScale({ -abs(t->GetScale().x), t->GetScale().y });
		r->SetVelocityX(-speed);
		movementGauge--;
	}

	if (AEInputCheckCurr(AEVK_D) && movementGauge > 0)
	{
		t->SetScale({ abs(t->GetScale().x), t->GetScale().y });
		r->SetVelocityX(speed);
		movementGauge--;
	}

	if (movementGauge <= 0)
	{
		moveState = false;
	}

	if (!turn)
	{
		movementGauge = maxMovementGauge;
	}

}

float PlayerComp::GetMovegauge()
{
	return movementGauge;
}

float PlayerComp::GetMovegauge()
{
	return movementGauge;
}

void PlayerComp::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		auto it = compData->find("speed");
		speed = it.value();
	}
}

json PlayerComp::SaveToJson()
{
	json data;
	data["type"] = TypeName;

	json compData;
	compData["speed"] = speed;
	data["compData"] = compData;

	return data;
}


BaseRTTI* PlayerComp::CreatePlayerComponent(GameObject* owner)
{
	BaseRTTI* p = new PlayerComp(owner);
	owner->AddComponent<PlayerComp>(static_cast<BaseComponent*>(p));
	return p;
}
