#include "Menu.h"
#include "../GameObject/GameObject.h"
#include "../Components/AudioComp.h"
#include "../Components/SpriteComp.h"
#include "../Components/TransformComp.h"
#include "../EventManager/EventManager.h"
#include <iostream>
GameObject* Logo = nullptr;
GameObject* start = nullptr;
GameObject* Quit = nullptr;
GameObject* setting = nullptr;
void level::Menu::Init()
{
	Logo = new GameObject();
	Logo->AddComponent<SpriteComp>();
	Logo->AddComponent<AudioComp>();
	Logo->AddComponent<TransformComp>();
	TransformComp* transLogo = Logo->GetComponent<TransformComp>();
	transLogo->SetScale({ 800,300 });
	transLogo->SetPos({ 0, 200 });
	SpriteComp* LogoSprite = Logo->GetComponent<SpriteComp>();
	LogoSprite->SetTexture("Assets/arrow.png");
	LogoSprite->SetColor(255, 255, 255);

	start = new GameObject();
	start->AddComponent<SpriteComp>();
	start->AddComponent<AudioComp>();
	start->AddComponent<TransformComp>();
	TransformComp* transStart = start->GetComponent<TransformComp>();
	transStart->SetScale({500,100});
	transStart->SetPos({ 0, -100 });
	SpriteComp* startSprite = start->GetComponent<SpriteComp>();
	startSprite->SetTexture("Assets/arrow.png");
	startSprite->SetColor(255, 255, 255);

	Quit = new GameObject();
	Quit->AddComponent<SpriteComp>();
	Quit->AddComponent<AudioComp>();
	Quit->AddComponent<TransformComp>();
	TransformComp* transQuit = Quit->GetComponent<TransformComp>();
	transQuit->SetScale({ 500,100 });
	transQuit->SetPos({ 0, -300 });
	SpriteComp* QuitSprite = Quit->GetComponent<SpriteComp>();
	QuitSprite->SetTexture("Assets/arrow.png");
	QuitSprite->SetColor(255, 255, 255);

	setting = new GameObject();
	setting->AddComponent<SpriteComp>();
	setting->AddComponent<AudioComp>();
	setting->AddComponent<TransformComp>();
	TransformComp* transSetting = setting->GetComponent<TransformComp>();
	transSetting->SetScale({ 100,100 });
	transSetting->SetPos({ 700, 300 });
	SpriteComp* settingSprite = setting->GetComponent<SpriteComp>();
	settingSprite->SetTexture("Assets/arrow.png");
	settingSprite->SetColor(255, 255, 255);

}
void level::Menu::Update()
{
	//s32 mouseX, mouseY;
	//AEInputGetCursorPosition(&mouseX, &mouseY);
	//t->SetPos({ 800, -(float)mouseY + 450 });
}
void level::Menu::Exit()
{

}