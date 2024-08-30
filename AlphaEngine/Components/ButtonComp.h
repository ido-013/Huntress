#pragma once
#include "../GameObject/GameObject.h"
#include "../EventManager/EventManager.h"
#include "../Components/TransformComp.h"
#include "../Components/SpriteComp.h"
#include "AEVec2.h"

class ButtonComp : public EngineComponent, public Entity
{
private:
    AEVec2 pos;
    AEVec2 scale;
    std::string texturePath;

public:
    ButtonComp(GameObject* _owner);
    ~ButtonComp();

    void Update() override;
    void OnEvent(Event* e) override;

    const AEVec2& GetPos() const { return pos; }
    const AEVec2& GetScale() const { return scale; }

    void SetPos(const AEVec2& otherPos);
    void SetScale(const AEVec2& otherScale);
    AEVec2 GetPos();
    AEVec2 Getscale();

    // IsClicked 메서드 추가: 마우스 좌표를 받아 클릭되었는지 확인
    bool IsClicked(int mouseX, int mouseY) const;

    // OnClick 메서드 추가: 클릭되었을 때 호출
    void OnClick();

    void LoadFromJson(const json&) override;
    json SaveToJson() override;

    static BaseRTTI* CreateButtonComponent(GameObject* owner);
    static constexpr const char* TypeName = "ButtonComp";
};
