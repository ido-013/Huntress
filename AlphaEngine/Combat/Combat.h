// Author : sinu

#pragma once
#include "AEVec2.h"
#include "../GameObject/GameObject.h"
#include "../ComponentManager/EngineComponent.h"

class CombatComp : public EngineComponent
{
public:
	CombatComp(GameObject* _owner);
	~CombatComp();
	
	static bool isDrawDirection;

	void DrawDirectionPegline(GameObject& directionArrow,
		GameObject& player, const AEVec2& DirectionPoint, 
		const std::pair<float, float> AngleRange);
	
	void Update() override;
	void LoadFromJson(const json& data) override;
	json SaveToJson() override;

	static BaseRTTI* CreateCombatComponent(GameObject* owner);
	static constexpr const char* TypeName = "CombatComp";
};