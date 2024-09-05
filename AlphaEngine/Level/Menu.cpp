#include "Menu.h"
#include "../GameObject/GameObject.h"
#include "../Components/AudioComp.h"
#include "../Components/UIComp.h"      // UIComponent ���
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

void level::Menu::Init() {
    AEGfxSetCamPosition(0, 0);

    menuBg = new GameObject("menuBg");
    menuBg->AddComponent<UIComponent>();
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
    // Start ��ư �ʱ�ȭ �� ���
    startButtonObj = new GameObject();
    startButtonObj->AddComponent<UIComponent>();  // UIComponent�� ����
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
        GSM::GameStateManager::GetInstance().ChangeLevel(new level::NormalLevel(1));
        });

    startBtn->SetOnHoverFunction([]() {
        std::cout << "Start Button Hovered!" << std::endl;
        // Hover ���� �߰� ���� ����
        });

    ButtonManager::GetInstance().RegisterButton(startBtn);


    // Quit ��ư �ʱ�ȭ �� ���
    quitButtonObj = new GameObject();
    quitButtonObj->AddComponent<UIComponent>();  // UIComponent�� ����
    UIComponent* quitUI = quitButtonObj->GetComponent<UIComponent>();
    quitUI->SetPos({ 0, -300 });
    quitUI->SetScale({ 500, 100 });
    quitUI->SetTexture("Assets/UI/Menu.png");
    quitUI->SetColor(0, 0, 0);
    quitUI->SetScreenSpace(true);  // Quit ��ư�� ��ũ�� ������ �ְ� ����
    quitButtonObj->AddComponent<ButtonComp>();
    ButtonComp* quitBtn = quitButtonObj->GetComponent<ButtonComp>();

    quitBtn->SetOnClickFunction([]() {
        std::cout << "Quit Button Clicked!" << std::endl;
        // Quit ���� ���� ���� �߰�
        GSM::GameStateManager::GetInstance().ChangeLevel(nullptr);
        });

    ButtonManager::GetInstance().RegisterButton(quitBtn);

    SubtitleComp::AddSubtitle({ {-0.15,-0.27}, 1, "START", 0.2, 0, 0, 1 });
    SubtitleComp::AddSubtitle({ {-0.11,-0.72}, 1, "EXIT", 0.2, 0, 0, 1 });

}

void level::Menu::Update() {

}

void level::Menu::Exit() {
    // ���ҽ� ���� ���� �ڵ�
    SubtitleComp::ClearSubtitle();
}
