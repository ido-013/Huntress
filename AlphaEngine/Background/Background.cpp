#include "Background.h"
#include "../Components.h"
#include "../Prefab/Prefab.h"
#include "../GameObjectManager/GameObjectManager.h"

GameObject* background = nullptr;

void InitBackground()
{
	/*Prefab b("Background");
	background = b.NewGameObject("background");*/

	background = GameObjectManager::GetInstance().GetObj("background");
	background->GetComponent<AudioComp>()->playAudio(-1, "./Assets/Audio/BGM.mp3", 0.3f);
	background->GetComponent<TransformComp>()->affectedByZoom = false;
}

void UpdateBackground()
{
	float camX, camY;
	AEGfxGetCamPosition(&camX, &camY);
	background->GetComponent<TransformComp>()->SetPos({ camX, camY });
}

void ExitBackground()
{

}