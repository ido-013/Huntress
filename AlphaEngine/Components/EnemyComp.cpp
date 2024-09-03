#include "EnemyComp.h"

float EnemyComp::GetMovegauge()
{
	return movementGauge;
}

EnemyComp::EnemyComp(GameObject* _owner) : LogicComponent(_owner)
{
}

EnemyComp::~EnemyComp()
{
}

void EnemyComp::Update()
{
}

void EnemyComp::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		auto it = compData->find("speed");
		speed = it.value();
	}
}

json EnemyComp::SaveToJson()
{
	json data;
	data["type"] = TypeName;

	json compData;
	
	data["compData"] = compData;

	return data;
}

BaseRTTI* EnemyComp::CreateEnemyComponent(GameObject* owner)
{
	BaseRTTI* p = new EnemyComp(owner);
	owner->AddComponent<EnemyComp>(static_cast<BaseComponent*>(p));
	return p;
}

