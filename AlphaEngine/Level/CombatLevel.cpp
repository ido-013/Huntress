// Author : sinu

#include "CombatLevel.h"
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
#include "../ResourceManager/ResourceManager.h"
#include "../Combat/Combat.h"
#include <iostream>
#include <string>

GameObject* background = nullptr;
GameObject* player = nullptr;
GameObject* directionArrow = nullptr;
GameObject* enemy = nullptr;

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

	// player
	player = new GameObject("player");

	player->AddComponent<TransformComp>();
	player->AddComponent<PlayerComp>();
	player->AddComponent<RigidbodyComp>();
	player->AddComponent<SpriteComp>();

	player->GetComponent<TransformComp>()->SetScale({ 90, 120 });
	player->GetComponent<TransformComp>()->SetPos({ -700, -280 });

	player->GetComponent<SpriteComp>()->SetTexture("../Assets/Character/ArrowAttack/sprite/ScoutAttackArrow1.png");

	// direction Arrow
	directionArrow = new GameObject("directionArrow");

	directionArrow->AddComponent<TransformComp>();
	directionArrow->AddComponent<SpriteComp>();
	directionArrow->AddComponent<CombatComp>();

	directionArrow->GetComponent<TransformComp>()->SetScale({ 42, 260 });
	directionArrow->GetComponent<SpriteComp>()->SetTexture("../Assets/Character/DirectionArrow.png");
	directionArrow->GetComponent<SpriteComp>()->SetAlpha(0);

	// enemy
	enemy = new GameObject("enemy");

	enemy->AddComponent<TransformComp>();
	enemy->AddComponent<PlayerComp>();
	enemy->AddComponent<RigidbodyComp>();
	enemy->AddComponent<SpriteComp>();

	enemy->GetComponent<TransformComp>()->SetScale({ -90, 120 });
	enemy->GetComponent<TransformComp>()->SetPos({ 700, -280 });

	enemy->GetComponent<SpriteComp>()->SetTexture("../Assets/Character/ArrowAttack/sprite/ScoutAttackArrow1.png");

	Prefab::SavePrefab("test", player);
}

void level::CombatLevel::Update()
{
	if (AEInputCheckTriggered(AEVK_F))
	{
		directionArrow->GetComponent<CombatComp>()->isDrawDirection = true;
		directionArrow->GetComponent<CombatComp>()->isChaseDirection = true;
	}
}

void level::CombatLevel::Exit()
{

}
