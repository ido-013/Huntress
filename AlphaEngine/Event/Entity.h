#pragma once
#include "Event.h"

class Entity
{
public:
	enum Type
	{
		None,
		Wall,
		Player,
		Button
	};

	virtual void OnEvent(Event* event) = 0;
	void SetType(const Type& _type);
	const Type GetType() const;

private:
	Type type;
};