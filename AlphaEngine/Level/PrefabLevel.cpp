#include "PrefabLevel.h"
#include "../GSM/GameStateManager.h"
#include "../ComponentManager/ComponentManager.h"
#include "../GameObject/GameObject.h"
#include "../Components/AudioComp.h"
#include "../Components/TransformComp.h"
#include "../Components/SpriteComp.h"
#include "../Components/PlayerComp.h"
#include "../Components/RigidbodyComp.h"
#include "../Components/AnimatorComp.h"
#include "../EventManager/EventManager.h"
#include "../Prefab/Prefab.h"
#include <iostream>

void level::PrefabLevel::Init()
{
	GameObject* temp = nullptr;
	TransformComp* tt = nullptr;
	SpriteComp* ts = nullptr;

	temp = new GameObject();

	temp->SetType(Entity::Square);

	temp->AddComponent<TransformComp>();
	temp->AddComponent<SpriteComp>();

	tt = temp->GetComponent<TransformComp>();
	tt->SetScale({ 100, 100 });
	tt->SetPos({ 0, 0 });

	ts = temp->GetComponent<SpriteComp>();
	ts->SetColor(0, 0, 0);

	Prefab::SavePrefab("Square", temp);

	//

	temp = new GameObject();

	temp->SetType(Entity::RightTri);

	temp->AddComponent<TransformComp>();
	temp->AddComponent<SpriteComp>();

	tt = temp->GetComponent<TransformComp>();
	tt->SetScale({ 100, 100 });
	tt->SetPos({ 0, 0 });

	ts = temp->GetComponent<SpriteComp>();
	ts->SetColor(0, 0, 0);
	//ts->SetTexture("Assets/PlanetTexture.png");

	Prefab::SavePrefab("RightTri", temp);

	//

	temp = new GameObject();

	temp->SetType(Entity::LeftTri);

	temp->AddComponent<TransformComp>();
	temp->AddComponent<SpriteComp>();

	tt = temp->GetComponent<TransformComp>();
	tt->SetScale({ 100, 100 });
	tt->SetPos({ 0, 0 });

	ts = temp->GetComponent<SpriteComp>();
	ts->SetColor(0, 0, 0);
	//ts->SetTexture("Assets/PlanetTexture.png");

	Prefab::SavePrefab("LeftTri", temp);
}

void level::PrefabLevel::Update()
{

}

void level::PrefabLevel::Exit()
{

}
