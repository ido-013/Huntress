#include "TransformComp.h"
#include "../CollisionManager/CollisionManager.h"

void TransformComp::CalculateMatrix()
{
	//Create a translate matrix
	AEMtx33 translateMtx;
	AEMtx33Trans(&translateMtx, pos.x, pos.y);

	//Create a rotation matrix
	AEMtx33 rotationMtx;
	AEMtx33Rot(&rotationMtx, rot);

	//Create a scale matrix
	AEMtx33 scaleMtx;
	AEMtx33Scale(&scaleMtx, scale.x, scale.y);

	//Concatenate them
	AEMtx33Concat(&transformMatrix, &rotationMtx, &scaleMtx);
	AEMtx33Concat(&transformMatrix, &translateMtx, &transformMatrix);
}

TransformComp::TransformComp(GameObject* _owner) : EngineComponent(_owner), pos(), scale(), rot(0), transformMatrix()
{
	pos.x = 0;
	pos.y = 0;

	scale.x = 1;
	scale.y = 1;

	CalculateMatrix();

	CollisionManager::GetInstance().AddTrans(this);
}

TransformComp::~TransformComp()
{
	CollisionManager::GetInstance().DelTrans(this);
}

void TransformComp::Update()
{
	
}

void TransformComp::SetPos(const AEVec2& otherPos)
{
	this->pos = otherPos;

	CalculateMatrix();
}

void TransformComp::SetScale(const AEVec2& otherScale)
{
	this->scale = otherScale;

	CalculateMatrix();
}

void TransformComp::SetRot(const float& otherRot)
{
	this->rot = otherRot;

	CalculateMatrix();
}

void TransformComp::PrintMatrix()
{
	std::cout << "Printing Transform Comp. With this values: " << std::endl;
	std::cout << "Translate : " << pos.x << " " << pos.y << std::endl;
	std::cout << "Rotation : " << rot << std::endl;
	std::cout << "Scale : " << scale.x << " " << scale.y << std::endl;

	for (int i = 0; i < 3; i++)
	{
		std::cout << "|";
		for (int x = 0; x < 3; x++)
		{
			std::cout << " " << transformMatrix.m[i][x];
		}

		std::cout << " |";
		std::cout << std::endl;
	}
}

void TransformComp::LoadFromJson(const json& data)
{
	// Check how you saved, load from there
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		auto p = compData->find("position");
		pos.x = p->begin().value();
		pos.y = (p->begin() + 1).value();

		auto s = compData->find("scale");
		scale.x = s->begin().value();
		scale.y = (s->begin() + 1).value();

		auto r = compData->find("rotation");
		rot = r.value();
	}

	// Data is loaded

	// Utilize the data
	CalculateMatrix();
}

json TransformComp::SaveToJson()
{
	json data;

	data["type"] = TypeName;

	json compData;
	compData["position"] = { pos.x, pos.y };
	compData["scale"] = { scale.x, scale.y };
	compData["rotation"] = rot;

	data["compData"] = compData;
	return data;
}

BaseRTTI* TransformComp::CreateTransformComponent(GameObject* owner)
{
	BaseRTTI* p = new TransformComp(owner);

	owner->AddComponent<TransformComp>(static_cast<BaseComponent*>(p));

	return p;
}

