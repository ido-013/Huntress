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

	{
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

		// enemy
		enemy = new GameObject("enemy");

		enemy->AddComponent<TransformComp>();
		//enemy->AddComponent<PlayerComp>();
		enemy->AddComponent<RigidbodyComp>();
		enemy->AddComponent<SpriteComp>();

		enemy->GetComponent<TransformComp>()->SetScale({ -90, 120 });
		enemy->GetComponent<TransformComp>()->SetPos({ 700, -280 });

		enemy->GetComponent<SpriteComp>()->SetTexture("../Assets/Character/ArrowAttack/sprite/ScoutAttackArrow.png");
		enemy->GetComponent<SpriteComp>()->SetAlpha(1);

		//Prefab::SavePrefab("test", player);
	}

	/*{
		UIBAR = new GameObject();
		UIBAR->AddComponent<SpriteComp>();
		UIBAR->AddComponent<AudioComp>();
		UIBAR->AddComponent<TransformComp>();
		TransformComp* transLogo = UIBAR->GetComponent<TransformComp>();
		transLogo->SetScale({ 1600,250 });
		transLogo->SetPos({ 0, -330 });
		SpriteComp* LogoSprite = UIBAR->GetComponent<SpriteComp>();
		LogoSprite->SetTexture("../Assets/arrow.png");
		LogoSprite->SetColor(255, 255, 255);

		Power = new GameObject();
		Power->AddComponent<SpriteComp>();
		Power->AddComponent<AudioComp>();
		Power->AddComponent<TransformComp>();
		TransformComp* transStart = Power->GetComponent<TransformComp>();
		transStart->SetScale({ 750,80 });
		transStart->SetPos({ 150, -280 });
		SpriteComp* PowerSprite = Power->GetComponent<SpriteComp>();
		PowerSprite->SetTexture("../Assets/arrow.png");
		PowerSprite->SetColor(255, 0, 0);

		Move = new GameObject();
		Move->AddComponent<SpriteComp>();
		Move->AddComponent<AudioComp>();
		Move->AddComponent<TransformComp>();
		TransformComp* transMove = Move->GetComponent<TransformComp>();
		transMove->SetScale({ 750,80 });
		transMove->SetPos({ 150, -380 });
		SpriteComp* MoveSprite = Move->GetComponent<SpriteComp>();
		MoveSprite->SetTexture("../Assets/arrow.png");
		MoveSprite->SetColor(0, 255, 0);

		Angle = new GameObject();
		Angle->AddComponent<SpriteComp>();
		Angle->AddComponent<AudioComp>();
		Angle->AddComponent<TransformComp>();
		TransformComp* transAngle = Angle->GetComponent<TransformComp>();
		transAngle->SetScale({ 200,200 });
		transAngle->SetPos({ -380, -330 });
		SpriteComp* AngleSprite = Angle->GetComponent<SpriteComp>();
		AngleSprite->SetTexture("../Assets/arrow.png");
		AngleSprite->SetColor(120, 120, 120);

		HP = new GameObject();
		HP->AddComponent<SpriteComp>();
		HP->AddComponent<AudioComp>();
		HP->AddComponent<TransformComp>();
		TransformComp* transHP = HP->GetComponent<TransformComp>();
		transHP->SetScale({ 80,200 });
		transHP->SetPos({ -720, -330 });
		SpriteComp* HPSprite = HP->GetComponent<SpriteComp>();
		HPSprite->SetTexture("../Assets/arrow.png");
		HPSprite->SetColor(0, 200, 0);

		Attack = new GameObject();
		Attack->AddComponent<SpriteComp>();
		Attack->AddComponent<AudioComp>();
		Attack->AddComponent<TransformComp>();
		TransformComp* transAttack = Attack->GetComponent<TransformComp>();
		transAttack->SetScale({ 130, 200 });
		transAttack->SetPos({ -600, -330 });
		SpriteComp* AttackSprite = Attack->GetComponent<SpriteComp>();
		AttackSprite->SetTexture("../Assets/arrow.png");
		AttackSprite->SetColor(0, 0, 0);

		enemyHP = new GameObject();
		enemyHP->AddComponent<SpriteComp>();
		enemyHP->AddComponent<AudioComp>();
		enemyHP->AddComponent<TransformComp>();
		TransformComp* transHP_e = enemyHP->GetComponent<TransformComp>();
		transHP_e->SetScale({ 80, 200 });
		transHP_e->SetPos({ 720, -330 });
		SpriteComp* HPSprite_e = enemyHP->GetComponent<SpriteComp>();
		HPSprite_e->SetTexture("../Assets/arrow.png");
		HPSprite_e->SetColor(200, 200, 0);

		enemyAttack = new GameObject();
		enemyAttack->AddComponent<SpriteComp>();
		enemyAttack->AddComponent<AudioComp>();
		enemyAttack->AddComponent<TransformComp>();
		TransformComp* transAttack_e = enemyAttack->GetComponent<TransformComp>();
		transAttack_e->SetScale({ 130,200 });
		transAttack_e->SetPos({ 600, -330 });
		SpriteComp* AttackSprite_e = enemyAttack->GetComponent<SpriteComp>();
		AttackSprite_e->SetTexture("../Assets/arrow.png");
		AttackSprite_e->SetColor(0, 0, 0);

		Wind = new GameObject();
		Wind->AddComponent<SpriteComp>();
		Wind->AddComponent<AudioComp>();
		Wind->AddComponent<TransformComp>();
		TransformComp* transSetting = Wind->GetComponent<TransformComp>();
		transSetting->SetScale({ 200,100 });
		transSetting->SetPos({ -700, 400 });
		SpriteComp* WindSprite = Wind->GetComponent<SpriteComp>();
		WindSprite->SetTexture("../Assets/arrow.png");
		WindSprite->SetColor(120, 120, 120);
	}*/
}

void level::CombatLevel::Update()
{
	/*TransformComp* transMove = Move->GetComponent<TransformComp>();
	transMove->SetScale({ 750 * (float(player->GetComponent<PlayerComp>()->GetMovegauge()) * (0.001f)), 80 });
	transMove->SetPos({ 150 - (750 - 750 * (float(player->GetComponent<PlayerComp>()->GetMovegauge()) * 0.001f)) / 2, -380 });*/

	if (AEInputCheckTriggered(AEVK_F) && player->GetComponent<PlayerComp>()->turn)
	{
		player->GetComponent<PlayerComp>()->moveState = false;
		directionArrow->GetComponent<CombatComp>()->isDrawDirection = true;
		directionArrow->GetComponent<CombatComp>()->isChaseDirection = true;
	}

	{
		TransformComp* playerTrans = player->GetComponent<TransformComp>();
		TransformComp* bgTrans = background->GetComponent<TransformComp>();

		AEGfxSetCamPosition(playerTrans->GetPos().x, playerTrans->GetPos().y);

		AEVec2 camPos;
		AEGfxGetCamPosition(&camPos.x, &camPos.y);
		bgTrans->SetPos({ camPos.x, camPos.y });
	}
}

void level::CombatLevel::Exit()
{

}
