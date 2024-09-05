// Author : sinu

#include "CombatLevel.h"
#include "../GSM/GameStateManager.h"
#include "../ComponentManager/ComponentManager.h"
#include "../GameObject/GameObject.h"
#include "../components.h"
#include "../EventManager/EventManager.h"
#include "../Prefab/Prefab.h"
#include "../ResourceManager/ResourceManager.h"
#include "../Combat/Combat.h"
#include "../Components/EnemyComp.h"
#include "../Serializer/Serializer.h"
#include <iostream>
#include <string>
#include "../UI/CombatUI.h"
#include "../UIM/BtnManager.h"
#include "../UI/StoreUI.h"
StoreUI storeUI;

#include "../Background/Background.h"
#include "../Utils/Utils.h"

GameObject* player = nullptr;
GameObject* directionArrow = nullptr;
GameObject* enemy = nullptr;

//std::string map[30] =
//{
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-SSSSSSSSSSSSSSSSSSSSSSSSSSSSS-",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//};

//std::string map[30] =
//{
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-SL----------------------------",
//	"----L--------------------------",
//	"------L------------------------",
//	"--------L----------------------",
//	"----------L--------------------",
//	"------------L------------------",
//	"--------------L----------------",
//	"----------------SSSSSSSSSSSSSS-",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//};
//
//std::string map[30] =
//{
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------R-SL--------------",
//	"-----------R------L------------",
//	"---------R----------L----------",
//	"-------R--------------L--------",
//	"-----R------------------L------",
//	"---R----------------------L----",
//	"-SS-------------------------SS-",	
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//};

//std::string map[30] =
//{
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"--------------rl---------------",
//	"-------------rSSl--------------",
//	"------------rSSSSl-------------",
//	"-------------------------------",
//	"-SSSSSSSSSSSSSSSSSSSSSSSSSSSSS-",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//};

//std::string map[30] =
//{
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"SL-------------------------R-S-",
//	"---L---------rSl---------R-----",
//	"-----L------rSSSl------R-------",
//	"-------L---rSSSSSl---R---------",
//	"---------L---------R-----------",
//	"-----------L-----R-------------",
//	"-------------L-R---------------",
//	"-------------------------------",
//	"-------------------------------",
//};

//std::string map[30] =
//{
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"---------------------------R-S-",
//	"-------------------------R-----",
//	"-----------------------R-------",
//	"------SSSSSSS--------R---------",
//	"------SSSSSSS------R-----------",
//	"------SSSSSSS----R-------------",
//	"---------------R---------------",
//	"-------------R-----------------",
//	"-----------R-------------------",
//	"---------R---------------------",
//	"-------R-----------------------",
//	"-----R-------------------------",
//	"---R---------------------------",
//	"-SS----------------------------",
//	"-------------------------------",
//	"-------------------------------",
//};

//std::string map[30] =
//{
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"---------------SSS-------------",
//	"----rl---------SSS-------------",
//	"---rSSl--------SSS-------------",
//	"--rSSSSl-------SSS-------------",
//	"-------------------------------",
//	"-------rSSSSSSSSL--------------",
//	"------r-----------L------------",
//	"-----r--------------L----------",
//	"-SSSS-----------------SSSSSS---",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//};

//std::string map[30] =
//{
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-SSSSSSSSSSSSSSSSSSSSSSSSSSSSS-",
//	"-------------------------------",
//	"---------R-SSSSSSSSSL----------",
//	"-------R--------------L--------",
//	"-----R------------------L------",
//	"-SSSS---------------------SSSS-",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//};

//std::string map[30] =
//{
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-SSSSSL------------------------",
//	"--------L----------------------",
//	"----------L----SSS-------------",
//	"------------L------------------",
//	"--------------L----------------",
//	"----------------L--------------",
//	"------------------L----rSSS----",
//	"--------------------L----------",
//	"----------------------L--------",
//	"------------------------L------",
//	"--------------------------SSSS-",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//};

std::string map[30] =
{
	"-------------------------------",
	"-------------------------------",
	"-------------------------------",
	"-------------------------------",
	"-------------------------------",
	"-------------------------------",
	"-------------------------------",
	"-------------------------------",
	"-------------------------------",
	"-------------------------------",
	"-------------------------------",
	"-------------------------------",
	"-------------------------------",
	"-------------------------------",
	"-------------------------------",
	"-------------------------------",
	"-------------------------------",
	"-------------------------------",
	"-------------------------------",
	"------rSl-------------rSl------",
	"-----r---l-----------r---l-----",
	"----r-----l---------r-----l----",
	"---r-------l-------r-------l---",
	"--r---------l-----r---------l--",
	"-S-----------SSSSS-----------S-",
	"-------------------------------",
	"-------------------------------",
	"-------------------------------",
	"-------------------------------",
	"-------------------------------",
};

