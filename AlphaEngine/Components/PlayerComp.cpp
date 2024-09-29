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

PlayerComp::PlayerComp(GameObject* _owner) : LogicComponent(_owner), playerData(new Data::PlayerData)
{
	GBYobj = new GameObject;
	TransformComp* t = GBYobj->AddComponent<TransformComp>();
	t->SetScale({ 100.f, 100.f });

	SpriteComp* s = GBYobj->AddComponent<SpriteComp>();
	s->SetTexture("./Assets/Character/SCS.jpg");
	//s->SetTexture("./Assets/Character/DSH.jpg");
	s->SetAlpha(0.f);
	s->SetColor(0, 0, 0);
}

PlayerComp::~PlayerComp()
{
	delete playerData;
}

void PlayerComp::Update()
{
	TransformComp* t = owner->GetComponent<TransformComp>();
	if (!t) return;

	RigidbodyComp* r = owner->GetComponent<RigidbodyComp>();
	if (!r) return;

	AnimatorComp* a = owner->GetComponent<AnimatorComp>();
	if (!a) return;

	AudioComp* ad = owner->GetComponent<AudioComp>();
	if (!ad) return;

	r->SetVelocityX(0);

	if(CombatComp::isCombat)
	{
		if (playerData->hp == 0)
		{
			a->SetAnimation(false, 1, "die");
			return;
		}

		else if (AEInputCheckCurr(AEVK_A) && movementGauge > 0 && moveState)
		{
			t->ReverseX(0);
			r->SetVelocityX(-speed);
			a->SetAnimation(true, 2, "walk");
			movementGauge--;
		}

		else if (AEInputCheckCurr(AEVK_D) && movementGauge > 0 && moveState)
		{
			t->ReverseX(1);
			r->SetVelocityX(speed);
			a->SetAnimation(true, 2, "walk");
			movementGauge--;
		}

		else if (CombatComp::turn == CombatComp::PLAYERTURN && Projectile::isLaunchProjectile)
		{
			a->SetAnimation(false, 1, "arrowShot");
			ad->playAudio(0, "./Assets/Audio/bow-release.mp3", 1.f);
		}

		else if (CombatComp::turn == CombatComp::PLAYERTURN && !CombatComp::isChaseDirection)
		{
			a->SetAnimation(false, 1, "arrowReady");
			ad->playAudio(0, "./Assets/Audio/bow-loading.mp3", 1.f);
		}

		else
		{
			a->SetAnimation(true, 1, "idle");
		}

		GBYEffect();

		if (movementGauge <= 0)
		{
			moveState = false;
		}

		if (CombatComp::turn == CombatComp::TURN::PLAYERTURN && turnTemp)
		{
			turnTemp = false;
			movementGauge = maxMovementGauge;
			moveState = true;
		}
		else if (CombatComp::turn == CombatComp::TURN::ENEMYTURN)
		{
			turnTemp = true;
		}

		if (CombatComp::turn == CombatComp::TURN::PLAYERTURN)
		{
			GameObjectManager::GetInstance().GetObj("directionArrow")->GetComponent<CombatComp>()->data.moveGauge = movementGauge;
		}
	}
}

int PlayerComp::GetMovegauge()
{
	return movementGauge;
}

float PlayerComp::GetHp()
{
	return playerData->hp;
}

void PlayerComp::AddHp(float value)
{
	playerData->hp += value;
	
	if (playerData->hp < 0)
	{
		playerData->hp = 0;
	}

	owner->GetComponent<AnimatorComp>()->SetAnimation(false, 1, "takeDamage");
	//owner->GetComponent<AudioComp>()->playAudio(0, "./Assets/Audio/weapon-arrow-shot.mp3", 0.3f);
}

void PlayerComp::GBYEffect()
{
	static float timer = 0;
	static bool preGBY = false;

	if (preGBY != GBY)
	{
		if (GBY == false)
		{
			GBYobj->GetComponent<SpriteComp>()->SetAlpha(0.f);
			timer = 0;
		}
		else
		{
			owner->GetComponent<AudioComp>()->playAudio(0, "./Assets/Audio/short-choir.mp3", 0.3f);
			GBYobj->GetComponent<SpriteComp>()->SetAlpha(0.5f);
		}

		preGBY = GBY;
	}

	if (GBY)
	{
		timer += (float)AEFrameRateControllerGetFrameTime();

		SpriteComp* s = owner->GetComponent<SpriteComp>();
		TransformComp* t = owner->GetComponent<TransformComp>();

		if (timer < 1.f)
		{
			s->SetAlpha(0.1f);
			s->SetColor(255, 255, 255);
			GBYobj->GetComponent<TransformComp>()->SetPos({ t->GetPos().x, t->GetPos().y });
		}

		else
		{
			s->SetAlpha(1.f);
			s->SetColor(0, 0, 0);
			GBY = false;
		}
	}
}

void PlayerComp::LoadFromJson(const json& data)
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

json PlayerComp::SaveToJson()
{
	json data;
	data["type"] = TypeName;

	json compData;
	compData["speed"] = speed;
	compData["maxMovementGauge"] = maxMovementGauge;
	data["compData"] = compData;

	return data;
}


BaseRTTI* PlayerComp::CreatePlayerComponent(GameObject* owner)
{
	BaseRTTI* p = new PlayerComp(owner);
	owner->AddComponent<PlayerComp>(static_cast<BaseComponent*>(p));
	return p;
}
