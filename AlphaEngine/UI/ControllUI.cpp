#include "ControllUI.h"
#include "../Components/UIComp.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Components/ButtonComp.h"
#include "../Components/SubtitleComp.h"

void ControllUI::SetUIVisibility(bool isVisible)
{
    int alphaValue = isVisible ? 1 : 0;
    UIComponent* backgroundUI = BgUI->GetComponent<UIComponent>();
    UIComponent* controlUI = ControlUI->GetComponent<UIComponent>();
    UIComponent* CloseUI = CloseBtn->GetComponent<UIComponent>();

    backgroundUI->SetAlpha(alphaValue);
    controlUI->SetAlpha(alphaValue);
    CloseUI->SetAlpha(alphaValue);

}

void ControllUI::SetControllUI()
{
	isOpen = true;
	SetUIVisibility(true);
}

void ControllUI::Setoff()
{
	isOpen = false;
	SetUIVisibility(false);
}
void ControllUI::Setmenu()
{
    auto MSB = GameObjectManager::GetInstance().GetObj("MenuStartBtn");
    MSB->GetComponent<UIComponent>()->SetAlpha(1);
    auto MCB = GameObjectManager::GetInstance().GetObj("MenuCtrBtn");
    MCB->GetComponent<UIComponent>()->SetAlpha(1);
    auto MQB = GameObjectManager::GetInstance().GetObj("MenuQuitBtn");
    MQB->GetComponent<UIComponent>()->SetAlpha(1);

}

void ControllUI::InitControllUI()
{
    BgUI = new GameObject();
    BgUI->AddComponent<UIComponent>();
    UIComponent* backgroundUI = BgUI->GetComponent<UIComponent>();
    backgroundUI->SetScale({ 1400,750 });
    backgroundUI->SetPos({ 0, 0 });
    backgroundUI->SetTexture("");
    backgroundUI->SetColor(120, 120, 120);
    backgroundUI->SetAlpha(0);

  
    ControlUI = new GameObject();
    ControlUI->AddComponent<UIComponent>();
    UIComponent* controlUI = ControlUI->GetComponent<UIComponent>();
    controlUI->SetScale({ 800,400 });
    controlUI->SetPos({ 0, 0 });
    controlUI->SetTexture("Assets/UI/htp.png");
    controlUI->SetColor(0, 0, 0);
    controlUI->SetAlpha(0);



    CloseBtn = new GameObject();
    CloseBtn->AddComponent<UIComponent>();
    UIComponent* CloseUI = CloseBtn->GetComponent<UIComponent>();
    CloseUI->SetScale({ 50,50 });
    CloseUI->SetPos({ 650, 300 });
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

void ControllUI::UpdateControllUI()
{
}

void ControllUI::ExitControllUI()
{
}
