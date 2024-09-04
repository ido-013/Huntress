#include "Background.h"
#include "../Components.h"

GameObject* background = nullptr;

void InitBackground()
{
	// background
	background = new GameObject("background");

	background->AddComponent<AudioComp>();
	background->AddComponent<TransformComp>();
	background->AddComponent<SpriteComp>();
	background->GetComponent<AudioComp>()->SetAudio("../Assets/Audio/BGM.mp3");
	background->GetComponent<AudioComp>()->playAudio(-1, "../Assets/Audio/BGM.mp3");

	background->GetComponent<TransformComp>()->SetScale({ 1600, 900 });
	background->GetComponent<TransformComp>()->SetPos({ 0, 0 });
	background->GetComponent<SpriteComp>()->SetTexture("../Assets/Background/Background.png");
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