#include "ButtonComp.h"
#include "../EventManager/EventManager.h"
#include "../UIM/BtnManager.h"
#include "../Event/ButtonClickEvent.h"

ButtonComp::ButtonComp(GameObject* _owner)
    : EngineComponent(_owner), pos(), scale()
{
    ButtonManager::GetInstance().RegisterButton(this);
    EventManager::GetInstance().AddEntity(this);
}

ButtonComp::~ButtonComp()
{
    ButtonManager::GetInstance().RemoveButton(this);
    EventManager::GetInstance().DelEntity(this);
}

void ButtonComp::Update()
{
    // 이곳에 추가적인 업데이트 로직을 구현할 수 있습니다.
}

void ButtonComp::OnEvent(Event* e)
{
    if (dynamic_cast<ButtonClickEvent*>(e) != nullptr)
    {
        std::cout << "Button clicked and handled in OnEvent!" << std::endl;
        // 클릭 시 실행할 추가 로직을 여기에 작성
    }
}

void ButtonComp::SetPos(const AEVec2& otherPos)
{
    pos = otherPos;
}

void ButtonComp::SetScale(const AEVec2& otherScale)
{
    scale = otherScale;
}

AEVec2 ButtonComp::GetPos()
{
    return pos;
}

AEVec2 ButtonComp::Getscale()
{
    return scale;
}

// 마우스가 버튼 영역 안에 있는지 확인하는 메서드
bool ButtonComp::IsClicked(int mouseX, int mouseY) const
{
    return (mouseX > pos.x - scale.x / 2 && mouseX < pos.x + scale.x / 2 &&
        mouseY > pos.y - scale.y / 2 && mouseY < pos.y + scale.y / 2);
}

// 버튼이 클릭되었을 때 호출되는 메서드
void ButtonComp::OnClick()
{
    // 이벤트 매니저에 버튼 클릭 이벤트 추가
    EventManager::GetInstance().AddEvent<ButtonClickEvent>(this, this);

    // 추가적으로 클릭 시 색상 변경 등 피드백을 추가할 수 있습니다.
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
