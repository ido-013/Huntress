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

GameObject* da = nullptr;

void level::PrefabLevel::Init()
{
	GameObject* temp = nullptr;
	TransformComp* tt = nullptr;
	SpriteComp* ts = nullptr;
	RigidbodyComp* tr = nullptr;
	ColliderComp* tc = nullptr;

	/*temp = new GameObject();

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

	Prefab::SavePrefab("Square", temp);*/

	da = new GameObject("directionArrow");

	da->AddComponent<TransformComp>();
	da->AddComponent<SpriteComp>();
	da->AddComponent<CombatComp>();

	da->GetComponent<TransformComp>()->SetScale({
		da->GetComponent<CombatComp>()->directionArrowWidth,
		da->GetComponent<CombatComp>()->directionArrowHeight });

	da->GetComponent<SpriteComp>()->SetTexture("./Assets/Character/da.png");
	da->GetComponent<SpriteComp>()->SetAlpha(0);

	da->GetComponent<CombatComp>()->turn = CombatComp::TURN::PLAYERTURN;
	da->GetComponent<CombatComp>()->state = CombatComp::STATE::COMBAT;
	da->GetComponent<CombatComp>()->isCombat = true;

	Prefab::SavePrefab("da", da);
}

void level::PrefabLevel::Update()
{

}

void level::PrefabLevel::Exit()
{

}
