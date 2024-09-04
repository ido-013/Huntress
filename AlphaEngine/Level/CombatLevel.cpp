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
	"-------------------------------",
	"-------------------------------",
	"-SL-------------------------RS-",
	"----L---------rSl----------R---",
	"------L------rSSSl------R------",
	"--------L---rSSSSSl---R--------",
	"----------L---------R----------",
	"------------L-----R------------",
	"--------------L-R--------------",
	"-------------------------------",
	"-------------------------------",
};

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
//	"------rSl-------------rSl------",
//	"-----r---l-----------r---l-----",
//	"----r-----l---------r-----l----",
//	"---r-------l-------r-------l---",
//	"--r---------l-----r---------l--",
//	"-S-----------SSSSS-----------S-",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//	"-------------------------------",
//};

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
	//Prefab sd("Square_DECO");
	//Prefab lrd("LeftTri_R_DECO"); 
	//Prefab rrd("RightTri_R_DECO"); 

	Prefab p("Player");
	Prefab e("Enemy");

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
	player->GetComponent<TransformComp>()->SetPos({ 400, -400 });
	
	/*player = new GameObject("player");
	player->type = GameObject::Player;

	player->AddComponent<TransformComp>();
	player->AddComponent<PlayerComp>();
	player->AddComponent<RigidbodyComp>();
	player->AddComponent<SpriteComp>();
	player->AddComponent<ColliderComp>();

	player->GetComponent<TransformComp>()->SetScale({ 30, 30 });
	player->GetComponent<TransformComp>()->SetPos({ 400, -400 });

	player->GetComponent<RigidbodyComp>()->useGravity = true;

	player->GetComponent<SpriteComp>()->SetTexture("../Assets/Character/ArrowAttack/sprite/ScoutAttackArrow.png");
	player->GetComponent<SpriteComp>()->SetAlpha(1);

	player->GetComponent<ColliderComp>()->SetCollider();*/

	// enemy
	enemy = e.NewGameObject("enemy");
	enemy->GetComponent<TransformComp>()->SetPos({ 500, -400 });

	/*enemy = new GameObject("enemy");
	enemy->type = GameObject::Enemy;

	enemy->AddComponent<TransformComp>();
	enemy->AddComponent<RigidbodyComp>();
	enemy->AddComponent<EnemyComp>();
	enemy->AddComponent<SpriteComp>();
	enemy->AddComponent<ColliderComp>();

	enemy->GetComponent<TransformComp>()->SetScale({ -30, 30 });
	enemy->GetComponent<TransformComp>()->SetPos({ 500, -400 });

	enemy->GetComponent<RigidbodyComp>()->useGravity = true;
	
	enemy->GetComponent<SpriteComp>()->SetTexture("../Assets/Character/ArrowAttack/sprite/ScoutAttackArrow.png");
	enemy->GetComponent<SpriteComp>()->SetAlpha(1);

	enemy->GetComponent<ColliderComp>()->SetCollider();*/

	// direction Arrow
	directionArrow = new GameObject("directionArrow");

	directionArrow->AddComponent<TransformComp>();
	directionArrow->AddComponent<SpriteComp>();
	directionArrow->AddComponent<CombatComp>();

	directionArrow->GetComponent<TransformComp>()->SetScale({ 
		directionArrow->GetComponent<CombatComp>()->directionArrowWidth, 
		directionArrow->GetComponent<CombatComp>()->directionArrowHeight });
	directionArrow->GetComponent<SpriteComp>()->SetTexture("../Assets/Character/DirectionArrow.png");
	directionArrow->GetComponent<SpriteComp>()->SetAlpha(0);
	directionArrow->GetComponent<CombatComp>()->turn = CombatComp::TURN::PLAYERTURN;
	directionArrow->GetComponent<CombatComp>()->state = CombatComp::STATE::COMBAT;
	directionArrow->GetComponent<CombatComp>()->isCombat = true;

	//InitData
	player->GetComponent<PlayerComp>()->data.InitData(100, 50, 50, 2, 1);
	enemy->GetComponent<EnemyComp>()->data.InitData(30, 0, 1, Data::EnemyData::GRADE::Normal);

	//Init UI
	InitCombatUI();
}

void level::CombatLevel::Update()
{
	UpdateBackground();

	if (AEInputCheckTriggered(AEVK_1))
	{
		Data::PrintPlayerData(player->GetComponent<PlayerComp>()->data);
	}
	if (AEInputCheckTriggered(AEVK_2))
	{
		Data::PrintEnemyData(enemy->GetComponent<EnemyComp>()->data);
	}
	if (AEInputCheckTriggered(AEVK_3))
	{
		Data::PrintCombatData(directionArrow->GetComponent<CombatComp>()->data);
	}

	UpdateCombatUI(player, enemy, directionArrow);
}

void level::CombatLevel::Exit()
{

}
