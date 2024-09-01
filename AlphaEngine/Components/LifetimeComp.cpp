#include "LifetimeComp.h"
#include "AEEngine.h"
#include "../ComponentManager/ComponentManager.h"
#include "../GameObjectManager/GameObjectManager.h"

LifetimeComp::LifetimeComp(GameObject* _owner) : BaseComponent(_owner), lifeTime(9999), currentTime(0)
{
	ComponentManager<LifetimeComp>::GetInstance().AddComp(this);
}

LifetimeComp::~LifetimeComp()
{
	ComponentManager<LifetimeComp>::GetInstance().DelComp(this);
}

void LifetimeComp::Update()
{
	float dt = AEFrameRateControllerGetFrameTime();
	currentTime += dt;
	
	if (currentTime > lifeTime)
	{
		GameObjectManager::GetInstance().RemoveObject(owner);
	}
}

void LifetimeComp::LoadFromJson(const json& data)
{

}

json LifetimeComp::SaveToJson()
{
	json data;

	return data;
}

BaseRTTI* LifetimeComp::CreateLifetimeComponent(GameObject* owner)
{
	BaseRTTI* p = new LifetimeComp(owner);
	owner->AddComponent<LifetimeComp>(static_cast<BaseComponent*>(p));
	return p;
}