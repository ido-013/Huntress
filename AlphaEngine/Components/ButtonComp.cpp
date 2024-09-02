#include "ButtonComp.h"
#include "../EventManager/EventManager.h"
#include "../UIM/BtnManager.h"
#include "../Event/ButtonClickEvent.h"

ButtonComp::ButtonComp(GameObject* _owner)
    : EngineComponent(_owner), pos(), scale()
{
    ButtonManager::GetInstance().RegisterButton(this);
    EventManager::GetInstance().AddEntity(this);
    pos = owner->GetComponent<TransformComp>()->GetPos();
    scale = owner->GetComponent<TransformComp>()->GetScale();
}

ButtonComp::~ButtonComp()
{
    ButtonManager::GetInstance().RemoveButton(this);
    EventManager::GetInstance().DelEntity(this);
}

void ButtonComp::Update()
{
    // �ʿ� �� �߰����� ������Ʈ ������ ���⿡ �ۼ�
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

// ���콺�� ��ư ���� �ȿ� �ִ��� Ȯ���ϴ� �޼���
bool ButtonComp::IsClicked(int mouseX, int mouseY) const
{
    return (mouseX > pos.x - scale.x / 2 && mouseX < pos.x + scale.x / 2 &&
        mouseY > pos.y - scale.y / 2 && mouseY < pos.y + scale.y / 2);
}

// ��ư�� Ŭ���Ǿ��� �� ȣ��Ǵ� �޼���
void ButtonComp::OnClick()
{
    // �̺�Ʈ �Ŵ����� ��ư Ŭ�� �̺�Ʈ �߰�
    EventManager::GetInstance().AddEvent<ButtonClickEvent>(this, this);
}

void ButtonComp::SetOnClickFunction(std::function<void()> func)
{
    onClickFunction = func;
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
