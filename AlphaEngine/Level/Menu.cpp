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
    startButtonObj->AddComponent<ButtonComp>();
    ButtonComp* startButton = startButtonObj->GetComponent<ButtonComp>();
    startButton->SetPos({ 0, -100 });
    startButton->SetScale({ 500, 100 });
    startButton->LoadFromJson({
        {"pos", {{"x", 0}, {"y", -100}}},
        {"scale", {{"x", 500}, {"y", 100}}},
        {"texturePath", "Assets/arrow.png"}
        });
    ButtonManager::GetInstance().RegisterButton(startButton);

    // Quit 버튼 초기화 및 등록
    quitButtonObj = new GameObject();
    quitButtonObj->AddComponent<ButtonComp>();
    ButtonComp* quitButton = quitButtonObj->GetComponent<ButtonComp>();
    quitButton->SetPos({ 0, -300 });
    quitButton->SetScale({ 500, 100 });
    quitButton->LoadFromJson({
        {"pos", {{"x", 0}, {"y", -300}}},
        {"scale", {{"x", 500}, {"y", 100}}},
        {"texturePath", "Assets/arrow.png"}
        });
    ButtonManager::GetInstance().RegisterButton(quitButton);
}

void level::Menu::Update() {
    // 매 프레임마다 버튼 매니저 업데이트

}

void level::Menu::Exit() {
    // 필요에 따라 리소스 정리
}
