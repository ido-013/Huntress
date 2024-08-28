#include "EditLevel.h"
#include "../GSM/GameStateManager.h"
#include "../ComponentManager/ComponentManager.h"
#include "../GameObject/GameObject.h"
#include "../Components.h"
#include "../EventManager/EventManager.h"
#include "../Prefab/Prefab.h"
#include "../Utils/Utils.h"
#include "../GameObjectManager/GameObjectManager.h"
#include <iostream>

std::string map[20] =
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
	"--------r-l---------",
	"--------------------",
	"-----R--------------",
	"------L-------------",
	"--------------------",
	"--SSSSSSSSSSS-------",
	"--------------------",
	"--------------------",
	"--------------------",
	"--------------------"
};

void level::EditLevel::Init()
{
	GameObject* go = nullptr;
	TransformComp* t = nullptr;

	Prefab s("Square");
	Prefab l("LeftTri");
	Prefab r("RightTri");
	Prefab p("Point");

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
				float x = MapToPosX(j);
				float y = MapToPosY(i);
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
				float x = MapToPosX(j);
				float y = MapToPosY(i);
				t->SetPos({ x + (windowWidth / width / 2), y });
				//t->SetPos({ x + width / 2, y });
				continue;
			}

			t = go->GetComponent<TransformComp>();
			t->SetScale({ windowWidth / width, windowHeight / height });
			//t->SetScale({ width, height }); 
			float x = MapToPosX(j);
			float y = MapToPosY(i);
			t->SetPos({ x, y });
		}
	}

	p.NewGameObject();
}

void level::EditLevel::Update()
{

}

void level::EditLevel::Exit()
{
	EventManager::GetInstance().DeleteUndispahchEvent();
	GameObjectManager::GetInstance().RemoveAllObject();
}
