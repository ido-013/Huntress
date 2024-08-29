#include "RigidbodyComp.h"
#include "AEEngine.h"
#include "TransformComp.h"
#include "../Utils/Direction.h"

bool RigidbodyComp::CheckEpsilon(float v, float EP)
{
	if (v < -EP || v > EP) 
		return true;

	return false;
}

RigidbodyComp::RigidbodyComp(GameObject* _owner) : EngineComponent(_owner), velocity(), maxVelocity()
{
	velocity.x = 0;
	velocity.y = 0;
	maxVelocity.x = 500;
	maxVelocity.y = 500;	 

	acceleration.x = 0;
	acceleration.y = 0;
	maxAcceleration.x = 500;
	maxAcceleration.y = 500;

	/*
	for (int i = 0; i < 4; i++)
	{
		collisionPos[i] = new ColliderComp(_owner);
	}
	*/
}

RigidbodyComp::~RigidbodyComp()
{
	/*for (int i = 0; i < 4; i++)
		delete collisionPos[i];*/
}

void RigidbodyComp::AddVelocity(const AEVec2& other)
{
	velocity.x += other.x;
	velocity.y += other.y;
}

void RigidbodyComp::AddVelocity(float x, float y)
{
	velocity.x += x;
	velocity.y += y;
}

void RigidbodyComp::SetVelocity(const AEVec2& other)
{
	velocity.x = other.x;
	velocity.y = other.y;
}

void RigidbodyComp::SetVelocity(float x, float y)
{
	velocity.x = x;
	velocity.y = y;
}

void RigidbodyComp::SetVelocityX(float x)
{
	velocity.x = x;
}

void RigidbodyComp::SetVelocityY(float y)
{
	velocity.y = y;
}

void RigidbodyComp::ClearVelocity()
{
	velocity.x = 0;
	velocity.y = 0;
}

void RigidbodyComp::AddAcceleration(const AEVec2& other)
{
	if (acceleration.x * other.x < 0) acceleration.x = 0;
	if (acceleration.y * other.y < 0) acceleration.y = 0;

	acceleration.x += other.x;
	acceleration.y += other.y;

	acceleration.x = AEClamp(acceleration.x, -maxAcceleration.x, maxAcceleration.x);
	acceleration.y = AEClamp(acceleration.y, -maxAcceleration.y, maxAcceleration.y);
}

void RigidbodyComp::AddAcceleration(float x, float y)
{
	if (acceleration.x * x < 0) acceleration.x = 0;
	if (acceleration.y * y < 0) acceleration.y = 0;

	acceleration.x += x;
	acceleration.y += y;

	acceleration.x = AEClamp(acceleration.x, -maxAcceleration.x, maxAcceleration.x);
	acceleration.y = AEClamp(acceleration.y, -maxAcceleration.y, maxAcceleration.y);
}

void RigidbodyComp::SetAcceleration(const AEVec2& other)
{
	acceleration.x = other.x;
	acceleration.y = other.y;
}

void RigidbodyComp::SetAcceleration(float x, float y)
{
	acceleration.x = x;
	acceleration.y = y;
}

void RigidbodyComp::ClearAcceleration()
{
	acceleration.x = 0;
	acceleration.y = 0;
}

