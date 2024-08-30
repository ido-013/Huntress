#pragma once
#include "Event.h"

class Entity
{
public:
	virtual void OnEvent(Event* event) = 0;
	void SetType(const Type& _type);
	const Type GetType() const;

private:
	Type type;
};