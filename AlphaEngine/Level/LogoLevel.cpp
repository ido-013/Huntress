#include "LogoLevel.h"
#include "AEEngine.h"
#include "Menu.h"
#include "../Components.h"
#include "../GSM/GameStateManager.h"

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
	float dt = AEFrameRateControllerGetFrameTime();

	timer += dt;

	if (timer < 3.f)
	{
		digipenLogo->GetComponent<SpriteComp>()->SetAlpha(timer / 3.f);
	}

	else if (timer < 5.f)
	{
		digipenLogo->GetComponent<SpriteComp>()->SetAlpha(1 - (timer - 3.f) / 2.f);
	}

	else if (timer < 8.f)
	{
		teamLogo->GetComponent<SpriteComp>()->SetAlpha((timer - 5.f) / 3.f);
	}

	else if (timer < 10.f)
	{
		teamLogo->GetComponent<SpriteComp>()->SetAlpha(1 - (timer - 8.f) / 2.f);
	}

	else
	{
		GSM::GameStateManager::GetInstance().ChangeLevel(new Menu);
	}
}

void level::LogoLevel::Exit() 
{
	
}
