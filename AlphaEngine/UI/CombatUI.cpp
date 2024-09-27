#include "CombatUI.h"
#include "../GameObject/GameObject.h"
#include "../Components/AudioComp.h"
#include "../Components/UIComp.h"
#include "../Components/PlayerComp.h"
#include "../Components/EnemyComp.h"
#include "../Combat/Combat.h"
#include "../Components/TransformComp.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Data/Data.h"
#include "../Components/SubtitleComp.h"
GameObject* UIBAR = nullptr;
GameObject* PowerFrame = nullptr;
GameObject* Power = nullptr;
GameObject* MoveFrame = nullptr;
GameObject* Move = nullptr;
GameObject* Angle = nullptr;
GameObject* playerAngle = nullptr;
GameObject* DirectAngle = nullptr;

GameObject* HPFrame = nullptr;
GameObject* HP = nullptr;
GameObject* enemyHPFrame = nullptr;
GameObject* enemyHP = nullptr;
GameObject* Attack = nullptr;
GameObject* enemyAttack = nullptr;
GameObject* WindDirection = nullptr;
GameObject* PreDirection = nullptr;
GameObject* Wind = nullptr;
GameObject* WindFrame = nullptr;


void InitCombatUI()
{
	GameObject* player = GameObjectManager::GetInstance().GetObj("player");
	GameObject* enemy = GameObjectManager::GetInstance().GetObj("enemy");
	GameObject* directionArrow = GameObjectManager::GetInstance().GetObj("directionArrow");

	UIBAR = new GameObject();
	UIBAR->AddComponent<UIComponent>();
	UIComponent* uiBarComp = UIBAR->GetComponent<UIComponent>();
	uiBarComp->SetScale({ 1600, 250 });
	uiBarComp->SetPos({ 0, -330 });
	uiBarComp->SetTexture("Assets/UI/UIBar.png");
	uiBarComp->SetColor(0, 0, 0);

	// Power Bar
	PowerFrame = new GameObject();
	PowerFrame->AddComponent<UIComponent>();
	UIComponent* powerFrameComp = PowerFrame->GetComponent<UIComponent>();
	powerFrameComp->SetScale({ 740 , 90 });
	powerFrameComp->SetPos({ 120  , -280 });
	powerFrameComp->SetTexture("Assets/UI/GAUGE_BOARD.png");
	powerFrameComp->SetColor(0, 0, 0);
	Power = new GameObject();
	Power->AddComponent<UIComponent>();
	UIComponent* powerComp = Power->GetComponent<UIComponent>();
	powerComp->SetScale({ 720 * (float(directionArrow->GetComponent<CombatComp>()->GetPlayerPower()) * (1 / (PLAYER_POWER_LIMIT + DEFAULT_POWER))), 80 });
	powerComp->SetPos({ 120 - (750 - 750 * (float(directionArrow->GetComponent<CombatComp>()->GetPlayerPower()) * (1 / (PLAYER_POWER_LIMIT + DEFAULT_POWER)))) / 2 , -280 });
	powerComp->SetTexture("Assets/UI/MOVE_GAUGE.png");
	powerComp->SetColor(255, 0, 0);

	// Move Bar
	MoveFrame = new GameObject();
	MoveFrame->AddComponent<UIComponent>();
	UIComponent* MoveFrameComp = MoveFrame->GetComponent<UIComponent>();
	MoveFrameComp->SetScale({ 740 , 90 });
	MoveFrameComp->SetPos({ 120  , -380 });
	MoveFrameComp->SetTexture("Assets/UI/GAUGE_BOARD.png");
	MoveFrameComp->SetColor(0, 0, 0);;
	Move = new GameObject();
	Move->AddComponent<UIComponent>();
	UIComponent* moveComp = Move->GetComponent<UIComponent>();
	moveComp->SetScale({ 720 * (float(player->GetComponent<PlayerComp>()->GetMovegauge()) * 0.001f), 80 });
	moveComp->SetPos({ 120 - (750 - 750 * (float(player->GetComponent<PlayerComp>()->GetMovegauge()) * 0.001f)) / 2 , -380 });
	moveComp->SetTexture("Assets/UI/MOVE_GAUGE.png");
	moveComp->SetColor(0, 255, 0);

	// Angle UI
	Angle = new GameObject();
	Angle->AddComponent<UIComponent>();
	UIComponent* angleComp = Angle->GetComponent<UIComponent>();
	angleComp->SetPos({ -370 , -330 });
	angleComp->SetScale({ 200, 200 });
	angleComp->SetTexture("Assets/UI/Angle.png");
	angleComp->SetColor(0, 0, 0);

	//playerAngleUI
	playerAngle = new GameObject();
	playerAngle->AddComponent<UIComponent>();
	UIComponent* playerAngleComp = playerAngle->GetComponent<UIComponent>();
	playerAngleComp->SetPos({ -370, -330 });
	playerAngleComp->SetRot(0.5f);
	playerAngleComp->SetScale({ 150,10 });
	playerAngleComp->SetTexture("Assets/arrow.png");
	playerAngleComp->SetColor(0, 0, 0);
	PreDirection = new GameObject();
	PreDirection->AddComponent<UIComponent>();
	UIComponent* transPreDirect = PreDirection->GetComponent<UIComponent>();
	transPreDirect->SetScale({ 150, 20 });
	transPreDirect->SetPos({ -370,-330 });
	transPreDirect->SetTexture("./Assets/UI/Arrow.png");
	transPreDirect->SetColor(0, 0, 220);
	transPreDirect->SetAlpha(0);
	//DirectAngleUI
	DirectAngle = new GameObject();
	DirectAngle->AddComponent<UIComponent>();
	UIComponent* directAngleComp = DirectAngle->GetComponent<UIComponent>();
	directAngleComp->SetPos({ -370,-330 });
	directAngleComp->SetColor(0, 255, 0);
	directAngleComp->SetTexture("Assets/UI/Arrow.png");
	directAngleComp->SetScale({ 100, 20 });


	// HP Bar
	HPFrame = new GameObject();
	HPFrame->AddComponent<UIComponent>();
	UIComponent* hpFrameComp = HPFrame->GetComponent<UIComponent>();
	hpFrameComp->SetScale({ 100, 220 });
	hpFrameComp->SetPos({ -720 , -330 });
	hpFrameComp->SetTexture("Assets/UI/HP_FRAME.png");
	hpFrameComp->SetColor(0, 0, 0);
	HP = new GameObject();
	HP->AddComponent<UIComponent>();
	UIComponent* hpComp = HP->GetComponent<UIComponent>();
	hpComp->SetScale({ 70, 200 * (float(player->GetComponent<PlayerComp>()->playerData->hp) / player->GetComponent<PlayerComp>()->playerData->maxLife) });
	hpComp->SetPos({ -720 , (-330 - (200 - 200 * (float(player->GetComponent<PlayerComp>()->playerData->hp) / player->GetComponent<PlayerComp>()->playerData->maxLife)) / 2.f) });
	hpComp->SetTexture("Assets/UI/HP_GAUGE.png");
	hpComp->SetColor(0, 0, 0);

	// Player Attack
	Attack = new GameObject();
	Attack->AddComponent<UIComponent>();
	UIComponent* attackComp = Attack->GetComponent<UIComponent>();
	attackComp->SetScale({ 130, 200 });
	attackComp->SetPos({ -600, -330 });
	attackComp->SetTexture("Assets/UI/HP_FRAME.png");
	attackComp->SetColor(0, 0, 0);
	//SubtitleComp::AddSubtitle({ {-0.75, -0.77}, 0.6, "randomVal1", 0, 0, 0, 1 });

	// Enemy HP Bar
	enemyHPFrame = new GameObject();
	enemyHPFrame->AddComponent<UIComponent>();
	UIComponent* enemyhpFrameComp = enemyHPFrame->GetComponent<UIComponent>();
	enemyhpFrameComp->SetScale({ 100, 220 });
	enemyhpFrameComp->SetPos({ 720 , -330 });
	enemyhpFrameComp->SetTexture("Assets/UI/HP_FRAME.png");
	enemyhpFrameComp->SetColor(0, 0, 0);
	enemyHP = new GameObject();
	enemyHP->AddComponent<UIComponent>();

	UIComponent* enemyHpComp = enemyHP->GetComponent<UIComponent>();
	enemyHpComp->SetScale({ 80, 200 * (float(enemy->GetComponent<EnemyComp>()->enemyData->hp) / player->GetComponent<PlayerComp>()->playerData->maxLife) });
	enemyHpComp->SetPos({ 720 , (-330 - (200 - 200 * (float(enemy->GetComponent<EnemyComp>()->enemyData->hp) / player->GetComponent<PlayerComp>()->playerData->maxLife)) / 2.f) });
	enemyHpComp->SetTexture("Assets/UI/HP_GAUGE.png");
	enemyHpComp->SetColor(200, 200, 0);

	// Enemy Attack
	enemyAttack = new GameObject();
	enemyAttack->AddComponent<UIComponent>();
	UIComponent* enemyAttackComp = enemyAttack->GetComponent<UIComponent>();
	enemyAttackComp->SetScale({ 130, 200 });
	enemyAttackComp->SetPos({ 600, -330 });
	enemyAttackComp->SetTexture("Assets/UI/HP_FRAME.png");
	enemyAttackComp->SetColor(0, 0, 0);
	//SubtitleComp::AddSubtitle({ {0.75, -0.77}, 0.6, "randomVal2", 0, 0, 0, 1 });

	// Wind UI
	Wind = new GameObject();
	Wind->AddComponent<UIComponent>();
	UIComponent* windComp = Wind->GetComponent<UIComponent>();
	windComp->SetScale({ 200, 100 });
	windComp->SetPos({ -700, 400 });
	windComp->SetTexture("Assets/arrow.png");
	windComp->SetColor(120, 120, 120);
	WindFrame = new GameObject();
	WindFrame->AddComponent<UIComponent>();
	UIComponent* windFrameComp = WindFrame->GetComponent<UIComponent>();
	windFrameComp->SetScale({ 200, 100 });
	windFrameComp->SetPos({ -700, 400 });
	windFrameComp->SetTexture("Assets/UI/windFrame.png");
	windFrameComp->SetColor(0, 0, 0);

	// Wind Direction Arrow
	WindDirection = new GameObject();
	WindDirection->AddComponent<UIComponent>();
	UIComponent* transWindDirect = WindDirection->GetComponent<UIComponent>();
	transWindDirect->SetScale({ 70,70 });
	transWindDirect->SetPos({ -725, 400 });
	transWindDirect->SetTexture("./Assets/UI/windArrow.png");
	transWindDirect->SetColor(1, 1, 1);
	SubtitleComp::AddSubtitle({ {(f32) - 0.85,(f32)0.82}, 1, "WindPower", (f32)0.2, 0, 0, 1});

}

