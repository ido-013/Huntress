#pragma once
#include <list>
#include "AEMath.h"
#include "../ComponentManager/ComponentManager.h"
#include "../ComponentManager/EngineComponent.h"
#include "../Event/Entity.h"

class ColliderComp : public EngineComponent, public Entity
{
private:
	AEVec2 pos;
	AEVec2 scale;
	float rot;

	std::list<Entity*> colliderList;

public:
	ColliderComp(GameObject* _owner);
	~ColliderComp();

	void Update() override;

	void OnEvent(Event* e) override;

	//Gettors
	const AEVec2& GetPos() const { return pos; }
	const AEVec2& GetScale() const { return scale; }
	const float& GetRot() const { return rot; }

	//Mutators
	void SetPos(const AEVec2& otherPos);
	void SetScale(const AEVec2& otherScale);
	void SetRot(const float& otherRot);

	bool isCollision;

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreateColliderComponent(GameObject* owner);
	static constexpr const char* TypeName = "ColliderComp";
};