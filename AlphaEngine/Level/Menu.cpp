#include "Menu.h"
#include "../GameObject/GameObject.h"
#include "../Components/AudioComp.h"
#include "../Components/SpriteComp.h"
#include "../Components/TransformComp.h"
#include "../EventManager/EventManager.h"
#include "../UIM/BtnManager.h"
#include "../Event/Button.h"
#include <iostream>

GameObject* Logo = nullptr;

void level::Menu::Init() {
    Logo = new GameObject();
    Logo->AddComponent<SpriteComp>();
    Logo->AddComponent<TransformComp>();
    TransformComp* transLogo = Logo->GetComponent<TransformComp>();
    transLogo->SetScale({ 800,300 });
    transLogo->SetPos({ 0, 200 });
    SpriteComp* LogoSprite = Logo->GetComponent<SpriteComp>();
    LogoSprite->SetTexture("Assets/arrow.png");
    LogoSprite->SetColor(255, 255, 255);

    Button* startButton = new Button("Assets/arrow.png", { 0, -100 }, { 500, 100 });
    ButtonManager::GetInstance().RegisterButton(startButton);


    Button* quitButton = new Button("Assets/arrow.png", { 0, -300 }, { 500, 100 });
    ButtonManager::GetInstance().RegisterButton(quitButton);
}

void level::Menu::Update() {

 
}

void level::Menu::Exit() {

}
