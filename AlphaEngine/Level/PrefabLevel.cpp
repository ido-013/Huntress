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

	//

	temp = new GameObject();

	temp->type = GameObject::Square;

	temp->AddComponent<TransformComp>();
	temp->AddComponent<SpriteComp>();
	temp->AddComponent<ColliderComp>();

	tt = temp->GetComponent<TransformComp>();
	tt->SetScale({ 100, 100 });
	tt->SetPos({ 100, 0 });

	ts = temp->GetComponent<SpriteComp>();
	ts->SetColor(0, 0, 0);

	tc = temp->GetComponent<ColliderComp>();
	tc->SetCollider();

	//

	temp = new GameObject();

	temp->type = GameObject::LeftTri;

	temp->AddComponent<TransformComp>();
	temp->AddComponent<SpriteComp>();
	temp->AddComponent<ColliderComp>();

	tt = temp->GetComponent<TransformComp>();
	tt->SetScale({ 100, 100 });
	tt->SetPos({ -100, 100 });

	ts = temp->GetComponent<SpriteComp>();
	ts->SetColor(0, 0, 0);

	tc = temp->GetComponent<ColliderComp>();
	tc->SetCollider();

	//

	temp = new GameObject();

	temp->type = GameObject::RightTri;

	temp->AddComponent<TransformComp>();
	temp->AddComponent<SpriteComp>();
	temp->AddComponent<ColliderComp>();

	tt = temp->GetComponent<TransformComp>();
	tt->SetScale({ 100, 100 });
	tt->SetPos({ 100, 100 });

	ts = temp->GetComponent<SpriteComp>();
	ts->SetColor(0, 0, 0);

	tc = temp->GetComponent<ColliderComp>();
	tc->SetCollider();
	
	//

	temp = new GameObject();

	temp->type = GameObject::Square;

	temp->AddComponent<TransformComp>();
	temp->AddComponent<SpriteComp>();
	temp->AddComponent<ColliderComp>();

	tt = temp->GetComponent<TransformComp>();
	tt->SetScale({ 100, 100 });
	tt->SetPos({ -100, 0 });

	ts = temp->GetComponent<SpriteComp>();
	ts->SetColor(0, 0, 0);

	tc = temp->GetComponent<ColliderComp>();
	tc->SetCollider();

	//

	temp = new GameObject();

	temp->type = GameObject::Square;

	temp->AddComponent<TransformComp>();
	temp->AddComponent<SpriteComp>();
	temp->AddComponent<ColliderComp>();

	tt = temp->GetComponent<TransformComp>();
	tt->SetScale({ 100, 100 });
	tt->SetPos({ -200, 100 });

	ts = temp->GetComponent<SpriteComp>();
	ts->SetColor(0, 0, 0);

	tc = temp->GetComponent<ColliderComp>();
	tc->SetCollider();

	//

	temp = new GameObject();

	temp->type = GameObject::Square;

	temp->AddComponent<TransformComp>();
	temp->AddComponent<SpriteComp>();
	temp->AddComponent<ColliderComp>();

	tt = temp->GetComponent<TransformComp>();
	tt->SetScale({ 100, 100 });
	tt->SetPos({ 200, 100 });

	ts = temp->GetComponent<SpriteComp>();
	ts->SetColor(0, 0, 0);

	tc = temp->GetComponent<ColliderComp>();
	tc->SetCollider();

	//

	temp = new GameObject();

	temp->type = GameObject::Square;

	temp->AddComponent<TransformComp>();
	temp->AddComponent<SpriteComp>();
	temp->AddComponent<PointComp>();
	temp->AddComponent<RigidbodyComp>();
	temp->AddComponent<ColliderComp>();

	tt = temp->GetComponent<TransformComp>();
	tt->SetScale({ 30, 30 });
	tt->SetPos({ 0, 400 });

	ts = temp->GetComponent<SpriteComp>();
	ts->SetColor(255, 0, 0);

	tr = temp->GetComponent<RigidbodyComp>();
	tr->useGravity = true;

	tc = temp->GetComponent<ColliderComp>();
	tc->SetCollider();
}

void level::PrefabLevel::Update()
{

}

void level::PrefabLevel::Exit()
{

}
