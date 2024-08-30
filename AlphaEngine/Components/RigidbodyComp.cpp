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

void RigidbodyComp::CorrectPosByAABB(ColliderComp* oc, ColliderComp* c, float& x, float& y)
{
	float dis[4];
	dis[0] = abs(oc->GetPos().x + oc->GetScale().x / 2 - c->GetPos().x);
	dis[1] = abs(oc->GetPos().x - oc->GetScale().x / 2 - c->GetPos().x);
	dis[2] = abs(oc->GetPos().y + oc->GetScale().y / 2 - c->GetPos().y);
	dis[3] = abs(oc->GetPos().y - oc->GetScale().y / 2 - c->GetPos().y);

	float minDis = dis[0];
	int minInd = 0;

	for (int i = 1; i < 4; i++)
	{
		if (dis[i] < minDis)
		{
			minDis = dis[i];
			minInd = i;
		}
	}

	switch (minInd)
	{
	case 0:
		x = oc->GetPos().x + oc->GetScale().x / 2 + c->GetScale().x / 2;
		break;
	case 1:
		x = oc->GetPos().x - oc->GetScale().x / 2 - c->GetScale().x / 2;
		break;
	case 2:
		y = oc->GetPos().y + oc->GetScale().y / 2 + c->GetScale().y / 2;
		break;
	case 3:
		y = oc->GetPos().y - oc->GetScale().y / 2 - c->GetScale().y / 2;
		break;
	}

	if (abs(x - (oc->GetPos().x - oc->GetScale().x / 2 - c->GetScale().x / 2)) < 0.1f && abs(y - (oc->GetPos().y + oc->GetScale().y / 2 + c->GetScale().y / 2)) < 0.1f)
	{
		x += -1;
	}
		
	if (abs(x - (oc->GetPos().x + oc->GetScale().x / 2 + c->GetScale().x / 2)) < 0.1f && abs(y - (oc->GetPos().y + oc->GetScale().y / 2 + c->GetScale().y / 2)) < 0.1f)
	{
		x += 1;
	}
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
}

RigidbodyComp::~RigidbodyComp()
{

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

	if (useGravity)
		acceleration.y = -500.f;
	else
		acceleration.y = 0.f;

	//
	// lerp 함수로 대체하기
	if (t->GetRot() < targetRot)
	{
		t->SetRot(t->GetRot() + dt * 10);
	}

	if (t->GetRot() > targetRot)
	{
		t->SetRot(t->GetRot() - dt * 10);
	}

	if (abs(t->GetRot() - targetRot) < 0.2f)
	{
		t->SetRot(targetRot);
	}

	velocity.x += acceleration.x * dt;
	velocity.y += acceleration.y * dt;

	velocity.x = AEClamp(velocity.x, -maxVelocity.x, maxVelocity.x);
	velocity.y = AEClamp(velocity.y, -maxVelocity.y, maxVelocity.y);
	
	/*if (velocity.x == 0)
	{
		if (AERadToDeg(targetRot) > 40)
			velocity.x = -10;

		if (AERadToDeg(targetRot) < -40)
			velocity.x = 10;
	}*/

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

			GameObject::Type type = oc->GetOwner()->type;

			if (type == GameObject::Square && !c->colliderType[GameObject::LeftTri] && !c->colliderType[GameObject::RightTri])
			{
				CorrectPosByAABB(oc, c, x, y);
				//t->SetRot(AEDegToRad(0));
				targetRot = AEDegToRad(0);
			}

			else if (type == GameObject::RightTri)
			{
				if (c->colliderType[GameObject::Square] && c->GetPos().x > oc->GetPos().x)
				{
					CorrectPosByAABB(oc, c, x, y);
					//t->SetRot(AEDegToRad(0));
					targetRot = AEDegToRad(0);
				}
				else
				{
					y = oc->GetPos().y + (c->GetPos().x - oc->GetPos().x) * (oc->GetScale().y / oc->GetScale().x) + c->GetScale().y / 2;
					//t->SetRot(AEATan(oc->GetScale().y / oc->GetScale().x));
					targetRot = AEATan(oc->GetScale().y / oc->GetScale().x);
				}
				//t->SetRot(AEDegToRad(45));
				//y = oc->GetPos().y + (c->GetPos().x - oc->GetPos().x) * (oc->GetScale().y / oc->GetScale().x) + c->GetScale().y / 2;
			}
		
			else if (type == GameObject::LeftTri)
			{
				if (c->colliderType[GameObject::Square] && c->GetPos().x < oc->GetPos().x)
				{
					CorrectPosByAABB(oc, c, x, y);
					//t->SetRot(AEDegToRad(0));
					targetRot = AEDegToRad(0);
				}
				else
				{
					y = oc->GetPos().y + (c->GetPos().x - oc->GetPos().x) * (-oc->GetScale().y / oc->GetScale().x) + c->GetScale().y / 2;
					//t->SetRot(AEATan(-oc->GetScale().y / oc->GetScale().x));
					targetRot = AEATan(-oc->GetScale().y / oc->GetScale().x);
				}
				//t->SetRot(AEDegToRad(-45));
				//x = c->GetPos().x + velocity.x * AECos(AEDegToRad(-45)) * dt + c->GetScale().x / 2;
				//x = oc->GetPos().x + (c->GetPos().y - oc->GetPos().y) * (-oc->GetScale().x / oc->GetScale().y) + c->GetScale().x / 2;
				//y = oc->GetPos().y + (c->GetPos().x - oc->GetPos().x) * (-oc->GetScale().y / oc->GetScale().x) + c->GetScale().y / 2;
				//y = c->GetPos().y + velocity.x * AESin(AEDegToRad(-45)) * dt + c->GetScale().y / 2;
				//if (velocity.x >= 0)
				//{
				//	y = t->GetPos().y + velocity.x * AESin(AEDegToRad(-45)) * dt + c->GetScale().y / 2;
				//	/*if (y < oc->GetPos().y + (c->GetPos().x - oc->GetPos().x) * (-oc->GetScale().y / oc->GetScale().x) + c->GetScale().y / 2)
				//		y = oc->GetPos().y + (c->GetPos().x - oc->GetPos().x) * (-oc->GetScale().y / oc->GetScale().x) + c->GetScale().y / 2;*/
				//}
				//	
				//else
				//	y = oc->GetPos().y + (c->GetPos().x - oc->GetPos().x) * (-oc->GetScale().y / oc->GetScale().x) + c->GetScale().y / 2;
			}
		}

		for (int i = 0; i < 10; i++)
		{
			c->colliderType[i] = false;
		}

		c->SetPos({ x, y });
	}

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
