#include "EnemyComp.h"
#include "../Components.h"
#include "../Combat/Combat.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Utils/Size.h"

EnemyComp::EnemyComp(GameObject* _owner) : LogicComponent(_owner), enemyData(new Data::EnemyData)
{
	cliffChecker = new GameObject();
	cliffChecker->type = GameObject::Checker;

	TransformComp* t = cliffChecker->AddComponent<TransformComp>();

	t->SetScale({ 5, 200 });

	cliffChecker->AddComponent<ColliderComp>();
}

EnemyComp::~EnemyComp()
{
	delete enemyData;
}

int EnemyComp::GetMovegauge()
{
	return movementGauge;
}

void EnemyComp::AddHp(float value)
{
	enemyData->hp += value;

	if (enemyData->hp < 0)
	{
		enemyData->hp = 0;
	}

	owner->GetComponent<AnimatorComp>()->SetAnimation(false, 1, "takeDamage");
	owner->GetComponent<AudioComp>()->playAudio(0, "./Assets/Audio/weapon-arrow-shot.mp3", 0.3f);
}

bool EnemyComp::isCliff()
{
	return cliffChecker->GetComponent<ColliderComp>()->isCollision;
}

void EnemyComp::RandomMove() // 투사체가 맞지 않는다고 판정된 경우
{
	TransformComp* pt = GameObjectManager::GetInstance().GetObj("player")->GetComponent<TransformComp>();

	TransformComp* t = owner->GetComponent<TransformComp>();
	RigidbodyComp* r = owner->GetComponent<RigidbodyComp>();
	AnimatorComp* a = owner->GetComponent<AnimatorComp>();

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
	TransformComp* t = owner->GetComponent<TransformComp>();
	if (!t) return;

	RigidbodyComp* r = owner->GetComponent<RigidbodyComp>();
	if (!r) return;

	AnimatorComp* a = owner->GetComponent<AnimatorComp>();
	if (!a) return;

	AudioComp* ad = owner->GetComponent<AudioComp>();
	if (!ad) return;

	if (enemyData->hp == 0)
	{
		a->SetAnimation(false, 1, "die");
	}

	else if (CombatComp::turn == CombatComp::ENEMYTURN && Projectile::isLaunchProjectile)
	{
		a->SetAnimation(false, 1, "arrowShot");
		ad->playAudio(0, "./Assets/Audio/bow-release.mp3");
	}

	else if (CombatComp::turn == CombatComp::ENEMYTURN && CombatComp::isReadyLaunch)
	{
		a->SetAnimation(false, 1, "arrowReady");
		ad->playAudio(0, "./Assets/Audio/bow-loading.mp3");
	}

	else if (r->GetVelocityX() == 0)
	{
		a->SetAnimation(true, 1, "idle");
	}

	else
	{
		a->SetAnimation(true, 2, "walk");
	}

	if (CombatComp::isCombat)
	{
		if (isMove)
		{
			RandomMove();
			isMove = false;
		}

		if (movementGauge <= 0 || !isCliff())
		{
			moveState = false;
			RandomMove();
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

		if (t->GetScale().x < 0)
		{
			cliffChecker->GetComponent<TransformComp>()->SetPos({ t->GetPos().x - 50, t->GetPos().y });
		}

		else
		{
			cliffChecker->GetComponent<TransformComp>()->SetPos({ t->GetPos().x + 50, t->GetPos().y });
		}

		cliffChecker->AddComponent<ColliderComp>()->SetCollider();
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

