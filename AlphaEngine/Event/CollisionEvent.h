#pragma once
#include "Event.h"

struct CollisionEvent : public Event
{
	bool isSlope;

	CollisionEvent(Entity* _src, Entity* _dst, bool _isSlope = false) : Event(_src, _dst), isSlope(_isSlope) {}
};