#include "Menu.h"
#include "../GameObject/GameObject.h"
#include "../Components/AudioComp.h"
#include "../Components/SpriteComp.h"
#include "../Components/TransformComp.h"
#include "../Components/ButtonComp.h"  // ButtonComp ����
#include "../EventManager/EventManager.h"
#include "../UIM/BtnManager.h"
#include <iostream>

GameObject* Logo = nullptr;
GameObject* startButtonObj = nullptr;
GameObject* quitButtonObj = nullptr;
void level::Menu::Init() {
    // �ΰ� �ʱ�ȭ
    Logo = new GameObject();
    Logo->AddComponent<SpriteComp>();
    Logo->AddComponent<TransformComp>();
    TransformComp* transLogo = Logo->GetComponent<TransformComp>();
    transLogo->SetScale({ 800,300 });
    transLogo->SetPos({ 0, 200 });
    SpriteComp* LogoSprite = Logo->GetComponent<SpriteComp>();
    LogoSprite->SetTexture("Assets/arrow.png");
    LogoSprite->SetColor(255, 255, 255);

    // Start ��ư �ʱ�ȭ �� ���
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

    // Quit ��ư �ʱ�ȭ �� ���
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
    // �� �����Ӹ��� ��ư �Ŵ��� ������Ʈ

}

void level::Menu::Exit() {
    // �ʿ信 ���� ���ҽ� ����
}
