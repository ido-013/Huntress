#include "EditLevel.h"
#include "../GSM/GameStateManager.h"
#include "../ComponentManager/ComponentManager.h"
#include "../GameObject/GameObject.h"
#include "../Components/AudioComp.h"
#include "../Components/TransformComp.h"
#include "../Components/SpriteComp.h"
#include "../Components/PlayerComp.h"
#include "../Components/RigidbodyComp.h"
#include "../Components/AnimatorComp.h"
#include "../EventManager/EventManager.h"
#include "../Prefab/Prefab.h"
#include <iostream>

GameObject* temp = nullptr;

void level::EditLevel::Init()
{
	temp = new GameObject();

	temp->AddComponent<TransformComp>();
	temp->AddComponent<SpriteComp>();
	temp->AddComponent<AudioComp>();
	temp->AddComponent<PlayerComp>();
	temp->AddComponent<RigidbodyComp>();
	temp->AddComponent<AnimatorComp>();

	AudioComp* ta = temp->GetComponent<AudioComp>();
	ta->SetAudio("Assets/Audio/bouken.mp3");
	ta->SetAudio("Assets/Audio/ore.mp3");

	TransformComp* tt = temp->GetComponent<TransformComp>();
	tt->SetScale({ 100, 100 });
	tt->SetPos({ 0, 0 });

	SpriteComp* ts = temp->GetComponent<SpriteComp>();
	ts->SetTexture("Assets/arrow.png");
	ts->SetColor(255, 255, 255);

	AnimatorComp* tan = temp->GetComponent<AnimatorComp>();
	tan->AddAnimation("abc");
	tan->UpdateAnimation(0.5f, "Assets/PlanetTexture.png", "abc");
	tan->UpdateAnimation(0.5f, "Assets/Flag.png", "abc");
	tan->SetAnimation(1, 1, "abc");

	Prefab::SavePrefab("test", temp);
}

void level::EditLevel::Update()
{

}

void level::EditLevel::Exit()
{

}
