#include "EnemyComp.h"
#include "../Components/TransformComp.h"
#include "../Components/RigidbodyComp.h"
#include "../Combat/Combat.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Utils/Size.h"

EnemyComp::EnemyComp(GameObject* _owner) : LogicComponent(_owner), data(*new Data::EnemyData)
{
}

EnemyComp::~EnemyComp()
{
}
int EnemyComp::GetMovegauge()
{
	return movementGauge;
}

void EnemyComp::RandomMove() // ����ü�� ���� �ʴ´ٰ� ������ ���
{
	TransformComp* t = owner->GetComponent<TransformComp>();
	if (!t) return;

	RigidbodyComp* r = owner->GetComponent<RigidbodyComp>();
	if (!r) return;

	r->SetVelocityX(0);

	if (isBack && movementGauge > 0 && moveState)
	{
		t->SetScale({ -abs(t->GetScale().x), t->GetScale().y });
		r->SetVelocityX(-speed);
		movementGauge--;
		if (t->GetPos().x >= windowWidthHalf) // �ڷ� �̵��� ���̻� �Ұ����ϴٰ� �Ǵܵ� ���
		{
			isBack = false;
		}
	}
	else if (!isBack && movementGauge > 0 && moveState)
	{
		t->SetScale({ abs(t->GetScale().x), t->GetScale().y });
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
			isBack = true;
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
	}
}

json EnemyComp::SaveToJson()
{
	json data;
	data["type"] = TypeName;

	json compData;
	
	data["compData"] = compData;

	return data;
}

BaseRTTI* EnemyComp::CreateEnemyComponent(GameObject* owner)
{
	BaseRTTI* p = new EnemyComp(owner);
	owner->AddComponent<EnemyComp>(static_cast<BaseComponent*>(p));
	return p;
}

