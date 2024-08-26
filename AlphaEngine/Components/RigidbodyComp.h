#pragma once
#include "AEVec2.h"
#include "../ComponentManager/EngineComponent.h"

class RigidbodyComp : public EngineComponent
{
	float drag = 1.01f;

	AEVec2 velocity;
	AEVec2 maxVelocity;
	AEVec2 acceleration;
	AEVec2 maxAcceleration;

	bool CheckEpsilon(float v, float EP = EPSILON);

public:
	RigidbodyComp(GameObject* _owner);

	void AddVelocity(const AEVec2& otherVec);
	void AddVelocity(float x, float y);
	void SetVelocity(const AEVec2& otherVec);
	void SetVelocity(float x, float y);
	void ClearVelocity();

	void AddAcceleration(const AEVec2& otherVec);
	void AddAcceleration(float x, float y);
	void ClearAcceleration();

	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreateRigidBodyComponent(GameObject* owner);
	static constexpr const char* TypeName = "RigidbodyComp";
};