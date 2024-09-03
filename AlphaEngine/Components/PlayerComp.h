#pragma once
#include "AEEngine.h"
#include "../ComponentManager/LogicComponent.h"
#include "../Event/Entity.h"
#include "../Data/Data.h"

class PlayerComp : public LogicComponent
{
private:
	float speed = 100;	
	int movementGauge = 1000;
	int maxMovementGauge = 1000;

public:
	Data::PlayerData data;
	bool moveState = true;
	bool turnTemp = true;
	float GetMovegauge();
	PlayerComp(GameObject* _owner);
	~PlayerComp();
	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreatePlayerComponent(GameObject* owner);
	static constexpr const char* TypeName = "PlayerComp";

	friend GameObject;
};