#include "Particle.h"

Particle::Particle(float _size, float _duration, int _count, SpriteComp::Color _color, ParticleType _type) :
					size(_size), duration(_duration), count(_count), color(_color), type(_type)
{
	
}

void Particle::PlayParticle(float x, float y)
{
	TransformComp* t;
	SpriteComp* s;
	RigidbodyComp* r;
	LifetimeComp* l;

	GameObject* obj;

	for (int i = 0; i < count; i++)
	{
		obj = new GameObject;

		t = obj->AddComponent<TransformComp>();
		s = obj->AddComponent<SpriteComp>();
		r = obj->AddComponent<RigidbodyComp>();
		l = obj->AddComponent<LifetimeComp>();

		s->SetColor(color.r, color.g, color.b);
		s->SetAlpha(0.3f);

		switch (type)
		{
		case Explosion:
			t->SetPos({ x, y });
			t->SetScale({ size, size });

			r->AddVelocity({ AERandFloat() * 100.f - 50.f, 200.f + AERandFloat() * 100.f });
			r->useGravity = true;

			break;
		}

		l->SetLifetime(duration);
	}
}

