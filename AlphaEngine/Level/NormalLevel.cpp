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


level::NormalLevel::~NormalLevel()
{
}

void level::NormalLevel::Init()
{
	CombatComp::blocks.reserve(200);
	Serializer::GetInstance().LoadLevel("./Assets/Level/test" + std::to_string(level) + ".lvl");
	Camera::GetInstance().fix = true;
	
	InitBackground();
	
	player = GameObjectManager::GetInstance().GetObj("player");
	enemy = GameObjectManager::GetInstance().GetObj("enemy");

	InitCombatUI();

#ifdef _DEBUG
	std::cout << "Current Level : " << level << std::endl;
#endif
	if (level == 1)
	{
		player->GetComponent<PlayerComp>()->playerData->InitData(15, 50, 50, 5, 1);
	}

	storeUI.InitStoreUI(player);
	Escmenu.InitEscUI();
}

void level::NormalLevel::Update()
{
	Escmenu.UpdateEscUI(&storeUI);

	UpdateBackground();


	if (CombatComp::state == CombatComp::CLEAR)
	{
		if (level == 10)
			GSM::GameStateManager::GetInstance().ChangeLevel(new ClearLevel);
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
	UpdateCombatUI();
}

void level::NormalLevel::Exit()
{
	
	storeUI.ExitStoreUI();
	CombatComp::blocks.clear();
}