void level::CombatLevel::Init()
{
	// background
	InitBackground();

	GameObject* go = nullptr;
	TransformComp* t = nullptr;
	ColliderComp* c = nullptr;

	Prefab s("Square");
	Prefab l("LeftTri");
	Prefab r("RightTri");
	Prefab p("Player");
	Prefab e("Enemy");
	Prefab d("DirectionArrow");

	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 30; j++)
		{
			if (map[i][j] == '-')
				continue;

			else if (map[i][j] == 'S')
			{
				go = s.NewGameObject();
			}

			else if (map[i][j] == 'r')
			{
				go = r.NewGameObject();
			}

			else if (map[i][j] == 'l')
			{
				go = l.NewGameObject();
			}

			else if (map[i][j] == 'R')
			{
				go = r.NewGameObject();

				t = go->GetComponent<TransformComp>();

				t->SetScale({ width * 2, height });

				float x = MapToPosX((float)j);
				float y = MapToPosY((float)i);
				t->SetPos({ x + width / 2, y });

				c = go->GetComponent<ColliderComp>();
				c->SetCollider();

				continue;
			}

			else if (map[i][j] == 'L')
			{
				go = l.NewGameObject();

				t = go->GetComponent<TransformComp>();

				t->SetScale({ width * 2, height });

				float x = MapToPosX((float)j);
				float y = MapToPosY((float)i);
				t->SetPos({ x + width / 2, y });

				c = go->GetComponent<ColliderComp>();
				c->SetCollider();

				continue;
			}

			t = go->GetComponent<TransformComp>();

			t->SetScale({ width, height }); 

			float x = MapToPosX((float)j);
			float y = MapToPosY((float)i);

			t->SetPos({ x, y });

			c = go->GetComponent<ColliderComp>();
			c->SetCollider();
		}
	}
	
	// player
	player = p.NewGameObject("player");
	player->GetComponent<TransformComp>()->SetPos({ 115, -2335 });

	// enemy
	enemy = e.NewGameObject("enemy");
	enemy->GetComponent<TransformComp>()->SetPos({ 2875, -2335 });

	// direction Arrow
	directionArrow = d.NewGameObject("directionArrow");

	int n = 9;

	//InitData
	player->GetComponent<PlayerComp>()->playerData->InitData(100, 50, 50, 5, 1);
	//enemy->GetComponent<EnemyComp>()->enemyData->InitData(30 + n, 30 + n, 0 + n, 0, Data::EnemyData::GRADE::Normal);
	//enemy->GetComponent<EnemyComp>()->enemyData->InitData(45 + 15 * n, 45 + 15 * n, 4 + 3 * n, 3, Data::EnemyData::GRADE::Elite);
	enemy->GetComponent<EnemyComp>()->enemyData->InitData((float)60 + (float)60 * n, (float)60 + 60 * n, (float)9 + 6 * n, (float)5, Data::EnemyData::GRADE::Boss);

	//Serializer::GetInstance().SaveLevel("./Assets/Level/test10.lvl", "./Assets/Background/BG8.png");

	//Init UI
	InitCombatUI();
	storeUI.InitStoreUI(player);
}

void level::CombatLevel::Update()
{
	UpdateCombatUI();
	UpdateBackground();

	if (AEInputCheckTriggered(AEVK_1))
	{
		Data::PrintPlayerData(*player->GetComponent<PlayerComp>()->playerData);
	}
	if (AEInputCheckTriggered(AEVK_2))
	{
		Data::PrintEnemyData(*enemy->GetComponent<EnemyComp>()->enemyData);
	}
	if (AEInputCheckTriggered(AEVK_3))
	{
		Data::PrintCombatData(directionArrow->GetComponent<CombatComp>()->data);
	}
	if (AEInputCheckTriggered(AEVK_4))
	{
		std::cout << player->GetComponent<TransformComp>()->GetPos().x << " " << player->GetComponent<TransformComp>()->GetPos().y << std::endl;
	}
}

void level::CombatLevel::Exit()
{

}
