#include "Menu.h"
#include "../GameObject/GameObject.h"
#include "../Components/AudioComp.h"
#include "../Components/UIComp.h"      // UIComponent 사용
#include "../Components/TransformComp.h"
#include "../Components/ButtonComp.h"
#include "../EventManager/EventManager.h"
#include "../UIM/BtnManager.h"
#include <iostream>
#include "CombatLevel.h"
#include "NormalLevel.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../GSM/GameStateManager.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Components/SubtitleComp.h"
#include "../Camera/Camera.h"
#include "../UI/ControllUI.h"
ControllUI CtrUI;
#define PLAY_AUDIO_CLICK GameObjectManager::GetInstance().GetObj("menuBg")->GetComponent<AudioComp>()->playAudio(0, "./Assets/Audio/click_effect.mp3")
void level::Menu::Init() {
    // 카메라 초기화
    Camera::GetInstance().SetPos(0, 0);

    // 메뉴 배경 초기화
    menuBg = new GameObject("menuBg");
    menuBg->AddComponent<UIComponent>();
    menuBg->AddComponent<AudioComp>()->SetAudio("./Assets/Audio/click_effect.mp3");
    UIComponent* BgUI = menuBg->GetComponent<UIComponent>();
    BgUI->SetScale({ 1600, 900 });
    BgUI->SetPos({ 0, 0 });
    BgUI->SetTexture("Assets/Background/BG5.png");
    BgUI->SetColor(0, 0, 0);
    BgUI->SetAlpha(1);
    BgUI->SetScreenSpace(true);


    Logo = new GameObject("Logo");
    Logo->AddComponent<UIComponent>();
    UIComponent* LogoUI = Logo->GetComponent<UIComponent>();
    LogoUI->SetScale({ 700, 450 });
    LogoUI->SetPos({ 0, 150 });
    LogoUI->SetTexture("Assets/UI/hutress Logo2.png");
    LogoUI->SetColor(0, 0, 0);
    LogoUI->SetAlpha(1);
    LogoUI->SetScreenSpace(true);

    // Start 버튼 초기화 및 등록
    startButtonObj = new GameObject("MenuStartBtn");
    startButtonObj->AddComponent<UIComponent>();
    UIComponent* startUI = startButtonObj->GetComponent<UIComponent>();
    startUI->SetPos({ 0, -100 });
    startUI->SetScale({ 500, 100 });
    startUI->SetTexture("Assets/UI/Menu.png");
    startUI->SetColor(0, 0, 0);
    startUI->SetScreenSpace(true);

    startButtonObj->AddComponent<ButtonComp>();
    ButtonComp* startBtn = startButtonObj->GetComponent<ButtonComp>();

    startBtn->SetOnClickFunction([]() {
        std::cout << "Start Button Clicked!" << std::endl;
        PLAY_AUDIO_CLICK;
        GSM::GameStateManager::GetInstance().ChangeLevel(new level::NormalLevel(1));
        });


    startBtn->SetOnHoverFunction([startUI]() {
        std::cout << "Start Button Hovered!" << std::endl;
        startUI->SetScale({ 480, 90 });  
        });


    startBtn->SetOnHoverOutFunction([startUI]() {
        std::cout << "Start Button Hover Out!" << std::endl;
        startUI->SetScale({ 500, 100 });
        });


    ControllButtonObj = new GameObject("MenuCtrBtn");
    ControllButtonObj->AddComponent<UIComponent>();
    UIComponent* ControllUI = ControllButtonObj->GetComponent<UIComponent>();
    ControllUI->SetPos({ 0, -200 });
    ControllUI->SetScale({ 500, 100 });
    ControllUI->SetTexture("Assets/UI/Menu.png");
    ControllUI->SetColor(0, 0, 0);
    ControllUI->SetScreenSpace(true);
    ControllButtonObj->AddComponent<ButtonComp>();
    ButtonComp* ControllBtn = ControllButtonObj->GetComponent<ButtonComp>();
    ControllBtn->SetOnClickFunction([this]() {
        Setoff();
        CtrUI.SetUIVisibility(true);
        });
 
    ControllBtn->SetOnHoverFunction([ControllUI]() {
        std::cout << "Control Button Hovered!" << std::endl;
        ControllUI->SetScale({ 480, 90 });
        });

    // Hover 해제 시 원래 크기로 복원
    ControllBtn->SetOnHoverOutFunction([ControllUI]() {
        std::cout << "Control Button Hover Out!" << std::endl;
        ControllUI->SetScale({ 500, 100 });
        });

    // Quit 버튼 초기화 및 등록
    quitButtonObj = new GameObject("MenuQuitBtn");
    quitButtonObj->AddComponent<UIComponent>();
    UIComponent* quitUI = quitButtonObj->GetComponent<UIComponent>();
    quitUI->SetPos({ 0, -300 });
    quitUI->SetScale({ 500, 100 });
    quitUI->SetTexture("Assets/UI/Menu.png");
    quitUI->SetColor(0, 0, 0);
    quitUI->SetScreenSpace(true);
    quitButtonObj->AddComponent<ButtonComp>();
    ButtonComp* quitBtn = quitButtonObj->GetComponent<ButtonComp>();

    quitBtn->SetOnClickFunction([]() {
        std::cout << "Quit Button Clicked!" << std::endl;
        PLAY_AUDIO_CLICK;
        GSM::GameStateManager::GetInstance().ChangeLevel(nullptr);
        });


    quitBtn->SetOnHoverFunction([quitUI]() {
        std::cout << "Quit Button Hovered!" << std::endl;
        quitUI->SetScale({ 480, 90 });
        });

    // Hover 해제 시 원래 크기로 복원
    quitBtn->SetOnHoverOutFunction([quitUI]() {
        std::cout << "Quit Button Hover Out!" << std::endl;
        quitUI->SetScale({ 500, 100 });
        });
    CtrUI.InitControllUI();
    // 자막 추가
    SubtitleComp::AddSubtitle({ {-0.15,-0.27}, 1, "START", 0.2, 0, 0, 1 });
    SubtitleComp::AddSubtitle({ {-0.15,-0.495}, 1, "Controll", 0.2, 0, 0, 1 });
    SubtitleComp::AddSubtitle({ {-0.11,-0.72}, 1, "EXIT", 0.2, 0, 0, 1 });
}


void level::Menu::Update() {

}

void level::Menu::Exit() {
    // 리소스 정리 등의 코드
    SubtitleComp::ClearSubtitle();
}

void level::Menu::Setoff()
{
    UIComponent* startUI = startButtonObj->GetComponent<UIComponent>();
    UIComponent* ControllUI = ControllButtonObj->GetComponent<UIComponent>();
    UIComponent* quitUI = quitButtonObj->GetComponent<UIComponent>();
    startUI->SetAlpha(0);
    ControllUI->SetAlpha(0);
    quitUI->SetAlpha(0);
}
