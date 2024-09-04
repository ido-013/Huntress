

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
#include "../GameObjectManager/GameObjectManager.h"
#include "../GSM/GameStateManager.h"
#include "../GameObjectManager/GameObjectManager.h"

void level::Menu::Init() {
    // 로고 초기화
    Logo = new GameObject("Logo");
    Logo->AddComponent<UIComponent>();
    UIComponent* LogoUI = Logo->GetComponent<UIComponent>();
    LogoUI->SetScale({ 800, 300 });
    LogoUI->SetPos({ 0, 200 });
    LogoUI->SetTexture("Assets/arrow.png");
    LogoUI->SetColor(255, 255, 255);
    LogoUI->SetAlpha(1);
    LogoUI->SetScreenSpace(true);
    // Start 버튼 초기화 및 등록
    startButtonObj = new GameObject();
    startButtonObj->AddComponent<UIComponent>();  // UIComponent로 변경
    UIComponent* startUI = startButtonObj->GetComponent<UIComponent>();
    startUI->SetPos({ 0, -100 });
    startUI->SetScale({ 500, 100 });
    startUI->SetTexture("Assets/arrow.png");
    startUI->SetColor(255, 255, 255);
    startUI->SetScreenSpace(true);

    startButtonObj->AddComponent<ButtonComp>();
    ButtonComp* startBtn = startButtonObj->GetComponent<ButtonComp>();

    startBtn->SetOnClickFunction([]() {
        std::cout << "Start Button Clicked!" << std::endl;
        GSM::GameStateManager::GetInstance().ChangeLevel(new level::CombatLevel);
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
    quitUI->SetTexture("Assets/arrow.png");
    quitUI->SetColor(255, 255, 255);
    quitUI->SetScreenSpace(true);  // Quit 버튼도 스크린 공간에 있게 설정
    quitButtonObj->AddComponent<ButtonComp>();
    ButtonComp* quitBtn = quitButtonObj->GetComponent<ButtonComp>();

    quitBtn->SetOnClickFunction([]() {
        std::cout << "Quit Button Clicked!" << std::endl;
        // Quit 게임 종료 로직 추가
        });

    ButtonManager::GetInstance().RegisterButton(quitBtn);
}

void level::Menu::Update() {

}

void level::Menu::Exit() {
    // 리소스 정리 등의 코드
}