void RigidbodyComp::Update()
{
	float dt = AEFrameRateControllerGetFrameTime();

	//Get the transform
	TransformComp* t = owner->GetComponent<TransformComp>();
	if (t == nullptr)
	{
		return;
	}

	float tx = t->GetPos().x;
	float ty = t->GetPos().y;

	float tw = t->GetScale().x;
	float th = t->GetScale().y;

	/*collisionPos[UP]->	SetPos({ tx, ty + th - 1 });
	collisionPos[DOWN]->	SetPos({ tx, ty - th + 1 });
	collisionPos[RIGHT]->	SetPos({ tx + tw + 1, ty });
	collisionPos[LEFT]->	SetPos({ tx - tw - 1, ty });
	
	collisionPos[UP]->		SetScale({ tw, 1 });
	collisionPos[DOWN]->	SetScale({ tw, 1 });
	collisionPos[LEFT]->	SetScale({ 1, th });
	collisionPos[RIGHT]->	SetScale({ 1, th });*/

	//

	if (useGravity)
		acceleration.y = -500.f;
	else
		acceleration.y = 0.f;

	//

	velocity.x += acceleration.x * dt;
	velocity.y += acceleration.y * dt;

	velocity.x = AEClamp(velocity.x, -maxVelocity.x, maxVelocity.x);
	velocity.y = AEClamp(velocity.y, -maxVelocity.y, maxVelocity.y);

	//

	float x = t->GetPos().x + velocity.x * dt;
	float y = t->GetPos().y + velocity.y * dt;

	velocity.x /= drag;
	velocity.y /= drag;

	//If im too low, just set to 0
	if (CheckEpsilon(velocity.x) == false)
		velocity.x = 0;

	if (CheckEpsilon(velocity.y) == false)
		velocity.y = 0;

	ColliderComp* c = owner->GetComponent<ColliderComp>();
	
	if (c != nullptr)
	{
		while (!c->oppoCollider.empty())
		{
			ColliderComp* oc = c->oppoCollider.front();
			c->oppoCollider.pop();

			velocity.y = 0;
			
			switch (oc->GetOwner()->type)
			{
			case GameObject::Square:
				if ((oc->GetPos().y + oc->GetScale().y / 2) > (c->GetPos().y - c->GetScale().y / 2))
					y = oc->GetPos().y + oc->GetScale().y / 2 + c->GetScale().y / 2;
				break;

			case GameObject::RightTri:
				y = oc->GetPos().y + (c->GetPos().x - oc->GetPos().x) * (oc->GetScale().y / oc->GetScale().x) + c->GetScale().y / 2;
				break;

			case GameObject::LeftTri:
				y = oc->GetPos().y + (c->GetPos().x - oc->GetPos().x) * (-oc->GetScale().y / oc->GetScale().x) + c->GetScale().y / 2;
				break;
			}
		}

		c->SetPos({ x, y });
	}

	/*if (collisionPos[DOWN]->isCollision)
	{
		velocity.y = 0;

		GameObject::Type type = collisionPos[DOWN]->oppoCollider->GetOwner()->type;

		if (type == GameObject::Square)
		{
			float oy = collisionPos[DOWN]->oppoCollider->GetPos().y;
			float oh = collisionPos[DOWN]->oppoCollider->GetScale().y / 2;

			y = (t->GetScale().y / 2) + oh + oy;
		}
		
		else if (type == GameObject::RightTri)
		{
			x = t->GetPos().x + AECos(AEDegToRad(45)) * velocity.x * dt;
			y = t->GetPos().y + AECos(AEDegToRad(45)) * velocity.y * dt;
		}

		else if (type == GameObject::LeftTri)
		{
			x = t->GetPos().x + AECos(AEDegToRad(-45)) * velocity.x * dt;
			y = t->GetPos().y + AECos(AEDegToRad(-45)) * velocity.y * dt;
		}
	}

	if (collisionPos[RIGHT]->isCollision)
	{
		GameObject::Type type = collisionPos[RIGHT]->oppoCollider->GetOwner()->type;

		if (type == GameObject::LeftTri || type == GameObject::Square)
		{
			velocity.x = 0;

			float ox = collisionPos[RIGHT]->oppoCollider->GetPos().x;
			float ow = collisionPos[RIGHT]->oppoCollider->GetScale().x / 2;

			x = (t->GetScale().x / 2) - ow - ox;
		}

		else if (type == GameObject::RightTri)
		{
			x = t->GetPos().x + AECos(AEDegToRad(45)) * velocity.x * dt;
			y = t->GetPos().y + AECos(AEDegToRad(45)) * velocity.y * dt;
		}
	}

	if (collisionPos[LEFT]->isCollision)
	{
		GameObject::Type type = collisionPos[LEFT]->oppoCollider->GetOwner()->type;

		if (type == GameObject::RightTri || type == GameObject::Square)
		{
			velocity.x = 0;

			float ox = collisionPos[LEFT]->oppoCollider->GetPos().x;
			float ow = collisionPos[LEFT]->oppoCollider->GetScale().x / 2;

			x = (t->GetScale().x / 2) - ow - ox;
		}

		else if (type == GameObject::LeftTri)
		{
			x = t->GetPos().x + AECos(AEDegToRad(45)) * velocity.x * dt;
			y = t->GetPos().y + AECos(AEDegToRad(45)) * velocity.y * dt;
		}
	}*/

	t->SetPos({ x, y });
}

void RigidbodyComp::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		auto it = compData->find("velocity");
		velocity.x = it->begin().value();
		velocity.y = (it->begin() + 1).value();

		it = compData->find("maxVelocity");
		maxVelocity.x = it->begin().value();
		maxVelocity.y = (it->begin() + 1).value();

		it = compData->find("useGravity");
		useGravity = it.value();
	}
}

json RigidbodyComp::SaveToJson()
{
	json data;
	data["type"] = TypeName;

	json compData;
	compData["velocity"] = { velocity.x, velocity.y };
	compData["maxVelocity"] = { maxVelocity.x, maxVelocity.y };
	compData["useGravity"] = useGravity;
	data["compData"] = compData;

	return data;
}

BaseRTTI* RigidbodyComp::CreateRigidBodyComponent(GameObject* owner)
{
	BaseRTTI* p = new RigidbodyComp(owner);
	owner->AddComponent<RigidbodyComp>(static_cast<BaseComponent*>(p));
	return p;
}
