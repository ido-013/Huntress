#include "LogoLevel.h"
#include "AEEngine.h"
#include "Menu.h"
#include "../Components.h"
#include "../GSM/GameStateManager.h"
#include "../Camera/Camera.h"

void level::LogoLevel::Init() 
{
	TransformComp* t = nullptr;
	SpriteComp* s = nullptr;

	digipenLogo = new GameObject;
	t = digipenLogo->AddComponent<TransformComp>();
	s = digipenLogo->AddComponent<SpriteComp>();

	t->SetScale({ 1026, 249 });
	s->SetTexture("./Assets/DigiPen_RED.png");
	s->SetAlpha(0);

	teamLogo = new GameObject;
	t = teamLogo->AddComponent<TransformComp>();
	s = teamLogo->AddComponent<SpriteComp>();

	t->SetScale({ 500, 500 });
	s->SetTexture("./Assets/Team_Logo.png");
	s->SetAlpha(0);
}

void level::LogoLevel::Update() 
{
	f64 dt = AEFrameRateControllerGetFrameTime();

	timer += dt;

	if (AEInputCheckTriggered(AEVK_ESCAPE) || AEInputCheckTriggered(AEVK_SPACE) || AEInputCheckTriggered(AEVK_LBUTTON)) 
	{
		GSM::GameStateManager::GetInstance().ChangeLevel(new Menu);
	}

	else if (timer < 3.f)
	{
		digipenLogo->GetComponent<SpriteComp>()->SetAlpha((float)timer / 3.f);
	}

	else if (timer < 5.f)
	{
		digipenLogo->GetComponent<SpriteComp>()->SetAlpha(1 - ((float)timer - 3.f) / 2.f);
	}

	else if (timer < 8.f)
	{
		teamLogo->GetComponent<SpriteComp>()->SetAlpha(((float)timer - 5.f) / 3.f);
	}

	else if (timer < 10.f)
	{
		teamLogo->GetComponent<SpriteComp>()->SetAlpha(1 - ((float)timer - 8.f) / 2.f);
	}

	else
	{
		GSM::GameStateManager::GetInstance().ChangeLevel(new Menu);
	}
}

void level::LogoLevel::Exit() 
{
	
}