void UpdateCombatUI()
{
	GameObject* player = GameObjectManager::GetInstance().GetObj("player");
	GameObject* enemy = GameObjectManager::GetInstance().GetObj("enemy");
	GameObject* directionArrow = GameObjectManager::GetInstance().GetObj("directionArrow");


	if (CombatComp::state==CombatComp::STATE::COMBAT|| CombatComp::state == CombatComp::STATE::RESET|| CombatComp::state == CombatComp::STATE::READY|| CombatComp::state == CombatComp::STATE::KILLENEMY)
	{
		if (directionArrow) {
			float angle = directionArrow->GetComponent<CombatComp>()->data.windAngle;
			UIComponent* windDirComp = WindDirection->GetComponent<UIComponent>();
			windDirComp->SetRot(angle);  // Set rotation for wind direction arrow

			if ((int)directionArrow->GetComponent<CombatComp>()->data.windPower == 0)
				windDirComp->SetAlpha(0);
			else
				windDirComp->SetAlpha(1);
		}
		if (player)
		{
			float playerslopeAngle = player->GetComponent<TransformComp>()->GetRot();
			UIComponent* playerAngleComp = playerAngle->GetComponent<UIComponent>();
			playerAngleComp->SetRot(playerslopeAngle);
			if (directionArrow->GetComponent<CombatComp>()->turn == CombatComp::PLAYERTURN)
			{
				float directAngle = directionArrow->GetComponent<CombatComp>()->data.angle;
				UIComponent* directAngleComp = DirectAngle->GetComponent<UIComponent>();
				if (directionArrow->GetComponent<CombatComp>()->isLaunched == TRUE)
				{
					UIComponent* PredirectAngle = PreDirection->GetComponent<UIComponent>();
					PredirectAngle->SetRot(directAngle);
					PredirectAngle->SetAlpha(0.5);
					directionArrow->GetComponent<CombatComp>()->isLaunched = false;

				}
				directAngleComp->SetRot(directAngle);

			}
		}

		UIComponent* moveComp = Move->GetComponent<UIComponent>();
		moveComp->SetScale({ 720 * (float(player->GetComponent<PlayerComp>()->GetMovegauge()) * 0.001f), 80 });
		moveComp->SetPos({ 120.f - (720 - 720 * (float(player->GetComponent<PlayerComp>()->GetMovegauge()) * 0.001f)) / 2 , -380 });

		UIComponent* powerComp = Power->GetComponent<UIComponent>();
		powerComp->SetScale({ 720 * (float(directionArrow->GetComponent<CombatComp>()->GetPlayerPower()) * (1 / (PLAYER_POWER_LIMIT + DEFAULT_POWER))), 80 });
		powerComp->SetPos({ 120.f - (720 - 720 * (float(directionArrow->GetComponent<CombatComp>()->GetPlayerPower()) * (1 / (PLAYER_POWER_LIMIT + DEFAULT_POWER)))) / 2 , -280 });

		UIComponent* hpComp = HP->GetComponent<UIComponent>();
		hpComp->SetScale({ 80, 200 * (float(player->GetComponent<PlayerComp>()->playerData->hp) / player->GetComponent<PlayerComp>()->playerData->maxLife) });
		hpComp->SetPos({ -720 , (-330 - (200 - 200 * (float(player->GetComponent<PlayerComp>()->playerData->hp) / player->GetComponent<PlayerComp>()->playerData->maxLife)) / 2.f) });

		UIComponent* enemyHpComp = enemyHP->GetComponent<UIComponent>();
		enemyHpComp->SetScale({ 80, 200 * (float(enemy->GetComponent<EnemyComp>()->enemyData->hp) / enemy->GetComponent<EnemyComp>()->enemyData->maxLife) });
		enemyHpComp->SetPos({ 720 , (-330 - (200 - 200 * (float(enemy->GetComponent<EnemyComp>()->enemyData->hp) / enemy->GetComponent<EnemyComp>()->enemyData->maxLife)) / 2.f) });

	}
	if (SubtitleComp::FindSubtitle("WindPower"))
	{
		SubtitleComp::ModifySubtitle("WindPower",std::to_string((int)directionArrow->GetComponent<CombatComp>()->data.windPower));

		
	}

}

void ExitCombatUI()
{
	SubtitleComp::ClearSubtitle();
}

