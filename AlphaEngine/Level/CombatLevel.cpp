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
#include "../Components/SubtitleComp.h"
StoreUI storeUI;

#include "../Background/Background.h"
#include "../Utils/Utils.h"
#include "../Tile/Tile.h"

GameObject* player = nullptr;
GameObject* directionArrow = nullptr;
GameObject* enemy = nullptr;

std::string map[10][30] =
{
	{
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"--P------rS--------Sl------N--",
		"-SSSSSSSS@D--------D@SSSSSSSS-",
		"--DDDDDDDD----------DDDDDDDD--",
		"---DDDDDD------------DDDDDDD--",
		"---DDDDDD-------------DDDDDD--",
		"---DDDDD--------------DDDDD---",
		"----DDDD--------------DDDDD---",
	},

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
		"-P-----------------------------",
		"-SL----------------------------",
		"-DD@L--------------------------",
		"--DDD@L------------------------",
		"--DD-DD@SS---------------------",
		"--DD-DDDD----------------------",
		"--DD-DD------------------------",
		"--DD-DD---------------------N--",
		"-DDDDDD--------------SSSSSSSSS-",
		"-DD-DDD---------------DDDDDDDD-",
		"-DD-DDDD--------------DDDDDD---",
		"-DD-DDDD---------------DDDDD---",
		"-DDDDDDD---------------DDDDD---",
		"--DDDDDD---------------DDDDD---",
	},

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
		"-------------------------------",
		"-------------------------------",
		"-------------------------------",
		"-------------------------------",
		"--P-------------------------E--",
		"-SSSSSS-----------------SSSSSS-",
		"-DDDDD-------------------DDDDD-",
		"--DDDD-------------------DDDD--",
		"--DDD---------------------DDD--",
		"--DDD---------------------DDD--",
		"--DDD---------------------DDD--",
	},

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
		"---------------D---------------",
		"---------------DD--------------",
		"--------------DDD--------------",
		"--------------DDD--------------",
		"--P----------DDD---------------",
		"-SSSL---------DDDD----------N--",
		"-DDDD@SSSS----DDDD---SSSSSSSSS-",
		"--DDDDDDD-----DDDD----DDDDDDDD-",
		"--DDDDD-------DDDD----DDDDDD---",
		"-DDDDDDD-----DDDDD-----DDDDD---",
		"-DDDDDDD-----DDDDD-----DDDDD---",
		"--DDDDDD-----DDDDD-----DDDDD---",
	},

	{
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"---------------------------B--",
		"-------------------SSSSSSSSSS-",
		"--------------------DDDDDDDD--",
		"---------------------DDDDDD---",
		"---------rS----------DDDDDD---",
		"--P-----r@D-----------DDDDD---",
		"-SSSSSSS@DD-----------DDDD----",
		"--DDDDDDDD------------DDDD----",
		"---DDDDDD--------------DDD----",
		"---DDDDD--------------DDD-----",
		"---DDDD----------------DDD----",
		"----DDD---------------DDDDD---",
	},

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
		"---------------D---------------",
		"--------------DD---------------",
		"--------------DD---------------",
		"--------------DD---------------",
		"--------------DD---------------",
		"-------------DDDD--------------",
		"-------------DDDD--------------",
		"-------------------------------",
		"-------------------------------",
		"---------------DD--------------",
		"--------------DDD--------------",
		"--P--R-S-----DDDD----------N---",
		"-SSSS@DD-----DDDDDD-----SSSSS--",
		"-DDDDDD------DDDDDD------DDD---",
		"--DDDDD-------DDDDD------DDD---",
		"--DDDDD-------DDDDD-------DD---",
		"--DDDD--------DDDDD-------DD---",
		"--DDDD--------DDDDD-------DD---",
	},

	{
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"----------------------------N-",
		"--------------------------R-S-",
		"------------------------R-@DD-",
		"----------------------R-@D----",
		"------DDDDD---------R-@D------",
		"-----DDDDDD-------R-@DDD------",
		"-----DDDDD------R-@DDDD-------",
		"--------------R-@DDDDD--------",
		"------------R-@DD-DDDD--------",
		"----------R-@D-----DDD--------",
		"--------R-@--------DDD--------",
		"------R-@D---------DDD--------",
		"----R-@DDD---------DDD--------",
		"-PR-@DDD-----------DDD--------",
		"-S@DDDDD-----------DDD--------",
		"-----DDD-----------DDD--------",
		"-----DDD-----------DDD--------",
		"-----DDD-----------DDD--------",
		"-----DDD-----------DDD--------",
		"-----DDD-----------DDD--------"
	},

	{
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"---------------DD-------------",
		"----rl---------DD-------------",
		"---rDDl-------DDD-------------",
		"--rDDDDl------DDD-------------",
		"------------------------------",
		"-------rS-----SL--------------",
		"------r@D-----DD@L------------",
		"--P--r@DD-----DDDD@L-------E--",
		"-SSSS@DDD------DDDDD@SSSSSSSS-",
		"-DDDDDDD-------DDDD-----DDDD--",
		"--D-DDDD--------DD------DDD---",
		"----DDDD--------DDD------DD---",
		"-----DDD--------DDD------DD---",
		"-----DD--------DDDDD----DDD---",
	},

	{
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"--P---------------------------",
		"-SSSSL------------------------",
		"-DDDDD@L----------------------",
		"-DDDDDDD@L----SSS-------------",
		"--DDDDD--D@L------------------",
		"--DDDD----DD@L----------------",
		"--DDDD----DDDD@L--------------",
		"--DDDD----DDDD--@L----rSSS----",
		"--DDDD----DDDD----@L----------",
		"-DDDDD----DDDD----DD@L--------",
		"-DDDDD----DDDD------DD@L---N--",
		"-DDDDD----DDDD------DDDD@SSSS-",
		"-DDDD-----DDDD-------DDDDDDD--",
		"-DDDD-----DDDD-------DDDDD----",
		"-DDDD------DDD--------DDDD----",
		"--DDD------DDD--------DDD-----",
		"--DDD------DDD--------DDD-----",
	},

	{
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------------------------------",
		"------rSl------------rSl------",
		"-----r@D@S----------S@D@l-----",
		"----r@DDDD----------DDDD@l----",
		"---r@DDDD-----------DDDDD@l---",
		"-Pr@DDDDD------------DDDDD@lB-",
		"-S@DDDDDD-------------DDDDD@S-",
		"-DDDDDDD--------------DDDDDDD-",
		"-DDDDDDD---------------DDDDD--",
		"--DDDDD----------------DDDDD--",
		"--DDDD-----------------DDDD---",
		"--DDDD-----------------DDDD---",
	}
};

