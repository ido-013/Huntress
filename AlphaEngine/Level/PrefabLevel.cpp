#include "PrefabLevel.h"
#include "../GSM/GameStateManager.h"
#include "../ComponentManager/ComponentManager.h"
#include "../Components.h"
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

	Prefab::SavePrefab("Square", temp);

	//

	temp = new GameObject();

	temp->type = GameObject::RightTri;

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

	temp->type = GameObject::LeftTri;

	temp->AddComponent<TransformComp>();
	temp->AddComponent<SpriteComp>();

	tt = temp->GetComponent<TransformComp>();
	tt->SetScale({ 100, 100 });
	tt->SetPos({ 0, 0 });

	ts = temp->GetComponent<SpriteComp>();
	ts->SetColor(0, 0, 0);
	//ts->SetTexture("Assets/PlanetTexture.png");

	Prefab::SavePrefab("LeftTri", temp);

	//

	temp = new GameObject();

	temp->type = GameObject::Point;

	temp->AddComponent<TransformComp>();
	temp->AddComponent<SpriteComp>();
	temp->AddComponent<PointComp>();
	temp->AddComponent<RigidbodyComp>();

	tt = temp->GetComponent<TransformComp>();
	tt->SetScale({ 10, 10 });
	tt->SetPos({ 0, 400 });

	ts = temp->GetComponent<SpriteComp>();
	ts->SetColor(255, 0, 0);

	tr = temp->GetComponent<RigidbodyComp>();
	tr->useGravity = true;

	Prefab::SavePrefab("Point", temp);
}

void level::PrefabLevel::Update()
{

}

void level::PrefabLevel::Exit()
{

}
