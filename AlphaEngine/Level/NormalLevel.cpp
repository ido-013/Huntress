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
#include "../GameObjectManager/GameObjectManager.h"
#include "../Background/Background.h"
#include "../Serializer/Serializer.h"
#include <iostream>
#include "../UI/CombatUI.h"
#include "../UIM/BtnManager.h"

#include "../Background/Background.h"
#include "../Utils/Utils.h"

#include "../Level/ClearLevel.h"
#include "../Level/OverLevel.h"

void level::NormalLevel::Init()
{
	Serializer::GetInstance().LoadLevel("./Assets/Level/test" + std::to_string(level) + ".lvl");

	InitBackground();

	player = GameObjectManager::GetInstance().GetObj("player");
	enemy = GameObjectManager::GetInstance().GetObj("enemy");

	InitCombatUI();

	if (level == 1)
	{
		player->GetComponent<PlayerComp>()->playerData->InitData(100, 50, 50, 5, 1);
	}

	if (level == 1 || level == 6)
	{
		CombatComp::isCombat = false;
		storeUI.InitStoreUI(player);
	}
}

void level::NormalLevel::Update()
{
	UpdateCombatUI();
	UpdateBackground();

	if (CombatComp::state == CombatComp::CLEAR)
	{
		if (level == 10)
			GSM::GameStateManager::GetInstance().ChangeLevel(new ClearLevel);
		else
			GSM::GameStateManager::GetInstance().ChangeLevel(new NormalLevel(level + 1));
	}

	if (CombatComp::state == CombatComp::GAMEOVER)
	{
		GSM::GameStateManager::GetInstance().ChangeLevel(new OverLevel);
	}
}

void level::NormalLevel::Exit()
{

}
