#pragma once
#include "AEEngine.h"
#include "../ComponentManager/LogicComponent.h"
#include "../Event/Entity.h"

class PointComp : public LogicComponent
{
private:
	float speed = 500;

public:
	PointComp(GameObject* _owner);
	~PointComp();
	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreatePointComponent(GameObject* owner);
	static constexpr const char* TypeName = "PointComp";

	friend GameObject;
};