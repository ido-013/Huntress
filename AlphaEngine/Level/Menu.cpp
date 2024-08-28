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
	// Get the mouse position
	s32 mouseX, mouseY;
	AEInputGetCursorPosition(&mouseX, &mouseY);

	// Assuming the screen coordinates are centered, adjust as needed
	mouseY = -mouseY + 450;
	mouseX = mouseX - 800;
	// Check if the mouse is over the start button
	TransformComp* transStart = start->GetComponent<TransformComp>();
	SpriteComp* startSprite = start->GetComponent<SpriteComp>();

	AEVec2 startPos = transStart->GetPos();
	AEVec2 startScale = transStart->GetScale();

	if (mouseX > startPos.x - startScale.x / 2 && mouseX < startPos.x + startScale.x / 2 &&
		mouseY > startPos.y - startScale.y / 2 && mouseY < startPos.y + startScale.y / 2) {
		// Mouse is over the start button
		startSprite->SetColor(200, 0, 0);  // Change color on hover
		std::cout << "Start" << std::endl;
		if (AEInputCheckCurr(AEVK_LBUTTON)) {
			// Trigger start event (e.g., change game state)
			//StartGame();
			std::cout << "Started" << std::endl;
		}
	}
	else {
		// Revert to original color
		startSprite->SetColor(255, 255, 255);
	}

	// Check if the mouse is over the quit button
	TransformComp* transQuit = Quit->GetComponent<TransformComp>();
	SpriteComp* quitSprite = Quit->GetComponent<SpriteComp>();

	AEVec2 quitPos = transQuit->GetPos();
	AEVec2 quitScale = transQuit->GetScale();

	if (mouseX > quitPos.x - quitScale.x / 2 && mouseX < quitPos.x + quitScale.x / 2 &&
		mouseY > quitPos.y - quitScale.y / 2 && mouseY < quitPos.y + quitScale.y / 2) {
		// Mouse is over the quit button
		quitSprite->SetColor(200, 0, 200);  // Change color on hover
		std::cout << "Quit" << std::endl;
		if (AEInputCheckCurr(AEVK_LBUTTON)) {
			// Trigger quit event (e.g., exit the game)
			//QuitGame();
			std::cout << "Quited" << std::endl;
		}
	}
	else {
		// Revert to original color
		quitSprite->SetColor(255, 255, 255);
	}
}
void level::Menu::Exit()
{

}