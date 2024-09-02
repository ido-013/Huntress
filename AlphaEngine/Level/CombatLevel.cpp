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
#include "../UI/CombatUI.h"
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

	// player
	player = new GameObject("player");
	player->type = GameObject::Square;

	player->AddComponent<TransformComp>();
	player->AddComponent<PlayerComp>();
	player->AddComponent<RigidbodyComp>();
	player->AddComponent<SpriteComp>();
	player->AddComponent<ColliderComp>();

	player->GetComponent<TransformComp>()->SetScale({ 30, 30 });
	player->GetComponent<TransformComp>()->SetPos({ -30, 400 });

	player->GetComponent<RigidbodyComp>()->useGravity = true;

	player->GetComponent<SpriteComp>()->SetTexture("../Assets/Character/ArrowAttack/sprite/ScoutAttackArrow.png");
	player->GetComponent<SpriteComp>()->SetAlpha(1);

	player->GetComponent<ColliderComp>()->SetCollider();

	// enemy
	enemy = new GameObject("enemy");
	enemy->type = GameObject::Square;

	enemy->AddComponent<TransformComp>();
	enemy->AddComponent<RigidbodyComp>();

	enemy->AddComponent<SpriteComp>();
	enemy->AddComponent<ColliderComp>();

	enemy->GetComponent<TransformComp>()->SetScale({ -30, 30 });
	enemy->GetComponent<TransformComp>()->SetPos({ 30, 400 });

	enemy->GetComponent<RigidbodyComp>()->useGravity = true;
	
	enemy->GetComponent<SpriteComp>()->SetTexture("../Assets/Character/ArrowAttack/sprite/ScoutAttackArrow.png");
	enemy->GetComponent<SpriteComp>()->SetAlpha(1);

	enemy->GetComponent<ColliderComp>()->SetCollider();


	// direction Arrow
	directionArrow = new GameObject("directionArrow");

	directionArrow->AddComponent<TransformComp>();
	directionArrow->AddComponent<SpriteComp>();
	directionArrow->AddComponent<CombatComp>();

	directionArrow->GetComponent<TransformComp>()->SetScale({ 
		directionArrow->GetComponent<CombatComp>()->directionArrowWidth, 
		directionArrow->GetComponent<CombatComp>()->directionArrowHeight });
	directionArrow->GetComponent<SpriteComp>()->SetTexture("../Assets/Character/DirectionArrow.png");
	directionArrow->GetComponent<SpriteComp>()->SetAlpha(0);
	directionArrow->GetComponent<CombatComp>()->turn = CombatComp::TURN::PLAYERTURN;
	directionArrow->GetComponent<CombatComp>()->isCombat = true;

	InitCombatUI();
}

void level::CombatLevel::Update()
{
	UpdateCombatUI(player);
	
}

void level::CombatLevel::Exit()
{

}
