#include "CombatUI.h"
#include "../Components/PlayerComp.h"
#include "../Components/AudioComp.h"
#include "../Components/TransformComp.h"
#include "../Components/SpriteComp.h"

GameObject* UIBAR = nullptr;
GameObject* Power = nullptr;
GameObject* Move = nullptr;
GameObject* Angle = nullptr;
GameObject* Wind = nullptr;
GameObject* HP = nullptr;
GameObject* enemyHP = nullptr;
GameObject* Attack = nullptr;
GameObject* enemyAttack = nullptr;

void InitCombatUI()
{
	UIBAR = new GameObject();
	UIBAR->AddComponent<SpriteComp>();
	UIBAR->AddComponent<AudioComp>();
	UIBAR->AddComponent<TransformComp>();
	TransformComp* transLogo = UIBAR->GetComponent<TransformComp>();
	transLogo->SetScale({ 1600,250 });
	transLogo->SetPos({ 0, -330 });
	SpriteComp* LogoSprite = UIBAR->GetComponent<SpriteComp>();
	LogoSprite->SetTexture("Assets/arrow.png");
	LogoSprite->SetColor(255, 255, 255);

	Power = new GameObject();
	Power->AddComponent<SpriteComp>();
	Power->AddComponent<AudioComp>();
	Power->AddComponent<TransformComp>();
	TransformComp* transStart = Power->GetComponent<TransformComp>();
	transStart->SetScale({ 750,80 });
	transStart->SetPos({ 150, -280 });
	SpriteComp* PowerSprite = Power->GetComponent<SpriteComp>();
	PowerSprite->SetTexture("Assets/arrow.png");
	PowerSprite->SetColor(255, 0, 0);

	Move = new GameObject();
	Move->AddComponent<SpriteComp>();
	Move->AddComponent<AudioComp>();
	Move->AddComponent<TransformComp>();
	TransformComp* transMove = Move->GetComponent<TransformComp>();
	transMove->SetScale({ 750,80 });
	transMove->SetPos({ 150, -380 });
	SpriteComp* MoveSprite = Move->GetComponent<SpriteComp>();
	MoveSprite->SetTexture("Assets/arrow.png");
	MoveSprite->SetColor(0, 255, 0);

	Angle = new GameObject();
	Angle->AddComponent<SpriteComp>();
	Angle->AddComponent<AudioComp>();
	Angle->AddComponent<TransformComp>();
	TransformComp* transAngle = Angle->GetComponent<TransformComp>();
	transAngle->SetScale({ 200,200 });
	transAngle->SetPos({ -380, -330 });
	SpriteComp* AngleSprite = Angle->GetComponent<SpriteComp>();
	AngleSprite->SetTexture("Assets/arrow.png");
	AngleSprite->SetColor(120, 120, 120);

	HP = new GameObject();
	HP->AddComponent<SpriteComp>();
	HP->AddComponent<AudioComp>();
	HP->AddComponent<TransformComp>();
	TransformComp* transHP = HP->GetComponent<TransformComp>();
	transHP->SetScale({ 80,200 });
	transHP->SetPos({ -720, -330 });
	SpriteComp* HPSprite = HP->GetComponent<SpriteComp>();
	HPSprite->SetTexture("Assets/arrow.png");
	HPSprite->SetColor(0, 200, 0);

	Attack = new GameObject();
	Attack->AddComponent<SpriteComp>();
	Attack->AddComponent<AudioComp>();
	Attack->AddComponent<TransformComp>();
	TransformComp* transAttack = Attack->GetComponent<TransformComp>();
	transAttack->SetScale({ 130,200 });
	transAttack->SetPos({ -600, -330 });
	SpriteComp* AttackSprite = Attack->GetComponent<SpriteComp>();
	AttackSprite->SetTexture("Assets/arrow.png");
	AttackSprite->SetColor(0, 0, 0);

	enemyHP = new GameObject();
	enemyHP->AddComponent<SpriteComp>();
	enemyHP->AddComponent<AudioComp>();
	enemyHP->AddComponent<TransformComp>();
	TransformComp* transHP_e = enemyHP->GetComponent<TransformComp>();
	transHP_e->SetScale({ 80,200 });
	transHP_e->SetPos({ 720, -330 });
	SpriteComp* HPSprite_e = enemyHP->GetComponent<SpriteComp>();
	HPSprite_e->SetTexture("Assets/arrow.png");
	HPSprite_e->SetColor(200, 200, 0);

	enemyAttack = new GameObject();
	enemyAttack->AddComponent<SpriteComp>();
	enemyAttack->AddComponent<AudioComp>();
	enemyAttack->AddComponent<TransformComp>();
	TransformComp* transAttack_e = enemyAttack->GetComponent<TransformComp>();
	transAttack_e->SetScale({ 130,200 });
	transAttack_e->SetPos({ 600, -330 });
	SpriteComp* AttackSprite_e = enemyAttack->GetComponent<SpriteComp>();
	AttackSprite_e->SetTexture("Assets/arrow.png");
	AttackSprite_e->SetColor(0, 0, 0);

	Wind = new GameObject();
	Wind->AddComponent<SpriteComp>();
	Wind->AddComponent<AudioComp>();
	Wind->AddComponent<TransformComp>();
	TransformComp* transSetting = Wind->GetComponent<TransformComp>();
	transSetting->SetScale({ 200,100 });
	transSetting->SetPos({ -700, 400 });
	SpriteComp* WindSprite = Wind->GetComponent<SpriteComp>();
	WindSprite->SetTexture("Assets/arrow.png");
	WindSprite->SetColor(120, 120, 120);
}

void UpdateCombatUI(GameObject* player)
{
	TransformComp* transMove = Move->GetComponent<TransformComp>();;
	transMove->SetScale({ 750 * (float(player->GetComponent<PlayerComp>()->GetMovegauge()) * 0.001f) ,80 });
	transMove->SetPos({ 150 - (750 - 750 * (float(player->GetComponent<PlayerComp>()->GetMovegauge()) * 0.001f)) / 2, -380 });
}

void ExitCombatUI()
{
}
