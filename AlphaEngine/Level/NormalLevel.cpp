#include "NormalLevel.h"
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
#include "../Utils/Utils.h"
#include "../Level/Menu.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Background/Background.h"
#include "../Serializer/Serializer.h"
#include <iostream>
#include "../UI/CombatUI.h"
#include "../UIM/BtnManager.h"

#include "../Background/Background.h"
#include "../Utils/Utils.h"
#include "../Tile/Tile.h"
#include "../Level/ClearLevel.h"
#include "../Level/OverLevel.h"
#include "../Components/SubtitleComp.h"
#include "../Data/Data.h"
#include "../UI/EscMenu.h"
EscUI Escmenu;
void level::NormalLevel::Init()
{
	Serializer::GetInstance().LoadLevel("./Assets/Level/test" + std::to_string(level) + ".lvl");

	InitBackground();

	player = GameObjectManager::GetInstance().GetObj("player");
	enemy = GameObjectManager::GetInstance().GetObj("enemy");

	InitCombatUI();
	Escmenu.InitEscUI();
#ifdef _DEBUG
	std::cout << "Current Level : " << level << std::endl;
#endif
	if (level == 1)
	{
		player->GetComponent<PlayerComp>()->playerData->InitData(15, 50, 50, 5, 1);
	}

	storeUI.InitStoreUI(player);
	//else
	//{
	//	Tile::ChangeTile();
	//}
}

void level::NormalLevel::Update()
{
	UpdateCombatUI();
	UpdateBackground();

	storeUI.UpdateStoreUI();
	Escmenu.UpdateEscUI();

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
}

void level::NormalLevel::Exit()
{
	// 리소스 정리 등의 코드
	storeUI.ExitStoreUI();
}
