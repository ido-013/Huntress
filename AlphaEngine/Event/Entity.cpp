#include "Entity.h"

void Entity::SetType(const Type& _type)
{
	type = _type;
}

const Entity::Type Entity::GetType() const
{
	return type;
}
