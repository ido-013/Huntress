#pragma once
#include "../GameObject/GameObject.h"
#include "../EventManager/EventManager.h"
#include "../Components/TransformComp.h"
#include "../Components/SpriteComp.h"
#include <functional>  // std::function 사용

class ButtonComp : public EngineComponent, public Entity
{
private:
    AEVec2 pos;
    AEVec2 scale;
    std::string texturePath;

    // 클릭 시 실행할 함수
    std::function<void()> onClickFunction;

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

    // 클릭 시 호출할 함수를 등록
    void SetOnClickFunction(std::function<void()> func);

    bool IsClicked(int mouseX, int mouseY) const;

    // OnClick 메서드 추가: 클릭되었을 때 호출
    void OnClick();

    void LoadFromJson(const json&) override;
    json SaveToJson() override;

    static BaseRTTI* CreateButtonComponent(GameObject* owner);
    static constexpr const char* TypeName = "ButtonComp";
};
