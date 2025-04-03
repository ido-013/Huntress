#pragma once
#include "../ComponentManager/BaseComponent.h"
#include "AEEngine.h"

class LifetimeComp : public BaseComponent
{
private:
	f64 lifeTime;
	f64 currentTime;

public:
	LifetimeComp(GameObject* _owner);
	~LifetimeComp();

	void SetLifetime(f64 _lifeTime) { lifeTime = _lifeTime; }

	void Update() override;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreateLifetimeComponent(GameObject* owner);
	static constexpr const char* TypeName = "LifetimeComp";
};