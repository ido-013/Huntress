#include "PrefabLevel.h"
#include "../GSM/GameStateManager.h"
#include "../ComponentManager/ComponentManager.h"
#include "../Components.h"
#include "../GameObject/GameObject.h"
#include "../EventManager/EventManager.h"
#include "../Prefab/Prefab.h"
#include <iostream>

GameObject* temp = nullptr;
GameObject* wall = nullptr;

void level::PrefabLevel::Init()
{
	TransformComp* tt = nullptr;
	SpriteComp* ts = nullptr;
	RigidbodyComp* tr = nullptr;
	ColliderComp* tc = nullptr;
	AnimatorComp* ta = nullptr;

	temp = new GameObject();

	temp->type = GameObject::Square;

	tt = temp->AddComponent<TransformComp>();
	ts = temp->AddComponent<SpriteComp>();
	tc = temp->AddComponent<ColliderComp>();
	ta = temp->AddComponent<AnimatorComp>();
	temp->AddComponent<PlayerComp>();
	temp->AddComponent<RigidbodyComp>();

	tt->SetScale({ 100, 100 });
	tt->SetPos({ 0, 0 });

	ts->SetColor(0, 0, 0);

	tc->SetCollider();

	ta->AddAnimation("walk");
	ta->UpdateAnimation(0.2f, "Assets/Character/Walk/sprite/ScoutWalk1.png", "walk");
	ta->UpdateAnimation(0.2f, "Assets/Character/Walk/sprite/ScoutWalk2.png", "walk");
	ta->UpdateAnimation(0.2f, "Assets/Character/Walk/sprite/ScoutWalk3.png", "walk");
	ta->UpdateAnimation(0.2f, "Assets/Character/Walk/sprite/ScoutWalk4.png", "walk");

	ta->AddAnimation("idle");
	ta->UpdateAnimation(0.2f, "Assets/Character/Idle/sprite/ScoutIdle1.png", "idle");
	ta->UpdateAnimation(0.2f, "Assets/Character/Idle/sprite/ScoutIdle2.png", "idle");
	ta->UpdateAnimation(0.2f, "Assets/Character/Idle/sprite/ScoutIdle3.png", "idle");
	ta->UpdateAnimation(0.2f, "Assets/Character/Idle/sprite/ScoutIdle4.png", "idle");

	ta->AddAnimation("attack");
	ta->UpdateAnimation(0.2f, "Assets/Character/Attack/sprite/Scout1.png", "attack");
	ta->UpdateAnimation(0.2f, "Assets/Character/Attack/sprite/Scout2.png", "attack");
	ta->UpdateAnimation(0.2f, "Assets/Character/Attack/sprite/Scout3.png", "attack");
	ta->UpdateAnimation(0.2f, "Assets/Character/Attack/sprite/Scout4.png", "attack");
	ta->UpdateAnimation(0.2f, "Assets/Character/Attack/sprite/Scout5.png", "attack");

	ta->AddAnimation("takeDamage");
	ta->UpdateAnimation(0.05f, "Assets/Character/TakeDamage/sprite/ScoutTakeDamage1.png", "takeDamage");
	ta->UpdateAnimation(0.05f, "Assets/Character/TakeDamage/sprite/ScoutTakeDamage2.png", "takeDamage");
	ta->UpdateAnimation(0.05f, "Assets/Character/TakeDamage/sprite/ScoutTakeDamage3.png", "takeDamage");
	ta->UpdateAnimation(0.1f, "Assets/Character/TakeDamage/sprite/ScoutTakeDamage4.png", "takeDamage");

	wall = new GameObject;

	wall->type = GameObject::Square;

	tt = wall->AddComponent<TransformComp>();
	ts = wall->AddComponent<SpriteComp>();
	tc = wall->AddComponent<ColliderComp>();

	tt->SetScale({ 100, 100 });
	tt->SetPos({ 0, 0 });
	tt->SetRot(50);

	ts->SetColor(0, 0, 0);

	tc->SetCollider();
}

void level::PrefabLevel::Update()
{
	AnimatorComp* ta = temp->GetComponent<AnimatorComp>();

	if (AEInputCheckCurr(AEVK_1))
	{
		ta->SetAnimation(true, 1, "idle");
	}

	if (AEInputCheckCurr(AEVK_2))
	{
		ta->SetAnimation(true, 1, "walk");
	}

	if (AEInputCheckCurr(AEVK_3))
	{
		ta->SetAnimation(true, 1, "attack");
	}

	if (AEInputCheckCurr(AEVK_4))
	{
		ta->SetAnimation(true, 1, "takeDamage");
	}
}

void level::PrefabLevel::Exit()
{

}
