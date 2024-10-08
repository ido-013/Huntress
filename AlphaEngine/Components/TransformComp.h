#pragma once
#include "AEMath.h"
#include "../ComponentManager/ComponentManager.h"
#include "../ComponentManager/EngineComponent.h"
#include "../Event/Entity.h"

class TransformComp : public EngineComponent
{
private:
	AEVec2 pos;
	AEVec2 scale;
	float rot;

	AEMtx33 transformMatrix;

	void CalculateMatrix();

public:
	TransformComp(GameObject* _owner);
	~TransformComp();

	bool affectedByZoom = true;

	void Update() override;

	//Gettors
	const AEVec2& GetPos() const { return pos; }
	const AEVec2& GetScale() const { return scale; }
	const float& GetRot() const { return rot; }
	const AEMtx33& GetMatrix() const { return transformMatrix; }

	//Mutators
	void SetPos(const AEVec2& otherPos);
	void SetScale(const AEVec2& otherScale);
	void SetRot(const float& otherRot);

	void ReverseX(int val);
	void ReverseY(int val);

	//Other Fn
	void PrintMatrix();

	void LoadFromJson(const json&) override;
	json SaveToJson() override;

	static BaseRTTI* CreateTransformComponent(GameObject* owner);
	static constexpr const char* TypeName = "TransformComp";
};