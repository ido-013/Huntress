#include <fstream>
#include "Serializer.h"
#include "json.hpp"
#include "../ComponentManager/BaseComponent.h"
#include "../ComponentManager/ComponentManager.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Components/TransformComp.h"
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

	for (auto& item : allData)
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
	}
}

void Serializer::SaveLevel(const std::string& filename)
{
	json allData;

	// Counter instead of name as I do not have one
	int i = 0;

	for (GameObject* go : GameObjectManager::GetInstance().GetAllObjects())
	{
		json obj;
		obj["object"] = go->name;

		json components;
		components.push_back(go->GetComponent<TransformComp>()->SaveToJson());
		obj["components"] = components;

		allData.push_back(obj);
	}

	// Open file
	std::fstream file;
	file.open(filename, std::fstream::out);	// Open as write mode. Create it if it does not exist!

	if (!file.is_open())
		throw std::invalid_argument("Serializer::SaveLevel file write error " + filename);

	file << std::setw(2) << allData;	// Separates in lines and each section

	file.close();
}
