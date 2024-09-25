#include "Background.h"
#include "../Components.h"
#include "../Prefab/Prefab.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../GSM/GameStateManager.h"
#include "../Level/CombatLevel.h"
#include "../Camera/Camera.h"

GameObject* background = nullptr;

void InitBackground()
{
	if (dynamic_cast<level::CombatLevel*>(GSM::GameStateManager::GetInstance().GetCurrentLevel()) != nullptr)
	{
		Prefab b("Background");
		background = b.NewGameObject("background");
	}
	else
	{
		background = GameObjectManager::GetInstance().GetObj("background");
	}

	background->GetComponent<AudioComp>()->playAudio(-1, "./Assets/Audio/BGM.mp3", 0.3f);
	background->GetComponent<TransformComp>()->affectedByZoom = false;

	Camera& c = Camera::GetInstance();
	background->GetComponent<TransformComp>()->SetPos({ (c.maxX + c.minX) / 2, (c.maxY + c.minY) / 2 });
}

void UpdateBackground()
{
	/*float camX, camY;
	Camera::GetInstance().GetPos(&camX, &camY);
	background->GetComponent<TransformComp>()->SetPos({ camX, camY });*/
}

void ExitBackground()
{

}