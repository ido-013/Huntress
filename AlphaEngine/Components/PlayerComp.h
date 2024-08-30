#pragma once
#include "AEEngine.h"
#include "../ComponentManager/LogicComponent.h"
#include "../Event/Entity.h"

class PlayerComp : public LogicComponent
{
private:
	float speed = 500;	
	int movementGauge = 100;

public:
	PlayerComp(GameObject* _owner);
	~PlayerComp();
	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreatePlayerComponent(GameObject* owner);
	static constexpr const char* TypeName = "PlayerComp";

	friend GameObject;
};