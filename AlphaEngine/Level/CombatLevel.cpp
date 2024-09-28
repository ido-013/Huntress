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
#include "../UI/EscMenu.h"
#include "../Components/SubtitleComp.h"


#include "../Background/Background.h"
#include "../Utils/Utils.h"
#include "../Tile/Tile.h"

GameObject* player = nullptr;
GameObject* directionArrow = nullptr;
GameObject* enemy = nullptr;

std::string map[10][30] =
{
	//1
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
	//2
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
		"-DDDD@L------------------------",
		"--DDDDD@SS---------------------",
		"--DDDDDDD----------------------",
		"--DDDDDD-----------------------",
		"---DDDDD--------------------N--",
		"---DDDDD-------------SSSSSSSSS-",
		"---DDDDD--------------DDDDDDDD-",
		"---DDDDD--------------DDDDDD---",
		"---DDDD----------------DDDDD---",
		"---DDDD----------------DDDDD---",
		"---DDDD----------------DDDDD---",
	},
	//3
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
	//4
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
		"---------------S---------------",
		"---------------DS--------------",
		"--------------SDD--------------",
		"--------------DDD--------------",
		"--P----------SDDD--------------",
		"-SSSL--------DDDDS----------N--",
		"-DDDD@SSSS---DDDDD---SSSSSSSSS-",
		"-DDDDDDDD----DDDDD----DDDDDDDD-",
		"--DDDDDD-----DDDDD----DDDDDD---",
		"--DDDDDD-----DDDDD-----DDDDD---",
		"--DDDDD------DDDDD-----DDDDD---",
		"--DDDDD------DDDDD-----DDDDD---",
	},
	//5
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
		"---DDDDDD-------------DDDD----",
		"---DDDDD--------------DDDD----",
		"---DDDD---------------DDDD----",
		"----DDD---------------DDDDD---",
	},
	//6
	{
		"--------------DD---------------",
		"--------------DD---------------",
		"--------------DD---------------",
		"--------------DD---------------",
		"--------------DD---------------",
		"--------------DD---------------",
		"--------------DD---------------",
		"--------------DD---------------",
		"--------------DD---------------",
		"--------------DD---------------",
		"--------------DD---------------",
		"--------------DD---------------",
		"--------------DD---------------",
		"--------------DD---------------",
		"--------------DD---------------",
		"--------------DD---------------",
		"--------------DDD--------------",
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
	//7
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
		"----------------------R-@DDD--",
		"------DDDDD---------R-@DDDDD--",
		"-----DDDDDD-------R-@DDDDD----",
		"-----DDDDD------R-@DDDDDD-----",
		"--------------R-@DDDDDDDD-----",
		"------------R-@DDDDDDDDD------",
		"----------R-@D---DDDDDDD------",
		"--------R-@-------DDDDDD------",
		"------R-@D--------DDDDD-------",
		"----R-@DDD--------DDDDD-------",
		"-PR-@DDDD----------DDDD-------",
		"-S@DDDDDD----------DDDD-------",
		"--DDDDDDD----------DDDD-------",
		"----DDDD-----------DDDD-------",
		"----DDDD-----------DDDD-------",
		"-----DDD-----------DDDD-------",
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
		"---------------SS-------------",
		"----rl---------DD-------------",
		"---rDDl-------SDD-------------",
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
		"-DDDDD@L-------D--------------",
		"-DDDDDDD@L-----DDD------------",
		"-DDDDDD--D@L------------------",
		"-DDDDD----DD@L----------------",
		"-DDDDD----DDDD@L------DD------",
		"-DDDDD----DDDD--@L------------",
		"--DDDD----DDDD----@L----------",
		"--DDDD----DDDD----DD@L--------",
		"--DDDD----DDDD------DD@L---N--",
		"--DDDD----DDDD------DDDD@SSSS-",
		"--DDD-----DDDD-------DDDDDDD--",
		"--DDD-----DDDD-------DDDDD----",
		"--DDD------DDD--------DDDD----",
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

	int i = level;

	Tile::ChangeTile(tileNum[i]);

	GameObject* go = nullptr;
	TransformComp* t = nullptr;
	ColliderComp* c = nullptr;

	Prefab gs("GhostSquare");
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
				go = gs.NewGameObject();
				go->GetComponent<SpriteComp>()->SetTexture("./Assets/Tile/FallGrassTileRect3.png");
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

	//Init UI
	InitCombatUI();

}

void level::CombatLevel::Update()
{
	UpdateCombatUI();
	UpdateBackground();

#ifdef _DEBUG
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
	if (AEInputCheckTriggered(AEVK_N))
	{
		GSM::GameStateManager::GetInstance().ChangeLevel(new CombatLevel(level + 1));
	}
#endif
}

void level::CombatLevel::Exit()
{
	ExitCombatUI();
}
