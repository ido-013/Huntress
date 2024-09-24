#include "EscMenu.h"
#include "../Components/UIComp.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Components/ButtonComp.h"
#include "../GSM/GameStateManager.h"
#include "../Combat/Combat.h"
#include "../Level/Menu.h"
void EscUI::SetUIVisibility(bool isVisible)
{
	int alphaValue = isVisible ? 1 : 0;
    UIComponent* backgroundUI = BgUI->GetComponent<UIComponent>();
    UIComponent* RestartUI = RestartBtn->GetComponent<UIComponent>();
    UIComponent* QuitUI = QuitBtn->GetComponent<UIComponent>();
    UIComponent* CloseUI = CloseBtn->GetComponent<UIComponent>();
    backgroundUI->SetAlpha(alphaValue);
    RestartUI->SetAlpha(alphaValue);
    QuitUI->SetAlpha(alphaValue);
    CloseUI->SetAlpha(alphaValue);
}

void EscUI::SetControllUI()
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
    backgroundUI->SetTexture("");
    backgroundUI->SetColor(120, 120, 120);
    backgroundUI->SetAlpha(0);

    RestartBtn = new GameObject();
    RestartBtn->AddComponent<UIComponent>();
    UIComponent* RestartUI = RestartBtn->GetComponent<UIComponent>();
    RestartUI->SetPos({ 0, -100 });
    RestartUI->SetScale({ 300, 100 });
    RestartUI->SetTexture("Assets/UI/Menu.png");
    RestartUI->SetColor(0, 0, 0);
    RestartUI->SetAlpha(0);
    RestartUI->SetScreenSpace(true);
    RestartBtn->AddComponent<ButtonComp>();
    ButtonComp* restartBtn = RestartBtn->GetComponent<ButtonComp>();

    restartBtn->SetOnClickFunction([]() {
        std::cout << "Start Button Clicked!" << std::endl;
        GSM::GameStateManager::GetInstance().ChangeLevel(new level::Menu);
        });

    // Hover 시 크기를 줄여서 눌리는 듯한 효과
    restartBtn->SetOnHoverFunction([RestartUI]() {
        std::cout << "Start Button Hovered!" << std::endl;
        RestartUI->SetScale({ 280, 90 });  // 크기 살짝 줄이기
        });

    // Hover 해제 시 원래 크기로 복원
    restartBtn->SetOnHoverOutFunction([RestartUI]() {
        std::cout << "Start Button Hover Out!" << std::endl;
        RestartUI->SetScale({ 300, 100 });  // 원래 크기로 되돌리기
        });
    QuitBtn = new GameObject();
    QuitBtn->AddComponent<UIComponent>();
    UIComponent* QuitUI = QuitBtn->GetComponent<UIComponent>();
    QuitUI->SetPos({ 0, -300 });
    QuitUI->SetScale({ 300, 100 });
    QuitUI->SetTexture("Assets/UI/Menu.png");
    QuitUI->SetColor(0, 0, 0);
    QuitUI->SetAlpha(0);
    QuitUI->SetScreenSpace(true);
    QuitBtn->AddComponent<ButtonComp>();
    ButtonComp* quitBtn = QuitBtn->GetComponent<ButtonComp>();
    quitBtn->SetOnClickFunction([]() {
        std::cout << "Start Button Clicked!" << std::endl;
        GSM::GameStateManager::GetInstance().ChangeLevel(nullptr);
        });

    // Hover 시 크기를 줄여서 눌리는 듯한 효과
    quitBtn->SetOnHoverFunction([QuitUI]() {
        std::cout << "Start Button Hovered!" << std::endl;
        QuitUI->SetScale({ 280, 90 });  // 크기 살짝 줄이기
        });

    // Hover 해제 시 원래 크기로 복원
    quitBtn->SetOnHoverOutFunction([QuitUI]() {
        std::cout << "Start Button Hover Out!" << std::endl;
        QuitUI->SetScale({ 300, 100 });  // 원래 크기로 되돌리기
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
        CombatComp::ResetCombat();
        });
}

void EscUI::UpdateEscUI()
{
    if (AEInputCheckTriggered(AEVK_ESCAPE)) {
        CombatComp::isCombat = false;
        CombatComp::state = CombatComp::STATE::STORE;
        SetUIVisibility(true);
    }
}

void EscUI::ExitEscUI()
{

}
