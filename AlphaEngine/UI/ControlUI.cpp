#include "ControlUI.h"
#include "../Components/UIComp.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Components/ButtonComp.h"
#include "../Components/SubtitleComp.h"

void ControlUI::SetUIVisibility(bool isVisible)
{
    float alphaValue = isVisible ? 1.f : 0.f;
    UIComponent* backgroundUI = BgUI->GetComponent<UIComponent>();
    UIComponent* controlUI = CtlUI->GetComponent<UIComponent>();
    UIComponent* CloseUI = CloseBtn->GetComponent<UIComponent>();

    backgroundUI->SetAlpha((float)alphaValue);
    controlUI->SetAlpha((float)alphaValue);
    CloseUI->SetAlpha((float)alphaValue);

}

void ControlUI::SetControlUI()
{
	isOpen = true;
	SetUIVisibility(true);
}

void ControlUI::Setoff()
{
	isOpen = false;
	SetUIVisibility(false);

        SubtitleComp::ModifySubtitle("START", 1);
        SubtitleComp::ModifySubtitle("Control", 1);
        SubtitleComp::ModifySubtitle("EXIT", 1);

}
void ControlUI::Setmenu()
{
    auto MSB = GameObjectManager::GetInstance().GetObj("MenuStartBtn");
    MSB->GetComponent<UIComponent>()->SetAlpha(1);
    auto MCB = GameObjectManager::GetInstance().GetObj("MenuCtrBtn");
    MCB->GetComponent<UIComponent>()->SetAlpha(1);
    auto MQB = GameObjectManager::GetInstance().GetObj("MenuQuitBtn");
    MQB->GetComponent<UIComponent>()->SetAlpha(1);

}

void ControlUI::InitControlUI()
{
    BgUI = new GameObject();
    BgUI->AddComponent<UIComponent>();
    UIComponent* backgroundUI = BgUI->GetComponent<UIComponent>();
    backgroundUI->SetScale({ 1400,750 });
    backgroundUI->SetPos({ 0, 0 });
    backgroundUI->SetTexture("Assets/UI/Option.png");
    backgroundUI->SetColor(0, 0, 0);
    backgroundUI->SetAlpha(0);

  
    CtlUI = new GameObject();
    CtlUI->AddComponent<UIComponent>();
    UIComponent* controlUI = CtlUI->GetComponent<UIComponent>();
    controlUI->SetScale({ 800,550 });
    controlUI->SetPos({ 0, 0 });
    controlUI->SetTexture("Assets/UI/htp.png");
    controlUI->SetColor(0, 0, 0);
    controlUI->SetAlpha(0);



    CloseBtn = new GameObject();
    CloseBtn->AddComponent<UIComponent>();
    UIComponent* CloseUI = CloseBtn->GetComponent<UIComponent>();
    CloseUI->SetScale({ 50,50 });
    CloseUI->SetPos({ 600, 300 });
    CloseUI->SetTexture("Assets/UI/Arrow.png");
    CloseUI->SetColor(250, 0, 0);
    CloseUI->SetAlpha(0);
    CloseBtn->AddComponent<ButtonComp>();
    ButtonComp* CloseButton = CloseBtn->GetComponent<ButtonComp>();
    CloseButton->SetOnClickFunction([this]() {
        Setmenu();
        Setoff(); 
        });


}

void ControlUI::UpdateControlUI()
{
}

void ControlUI::ExitControlUI()
{
}
