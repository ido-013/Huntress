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
#include <iostream>

std::string map[100] =
{
	"--------------------",
	"--------------------",
	"--------------------",
	"--------------------",
	"--------------------",
	"--------------------",
	"--------------------",
	"--------------------",
	"--------------------",
	"--------------------",
	"--------------------",
	"--------------------",
	"-------R-S----------",
	"-----R-SSSSSSSSS----",
	"---R-SSSSSSSSSSSS---",
	"-R-SSSSSSSSSSSSSS---",
	"SSSSSSSSSSSSSSSSSSSS",
	"SSSSSSSSSSSSSSSSSSSS",
	"SSSSSSSSSSSSSSSSSSSS",
	"SSSSSSSSSSSSSSSSSSSS"
};

void level::NormalLevel::Init()
{
	GameObject* go = nullptr;
	TransformComp* t = nullptr;
	Prefab s("Square");
	Prefab l("LeftTri");
	Prefab r("RightTri");

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
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
				t->SetScale({ windowWidth / width * 2, windowHeight / height });
				//t->SetScale({ width * 2, height });
				float x = MapToPosX((float)j);
				float y = MapToPosY((float)i);
				t->SetPos({ x + (windowWidth / width / 2), y });
				//t->SetPos({ x + width / 2, y });
				continue;
			}

			else if (map[i][j] == 'L')
			{
				go = l.NewGameObject();
				t = go->GetComponent<TransformComp>();
				t->SetScale({ windowWidth / width * 2, windowHeight / height });
				//t->SetScale({ width * 2, height });
				float x = MapToPosX((float)j);
				float y = MapToPosY((float)i);
				t->SetPos({ x + (windowWidth / width / 2), y });
				//t->SetPos({ x + width / 2, y });
				continue;
			}

			t = go->GetComponent<TransformComp>();
			t->SetScale({ windowWidth / width, windowHeight / height });
			//t->SetScale({ width, height }); 
			float x = MapToPosX((float)j);
			float y = MapToPosY((float)i);
			t->SetPos({ x, y });
		}
	}
}

void level::NormalLevel::Update()
{

}

void level::NormalLevel::Exit()
{
	EventManager::GetInstance().DeleteUndispahchEvent();
	GameObjectManager::GetInstance().RemoveAllObject();
}
