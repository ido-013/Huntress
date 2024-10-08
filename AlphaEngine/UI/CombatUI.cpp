#include "CombatUI.h"
#include "../GameObject/GameObject.h"
#include "../Components/AudioComp.h"
#include "../Components/UIComp.h"
#include "../Components/PlayerComp.h"
#include "../Components/EnemyComp.h"
#include "../Components/ButtonComp.h"
#include "../Combat/Combat.h"
#include "../Components/TransformComp.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Data/Data.h"
#include "../Components/SubtitleComp.h"
#include "../Data/Inventory.h"
#include "ItemInfo.h"



CombatUI::~CombatUI()
{
	
}

void CombatUI::InitCombatUI()
{
	GameObject* player = GameObjectManager::GetInstance().GetObj("player");
	GameObject* enemy = GameObjectManager::GetInstance().GetObj("enemy");
	GameObject* directionArrow = GameObjectManager::GetInstance().GetObj("directionArrow");

	UIBAR = new GameObject();
	UIBAR->AddComponent<UIComponent>();
	UIComponent* uiBarComp = UIBAR->GetComponent<UIComponent>();
	uiBarComp->SetScale({ 1600, 250 });
	uiBarComp->SetPos({ 0, -330 });
	uiBarComp->SetTexture("Assets/UI/Option.png");
	uiBarComp->SetColor(0, 0, 0);
	// Power Bar
	PowerFrame = new GameObject();
	PowerFrame->AddComponent<UIComponent>();
	UIComponent* powerFrameComp = PowerFrame->GetComponent<UIComponent>();
	powerFrameComp->SetScale({ 720 , 90 });
	powerFrameComp->SetPos({ 250  , -280 });
	powerFrameComp->SetTexture("Assets/UI/GAUGE_BOARD.png");
	powerFrameComp->SetColor(0, 0, 0);
	Power = new GameObject();
	Power->AddComponent<UIComponent>();
	UIComponent* powerComp = Power->GetComponent<UIComponent>();
	powerComp->SetScale({ 700 * (float(directionArrow->GetComponent<CombatComp>()->GetPlayerPower() - PLAYER_POWER_MIN) * (1 / (PLAYER_POWER_MAX + DEFAULT_POWER - PLAYER_POWER_MIN))), 80 });
	powerComp->SetPos({ 250 - (700 - 700 * (float(directionArrow->GetComponent<CombatComp>()->GetPlayerPower() - PLAYER_POWER_MIN) * (1 / (PLAYER_POWER_MAX + DEFAULT_POWER - PLAYER_POWER_MIN)))) / 2 , -280 });
	powerComp->SetTexture("Assets/UI/MOVE_GAUGE.png");
	powerComp->SetColor(255, 0, 0);

	// Move Bar
	MoveFrame = new GameObject();
	MoveFrame->AddComponent<UIComponent>();
	UIComponent* MoveFrameComp = MoveFrame->GetComponent<UIComponent>();
	MoveFrameComp->SetScale({ 720 , 90 });
	MoveFrameComp->SetPos({ 250  , -380 });
	MoveFrameComp->SetTexture("Assets/UI/GAUGE_BOARD.png");
	MoveFrameComp->SetColor(0, 0, 0);;
	Move = new GameObject();
	Move->AddComponent<UIComponent>();
	UIComponent* moveComp = Move->GetComponent<UIComponent>();
	moveComp->SetScale({ 700 * (float(player->GetComponent<PlayerComp>()->GetMovegauge()) * 0.001f), 80 });
	moveComp->SetPos({ 250 - (700 - 700 * (float(player->GetComponent<PlayerComp>()->GetMovegauge()) * 0.001f)) / 2 , -380 });
	moveComp->SetTexture("Assets/UI/MOVE_GAUGE.png");
	moveComp->SetColor(0, 255, 0);

	// Angle UI
	Angle = new GameObject();
	Angle->AddComponent<UIComponent>();
	UIComponent* angleComp = Angle->GetComponent<UIComponent>();
	angleComp->SetPos({ -210 , -330 });
	angleComp->SetScale({ 200, 200 });
	angleComp->SetTexture("Assets/UI/Angle.png");
	angleComp->SetColor(0, 0, 0);

	//playerAngleUI
	playerAngle = new GameObject();
	playerAngle->AddComponent<UIComponent>();
	UIComponent* playerAngleComp = playerAngle->GetComponent<UIComponent>();
	playerAngleComp->SetPos({ -210, -330 });
	playerAngleComp->SetRot(0.5f);
	playerAngleComp->SetScale({ 150,5 });
	playerAngleComp->SetTexture("Assets/arrow.png");
	playerAngleComp->SetColor(0, 120, 0);
	PreDirection = new GameObject();
	PreDirection->AddComponent<UIComponent>();
	UIComponent* transPreDirect = PreDirection->GetComponent<UIComponent>();
	transPreDirect->SetScale({ 150, 20 });
	transPreDirect->SetPos({ -210,-330 });
	transPreDirect->SetTexture("./Assets/UI/Arrow.png");
	transPreDirect->SetColor(0, 0, 220);
	transPreDirect->SetAlpha(0);

	//DirectAngleUI
	DirectAngle = new GameObject();
	DirectAngle->AddComponent<UIComponent>();
	UIComponent* directAngleComp = DirectAngle->GetComponent<UIComponent>();
	directAngleComp->SetPos({ -210,-330 });
	directAngleComp->SetColor(0, 255, 0);
	directAngleComp->SetTexture("Assets/UI/Arrow.png");
	directAngleComp->SetScale({ 100, 20 });


	// HP Bar
	HPFrame = new GameObject();
	HPFrame->AddComponent<UIComponent>();
	UIComponent* hpFrameComp = HPFrame->GetComponent<UIComponent>();
	hpFrameComp->SetScale({ 100, 220 });
	hpFrameComp->SetPos({ -700 , -330 });
	hpFrameComp->SetTexture("Assets/UI/HP_FRAME.png");
	hpFrameComp->SetColor(0, 0, 0);
	HP = new GameObject("HP");
	HP->AddComponent<UIComponent>();
	UIComponent* hpComp = HP->GetComponent<UIComponent>();
	hpComp->SetScale({ 70, 200 * (float(player->GetComponent<PlayerComp>()->playerData->hp) / player->GetComponent<PlayerComp>()->playerData->maxLife) });
	hpComp->SetPos({ -700 , (-330 - (200 - 200 * (float(player->GetComponent<PlayerComp>()->playerData->hp) / player->GetComponent<PlayerComp>()->playerData->maxLife)) / 2.f) });
	hpComp->SetTexture("Assets/UI/HP_GAUGE.png");
	hpComp->SetColor(0, 0, 0);

	item[0] = new GameObject();
	item[0]->AddComponent<UIComponent>();
	UIComponent* itemComp0 = item[0]->GetComponent<UIComponent>();
	itemComp0->SetScale({ 130, 100 });
	itemComp0->SetPos({ -550, -280 });
	itemComp0->SetTexture("Assets/UI/HP_FRAME.png");
	itemComp0->SetColor(0, 0, 0);

	item[1] = new GameObject();
	item[1]->AddComponent<UIComponent>();
	UIComponent* itemComp1 = item[1]->GetComponent<UIComponent>();
	itemComp1->SetScale({ 130, 100 });
	itemComp1->SetPos({ -550, -380 });
	itemComp1->SetTexture("Assets/UI/HP_FRAME.png");
	itemComp1->SetColor(0, 0, 0);
	item[2] = new GameObject();
	item[2]->AddComponent<UIComponent>();
	UIComponent* itemComp2 = item[2]->GetComponent<UIComponent>();
	itemComp2->SetScale({ 130, 100 });
	itemComp2->SetPos({ -420, -280 });
	itemComp2->SetTexture("Assets/UI/HP_FRAME.png");
	itemComp2->SetColor(0, 0, 0);
	item[3] = new GameObject();
	item[3]->AddComponent<UIComponent>();
	UIComponent* itemComp3 = item[3]->GetComponent<UIComponent>();
	itemComp3->SetScale({ 130, 100 });
	itemComp3->SetPos({ -420, -380 });
	itemComp3->SetTexture("Assets/UI/HP_FRAME.png");
	itemComp3->SetColor(0, 0, 0);


	itemIcon[0] = new GameObject();
	itemIcon[0]->AddComponent<UIComponent>();
	itemIcon[0]->AddComponent<ButtonComp>();
	UIComponent* itemIconComp0 = itemIcon[0]->GetComponent<UIComponent>();
	itemIconComp0->SetScale({ 130, 100 });
	itemIconComp0->SetPos({ -550, -280 });
	itemIconComp0->SetTexture("Assets/UI/Bigger.png");
	itemIconComp0->SetColor(0, 0, 0);
	ButtonComp* item0btn = itemIcon[0]->GetComponent<ButtonComp>();
	item0btn->SetOnClickFunction([]() {
		CombatComp::ItemState = CombatComp::ItemUse::Big;

	});

	SubtitleComp::AddSubtitle({ {-(f32)(0.65),-(f32)(0.73)}, f32(0.4), "Bigger", (f32)0.2, 0, 0, 1});
	
	itemIcon[1] = new GameObject();
	itemIcon[1]->AddComponent<UIComponent>();
	itemIcon[1]->AddComponent<ButtonComp>();
	UIComponent* itemIconComp1 = itemIcon[1]->GetComponent<UIComponent>();
	itemIconComp1->SetScale({ 130, 100 });
	itemIconComp1->SetPos({ -550, -380 });
	itemIconComp1->SetTexture("Assets/UI/StraightArrow.png");
	itemIconComp1->SetColor(0, 0, 0);
	ButtonComp* item1btn = itemIcon[1]->GetComponent<ButtonComp>();
	item1btn->SetOnClickFunction([]() {
	CombatComp::ItemState = CombatComp::ItemUse::Straight;

	});

	SubtitleComp::AddSubtitle({ {-(f32)(0.65),-(f32)(0.95)}, f32(0.4), "StraightArrow", (f32)0.2, 0, 0, 1 });
	itemIcon[2] = new GameObject();
	itemIcon[2]->AddComponent<UIComponent>();
	itemIcon[2]->AddComponent<ButtonComp>();
	UIComponent* itemIconComp2 = itemIcon[2]->GetComponent<UIComponent>();
	itemIconComp2->SetScale({ 130, 100 });
	itemIconComp2->SetPos({ -420, -280 });
	itemIconComp2->SetTexture("Assets/UI/stun.png");
	itemIconComp2->SetColor(0, 0, 0);
	ButtonComp* item2btn = itemIcon[2]->GetComponent<ButtonComp>();
	item2btn->SetOnClickFunction([]() {	
		CombatComp::ItemState = CombatComp::ItemUse::Stun;

	});

	SubtitleComp::AddSubtitle({ {-(f32)(0.485),-(f32)(0.73)}, f32(0.4), "stun", (f32)0.2, 0, 0, 1 });
	itemIcon[3] = new GameObject();
	itemIcon[3]->AddComponent<UIComponent>();
	itemIcon[3]->AddComponent<ButtonComp>();
	UIComponent* itemIconComp3 = itemIcon[3]->GetComponent<UIComponent>();
	itemIconComp3->SetScale({ 130, 100 });
	itemIconComp3->SetPos({ -420, -380 });
	itemIconComp3->SetTexture("Assets/UI/Orbit.png");
	itemIconComp3->SetColor(0, 0, 0);
	ButtonComp* item3btn = itemIcon[3]->GetComponent<ButtonComp>();
	item3btn->SetOnClickFunction([]() {		
		CombatComp::ItemState = CombatComp::ItemUse::Orbit;

	});

	SubtitleComp::AddSubtitle({ {-(f32)(0.485),-(f32)(0.95)}, f32(0.4), "Orbit", (f32)0.2, 0, 0, 1 });

	enemyHPFrame = new GameObject();
	enemyHPFrame->AddComponent<UIComponent>();
	UIComponent* enemyhpFrameComp = enemyHPFrame->GetComponent<UIComponent>();
	enemyhpFrameComp->SetScale({ 100, 220 });
	enemyhpFrameComp->SetPos({ 720 , -330 });
	enemyhpFrameComp->SetTexture("Assets/UI/HP_FRAME.png");
	enemyhpFrameComp->SetColor(0, 0, 0);
	enemyHP = new GameObject("enemyHP");
	enemyHP->AddComponent<UIComponent>();

	UIComponent* enemyHpComp = enemyHP->GetComponent<UIComponent>();
	enemyHpComp->SetScale({ 80, 200 * (float(enemy->GetComponent<EnemyComp>()->enemyData->hp) / enemy->GetComponent<EnemyComp>()->enemyData->maxLife) });
	enemyHpComp->SetPos({ 720 , (-330 - (200 - 200 * (float(enemy->GetComponent<EnemyComp>()->enemyData->hp) / enemy->GetComponent<EnemyComp>()->enemyData->maxLife)) / 2.f) });
	enemyHpComp->SetTexture("Assets/UI/HP_GAUGE.png");
	enemyHpComp->SetColor(200, 200, 0);

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

	WindDirection = new GameObject();
	WindDirection->AddComponent<UIComponent>();
	UIComponent* transWindDirect = WindDirection->GetComponent<UIComponent>();
	transWindDirect->SetScale({ 70,70 });
	transWindDirect->SetPos({ -725, 400 });
	transWindDirect->SetTexture("./Assets/UI/windArrow.png");
	transWindDirect->SetColor(1, 1, 1);
	SubtitleComp::AddSubtitle({ {(f32)-0.85,(f32)0.82}, 1, "WindPower", (f32)0.2, 0, 0, 1 });
	iteminfo[0]->CreateItemInfo("OrbitUI", "Assets/UI/OrbitInfo.png");
	iteminfo[1]->CreateItemInfo("StunUI", "Assets/UI/StunarrowInfo.png");
	iteminfo[2]->CreateItemInfo("StraightUI", "Assets/UI/StraightarrowInfo.png");
	iteminfo[3]->CreateItemInfo("BiggerUI", "Assets/UI/BiggerInfo.png");
	item0btn->SetOnHoverFunction([itemIconComp0,this]() {
		itemIconComp0->SetAlpha(float(0.7));
		if (CombatComp::state != CombatComp::STATE::STORE)
		{
			iteminfo[0]->SetPosition("BiggerUI", itemIconComp0->GetPos());
			iteminfo[0]->SetonInfo("BiggerUI");
			
		}
		});
	item0btn->SetOnHoverOutFunction([itemIconComp0,this]() {
		itemIconComp0->SetAlpha(1);
		if (CombatComp::state != CombatComp::STATE::STORE)
		{
			iteminfo[0]->SetPosition("BiggerUI", itemIconComp0->GetPos());
			iteminfo[0]->SetoffInfo("BiggerUI");
		}
		});
	item1btn->SetOnHoverFunction([itemIconComp1,this]() {
		itemIconComp1->SetAlpha(float(0.7));
		if (CombatComp::state != CombatComp::STATE::STORE)
		{
			iteminfo[1]->SetPosition("StunUI", itemIconComp1->GetPos());
			iteminfo[1]->SetonInfo("StunUI");
		}
		});
	item1btn->SetOnHoverOutFunction([itemIconComp1,this]() {
		itemIconComp1->SetAlpha(1);
		if (CombatComp::state != CombatComp::STATE::STORE)
		{
			iteminfo[1]->SetPosition("StunUI", itemIconComp1->GetPos());
			iteminfo[1]->SetoffInfo("StunUI");
		}
		});
	item2btn->SetOnHoverFunction([itemIconComp2,this]() {
		itemIconComp2->SetAlpha(float(0.7));
		if (CombatComp::state != CombatComp::STATE::STORE)
		{
			iteminfo[2]->SetPosition("StraightUI", itemIconComp2->GetPos());
			iteminfo[2]->SetoffInfo("StraightUI");
		}
		});
	item2btn->SetOnHoverOutFunction([itemIconComp2,this]() {
		itemIconComp2->SetAlpha(1);
		if (CombatComp::state != CombatComp::STATE::STORE)
		{
			iteminfo[2]->SetPosition("StraightUI", itemIconComp2->GetPos());
			iteminfo[2]->SetoffInfo("StraightUI");
		}
		});
	item3btn->SetOnHoverFunction([itemIconComp3,this]() {
		itemIconComp3->SetAlpha(float(0.7));
		if (CombatComp::state != CombatComp::STATE::STORE)
		{
			iteminfo[3]->SetPosition("BiggerUI", itemIconComp3->GetPos());
			iteminfo[3]->SetoffInfo("BiggerUI");
		}
		});
	item3btn->SetOnHoverOutFunction([itemIconComp3,this]() {
		itemIconComp3->SetAlpha(1);
		if (CombatComp::state != CombatComp::STATE::STORE)
		{
			iteminfo[3]->SetPosition("BiggerUI", itemIconComp3->GetPos());
			iteminfo[3]->SetoffInfo("BiggerUI");
		}
		});
}

