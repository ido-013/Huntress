// Author : sinu

#include "CombatLevel.h"
#include "../GSM/GameStateManager.h"
#include "../ComponentManager/ComponentManager.h"
#include "../GameObject/GameObject.h"
#include "../components.h"
#include "../EventManager/EventManager.h"
#include "../Prefab/Prefab.h"
#include "../ResourceManager/ResourceManager.h"
#include "../Combat/Combat.h"
#include <iostream>
#include <string>

GameObject* background = nullptr;
GameObject* player = nullptr;
GameObject* directionArrow = nullptr;
GameObject* enemy = nullptr;

GameObject* UIBAR = nullptr;
GameObject* Power = nullptr;
GameObject* Move = nullptr;
GameObject* Angle = nullptr;
GameObject* Wind = nullptr;
GameObject* HP = nullptr;
GameObject* enemyHP = nullptr;
GameObject* Attack = nullptr;
GameObject* enemyAttack = nullptr;

void level::CombatLevel::Init()
{
	// background
	background = new GameObject("background");

	background->AddComponent<AudioComp>();
	background->AddComponent<TransformComp>();
	background->AddComponent<SpriteComp>();
	background->GetComponent<AudioComp>()->SetAudio("../Assets/Audio/BGM.mp3");
	background->GetComponent<AudioComp>()->playAudio(-1, "../Assets/Audio/BGM.mp3");

	background->GetComponent<TransformComp>()->SetScale({ 1600, 900 });
	background->GetComponent<TransformComp>()->SetPos({ 0, 0 });
	background->GetComponent<SpriteComp>()->SetTexture("../Assets/Background/Background.png");
	background->GetComponent<SpriteComp>()->SetAlpha(1);

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
		ts->SetAlpha(1);

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
		ts->SetAlpha(1);

		tc = temp->GetComponent<ColliderComp>();
		tc->SetCollider();

		////

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
		ts->SetAlpha(1);

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
		ts->SetAlpha(1);

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
		ts->SetAlpha(1);

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
		ts->SetAlpha(1);

		tc = temp->GetComponent<ColliderComp>();
		tc->SetCollider();

		////

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
		ts->SetAlpha(1);

		tc = temp->GetComponent<ColliderComp>();
		tc->SetCollider();

		//

		temp = new GameObject();

		temp->type = GameObject::LeftTri;

		temp->AddComponent<TransformComp>();
		temp->AddComponent<SpriteComp>();
		temp->AddComponent<ColliderComp>();

		tt = temp->GetComponent<TransformComp>();
		tt->SetScale({ 200, 100 });
		tt->SetPos({ -250, 200 });

		ts = temp->GetComponent<SpriteComp>();
		ts->SetColor(0, 0, 0);
		ts->SetAlpha(1);

		tc = temp->GetComponent<ColliderComp>();
		tc->SetCollider();
	}

	// player
	player = new GameObject("player");
	player->type = GameObject::Square;

	player->AddComponent<TransformComp>();
	player->AddComponent<PlayerComp>();
	player->AddComponent<RigidbodyComp>();
	player->AddComponent<SpriteComp>();
	player->AddComponent<ColliderComp>();

	player->GetComponent<TransformComp>()->SetScale({ 30, 30 });
	player->GetComponent<TransformComp>()->SetPos({ 0, 400 });

	player->GetComponent<RigidbodyComp>()->useGravity = true;

	player->GetComponent<SpriteComp>()->SetTexture("../Assets/Character/ArrowAttack/sprite/ScoutAttackArrow.png");
	player->GetComponent<SpriteComp>()->SetAlpha(1);

	player->GetComponent<ColliderComp>()->SetCollider();

	// direction Arrow
	directionArrow = new GameObject("directionArrow");

	directionArrow->AddComponent<TransformComp>();
	directionArrow->AddComponent<SpriteComp>();
	directionArrow->AddComponent<CombatComp>();

	directionArrow->GetComponent<TransformComp>()->SetScale({ 42, 260 });
	directionArrow->GetComponent<SpriteComp>()->SetTexture("../Assets/Character/DirectionArrow.png");
	directionArrow->GetComponent<SpriteComp>()->SetAlpha(0);
	directionArrow->GetComponent<CombatComp>()->turn = CombatComp::TURN::PLAYERTURN;
	directionArrow->GetComponent<CombatComp>()->isCombat = true;

	// enemy
	enemy = new GameObject("enemy");

	enemy->AddComponent<TransformComp>();
	enemy->AddComponent<RigidbodyComp>();
	enemy->AddComponent<SpriteComp>();

	enemy->GetComponent<TransformComp>()->SetScale({ -90, 120 });
	enemy->GetComponent<TransformComp>()->SetPos({ 700, -280 });

	enemy->GetComponent<SpriteComp>()->SetTexture("../Assets/Character/ArrowAttack/sprite/ScoutAttackArrow.png");
	enemy->GetComponent<SpriteComp>()->SetAlpha(1);

}

void level::CombatLevel::Update()
{
}

void level::CombatLevel::Exit()
{

}
