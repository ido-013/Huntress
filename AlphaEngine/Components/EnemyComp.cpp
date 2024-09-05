#include "EnemyComp.h"
#include "../Components/TransformComp.h"
#include "../Components/RigidbodyComp.h"
#include "../Combat/Combat.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Utils/Size.h"

EnemyComp::EnemyComp(GameObject* _owner) : LogicComponent(_owner), enemyData(new Data::EnemyData)
{
}

EnemyComp::~EnemyComp()
{
	delete enemyData;
}

int EnemyComp::GetMovegauge()
{
	return movementGauge;
}

void EnemyComp::RandomMove() // 투사체가 맞지 않는다고 판정된 경우
{
	TransformComp* pt = GameObjectManager::GetInstance().GetObj("player")->GetComponent<TransformComp>();

	TransformComp* t = owner->GetComponent<TransformComp>();
	if (!t) return;

	RigidbodyComp* r = owner->GetComponent<RigidbodyComp>();
	if (!r) return;

	r->SetVelocityX(0);

	if (t->GetPos().x < pt->GetPos().x) // 플레이어보다 -x에 있다고 판단되는 경우
	{
		isGo = false;
	}
	else
	{
		isGo = true;
	}

	if (isGo && movementGauge > 0 && moveState)
	{
		t->ReverseX(0);
		r->SetVelocityX(-speed);
		movementGauge--;
	}
	else if (!isGo && movementGauge > 0 && moveState)
	{
		t->ReverseX(1);
		r->SetVelocityX(speed);
		movementGauge--;
	}
}

void EnemyComp::Update()
{
	if (CombatComp::isCombat)
	{
		if (isMove)
		{
			RandomMove();
			isMove = false;
		}

		if (movementGauge <= 0)
		{
			moveState = false;
		}

		if (CombatComp::turn == CombatComp::TURN::ENEMYTURN && turnTemp)
		{
			turnTemp = false;
			movementGauge = maxMovementGauge;
			moveState = true;
		}
		else if (CombatComp::turn == CombatComp::TURN::PLAYERTURN)
		{
			isGo = true;
			turnTemp = true;
		}

		if (CombatComp::turn == CombatComp::TURN::ENEMYTURN)
		{
			GameObjectManager::GetInstance().GetObj("directionArrow")->GetComponent<CombatComp>()->data.moveGauge = movementGauge;
		}
	}
}

void EnemyComp::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		auto it = compData->find("speed");
		speed = it.value();

		it = compData->find("maxMovementGauge");
		maxMovementGauge = it.value();
	}
}

json EnemyComp::SaveToJson()
{
	json data;
	data["type"] = TypeName;

	json compData;
	compData["speed"] = speed;
	compData["maxMovementGauge"] = maxMovementGauge;

	data["compData"] = compData;

	return data;
}

BaseRTTI* EnemyComp::CreateEnemyComponent(GameObject* owner)
{
	BaseRTTI* p = new EnemyComp(owner);
	owner->AddComponent<EnemyComp>(static_cast<BaseComponent*>(p));
	return p;
}

