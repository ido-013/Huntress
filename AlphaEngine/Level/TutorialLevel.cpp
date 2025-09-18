#include "TutorialLevel.h"
#include "AEEngine.h"
#include "NormalLevel.h"
#include "../Components.h"
#include "../GSM/GameStateManager.h"
#include "../Camera/Camera.h"

void level::TutorialLevel::Init()
{
	TransformComp* t = nullptr;
	SpriteComp* s = nullptr;

	img = new GameObject;
	t = img->AddComponent<TransformComp>();
	s = img->AddComponent<SpriteComp>();

	t->SetScale({ 1600, 900 });
	t->SetPos({ 0, -800 });
}

void level::TutorialLevel::Update()
{
	if (AEInputCheckTriggered(AEVK_SPACE))
	{
		ind++;
	}

	if (ind == 8)
	{
		GSM::GameStateManager::GetInstance().ChangeLevel(new NormalLevel(1));
	}
	else
	{
		img->GetComponent<SpriteComp>()->SetTexture("./Assets/UI/howtoplay-ui/" + std::to_string(ind) + ".png");
	}
}

void level::TutorialLevel::Exit()
{

}
