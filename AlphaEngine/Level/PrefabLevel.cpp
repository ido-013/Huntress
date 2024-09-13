#include "PrefabLevel.h"
#include "../GSM/GameStateManager.h"
#include "../ComponentManager/ComponentManager.h"
#include "../Components.h"
#include "../Components/EnemyComp.h"
#include "../GameObject/GameObject.h"
#include "../EventManager/EventManager.h"
#include "../Prefab/Prefab.h"
#include "../Combat/Combat.h"
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
	ts->SetColor(255, 0, 0);

	tc = temp->GetComponent<ColliderComp>();
	tc->SetCollider();

	temp = new GameObject();

	temp->type = GameObject::Square;

	temp->AddComponent<TransformComp>();
	temp->AddComponent<SpriteComp>();
	temp->AddComponent<ColliderComp>();

	tt = temp->GetComponent<TransformComp>();
	tt->SetScale({ 100, 100 });
	tt->SetPos({ 0, 100 });

	ts = temp->GetComponent<SpriteComp>();
	ts->SetColor(255, 255, 0);

	tc = temp->GetComponent<ColliderComp>();
	tc->SetCollider();

	//Prefab::SavePrefab("Square", temp);

	/*GameObject* enemy = new GameObject("player");
	enemy->type = GameObject::Player;

	enemy->AddComponent<TransformComp>();
	enemy->AddComponent<RigidbodyComp>();
	enemy->AddComponent<PlayerComp>();
	enemy->AddComponent<SpriteComp>();
	enemy->AddComponent<AnimatorComp>();
	enemy->AddComponent<ColliderComp>();

	enemy->GetComponent<TransformComp>()->SetScale({ 30, 30 });
	enemy->GetComponent<TransformComp>()->SetPos({ 0, 0 });

	enemy->GetComponent<RigidbodyComp>()->useGravity = true;

	enemy->GetComponent<AnimatorComp>()->AddAnimation("walk");
	enemy->GetComponent<AnimatorComp>()->UpdateAnimation(0.5, "./Assets/Character/Walk/sprite/ScoutWalk2.png", "walk");
	enemy->GetComponent<AnimatorComp>()->UpdateAnimation(0.5, "./Assets/Character/Walk/sprite/ScoutWalk3.png", "walk");

	enemy->GetComponent<SpriteComp>()->SetTexture("./Assets/Character/ArrowAttack/sprite/ScoutAttackArrow.png");	
	enemy->GetComponent<AnimatorComp>()->SetAnimation(true, 1, "walk");

	enemy->GetComponent<ColliderComp>()->SetCollider();*/

	//Prefab::SavePrefab("Player", enemy);
}

void level::PrefabLevel::Update()
{
	
}

void level::PrefabLevel::Exit()
{

}
