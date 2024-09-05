#pragma once
#include "AEEngine.h"
#include "../ComponentManager/LogicComponent.h"
#include "../Event/Entity.h"
#include "../Data/Data.h"

class EnemyComp : public LogicComponent
{
private:
	float speed = 50;
	int movementGauge = 1000;
	int maxMovementGauge = 1000;

public:
	Data::EnemyData* enemyData;
	bool isMove = false;
	bool moveState = true;
	bool turnTemp = true;
	bool isGo = true;
	void RandomMove();
	int GetMovegauge();

	EnemyComp(GameObject* _owner);
	~EnemyComp();
	void Update() override;

	void LoadFromJson(const json& data) override;
	json SaveToJson() override;

	static BaseRTTI* CreateEnemyComponent(GameObject* owner);
	static constexpr const char* TypeName = "EnemyComp";

	friend GameObject;
};