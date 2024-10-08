#include "NormalLevel.h"
#include <iostream>
#include "../GSM/GameStateManager.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../ComponentManager/ComponentManager.h"
#include "../Level/ClearLevel.h"
#include "../Level/OverLevel.h"
#include "../Components.h"
#include "../Components/SubtitleComp.h"
#include "../EventManager/EventManager.h"
#include "../Prefab/Prefab.h"
#include "../Utils/Utils.h"
#include "../Level/Menu.h"
#include "../Background/Background.h"
#include "../Serializer/Serializer.h"
#include "../UI/CombatUI.h"
#include "../UIM/BtnManager.h"
#include "../Background/Background.h"
#include "../Tile/Tile.h"
#include "../Data/Data.h"
#include "../UI/EscMenu.h"
#include "../Camera/Camera.h"

level::NormalLevel::NormalLevel(int _level) : level(_level)
{
	unsigned char r = 255;
	unsigned char g = 255;
	unsigned char b = 255;
	float maxTimer = 0.6f;

	switch (level)
	{
	case 1:
	case 3:
	case 7:
		r = 224;
		g = 202;
		b = 141;
		break;
	case 2:
	case 4:
	case 8:
	case 10:
		r = 255;
		g = 255;
		b = 255;
		break;
	case 5:
	case 6:
	case 9:
		r = 118;
		g = 248;
		b = 64;
		break;
	}

	Weather::GetInstance().ChangeWeather({ -4000, -2500 }, { 4000, -300 }, { 10, 10 }, r, g, b, 0.3f, 0.6f);
}

level::NormalLevel::~NormalLevel()
{

}

void level::NormalLevel::Init()
{
	CombatComp::blocks.reserve(200);
	Serializer::GetInstance().LoadLevel("./Assets/Level/test" + std::to_string(level) + ".lvl");
	CombatComp::isHit = false;
	CombatComp::isItemUsed = false;
	CombatComp::SetItemState(false);
	InitBackground();
	GameObjectManager::GetInstance().GetObj("directionArrow")->GetComponent<CombatComp>()->InitOrbit();
	player = GameObjectManager::GetInstance().GetObj("player");
	enemy = GameObjectManager::GetInstance().GetObj("enemy");

	CombatHUD.InitCombatUI();

#ifdef _DEBUG
	std::cout << "Current Level : " << level << std::endl;
#endif
	if (level == 1)
	{
		player->GetComponent<PlayerComp>()->playerData->InitData(15, 50, 50, 5, 1);
		player->GetComponent<PlayerComp>()->playerData->inventory.InitInventory();
	}

	storeUI.InitStoreUI(player);
	Escmenu.InitEscUI();
}

void level::NormalLevel::Update()
{
	CombatHUD.UpdateCombatUI();
	Escmenu.UpdateEscUI(&storeUI);
	storeUI.UpdateStoreUI();
	UpdateBackground();
	Weather::GetInstance().Update();

#ifdef _DEBUG
	if (AEInputCheckTriggered(AEVK_F1))
	{
		enemy->GetComponent<EnemyComp>()->big = true;
	}

	if (AEInputCheckTriggered(AEVK_F2))
	{
		enemy->GetComponent<EnemyComp>()->stun = true;
	}

	if (AEInputCheckTriggered(AEVK_F3))
	{
		player->GetComponent<PlayerComp>()->GBY = true;
	}

#endif

	if (CombatComp::state == CombatComp::CLEAR)
	{
		if (level == 10)
		{
			player->GetComponent<PlayerComp>()->playerData->RemoveData();
			GSM::GameStateManager::GetInstance().ChangeLevel(new ClearLevel);
		}
		else
		{
			GSM::GameStateManager::GetInstance().ChangeLevel(new NormalLevel(level + 1));
			player = GameObjectManager::GetInstance().GetObj("player");
			enemy = GameObjectManager::GetInstance().GetObj("enemy");
			switch (enemy->GetComponent<EnemyComp>()->enemyData->grade)
			{
			case Data::EnemyData::GRADE::Normal :

				player->GetComponent<PlayerComp>()->playerData->gold += 8 + (rand() % 3);
				break;
			case Data::EnemyData::GRADE::Elite :

				player->GetComponent<PlayerComp>()->playerData->gold += 15 + (rand() % 3) * 2;
				break;
			case Data::EnemyData::GRADE::Boss :

				player->GetComponent<PlayerComp>()->playerData->gold += 25 + (rand() % 3) * 3;
				break;
			}
		}
	}

	if (CombatComp::state == CombatComp::RESET)
	{
		GSM::GameStateManager::GetInstance().ChangeLevel(new Menu);
	}

}

void level::NormalLevel::Exit()
{
	CombatHUD.ExitCombatUI();
	storeUI.ExitStoreUI();
	CombatComp::blocks.clear();
}
