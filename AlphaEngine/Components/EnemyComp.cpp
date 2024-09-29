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
	//owner->GetComponent<AudioComp>()->playAudio(0, "./Assets/Audio/weapon-arrow-shot.mp3", 0.3f);
}

bool EnemyComp::isCliff()
{
	return cliffChecker->GetComponent<ColliderComp>()->isCollision;
}

void EnemyComp::StunEffect()
{
	static float timer = 0;
	static bool preStun = false;

	if (preStun != stun)
	{
		if (stun == false)
		{
			timer = 0;
		}
		else
		{
			owner->GetComponent<AudioComp>()->playAudio(0, "./Assets/Audio/electric_zap_001.mp3", 1.f);
		}

		preStun = stun;
	}

	if (stun)
	{
		timer += (float)AEFrameRateControllerGetFrameTime();

		SpriteComp* s = owner->GetComponent<SpriteComp>();

		if (timer < 0.1f)
		{
			s->SetAlpha(0.3f);
		}

		else if (timer < 0.2f)
		{
			s->SetAlpha(1.f);
		}

		else if (timer < 0.3f)
		{
			s->SetAlpha(0.3f);
		}

		else
		{
			s->SetAlpha(1.f);
			stun = false;
		}
	}
}

void EnemyComp::BigEffect()
{
	static float timer = 0;
	static bool preBig = false;

	if (preBig != big)
	{
		if (big == false)
		{
			timer = 0;
		}
		else
		{
			owner->GetComponent<AudioComp>()->playAudio(0, "./Assets/Audio/power_up_grab.mp3", 0.3f, 0.6f);
		}

		preBig = big;
	}

	if (big)
	{
		timer += (float)AEFrameRateControllerGetFrameTime();

		TransformComp* t = owner->GetComponent<TransformComp>();
		ColliderComp* c = owner->GetComponent<ColliderComp>();
		
		if (timer < 0.1f)
		{
			t->SetScale({ 90, 90 });
			t->SetPos({ t->GetPos().x, t->GetPos().y + 30 });
			c->SetCollider();
		}

		else if (timer < 0.2f)
		{
			t->SetScale({ 50, 50 });
			t->SetPos({ t->GetPos().x, t->GetPos().y - 30 });
			c->SetCollider();
		}

		else if (timer < 0.3f)
		{
			t->SetScale({ 90, 90 });
			t->SetPos({ t->GetPos().x, t->GetPos().y + 30 });
			c->SetCollider();
		}

		else if (timer < 0.4f)
		{
			t->SetScale({ 50, 50 });
			t->SetPos({ t->GetPos().x, t->GetPos().y - 30 });
			c->SetCollider();
		}

		else
		{
			t->SetScale({ 90, 90 });
			t->SetPos({ t->GetPos().x, t->GetPos().y + 30 });
			c->SetCollider();
			big = false;
		}
	}
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
		return;
	}

	else if (CombatComp::turn == CombatComp::ENEMYTURN && Projectile::isLaunchProjectile)
	{
		a->SetAnimation(false, 1, "arrowShot");
		ad->playAudio(0, "./Assets/Audio/bow-release.mp3", 1.f);
	}

	else if (CombatComp::turn == CombatComp::ENEMYTURN && CombatComp::isReadyLaunch)
	{
		a->SetAnimation(false, 1, "arrowReady");
		ad->playAudio(0, "./Assets/Audio/bow-loading.mp3", 1.f);
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
		BigEffect();
		StunEffect();

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

