#include "Particle.h"

Particle::Particle(float _size, float _duration, int _count, SpriteComp::Color _color) :
					size(_size), duration(_duration), count(_count), color(_color)
{
	
}

void Particle::MakeGameObject(AEVec2 pos, AEVec2 vel)
{

	GameObject* obj = new GameObject;
	TransformComp*	t = obj->AddComponent<TransformComp>();
	SpriteComp*		s = obj->AddComponent<SpriteComp>();
	RigidbodyComp*	r = obj->AddComponent<RigidbodyComp>();
	LifetimeComp*	l = obj->AddComponent<LifetimeComp>();

	s->SetColor(color.r, color.g, color.b);
	s->SetAlpha(0.3f);

	t->SetPos({ pos.x, pos.y });
	t->SetScale({ size, size });

	r->AddVelocity(vel);
	r->useGravity = true;

	l->SetLifetime(duration);
}

void Particle::Explosion(AEVec2 pos, AEVec2 minVel, AEVec2 maxVel)
{
	for (int i = 0; i < count; i++)
	{
		MakeGameObject(pos, { minVel.x + (maxVel.x - minVel.x) * AERandFloat(), 
							  minVel.y + (maxVel.y - minVel.y) * AERandFloat() });
		//MakeGameObject(pos, { AERandFloat() * 100.f - 50.f, 200.f + AERandFloat() * 100.f });
	}
}

void Particle::Flutter(AEVec2 pos, AEVec2 vel)
{
	for (int i = 0; i < count; i++)
	{
		MakeGameObject(pos, { vel });
	}
}
