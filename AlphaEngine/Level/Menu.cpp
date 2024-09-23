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

#define PLAY_AUDIO_CLICK GameObjectManager::GetInstance().GetObj("menuBg")->GetComponent<AudioComp>()->playAudio(0, "./Assets/Audio/click_effect.mp3")

void level::Menu::Init() {
    //AEGfxSetCamPosition(0, 0);
    Camera::GetInstance().SetPos(0, 0);

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
    startButtonObj = new GameObject();
    startButtonObj->AddComponent<UIComponent>();  // UIComponent로 변경
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

    startBtn->SetOnHoverFunction([]() {
        std::cout << "Start Button Hovered!" << std::endl;
        // Hover 시의 추가 동작 구현
        });

    ButtonManager::GetInstance().RegisterButton(startBtn);


    // Quit 버튼 초기화 및 등록
    quitButtonObj = new GameObject();
    quitButtonObj->AddComponent<UIComponent>();  // UIComponent로 변경
    UIComponent* quitUI = quitButtonObj->GetComponent<UIComponent>();
    quitUI->SetPos({ 0, -300 });
    quitUI->SetScale({ 500, 100 });
    quitUI->SetTexture("Assets/UI/Menu.png");
    quitUI->SetColor(0, 0, 0);
    quitUI->SetScreenSpace(true);  // Quit 버튼도 스크린 공간에 있게 설정
    quitButtonObj->AddComponent<ButtonComp>();
    ButtonComp* quitBtn = quitButtonObj->GetComponent<ButtonComp>();

    quitBtn->SetOnClickFunction([]() {
        std::cout << "Quit Button Clicked!" << std::endl;
        PLAY_AUDIO_CLICK;
        // Quit 게임 종료 로직 추가
        GSM::GameStateManager::GetInstance().ChangeLevel(nullptr);
        });

    ButtonManager::GetInstance().RegisterButton(quitBtn);

    SubtitleComp::AddSubtitle({ {(f32)-0.15,(f32)-0.27}, (f32)1, "START", (f32)0.2, (f32)0, (f32)0, (f32)1 });
    SubtitleComp::AddSubtitle({ {(f32)-0.11,(f32)-0.72}, (f32)1, "EXIT", (f32)0.2, (f32)0, (f32)0, (f32)1 });

}

void level::Menu::Update() {

}

void level::Menu::Exit() {
    // 리소스 정리 등의 코드
    SubtitleComp::ClearSubtitle();
}
