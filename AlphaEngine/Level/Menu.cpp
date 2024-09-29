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
#include "../Camera/Camera.h"
#include "../UI/ControlUI.h"
ControlUI CtrUI;
#define PLAY_AUDIO_CLICK GameObjectManager::GetInstance().GetObj("menuBg")->GetComponent<AudioComp>()->playAudio(0, "./Assets/Audio/click_effect.mp3")
void level::Menu::Init() {
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

    // Start ��ư �ʱ�ȭ �� ���
    startButtonObj = new GameObject("MenuStartBtn");
    startButtonObj->AddComponent<UIComponent>();
    UIComponent* startUI = startButtonObj->GetComponent<UIComponent>();
    startUI->SetPos({ 0, -100 });
    startUI->SetScale({ 480, 90 });
    startUI->SetTexture("Assets/UI/Menu.png");
    startUI->SetColor(0, 0, 0);
    startUI->SetScreenSpace(true);

    startButtonObj->AddComponent<ButtonComp>();
    ButtonComp* startBtn = startButtonObj->GetComponent<ButtonComp>();

    startBtn->SetOnClickFunction([]() {
        PLAY_AUDIO_CLICK;
        GSM::GameStateManager::GetInstance().ChangeLevel(new level::NormalLevel(1));
        });


    startBtn->SetOnHoverFunction([startUI]() {
        startUI->SetScale({ 500, 100 });
        });


    startBtn->SetOnHoverOutFunction([startUI]() {
        startUI->SetScale({ 480, 90 });
        });


    CtlButtonObj = new GameObject("MenuCtrBtn");
    CtlButtonObj->AddComponent<UIComponent>();
    UIComponent* ControllUI = CtlButtonObj->GetComponent<UIComponent>();
    ControllUI->SetPos({ 0, -200 });
    ControllUI->SetScale({ 480, 90 });
    ControllUI->SetTexture("Assets/UI/Menu.png");
    ControllUI->SetColor(0, 0, 0);
    ControllUI->SetScreenSpace(true);
    CtlButtonObj->AddComponent<ButtonComp>();
    ButtonComp* ControllBtn = CtlButtonObj->GetComponent<ButtonComp>();
    ControllBtn->SetOnClickFunction([this]() {
        Setoff();
        CtrUI.SetUIVisibility(true);
        });
 
    ControllBtn->SetOnHoverFunction([ControllUI]() {

        ControllUI->SetScale({ 500, 100 });
        });

    // Hover ���� �� ���� ũ��� ����
    ControllBtn->SetOnHoverOutFunction([ControllUI]() {
        ControllUI->SetScale({ 480, 90 });
        });

    // Quit ��ư �ʱ�ȭ �� ���
    quitButtonObj = new GameObject("MenuQuitBtn");
    quitButtonObj->AddComponent<UIComponent>();
    UIComponent* quitUI = quitButtonObj->GetComponent<UIComponent>();
    quitUI->SetPos({ 0, -300 });
    quitUI->SetScale({ 480, 90 });
    quitUI->SetTexture("Assets/UI/Menu.png");
    quitUI->SetColor(0, 0, 0);
    quitUI->SetScreenSpace(true);
    quitButtonObj->AddComponent<ButtonComp>();
    ButtonComp* quitBtn = quitButtonObj->GetComponent<ButtonComp>();

    quitBtn->SetOnClickFunction([]() {
        PLAY_AUDIO_CLICK;
        GSM::GameStateManager::GetInstance().ChangeLevel(nullptr);
        });


    quitBtn->SetOnHoverFunction([quitUI]() {
  
        quitUI->SetScale({ 500, 100 });
        });

    // Hover ���� �� ���� ũ��� ����
    quitBtn->SetOnHoverOutFunction([quitUI]() {
        quitUI->SetScale({ 480, 90 });
        });
    CtrUI.InitControlUI();
    // �ڸ� �߰�
    SubtitleComp::AddSubtitle({ {-0.15f,-0.27f}, 1, "START", 0.2f, 0, 0, 1 });
    SubtitleComp::AddSubtitle({ {-0.15f,-0.495f}, 1, "Control", 0.2f, 0, 0, 1 });
    SubtitleComp::AddSubtitle({ {-0.11f,-0.72f}, 1, "EXIT", 0.2f, 0, 0, 1 });
}


void level::Menu::Update() {

}

void level::Menu::Exit() {
    // ���ҽ� ���� ���� �ڵ�
    SubtitleComp::ClearSubtitle();
}

void level::Menu::Setoff()
{
    UIComponent* startUI = startButtonObj->GetComponent<UIComponent>();
    UIComponent* ControllUI = CtlButtonObj->GetComponent<UIComponent>();
    UIComponent* quitUI = quitButtonObj->GetComponent<UIComponent>();
    startUI->SetAlpha(0);
    ControllUI->SetAlpha(0);
    quitUI->SetAlpha(0);
    SubtitleComp::ModifySubtitle("START", 0);
    SubtitleComp::ModifySubtitle("Control", 0);
    SubtitleComp::ModifySubtitle("EXIT", 0);
}
