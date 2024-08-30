#include "TestLevel.h"
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
	//"-------rSSSSl-------",
	//"------rSSSSSSl------",
	//"-----rSSSSSSSSl-----",
	//"----rSSSSSSSSSSl----",
	//"---rSSSSSSSSSSSSl---",
	//"SSSSSSSSSSSSSSSSSSSS",
	//"SSSSSSSSSSSSSSSSSSSS",
	//"SSSSSSSSSSSSSSSSSSSS",
	//"SSSSSSSSSSSSSSSSSSSS",
	//"SSSSSSSSSSSSSSSSSSSS"
};

void level::TestLevel::Init()
{
	
}

void level::TestLevel::Update()
{

}

void level::TestLevel::Exit()
{
	EventManager::GetInstance().DeleteUndispahchEvent();
	GameObjectManager::GetInstance().RemoveAllObject();
}
