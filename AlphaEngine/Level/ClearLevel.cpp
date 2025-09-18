#include "ClearLevel.h"
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
#include "../Camera/Camera.h"

void level::ClearLevel::Init() {
    //AEGfxSetCamPosition(0, 0);
    Camera::GetInstance().SetPos(0, 0);

    // 로고 초기화
    Credit = new GameObject("Credit");

    Credit->AddComponent<UIComponent>();
    UIComponent* CreditUI = Credit->GetComponent<UIComponent>();

    AudioComp* a = Credit->AddComponent<AudioComp>();
    a->SetAudio("./Assets/Audio/Credit.mp3");
    a->playAudio(-1, "./Assets/Audio/Credit.mp3");

    CreditUI->SetScale({ 1600, 900 });
    CreditUI->SetPos({ 0, 0 });
    CreditUI->SetTexture("Assets/credit.png");
    CreditUI->SetColor(0, 0, 0);
    CreditUI->SetAlpha(1);
    CreditUI->SetScreenSpace(true);
    Escmenu.InitEscUI();
}

void level::ClearLevel::Update() {
    Escmenu.UpdateEscUI(nullptr);
}

void level::ClearLevel::Exit() {
    // 리소스 정리 등의 코드
}

