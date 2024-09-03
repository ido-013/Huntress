#pragma once
#include "AEEngine.h"
#include "../ComponentManager/LogicComponent.h"
#include "../Event/Entity.h"

class EnemyComp : public LogicComponent
{
private:
	float speed = 100;
	int movementGauge = 1000;
	int maxMovementGauge = 1000;

public:
	bool turn = true;
	bool moveState = true;
	bool shootState = false;

	EnemyComp(GameObject* _owner);
	~EnemyComp();
	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;
	float GetMovegauge();
	static BaseRTTI* CreatePlayerComponent(GameObject* owner);
	static constexpr const char* TypeName = "EnemyComp";

	friend GameObject;
};