#include "Background.h"
#include "../Components.h"
#include "../Prefab/Prefab.h"
#include "../GameObjectManager/GameObjectManager.h"

GameObject* background = nullptr;

void InitBackground()
{
	/*Prefab b("Background");
	background = b.NewGameObject();*/

	background = GameObjectManager::GetInstance().GetObj("background");
	background->GetComponent<AudioComp>()->playAudio(-1, "./Assets/Audio/BGM.mp3");
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