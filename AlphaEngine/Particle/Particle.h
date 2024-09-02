#pragma once
#include "../GameObject/GameObject.h"
#include "../Components.h"
#include "../GameObjectManager/GameObjectManager.h"

class Particle
{
private:
	float size;
	float duration;
	int count;
	SpriteComp::Color color;

public:
	Particle(float _size, float _duration, int _count, SpriteComp::Color _color);
	
	void PlayParticle(float x, float y);
};