#include "CombatUI.h"
#include "../GameObject/GameObject.h"
#include "../Components/AudioComp.h"
#include "../Components/SpriteComp.h"
#include "../Components/TransformComp.h"
#include "../EventManager/EventManager.h"
#include <iostream>


GameObject* UIBAR = nullptr;
GameObject* Power = nullptr;
GameObject* Move = nullptr;
GameObject* Angle = nullptr;
GameObject* Wind = nullptr;
GameObject* Windwindow = nullptr;
void level::CombatUI::Init()
{
	UIBAR = new GameObject();
	UIBAR->AddComponent<SpriteComp>();
	UIBAR->AddComponent<AudioComp>();
	UIBAR->AddComponent<TransformComp>();
	TransformComp* transLogo = UIBAR->GetComponent<TransformComp>();
	transLogo->SetScale({ 1600,250 });
	transLogo->SetPos({ 0, -330 });
	SpriteComp* LogoSprite = UIBAR->GetComponent<SpriteComp>();
	LogoSprite->SetTexture("Assets/arrow.png");
	LogoSprite->SetColor(255, 255, 255);

	Power = new GameObject();
	Power->AddComponent<SpriteComp>();
	Power->AddComponent<AudioComp>();
	Power->AddComponent<TransformComp>();
	TransformComp* transStart = Power->GetComponent<TransformComp>();
	transStart->SetScale({ 750,80 });
	transStart->SetPos({ 150, -280 });
	SpriteComp* PowerSprite = Power->GetComponent<SpriteComp>();
	PowerSprite->SetTexture("Assets/arrow.png");
	PowerSprite->SetColor(255, 0, 0);

	Move = new GameObject();
	Move->AddComponent<SpriteComp>();
	Move->AddComponent<AudioComp>();
	Move->AddComponent<TransformComp>();
	TransformComp* transMove = Move->GetComponent<TransformComp>();
	transMove->SetScale({ 750,80 });
	transMove->SetPos({ 150, -380 });
	SpriteComp* MoveSprite = Move->GetComponent<SpriteComp>();
	MoveSprite->SetTexture("Assets/arrow.png");
	MoveSprite->SetColor(0, 255, 0);


	Angle = new GameObject();
	Angle->AddComponent<SpriteComp>();
	Angle->AddComponent<AudioComp>();
	Angle->AddComponent<TransformComp>();
	TransformComp* transAngle = Angle->GetComponent<TransformComp>();
	transAngle->SetScale({ 200,200 });
	transAngle->SetPos({ -410, -330 });
	SpriteComp* AngleSprite = Angle->GetComponent<SpriteComp>();
	AngleSprite->SetTexture("Assets/arrow.png");
	AngleSprite->SetColor(120, 120, 120);

	Wind = new GameObject();
	Wind->AddComponent<SpriteComp>();
	Wind->AddComponent<AudioComp>();
	Wind->AddComponent<TransformComp>();
	TransformComp* transSetting = Wind->GetComponent<TransformComp>();
	transSetting->SetScale({ 200,100 });
	transSetting->SetPos({ -700, 400 });
	SpriteComp* WindSprite = Wind->GetComponent<SpriteComp>();
	WindSprite->SetTexture("Assets/arrow.png");
	WindSprite->SetColor(120, 120, 120);
	 
}
void level::CombatUI::Update()
{

}
void level::CombatUI::Exit()
{

}