int tileNum[10] = { 0, 2, 0, 2, 1, 1, 0, 2, 1, 2 };
int bgNum[10] = { 1, 2, 3, 4, 5, 6, 7, 1, 2, 8 };

void level::CombatLevel::Init()
{
	// background
	InitBackground();

	int i = 9;

	Tile::ChangeTile(tileNum[i]);

	GameObject* go = nullptr;
	TransformComp* t = nullptr;
	ColliderComp* c = nullptr;

	Prefab s("Square");
	Prefab l("LeftTri");
	Prefab r("RightTri");
	Prefab p("Player");
	Prefab e("Enemy");
	Prefab d("DirectionArrow");

	AEVec2 pPos;
	AEVec2 ePos;
	char initial;

	for (int j = 0; j < 30; j++)
	{
		for (int k = 0; k < 30; k++)
		{
			if (map[i][j][k] == '-')
				continue;

			else if (map[i][j][k] == 'S')
			{
				go = s.NewGameObject();
			}

			else if (map[i][j][k] == 'D')
			{
				go = s.NewGameObject();
				go->GetComponent<SpriteComp>()->SetTexture("./Assets/Tile/FallGrassTileRect3.png");
			}

			else if (map[i][j][k] == '@')
			{
				go = s.NewGameObject();
				go->GetComponent<SpriteComp>()->SetTexture("./Assets/Tile/FallGrassTileRect3.png");
				go->RemoveComponent("ColliderComp");
			}

			else if (map[i][j][k] == 'r')
			{
				go = r.NewGameObject();
			}

			else if (map[i][j][k] == 'l')
			{
				go = l.NewGameObject();
			}

			else if (map[i][j][k] == 'P')
			{
				pPos = { MapToPosX((float)k), MapToPosY((float)j) };
				continue;
			}

			else if (map[i][j][k] == 'N')
			{
				ePos = { MapToPosX((float)k), MapToPosY((float)j) };
				initial = 'N';
				continue;
			}

			else if (map[i][j][k] == 'E')
			{
				ePos = { MapToPosX((float)k), MapToPosY((float)j) };
				initial = 'E';
				continue;
			}

			else if (map[i][j][k] == 'B')
			{
				ePos = { MapToPosX((float)k), MapToPosY((float)j) };
				initial = 'B';
				continue;
			}

			else if (map[i][j][k] == 'R')
			{
				go = r.NewGameObject();

				t = go->GetComponent<TransformComp>();

				t->SetScale({ width * 2, height });

				float x = MapToPosX((float)k);
				float y = MapToPosY((float)j);
				t->SetPos({ x + width / 2, y });

				c = go->GetComponent<ColliderComp>();
				c->SetCollider();

				continue;
			}

			else if (map[i][j][k] == 'L')
			{
				go = l.NewGameObject();

				t = go->GetComponent<TransformComp>();

				t->SetScale({ width * 2, height });

				float x = MapToPosX((float)k);
				float y = MapToPosY((float)j);
				t->SetPos({ x + width / 2, y });

				c = go->GetComponent<ColliderComp>();
				c->SetCollider();

				continue;
			}

			t = go->GetComponent<TransformComp>();

			t->SetScale({ width, height });

			float x = MapToPosX((float)k);
			float y = MapToPosY((float)j);

			t->SetPos({ x, y });

			c = go->GetComponent<ColliderComp>();
			if (c != nullptr)
				c->SetCollider();
		}
	}
	
	// player
	player = p.NewGameObject("player");

	t = player->GetComponent<TransformComp>(); 
	t->SetScale({ 50, 50 });
	t->SetPos({ pPos.x, pPos.y });

	c = player->GetComponent<ColliderComp>();
	if (c != nullptr)
		c->SetCollider();

	// enemy
	enemy = e.NewGameObject("enemy");

	if (initial == 'N')
	{
		enemy->GetComponent<EnemyComp>()->enemyData->InitData(30, 30, 0, 0, Data::EnemyData::GRADE::Normal);
	}

	else if (initial == 'E')
	{
		enemy->GetComponent<EnemyComp>()->enemyData->InitData(45.f + 15.f, 45.f + 15.f, 4.f, 3.f, Data::EnemyData::GRADE::Elite);
	}

	else
	{
		enemy->GetComponent<EnemyComp>()->enemyData->InitData((float)60 + (float)60, (float)60 + 60, (float)9, (float)5, Data::EnemyData::GRADE::Boss);
	}
	
	t = enemy->GetComponent<TransformComp>();
	t->SetScale({ 50, 50 });
	t->SetPos({ ePos.x, ePos.y });

	c = enemy->GetComponent<ColliderComp>();
	if (c != nullptr)
		c->SetCollider();

	// direction Arrow
	directionArrow = d.NewGameObject("directionArrow");

	Serializer::GetInstance().SaveLevel("./Assets/Level/test" + std::to_string(i + 1) + ".lvl", "./Assets/Background/BG" + std::to_string(bgNum[i]) + ".png");

	//InitData
	//player->GetComponent<PlayerComp>()->playerData->InitData(100, 50, 50, 5, 1);
	//enemy->GetComponent<EnemyComp>()->enemyData->InitData(30 + n, 30 + n, 0 + n, 0, Data::EnemyData::GRADE::Normal);
	//enemy->GetComponent<EnemyComp>()->enemyData->InitData(45.f + 15.f * n, 45.f + 15.f * n, 4.f + 3.f * n, 3.f, Data::EnemyData::GRADE::Elite);
	//enemy->GetComponent<EnemyComp>()->enemyData->InitData((float)60 + (float)60 * n, (float)60 + 60 * n, (float)9 + 6 * n, (float)5, Data::EnemyData::GRADE::Boss);

	//Serializer::GetInstance().SaveLevel("./Assets/Level/test" + std::to_string(i) + ".lvl", "./Assets/Background/BG" + std::to_string(bgNum[i]) + ".png");

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
		SubtitleComp::IntersectDissolveText({ {{0,0}, 1, "Test", 1, 1, 1, 1}, 5, 2, 2 });
	}
}

void level::CombatLevel::Exit()
{

}
