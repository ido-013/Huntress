#include "ClearLevel.h"
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
#include "../Camera/Camera.h"

void level::ClearLevel::Init() {
    //AEGfxSetCamPosition(0, 0);
    Camera::GetInstance().SetPos(0, 0);

    // �ΰ� �ʱ�ȭ
    Credit = new GameObject("Credit");
    Credit->AddComponent<UIComponent>();
    UIComponent* CreditUI = Credit->GetComponent<UIComponent>();
    CreditUI->SetScale({ 1600, 900 });
    CreditUI->SetPos({ 0, 0 });
    CreditUI->SetTexture("Assets/credit.png");
    CreditUI->SetColor(0, 0, 0);
    CreditUI->SetAlpha(1);
    CreditUI->SetScreenSpace(true);
}

void level::ClearLevel::Update() {

}

void level::ClearLevel::Exit() {
    // ���ҽ� ���� ���� �ڵ�
}

