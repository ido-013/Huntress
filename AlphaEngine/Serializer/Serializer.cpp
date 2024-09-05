#include <fstream>
#include "Serializer.h"
#include "json.hpp"
#include "../ComponentManager/BaseComponent.h"
#include "../ComponentManager/ComponentManager.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Components.h"
#include "../RTTI/Registry.h"
#include "../Prefab/Prefab.h"

using json = nlohmann::ordered_json;	// Map. Orders the order the variables were declared in

void Serializer::LoadLevel(const std::string& filename)
{
	// Open file
	std::fstream file;
	file.open(filename, std::fstream::in);

	// Check the file is valid
	if (!file.is_open())
		throw std::invalid_argument("Serializer::LoadLevel Invalid filename " + filename);

	json allData;
	file >> allData;	// the json has all the file data

	json background;
	background = allData.find("background").value();
	auto& item = background;
	{
		auto objIt = background.find("object");
		Prefab p(objIt.value());
		GameObject* go = p.NewGameObject("background");

		if (objIt != item.end())
		{
			auto compIt = item.find("components");

			// iterate on the json on cmp for each component, add it
			for (auto& comp : *compIt)
			{
				auto dataIt = comp.find("type");
				if (dataIt == comp.end())	// not found
					continue;

				std::string typeName = dataIt.value().dump();	// convert to string
				typeName = typeName.substr(1, typeName.size() - 2);

				go->GetBase(typeName)->LoadFromJson(comp);
			}
		}

		if (go->GetComponent<ColliderComp>() != nullptr)
			go->GetComponent<ColliderComp>()->SetCollider();
	}

	json objects;
	objects = allData.find("objects").value();

	for (auto& item : objects)
	{
		auto objIt = item.find("object");
		Prefab p(objIt.value());
		GameObject* go = p.NewGameObject();

		if (objIt != item.end())
		{
			auto compIt = item.find("components");
			if (compIt == item.end())
				continue;

			// iterate on the json on cmp for each component, add it
			for (auto& comp : *compIt)
			{
				auto dataIt = comp.find("type");
				if (dataIt == comp.end())	// not found
					continue;

				std::string typeName = dataIt.value().dump();	// convert to string
				typeName = typeName.substr(1, typeName.size() - 2);

				go->GetBase(typeName)->LoadFromJson(comp);
			}
		}

		if (go->GetComponent<ColliderComp>() != nullptr)
			go->GetComponent<ColliderComp>()->SetCollider();
	}

	json player;
	player = allData.find("player").value();
	item = player;
	{
		auto objIt = item.find("object");
		Prefab p(objIt.value());
		GameObject* go = p.NewGameObject("player");

		if (objIt != item.end())
		{
			auto compIt = item.find("components");

			// iterate on the json on cmp for each component, add it
			for (auto& comp : *compIt)
			{
				auto dataIt = comp.find("type");
				if (dataIt == comp.end())	// not found
					continue;

				std::string typeName = dataIt.value().dump();	// convert to string
				typeName = typeName.substr(1, typeName.size() - 2);

				go->GetBase(typeName)->LoadFromJson(comp);
			}
		}

		if (go->GetComponent<ColliderComp>() != nullptr)
			go->GetComponent<ColliderComp>()->SetCollider();
	}

	json enemy;
	enemy = allData.find("enemy").value();
	item = enemy;
	{
		auto objIt = item.find("object");
		Prefab p(objIt.value());
		GameObject* go = p.NewGameObject("enemy");

		if (objIt != item.end())
		{
			auto compIt = item.find("components");

			// iterate on the json on cmp for each component, add it
			for (auto& comp : *compIt)
			{
				auto dataIt = comp.find("type");
				if (dataIt == comp.end())	// not found
					continue;

				std::string typeName = dataIt.value().dump();	// convert to string
				typeName = typeName.substr(1, typeName.size() - 2);

				go->GetBase(typeName)->LoadFromJson(comp);
			}
		}

		if (go->GetComponent<ColliderComp>() != nullptr)
			go->GetComponent<ColliderComp>()->SetCollider();
	}

	json directionArrow;
	directionArrow = allData.find("directionArrow").value();
	item = directionArrow;
	{
		auto objIt = item.find("object");
		Prefab p(objIt.value());
		GameObject* go = p.NewGameObject("directionArrow");

		if (objIt != item.end())
		{
			auto compIt = item.find("components");

			// iterate on the json on cmp for each component, add it
			for (auto& comp : *compIt)
			{
				auto dataIt = comp.find("type");
				if (dataIt == comp.end())	// not found
					continue;

				std::string typeName = dataIt.value().dump();	// convert to string
				typeName = typeName.substr(1, typeName.size() - 2);

				go->GetBase(typeName)->LoadFromJson(comp);
			}
		}

		if (go->GetComponent<ColliderComp>() != nullptr)
			go->GetComponent<ColliderComp>()->SetCollider();
	}

	json enemyData = allData.find("enemyData").value();
	GameObject* enemyObj = GameObjectManager::GetInstance().GetObj("enemy");
	enemyObj->GetComponent<EnemyComp>()->enemyData->LoadFromJson(enemyData);

	if (enemyObj->GetComponent<EnemyComp>()->enemyData->grade == Data::EnemyData::Elite)
		enemyObj->GetComponent<SpriteComp>()->SetColor(130, 0, 130);

	if (enemyObj->GetComponent<EnemyComp>()->enemyData->grade == Data::EnemyData::Boss)
		enemyObj->GetComponent<SpriteComp>()->SetColor(130, 130, 0);

	GameObjectManager::GetInstance().GetObj("player")->GetComponent<AnimatorComp>()->SetAnimation(true, 1, "walk");

	GameObjectManager::GetInstance().GetObj("background")->GetComponent<SpriteComp>()->SetTexture(allData.find("backgroundFileName").value());
}

void Serializer::SaveLevel(const std::string& filename, const std::string& backgroundFileName)
{
	json allData;

	// Counter instead of name as I do not have one
	int i = 0;

	for (auto go : GameObjectManager::GetInstance().GetAllObjects())
	{
		json obj;
		obj["object"] = go.first->prefabName;

		json components;
		components.push_back(go.first->GetComponent<TransformComp>()->SaveToJson());
		obj["components"] = components;

		if (go.first->name.size() > 0)
		{
			allData[go.first->name] = obj;
		}
		else
			allData["objects"].push_back(obj);
	}

	allData["enemyData"] = GameObjectManager::GetInstance().GetObj("enemy")->GetComponent<EnemyComp>()->enemyData->SaveToJson();
	allData["backgroundFileName"] = backgroundFileName;

	// Open file
	std::fstream file;
	file.open(filename, std::fstream::out);	// Open as write mode. Create it if it does not exist!

	if (!file.is_open())
		throw std::invalid_argument("Serializer::SaveLevel file write error " + filename);

	file << std::setw(2) << allData;	// Separates in lines and each section

	file.close();
}
