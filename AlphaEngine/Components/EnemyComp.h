#pragma once
#include "AEEngine.h"
#include "../ComponentManager/LogicComponent.h"
#include "../Event/Entity.h"
#include "../Data/Data.h"

class EnemyComp : public LogicComponent
{
private:
	float speed = 100;
	int movementGauge = 1000;
	int maxMovementGauge = 1000;

public:
	Data::EnemyData data;
	bool turn = true;
	bool moveState = true;
	bool shootState = false;
	float GetMovegauge();

	EnemyComp(GameObject* _owner);
	~EnemyComp();
	void Update() override;

	void LoadFromJson(const json& data) override;
	json SaveToJson() override;

	static BaseRTTI* CreateEnemyComponent(GameObject* owner);
	static constexpr const char* TypeName = "EnemyComp";

	friend GameObject;
};