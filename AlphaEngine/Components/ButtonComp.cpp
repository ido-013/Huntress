#include "ButtonComp.h"
#include "../EventManager/EventManager.h"
#include "../UIM/BtnManager.h"
#include "../Event/ButtonClickEvent.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Components/SpriteComp.h"
#include "../Components/UIComp.h"

ButtonComp::ButtonComp(GameObject* _owner)
    : GraphicComponent(_owner), pos(), scale(), isHovered(false)
{
    ButtonManager::GetInstance().RegisterButton(this);
    EventManager::GetInstance().AddEntity(this);

    // pos와 scale을 UIComponent로부터 가져오도록 설정
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
    // pos와 scale을 UIComponent로부터 계속 동기화
    if (auto* uiComp = owner->GetComponent<UIComponent>()) {
        pos = uiComp->GetPos();
        scale = uiComp->GetScale();
    }

    // 마우스 포지션 체크
    int mouseX, mouseY;
    AEInputGetCursorPosition(&mouseX, &mouseY);

    // 현재 마우스가 버튼 위에 있는지 확인
    bool currentlyHovered = IsHovered(mouseX, mouseY);

    if (currentlyHovered && !isHovered) {
        // 마우스가 버튼 위에 처음 올라왔을 때
        OnHover();
        isHovered = true;
    }
    else if (!currentlyHovered && isHovered) {
        // 마우스가 버튼에서 벗어났을 때
        OnHoverOut();
        isHovered = false;
    }
    // 만약 버튼 위에 계속 마우스가 있는 상태라면 아무 동작도 하지 않음
}

void ButtonComp::OnEvent(Event* e)
{
    if (dynamic_cast<ButtonClickEvent*>(e) != nullptr)
    {
        if (onClickFunction) {
            onClickFunction();  // 등록된 클릭 함수를 호출
        }
    }
}

bool ButtonComp::IsClicked(int mouseX, int mouseY) const
{
    // UIComponent의 알파값 확인 후 처리
    UIComponent* uiComp = owner->GetComponent<UIComponent>();
    if (uiComp && uiComp->GetAlpha() != 1) {
        return false;
    }
    // pos와 scale을 이용해 클릭 여부 확인
    return (mouseX > pos.x - scale.x / 2 && mouseX < pos.x + scale.x / 2 &&
        mouseY > pos.y - scale.y / 2 && mouseY < pos.y + scale.y / 2);
}

bool ButtonComp::IsHovered(int mouseX, int mouseY) const
{
    return IsClicked(mouseX, mouseY);  // 클릭 가능 여부와 동일하게 동작
}

void ButtonComp::OnClick()
{
    EventManager::GetInstance().AddEvent<ButtonClickEvent>(this, this);
}

void ButtonComp::OnHover()
{
    if (onHoverFunction) {
        onHoverFunction();  // Hover 시 실행할 함수 호출
    }
}

void ButtonComp::OnHoverOut()
{
    if (onHoverOutFunction) {
        onHoverOutFunction();  // Hover 해제 시 실행할 함수 호출
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

void ButtonComp::SetOnHoverOutFunction(std::function<void()> func)
{
    onHoverOutFunction = func;
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
