#include "Weather.h"
#include "../Components.h"

void Weather::ChangeWeather(AEVec2 _minPos, AEVec2 _maxPos, AEVec2 _scale, float _r, float _g, float _b, float _a, float _maxTimer)
{
	minPos = _minPos;
	maxPos = _maxPos;
	scale = _scale;
	r = _r;
	g = _g;
	b = _b;
	a = _a;
	index = 0;
	preWindVec = { 0, -150 };
	maxTimer = _maxTimer;
}

void Weather::Update()
{
	TransformComp* t = nullptr;
	SpriteComp* s = nullptr;
	RigidbodyComp* rb = nullptr;

	static float timer = 0;
	timer += AEFrameRateControllerGetFrameTime();

	if (go[index] == nullptr)
	{
		go[index] = new GameObject;
		t = go[index]->AddComponent<TransformComp>();
		s = go[index]->AddComponent<SpriteComp>();
		rb = go[index]->AddComponent<RigidbodyComp>();

		t->SetScale({ scale.x, scale.y });
		t->SetPos({ minPos.x + (maxPos.x - minPos.x) * AERandFloat(), maxPos.y });

		s->SetColor(r, g, b);
		s->SetAlpha(a);	

		rb->AddAcceleration(preWindVec);
	}
	else
	{
		t = go[index]->GetComponent<TransformComp>();

		if (t->GetPos().y < minPos.y)
		{
			t->SetPos({ minPos.x + (maxPos.x - minPos.x) * AERandFloat(), maxPos.y });
		}
	}

	if (timer > maxTimer)
	{
		index++;
		index %= size;
		timer = 0;
	}
}

void Weather::ChangeWind(AEVec2 windVec)
{	
	RigidbodyComp* rb = nullptr;

	for (int i = 0; i < size; i++)
	{
		if (go[i] != nullptr)
		{
			rb = go[i]->GetComponent<RigidbodyComp>();
			rb->SetAcceleration(windVec);
			rb->SetVelocityX(0);
			preWindVec = windVec;
		}
	}
}

void Weather::ClearWeather()
{
	for (int i = 0; i < size; i++)
	{
		if (go[i] != nullptr)
		{
			go[i] = nullptr;
		}
	}
}
