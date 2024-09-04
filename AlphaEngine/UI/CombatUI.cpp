#include "CombatUI.h"
#include "../GameObject/GameObject.h"
#include "../Components/AudioComp.h"
#include "../Components/UIComp.h"
#include "../Components/PlayerComp.h"
#include "../Components/EnemyComp.h"
#include "../Combat/Combat.h"
#include "../Components/TransformComp.h"
GameObject* UIBAR = nullptr;
GameObject* Power = nullptr;
GameObject* Move = nullptr;
GameObject* Angle = nullptr;
GameObject* playerAngle = nullptr;
GameObject* DirectAngle = nullptr;
GameObject* Wind = nullptr;
GameObject* HP = nullptr;
GameObject* enemyHP = nullptr;
GameObject* Attack = nullptr;
GameObject* enemyAttack = nullptr;
GameObject* WindDirection = nullptr;

void InitCombatUI(GameObject* player, GameObject* enemy, GameObject* directionArrow)
{
	UIBAR = new GameObject();
	UIBAR->AddComponent<UIComponent>();
	UIComponent* uiBarComp = UIBAR->GetComponent<UIComponent>();
	uiBarComp->SetScale({ 1600, 250 });
	uiBarComp->SetPos({ 0, -330 });
	uiBarComp->SetTexture("Assets/arrow.png");
	uiBarComp->SetColor(255, 255, 255);

	// Power Bar
	Power = new GameObject();
	Power->AddComponent<UIComponent>();
	UIComponent* powerComp = Power->GetComponent<UIComponent>();
	powerComp->SetScale({ 750 * (float(directionArrow->GetComponent<CombatComp>()->GetPlayerPower()) * (1 / (POWER_LIMIT + DEFAULT_POWER))), 80 });
	powerComp->SetPos({ 150 - (750 - 750 * (float(directionArrow->GetComponent<CombatComp>()->GetPlayerPower()) * (1 / (POWER_LIMIT + DEFAULT_POWER)))) / 2 , -280 });
	powerComp->SetTexture("Assets/arrow.png");
	powerComp->SetColor(255, 0, 0);

	// Move Bar
	Move = new GameObject();
	Move->AddComponent<UIComponent>();
	UIComponent* moveComp = Move->GetComponent<UIComponent>();
	moveComp->SetScale({ 750 * (float(player->GetComponent<PlayerComp>()->GetMovegauge()) * 0.001f), 80 });
	moveComp->SetPos({ 150 - (750 - 750 * (float(player->GetComponent<PlayerComp>()->GetMovegauge()) * 0.001f)) / 2 , -380 });
	moveComp->SetTexture("Assets/arrow.png");
	moveComp->SetColor(0, 255, 0);

	// Angle UI
	Angle = new GameObject();
	Angle->AddComponent<UIComponent>();
	UIComponent* angleComp = Angle->GetComponent<UIComponent>();
	angleComp->SetPos({ -380 , -330 });
	angleComp->SetScale({ 200, 200 });
	angleComp->SetTexture("Assets/arrow.png");
	angleComp->SetColor(120, 120, 120);

	//playerAngleUI
	playerAngle = new GameObject();
	playerAngle->AddComponent<UIComponent>();
	UIComponent* playerAngleComp = playerAngle->GetComponent<UIComponent>();
	playerAngleComp->SetPos({ -380, -330 });
	playerAngleComp->SetRot(0.5f);
	playerAngleComp->SetScale({ 150,10 });
	playerAngleComp->SetTexture("Assets/arrow.png");
	playerAngleComp->SetColor(255, 0, 0);

	//DirectAngleUI
	DirectAngle = new GameObject();
	DirectAngle->AddComponent<UIComponent>();
	UIComponent* directAngleComp = DirectAngle->GetComponent<UIComponent>();
	directAngleComp->SetPos({ -380,-330 });
	directAngleComp->SetColor(0, 255, 0);
	directAngleComp->SetTexture("");
	directAngleComp->SetScale({150, 10});
	// HP Bar
	HP = new GameObject();
	HP->AddComponent<UIComponent>();
	UIComponent* hpComp = HP->GetComponent<UIComponent>();
	hpComp->SetScale({ 80, 200 * (float(player->GetComponent<PlayerComp>()->data.hp) / player->GetComponent<PlayerComp>()->data.maxLife) });
	hpComp->SetPos({ -720 , (-330 - (200 - 200 * (float(player->GetComponent<PlayerComp>()->data.hp) / player->GetComponent<PlayerComp>()->data.maxLife)) / 2.f) });
	hpComp->SetTexture("Assets/arrow.png");
	hpComp->SetColor(0, 200, 0);

	// Player Attack
	Attack = new GameObject();
	Attack->AddComponent<UIComponent>();
	UIComponent* attackComp = Attack->GetComponent<UIComponent>();
	attackComp->SetScale({ 130, 200 });
	attackComp->SetPos({ -600, -330 });
	attackComp->SetTexture("Assets/arrow.png");
	attackComp->SetColor(0, 0, 0);

	// Enemy HP Bar
	enemyHP = new GameObject();
	enemyHP->AddComponent<UIComponent>();

	UIComponent* enemyHpComp = enemyHP->GetComponent<UIComponent>();
	enemyHpComp->SetScale({ 80, 200 * (float(enemy->GetComponent<EnemyComp>()->data.hp) / player->GetComponent<PlayerComp>()->data.maxLife) });
	enemyHpComp->SetPos({ 720 , (-330 - (200 - 200 * (float(enemy->GetComponent<EnemyComp>()->data.hp) / player->GetComponent<PlayerComp>()->data.maxLife)) / 2.f) });
	enemyHpComp->SetTexture("Assets/arrow.png");
	enemyHpComp->SetColor(200, 200, 0);

	// Enemy Attack
	enemyAttack = new GameObject();
	enemyAttack->AddComponent<UIComponent>();
	UIComponent* enemyAttackComp = enemyAttack->GetComponent<UIComponent>();
	enemyAttackComp->SetScale({ 130, 200 });
	enemyAttackComp->SetPos({ 600, -330 });
	enemyAttackComp->SetTexture("Assets/arrow.png");
	enemyAttackComp->SetColor(0, 0, 0);

	// Wind UI
	Wind = new GameObject();
	Wind->AddComponent<UIComponent>();
	UIComponent* windComp = Wind->GetComponent<UIComponent>();
	windComp->SetScale({ 200, 100 });
	windComp->SetPos({ -700, 400 });
	windComp->SetTexture("Assets/arrow.png");
	windComp->SetColor(120, 120, 120);

	// Wind Direction Arrow
	WindDirection = new GameObject();
	WindDirection->AddComponent<UIComponent>();
	float angle = directionArrow->GetComponent<CombatComp>()->data.windAngle;
	UIComponent* windDirComp = WindDirection->GetComponent<UIComponent>();
	windDirComp->SetRot(angle);  // Set rotation for wind direction arrow
	windDirComp->SetScale({ 100,100 });
	windDirComp->SetPos({ -700, 400 });
	windDirComp->SetTexture("../Assets/UI/windArrow.png");
	windDirComp->SetColor(1, 1, 1);
}

