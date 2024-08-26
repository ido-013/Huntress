#include "TestLevel.h"
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

std::string map[height] =
{
	"----------",
	"----------",
	"----------",
	"----------",
	"----------",
	"----------",
	"--RL---LR-",
	"-11111111-",
	"1111111111",
	"1111111111"
};

void level::TestLevel::Init()
{
	GameObject* go = nullptr;
	TransformComp* t = nullptr;

	Prefab s("Square");
	Prefab l("LeftTri");
	Prefab r("RightTri");

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (map[i][j] == '-')
				continue;

			else if (map[i][j] == '1')
			{
				go = s.NewGameObject();
			}

			else if (map[i][j] == 'R')
			{
				go = r.NewGameObject();
			}

			else if (map[i][j] == 'L')
			{
				go = l.NewGameObject();
			}

			t = go->GetComponent<TransformComp>();
			t->SetScale({ windowWidth / width, windowHeight / height });
			float x = MapToPosX(j);
			float y = MapToPosY(i);
			t->SetPos({ x, y });
		}
	}
}

void level::TestLevel::Update()
{

}

void level::TestLevel::Exit()
{
	EventManager::GetInstance().DeleteUndispahchEvent();
	GameObjectManager::GetInstance().RemoveAllObject();
}
