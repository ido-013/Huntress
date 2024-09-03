#pragma once

#include "../ComponentManager/LogicComponent.h"

class DataManager : public LogicComponent
{
public:
	

	void Update() override;
	void LoadFromJson(const json& data) override;
	json SaveToJson() override;

	static BaseRTTI* CreateCombatComponent(GameObject* owner);
	static constexpr const char* TypeName = "DataManager";
};