void UpdateCombatUI(GameObject* player, GameObject* enemy, GameObject* directionArrow)
{
	float angle = directionArrow->GetComponent<CombatComp>()->data.windAngle;
	UIComponent* windDirComp = WindDirection->GetComponent<UIComponent>();
	windDirComp->SetRot(angle);  // Set rotation for wind direction arrow

	float playerslopeAngle = player->GetComponent<TransformComp>()->GetRot();
	UIComponent* playerAngleComp = playerAngle->GetComponent<UIComponent>();
	playerAngleComp->SetRot(playerslopeAngle);

	float directAngle = directionArrow->GetComponent<CombatComp>()->data.angle;
	UIComponent* directAngleComp = DirectAngle->GetComponent<UIComponent>();
	directAngleComp->SetRot(directAngle);

	UIComponent* moveComp = Move->GetComponent<UIComponent>();
	moveComp->SetScale({ 750 * (float(player->GetComponent<PlayerComp>()->GetMovegauge()) * 0.001f), 80 });
	moveComp->SetPos({ 150 - (750 - 750 * (float(player->GetComponent<PlayerComp>()->GetMovegauge()) * 0.001f)) / 2 , -380 });

	UIComponent* powerComp = Power->GetComponent<UIComponent>();
	powerComp->SetScale({ 750 * (float(directionArrow->GetComponent<CombatComp>()->GetPlayerPower()) * (1 / (POWER_LIMIT + DEFAULT_POWER))), 80 });
	powerComp->SetPos({ 150 - (750 - 750 * (float(directionArrow->GetComponent<CombatComp>()->GetPlayerPower()) * (1 / (POWER_LIMIT + DEFAULT_POWER)))) / 2 , -280 });


	UIComponent* hpComp = HP->GetComponent<UIComponent>();
	hpComp->SetScale({ 80, 200 * (float(player->GetComponent<PlayerComp>()->data.hp) / player->GetComponent<PlayerComp>()->data.maxLife) });
	hpComp->SetPos({ -720 , (-330 - (200 - 200 * (float(player->GetComponent<PlayerComp>()->data.hp) / player->GetComponent<PlayerComp>()->data.maxLife)) / 2.f) });


	UIComponent* enemyHpComp = enemyHP->GetComponent<UIComponent>();
	enemyHpComp->SetScale({ 80, 200 * (float(enemy->GetComponent<EnemyComp>()->data.hp) / enemy->GetComponent<EnemyComp>()->data.maxLife) });
	enemyHpComp->SetPos({ 720 , (-330 - (200 - 200 * (float(enemy->GetComponent<EnemyComp>()->data.hp) / enemy->GetComponent<EnemyComp>()->data.maxLife)) / 2.f) });


}

void ExitCombatUI()
{

}
