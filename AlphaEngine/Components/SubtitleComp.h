#pragma once

#include "../ComponentManager/GraphicComponent.h"
#include <string>
#include "AEEngine.h"


class SubtitleComp : public GraphicComponent
{

public:
	SubtitleComp(GameObject* _owner);
	~SubtitleComp();

	void OnSubtitle(AEVec2& loc, float size, std::string content, );

	void Update() override;
	void LoadFromJson(const json& data) override;
	json SaveToJson() override;

	static BaseRTTI* CreateSubtitleComponent(GameObject* owner);
	static constexpr const char* TypeName = "SubtitleComp";
};