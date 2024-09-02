#pragma once
#include "../ComponentManager/BaseComponent.h"

class LifetimeComp : public BaseComponent
{
private:
	float lifeTime;
	float currentTime;

public:
	LifetimeComp(GameObject* _owner);
	~LifetimeComp();

	void SetLifetime(float _lifeTime) { lifeTime = _lifeTime; }

	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreateLifetimeComponent(GameObject* owner);
	static constexpr const char* TypeName = "LifetimeComp";
};