#include "EscMenu.h"
#include "../Components/UIComp.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Components/ButtonComp.h"
#include "../GSM/GameStateManager.h"
#include "../Combat/Combat.h"
#include "../Level/Menu.h"
#include "../Components//SubtitleComp.h"

bool EscUI::getOpen()
{
    return isOpen;
}
void EscUI::ToggleUI() {
    isOpen = !isOpen;
    SetUIVisibility(isOpen);
    CombatComp::isCombat = !isOpen; 
}

void EscUI::SetUIVisibility(bool isVisible)
{
	float alphaValue = isVisible ? 1.f : 0.f;
    UIComponent* backgroundUI = BgUI->GetComponent<UIComponent>();
    UIComponent* htpUI = htp->GetComponent<UIComponent>();
    UIComponent* RestartUI = RestartBtn->GetComponent<UIComponent>();
    UIComponent* QuitUI = QuitBtn->GetComponent<UIComponent>();
    UIComponent* CloseUI = CloseBtn->GetComponent<UIComponent>();
    backgroundUI->SetAlpha(alphaValue);
    htpUI->SetAlpha(alphaValue);
    RestartUI->SetAlpha(alphaValue);
    QuitUI->SetAlpha(alphaValue);
    CloseUI->SetAlpha(alphaValue);
}

void EscUI::SetEscUI()
{
	isOpen = true;
	SetUIVisibility(true);
}

void EscUI::Setoff()
{
	isOpen = false;
	SetUIVisibility(false);
}



void EscUI::InitEscUI()
{
    BgUI = new GameObject();
    BgUI->AddComponent<UIComponent>();
    UIComponent* backgroundUI = BgUI->GetComponent<UIComponent>();
    backgroundUI->SetScale({ 1400,750 });
    backgroundUI->SetPos({ 0, 0 });
    backgroundUI->SetTexture("Assets/UI/Option.png");
    backgroundUI->SetColor(0, 0, 0);
    backgroundUI->SetAlpha(0);

    htp = new GameObject();
    htp->AddComponent<UIComponent>();
    UIComponent* htpUI = htp->GetComponent<UIComponent>();
    htpUI->SetScale({ 800,300 });
    htpUI->SetPos({ 0, 100 });
    htpUI->SetTexture("Assets/UI/htp.png");
    htpUI->SetColor(0, 0, 0);
    htpUI->SetAlpha(0);

    RestartBtn = new GameObject();
    RestartBtn->AddComponent<UIComponent>();
    UIComponent* RestartUI = RestartBtn->GetComponent<UIComponent>();
    RestartUI->SetPos({ -370, -100 });
    RestartUI->SetScale({ 350, 100 });
    RestartUI->SetTexture("Assets/UI/EscMenu.png");
    RestartUI->SetColor(0, 0, 0);
    RestartUI->SetAlpha(0);
    RestartUI->SetScreenSpace(true);
    RestartBtn->AddComponent<ButtonComp>();
    ButtonComp* restartBtn = RestartBtn->GetComponent<ButtonComp>();

    restartBtn->SetOnClickFunction([]() {

        GSM::GameStateManager::GetInstance().ChangeLevel(new level::Menu);
        });

    restartBtn->SetOnHoverFunction([RestartUI]() {

        RestartUI->SetScale({ 330, 90 });  
        });

    // Hover 해제 시 원래 크기로 복원
    restartBtn->SetOnHoverOutFunction([RestartUI]() {

        RestartUI->SetScale({ 350, 100 });  
        });
   
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
        Setoff();

        SubtitleComp::ModifySubtitle("goldText", 1);
        CombatComp::isCombat = true;
        });

    QuitBtn = new GameObject();
    QuitBtn->AddComponent<UIComponent>();
    UIComponent* QuitUI = QuitBtn->GetComponent<UIComponent>();
    QuitUI->SetPos({ -370, -200 });
    QuitUI->SetScale({ 350, 100 });
    QuitUI->SetTexture("Assets/UI/GameQuit.png");
    QuitUI->SetColor(0, 0, 0);
    QuitUI->SetAlpha(0);
    QuitUI->SetScreenSpace(true);
    QuitBtn->AddComponent<ButtonComp>();
    ButtonComp* quitBtn = QuitBtn->GetComponent<ButtonComp>();
    quitBtn->SetOnClickFunction([this]() {
        GSM::GameStateManager::GetInstance().ChangeLevel(nullptr);
        });

    quitBtn->SetOnHoverFunction([QuitUI]() {
        QuitUI->SetScale({ 330, 90 });
        });

    // Hover 해제 시 원래 크기로 복원
    quitBtn->SetOnHoverOutFunction([QuitUI]() {
        QuitUI->SetScale({ 350, 100 });
        });

}

void EscUI::UpdateEscUI(StoreUI* storeUI) {

    if (AEInputCheckTriggered(AEVK_ESCAPE)) {
        ToggleUI(); 

        if (storeUI && storeUI->getOpen()) {
            storeUI->StoreOnEsc();
        }
        else if (storeUI && storeUI->getisEsc()) {
            storeUI->StoreOffEsc();
        }
    }
}

void EscUI::ExitEscUI()
{

}
