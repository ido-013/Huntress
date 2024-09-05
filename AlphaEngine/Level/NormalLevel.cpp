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

void level::NormalLevel::Init()
{
	Serializer::GetInstance().LoadLevel("./Assets/Level/test" + std::to_string(level) + ".lvl");

	InitBackground();

	player = GameObjectManager::GetInstance().GetObj("player");
	enemy = GameObjectManager::GetInstance().GetObj("enemy");

	player->GetComponent<PlayerComp>()->playerData->InitData(100, 50, 50, 500, 1);

	InitCombatUI();

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
		GSM::GameStateManager::GetInstance().ChangeLevel(new NormalLevel(level + 1));
	}
}

void level::NormalLevel::Exit()
{

}
