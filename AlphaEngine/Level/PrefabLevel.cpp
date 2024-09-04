#include "PrefabLevel.h"
#include "../GSM/GameStateManager.h"
#include "../ComponentManager/ComponentManager.h"
#include "../Components.h"
#include "../Components/EnemyComp.h"
#include "../GameObject/GameObject.h"
#include "../EventManager/EventManager.h"
#include "../Prefab/Prefab.h"
#include <iostream>

void level::PrefabLevel::Init()
{
	GameObject* temp = nullptr;
	TransformComp* tt = nullptr;
	SpriteComp* ts = nullptr;
	RigidbodyComp* tr = nullptr;
	ColliderComp* tc = nullptr;

	temp = new GameObject();

	temp->type = GameObject::Square;

	temp->AddComponent<TransformComp>();
	temp->AddComponent<SpriteComp>();
	temp->AddComponent<ColliderComp>();

	tt = temp->GetComponent<TransformComp>();
	tt->SetScale({ 100, 100 });
	tt->SetPos({ 0, 0 });

	ts = temp->GetComponent<SpriteComp>();
	ts->SetColor(0, 0, 0);

	tc = temp->GetComponent<ColliderComp>();
	tc->SetCollider();

	Prefab::SavePrefab("Square", temp);

	/*GameObject* enemy = new GameObject("enemy");
	enemy->type = GameObject::Enemy;

	enemy->AddComponent<TransformComp>();
	enemy->AddComponent<RigidbodyComp>();
	enemy->AddComponent<EnemyComp>();
	enemy->AddComponent<SpriteComp>();
	enemy->AddComponent<ColliderComp>();

	enemy->GetComponent<TransformComp>()->SetScale({ -30, 30 });
	enemy->GetComponent<TransformComp>()->SetPos({ 0, 0 });

	enemy->GetComponent<RigidbodyComp>()->useGravity = true;

	enemy->GetComponent<SpriteComp>()->SetTexture("../Assets/Character/ArrowAttack/sprite/ScoutAttackArrow.png");
	enemy->GetComponent<SpriteComp>()->SetColor(130, 0, 0);

	enemy->GetComponent<ColliderComp>()->SetCollider();
	Prefab::SavePrefab("Enemy", enemy);*/
}

void level::PrefabLevel::Update()
{

}

void level::PrefabLevel::Exit()
{

}
