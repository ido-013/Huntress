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

	GameObject* GBYobj;

public:
	Data::PlayerData* playerData;
	bool moveState = true;
	bool turnTemp = true;

	bool GBY = false;

	int GetMovegauge();

	float GetHp();
	void AddHp(float value);

	void GBYEffect();

	PlayerComp(GameObject* _owner);
	~PlayerComp();
	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreatePlayerComponent(GameObject* owner);
	static constexpr const char* TypeName = "PlayerComp";

	friend GameObject;
};