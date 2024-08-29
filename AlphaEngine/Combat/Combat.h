// Author : sinu

#pragma once
#include "AEVec2.h"
#include "../GameObject/GameObject.h"
#include "../ComponentManager/EngineComponent.h"
#include "../Combat/Projectile.h"

class CombatComp : public EngineComponent
{
	//player
	float pAngle;
	float pVelocity;

	//enemy
	float eAngle;
	float eVelocity;
public:
	CombatComp(GameObject* _owner);
	~CombatComp();
	
	static bool isDrawDirection;
	static bool isChaseDirection;
	static bool isReadyLaunch;

	void SetPlayerAngle(float angle);
	float GetPlayerAngle();
	void SetEnemyAngle(float angle);
	float GetEnemyAngle();
	void SetPlayerVelocity(float velocity);
	float GetPlayerVelocity();
	void SetEnemyVelocity(float velocity);
	float GetEnemyVelocity();

	void DrawDirectionPegline(GameObject& directionArrow,
		int dealer, const AEVec2& DirectionPoint, 
		const std::pair<float, float> AngleRange);
	
	void FireAnArrow(int dealer, GameObject& directionArrow);

	void Update() override;
	void LoadFromJson(const json& data) override;
	json SaveToJson() override;

	static BaseRTTI* CreateCombatComponent(GameObject* owner);
	static constexpr const char* TypeName = "CombatComp";
};