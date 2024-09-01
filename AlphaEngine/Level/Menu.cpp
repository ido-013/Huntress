#include "Menu.h"
#include "../GameObject/GameObject.h"
#include "../Components/AudioComp.h"
#include "../Components/SpriteComp.h"
#include "../Components/TransformComp.h"
#include "../Components/ButtonComp.h"  // ButtonComp 포함
#include "../EventManager/EventManager.h"
#include "../UIM/BtnManager.h"
#include <iostream>

GameObject* Logo = nullptr;
GameObject* startButtonObj = nullptr;
GameObject* quitButtonObj = nullptr;
void level::Menu::Init() {
    // 로고 초기화
    Logo = new GameObject();
    Logo->AddComponent<SpriteComp>();
    Logo->AddComponent<TransformComp>();
    TransformComp* transLogo = Logo->GetComponent<TransformComp>();
    transLogo->SetScale({ 800,300 });
    transLogo->SetPos({ 0, 200 });
    SpriteComp* LogoSprite = Logo->GetComponent<SpriteComp>();
    LogoSprite->SetTexture("Assets/arrow.png");
    LogoSprite->SetColor(255, 255, 255);
    
    // Start 버튼 초기화 및 등록
    startButtonObj = new GameObject();
    startButtonObj->AddComponent<SpriteComp>();
    startButtonObj->AddComponent<TransformComp>();
    TransformComp* startButton = startButtonObj->GetComponent<TransformComp>();
    startButton->SetPos({ 0, -100 });
    startButton->SetScale({ 500, 100 });
    SpriteComp* startSprite = startButtonObj->GetComponent<SpriteComp>();
    startSprite->SetTexture("Assets/arrow.png");
    startSprite->SetColor(255, 255, 255);
    startButtonObj->AddComponent<ButtonComp>();
    ButtonComp* startBtn = startButtonObj->GetComponent<ButtonComp>();
    startBtn->SetOnClickFunction([]() {
        std::cout << "Start Button Clicked!" << std::endl;
        // Start 게임 시작 로직 추가
    });
    ButtonManager::GetInstance().RegisterButton(startBtn);

    // Quit 버튼 초기화 및 등록
    quitButtonObj = new GameObject();
    quitButtonObj->AddComponent<SpriteComp>();
    quitButtonObj->AddComponent<TransformComp>();
    TransformComp* quitButton = quitButtonObj->GetComponent<TransformComp>();
    quitButton->SetPos({ 0, -300 });
    quitButton->SetScale({ 500, 100 });
    SpriteComp* quitSprite = quitButtonObj->GetComponent<SpriteComp>();
    quitSprite->SetTexture("Assets/arrow.png");
    quitSprite->SetColor(255, 255, 255);
    quitButtonObj->AddComponent<ButtonComp>();
    ButtonComp* quitBtn = quitButtonObj->GetComponent<ButtonComp>();
    quitBtn->SetOnClickFunction([]() {
        std::cout << "Quit Button Clicked!" << std::endl;
        // Quit 게임 종료 로직 추가
    });
    ButtonManager::GetInstance().RegisterButton(quitBtn);
}

void level::Menu::Update() {
    // 매 프레임마다 버튼 매니저 업데이트

}

void level::Menu::Exit() {
    // 필요에 따라 리소스 정리
}
