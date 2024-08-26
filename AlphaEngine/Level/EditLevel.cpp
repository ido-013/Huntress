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
#include "../ResourceManager/ResourceManager.h"
#include <iostream>
#include <string>

GameObject* background = nullptr;
GameObject* temp = nullptr;

void level::EditLevel::Init()
{
	background = new GameObject();
	
	background->AddComponent<AudioComp>();
	background->AddComponent<TransformComp>();
	background->AddComponent<SpriteComp>();
	background->GetComponent<AudioComp>()->SetAudio("../Assets/Audio/BGM.mp3");
	background->GetComponent<AudioComp>()->playAudio(-1, "../Assets/Audio/BGM.mp3");


	background->GetComponent<TransformComp>()->SetScale({ 1600, 900 });
	background->GetComponent<TransformComp>()->SetPos({ 0, 0 });
	background->GetComponent<SpriteComp>()->SetTexture("../Assets/Background/Background.png");

	temp = new GameObject();

	temp->AddComponent<TransformComp>();
	temp->AddComponent<PlayerComp>();
	temp->AddComponent<RigidbodyComp>();
	temp->AddComponent<SpriteComp>();

	temp->GetComponent<TransformComp>()->SetScale({ 90, 120 });
	temp->GetComponent<TransformComp>()->SetPos({ 0, 0 });

	temp->GetComponent<SpriteComp>()->SetTexture("../Assets/Character/ArrowAttack/sprite/ScoutAttackArrow1.png");

	/*AnimatorComp* tan = temp->GetComponent<AnimatorComp>();
	tan->AddAnimation("abc");
	tan->UpdateAnimation(0.5f, "Assets/PlanetTexture.png", "abc");
	tan->UpdateAnimation(0.5f, "Assets/Flag.png", "abc");
	tan->SetAnimation(1, 1, "abc");*/

	Prefab::SavePrefab("test", temp);
}

void level::EditLevel::Update()
{

}

void level::EditLevel::Exit()
{

}
