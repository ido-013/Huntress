#pragma once
#include "../GameObject/GameObject.h"
#include "../Components.h"
#include "../GameObjectManager/GameObjectManager.h"

class Particle
{
public:
	enum ParticleType
	{
		Explosion,
		Flutter
	};

private:
	float size;
	float duration;
	int count;
	SpriteComp::Color color;
	ParticleType type;

public:
	Particle(float _size, float _duration, int _count, SpriteComp::Color _color, ParticleType _type);
	void PlayParticle(float x, float y);
};