void CombatUI::UpdateCombatUI()
{
	GameObject* player = GameObjectManager::GetInstance().GetObj("player");
	GameObject* enemy = GameObjectManager::GetInstance().GetObj("enemy");
	GameObject* directionArrow = GameObjectManager::GetInstance().GetObj("directionArrow");
	GameObject* HP_ = GameObjectManager::GetInstance().GetObj("HP");
	GameObject* enemyHP_ = GameObjectManager::GetInstance().GetObj("enemyHP");
	if (CombatComp::state != CombatComp::STATE::STORE){
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
			if(CombatComp::state != CombatComp::STATE::GAMEOVER)
				if (Move) {
					UIComponent* moveComp = Move->GetComponent<UIComponent>();
					moveComp->SetScale({ 700 * (float(player->GetComponent<PlayerComp>()->GetMovegauge()) * 0.001f), 80 });
					moveComp->SetPos({ 250.f - (700 - 700 * (float(player->GetComponent<PlayerComp>()->GetMovegauge()) * 0.001f)) / 2 , -380 });

					UIComponent* powerComp = Power->GetComponent<UIComponent>();
					powerComp->SetScale({ 700 * (float(directionArrow->GetComponent<CombatComp>()->GetPlayerPower() - PLAYER_POWER_MIN) * (1 / (PLAYER_POWER_MAX + DEFAULT_POWER - PLAYER_POWER_MIN))), 80 });
					powerComp->SetPos({ 250 - (700 - 700 * (float(directionArrow->GetComponent<CombatComp>()->GetPlayerPower() - PLAYER_POWER_MIN) * (1 / (PLAYER_POWER_MAX + DEFAULT_POWER - PLAYER_POWER_MIN)))) / 2 , -280 });

					}
			
		}
	
			if (HP_)
			{
				UIComponent* hpComp = HP_->GetComponent<UIComponent>();
				hpComp->SetScale({ 80, 200 * (float(player->GetComponent<PlayerComp>()->playerData->hp) / player->GetComponent<PlayerComp>()->playerData->maxLife) });
				hpComp->SetPos({ -700 , (-330 - (200 - 200 * (float(player->GetComponent<PlayerComp>()->playerData->hp) / player->GetComponent<PlayerComp>()->playerData->maxLife)) / 2.f) });
			}
			if (enemyHP_)
			{
				UIComponent* enemyHpComp = enemyHP_->GetComponent<UIComponent>();
				enemyHpComp->SetScale({ 80, 200 * (float(enemy->GetComponent<EnemyComp>()->enemyData->hp) / enemy->GetComponent<EnemyComp>()->enemyData->maxLife) });
				enemyHpComp->SetPos({ 720 , (-330 - (200 - 200 * (float(enemy->GetComponent<EnemyComp>()->enemyData->hp) / enemy->GetComponent<EnemyComp>()->enemyData->maxLife)) / 2.f) });
			}
		
	}
	if (SubtitleComp::FindSubtitle("WindPower"))
	{
		SubtitleComp::ModifySubtitle("WindPower", std::to_string((int)directionArrow->GetComponent<CombatComp>()->data.windPower));

	}
	if (SubtitleComp::FindSubtitle("Bigger"))
	{
		SubtitleComp::ModifySubtitle("Bigger", std::to_string((int)player->GetComponent<PlayerComp>()->playerData->inventory.GetItemCount(Inventory::Big)));
	}
	if (SubtitleComp::FindSubtitle("stun"))
	{
		SubtitleComp::ModifySubtitle("stun", std::to_string((int)player->GetComponent<PlayerComp>()->playerData->inventory.GetItemCount(Inventory::Stun)));
	}
	if (SubtitleComp::FindSubtitle("StraightArrow"))
	{
		SubtitleComp::ModifySubtitle("StraightArrow", std::to_string((int)player->GetComponent<PlayerComp>()->playerData->inventory.GetItemCount(Inventory::Straight)));
	}
	if (SubtitleComp::FindSubtitle("Orbit"))
	{
		SubtitleComp::ModifySubtitle("Orbit", std::to_string((int)player->GetComponent<PlayerComp>()->playerData->inventory.GetItemCount(Inventory::Orbit)));
	}
	// Set alpha based on whether an item is used
	float alpha = CombatComp::isItemUsed ? 0.2f : 1.0f;

	// Apply alpha to all items and subtitles if the alpha needs to change
	for (int i = 0; i < 4; i++) {
		if (item[i]->GetComponent<UIComponent>()->GetAlpha() != alpha) {
			item[i]->GetComponent<UIComponent>()->SetAlpha(alpha);
			itemIcon[i]->GetComponent<UIComponent>()->SetAlpha(alpha);
		}
	}

	// Update subtitles only if they need to change
	SubtitleComp::ModifySubtitle("Bigger", alpha);
	SubtitleComp::ModifySubtitle("stun", alpha);
	SubtitleComp::ModifySubtitle("StraightArrow", alpha);
	SubtitleComp::ModifySubtitle("Orbit", alpha);

	// Array of inventory data for checking item counts


	InventoryCheck inventoryChecks[4] = {
		{0, Inventory::Big, "Bigger"},
		{2, Inventory::Stun, "stun"},
		{1, Inventory::Straight, "StraightArrow"},
		{3, Inventory::Orbit, "Orbit"}
	};

	// Check inventory counts and set alpha accordingly
	for (const auto& check : inventoryChecks) {
		int count = (int)player->GetComponent<PlayerComp>()->playerData->inventory.GetItemCount(check.type);
		float newAlpha = (count == 0) ? 0.2f : 1.0f;

		// Update only if the current alpha is different from the new alpha
		if (item[check.index]->GetComponent<UIComponent>()->GetAlpha() != newAlpha) {
			item[check.index]->GetComponent<UIComponent>()->SetAlpha(newAlpha);
			itemIcon[check.index]->GetComponent<UIComponent>()->SetAlpha(newAlpha);
			SubtitleComp::ModifySubtitle(check.subtitleName, newAlpha);
		}
	}

}

void CombatUI::ExitCombatUI()
{
	SubtitleComp::ClearSubtitle();
}
