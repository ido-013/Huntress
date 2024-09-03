#pragma once
#include "../GameObject/GameObject.h"
#include "../EventManager/EventManager.h"
#include "../Components/TransformComp.h"
#include <functional>  // std::function ���

class ButtonComp : public EngineComponent, public Entity
{
private:
    AEVec2 pos;
    AEVec2 scale;
    std::string texturePath;

    // Ŭ�� �� ������ �Լ�
    std::function<void()> onClickFunction;
    std::function<void()> onHoverFunction;
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

    // Ŭ�� �� ȣ���� �Լ��� ���
    void SetOnClickFunction(std::function<void()> func);
    void SetOnHoverFunction(std::function<void()> func);

    bool IsClicked(int mouseX, int mouseY) const;
    bool IsHovered(int mouseX, int mouseY) const;
    void OnClick();
    void OnHover();
    void LoadFromJson(const json&) override;
    json SaveToJson() override;

    static BaseRTTI* CreateButtonComponent(GameObject* owner);
    static constexpr const char* TypeName = "ButtonComp";
};
