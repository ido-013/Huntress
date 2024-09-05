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
#include "../UI/StoreUI.h"
#include "../Background/Background.h"
#include "../Utils/Utils.h"

void level::NormalLevel::Init()
{
	//Serializer::GetInstance().LoadLevel("./Assets/Level/test.lvl");
	Serializer::GetInstance().LoadLevel("./Assets/Level/test" + std::to_string(level) + ".lvl");

	InitBackground();

	std::cout << level << std::endl;

	player = GameObjectManager::GetInstance().GetObj("player");
	enemy = GameObjectManager::GetInstance().GetObj("enemy");

	player->GetComponent<PlayerComp>()->playerData->InitData(100, 50, 50, 5, 1);

	InitCombatUI();
	//storeUI.InitStoreUI(player);
}

void level::NormalLevel::Update()
{
	UpdateCombatUI();
	UpdateBackground();

	if (AEInputCheckTriggered(AEVK_1))
	{
		GSM::GameStateManager::GetInstance().ChangeLevel(new NormalLevel(level + 1));
	}
}

void level::NormalLevel::Exit()
{

}
