#include "ButtonComp.h"
#include "../EventManager/EventManager.h"
#include "../UIM/BtnManager.h"
#include "../Event/ButtonClickEvent.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Components/SpriteComp.h"
#include "../Components/UIComp.h"

ButtonComp::ButtonComp(GameObject* _owner)
    : GraphicComponent(_owner), pos(), scale()
{
    ButtonManager::GetInstance().RegisterButton(this);
    EventManager::GetInstance().AddEntity(this);
    // pos�� scale�� UIComponent�κ��� ���������� ����
    if (auto* uiComp = owner->GetComponent<UIComponent>()) {
        pos = uiComp->GetPos();
        scale = uiComp->GetScale();
    }
}

ButtonComp::~ButtonComp()
{
    ButtonManager::GetInstance().RemoveButton(this);
    EventManager::GetInstance().DelEntity(this);
}

void ButtonComp::Update()
{
    // pos�� scale�� UIComponent�κ��� ��� ����ȭ
    if (auto* uiComp = owner->GetComponent<UIComponent>()) {
        pos = uiComp->GetPos();
        scale = uiComp->GetScale();
    }
}

void ButtonComp::OnEvent(Event* e)
{
    if (dynamic_cast<ButtonClickEvent*>(e) != nullptr)
    {
        if (onClickFunction) {
            onClickFunction();  // ��ϵ� �Լ��� ȣ��
        }
    }
}

bool ButtonComp::IsClicked(int mouseX, int mouseY) const
{
    // UIComponent�� ���İ� Ȯ�� �� ó��
    UIComponent* uiComp = owner->GetComponent<UIComponent>();
    if (uiComp && uiComp->GetAlpha() != 1) {
        return false;
    }
    // pos�� scale�� �̿��� Ŭ�� ���� Ȯ��
    return (mouseX > pos.x - scale.x / 2 && mouseX < pos.x + scale.x / 2 &&
        mouseY > pos.y - scale.y / 2 && mouseY < pos.y + scale.y / 2);
}

bool ButtonComp::IsHovered(int mouseX, int mouseY) const
{
    return IsClicked(mouseX, mouseY);  // Ŭ�� ���� ���ο� �����ϰ� ����
}

void ButtonComp::OnClick()
{
    EventManager::GetInstance().AddEvent<ButtonClickEvent>(this, this);
}

void ButtonComp::OnHover()
{
    if (onHoverFunction) {
        onHoverFunction();  // Hover �� ������ �Լ� ȣ��
    }
}

void ButtonComp::SetOnClickFunction(std::function<void()> func)
{
    onClickFunction = func;
}
void ButtonComp::SetOnHoverFunction(std::function<void()> func)
{
    onHoverFunction = func;
}

void ButtonComp::LoadFromJson(const json& data)
{
    pos = { data["pos"]["x"], data["pos"]["y"] };
    scale = { data["scale"]["x"], data["scale"]["y"] };
    texturePath = data["texturePath"];
}

json ButtonComp::SaveToJson()
{
    json data;
    data["pos"] = { {"x", pos.x}, {"y", pos.y} };
    data["scale"] = { {"x", scale.x}, {"y", scale.y} };
    data["texturePath"] = texturePath;
    return data;
}

BaseRTTI* ButtonComp::CreateButtonComponent(GameObject* owner)
{
    return new ButtonComp(owner);
}
