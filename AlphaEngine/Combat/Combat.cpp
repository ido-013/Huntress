// Author : sinu

//include
#include "Combat.h"
#include "../Components/TransformComp.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Components/SpriteComp.h"
#include <cmath>
#include "AEInput.h"
#include "AEMath.h"

bool CombatComp::isDrawDirection = false;
bool CombatComp::isChaseDirection = false;

CombatComp::CombatComp(GameObject* _owner) : EngineComponent(_owner), pAngle(0)
{
	
}

CombatComp::~CombatComp()
{
}

// �� ���� ����Ͽ� ���͸� ����ϴ� �Լ�
AEVec2 VectorFromPoints(const AEVec2& P1, const AEVec2& P2) {
	return { P2.x - P1.x, P2.y - P1.y };
}

// ���⸦ ����ϴ� �Լ�
float GetSlope(const AEVec2& P1, const AEVec2& P2) { // defualt x axis
	return P2.y - P1.y / P2.x - P1.x;
}

// �� ���� �մ� ������ ?��� �̷�� ������ ���ϴ� �Լ�
// P1 : ù��° ��, P2 : �ι�° ��, axis : �� (0 <<< x��, 1 <<< y��)
float GetCacluateSlopeAngle(const AEVec2& P1, const AEVec2& P2, const int axis = 0)
{
	float theta = 0;
	// 1. �� ���� �մ� ���� ���
	AEVec2 V = VectorFromPoints(P1, P2);
	// 2. ���Ϳ� ?�� ������ ���� ���
	theta = atanf(axis == 0 ? GetSlope(P1, P2) : GetSlope(P2, P1));
	// 3. ������ ���� ���� (���ȿ��� ��׸���) << ���� �ʿ� ����
	//RadianToDegree(theta);
	
	return theta;
}

// �� ���� �߽����� �ٸ� ���� ȸ����Ű�� ����� �����ϴ� �Լ�
AEVec2 RotatePointAround(const AEVec2& P, const AEVec2& Q, float theta)
{
	// 1. ���� �̵�
	AEVec2 Res = { Q.x - P.x, Q.y - P.y };
	// 2. ȸ�� ��ȯ
	Res = { (cosf(theta) * Res.x) + (-sinf(theta) * Res.y),
			(sinf(theta) * Res.x) + (cosf(theta) * Res.y) };
	// 3. ���� ����
	Res = { Res.x + P.x , Res.y + P.y };

	return Res;
}

// �� ���� ������ ������ ����ϴ� �Լ�
float AngleBetweenVectors(const AEVec2& v1, const AEVec2& v2) {
	// ���� ���
	float dot_product = v1.x * v2.x + v1.y * v2.y;

	// ���� ũ�� ���
	float norm_v1 = std::sqrt(v1.x * v1.x + v1.y * v1.y);
	float norm_v2 = std::sqrt(v2.x * v2.x + v2.y * v2.y);

	// �ڻ��� ��Ÿ ���
	float cos_theta = dot_product / (norm_v1 * norm_v2);

	// ����(���� ����) ���
	float angle = AEACos(cos_theta);
	// ������ ��(degree) ������ ��ȯ << �ʿ� x
	//RadianToDegree(angle);

	return angle;
}

// �� ���� ������ ������ ����ϴ� �Լ�
float AngleBetweenSegments(const AEVec2& p1, const AEVec2& p2, const AEVec2& p3, const AEVec2& p4) {
	// ���� 1�� ���� 2�� ���� ���
	AEVec2 v1 = VectorFromPoints(p1, p2);
	AEVec2 v2 = VectorFromPoints(p3, p4);
	
	// �� ���� ������ ���� ���
	return v2.x < 0 ? AngleBetweenVectors(v1, v2) : -AngleBetweenVectors(v1, v2);
}

// ������ -180���� 180�� ���̷� ����ȭ
float NormalizedAngle(float angle) {
	angle = fmod(angle + 180, 360);
	if (angle < 0) {
		angle += 360;
	}

	return angle - 180;
}

void CombatComp::DrawDirectionPegline(GameObject& directionArrow,
	GameObject& player, const AEVec2& DirectionPoint, 
	const std::pair<float, float> AngleRange)
{
	// Variable Simplification
	TransformComp* dtf = directionArrow.GetComponent<TransformComp>();
	TransformComp* ptf = player.GetComponent<TransformComp>();

	// Step1. Default pos,rot setting
	dtf->SetPos({ ptf->GetPos().x , ptf->GetPos().y + dtf->GetScale().y / 2 });
	dtf->SetRot(0);

	// Step2. Calculate angle and setting limit to based on limit value
	float angle = AngleBetweenSegments(ptf->GetPos(), dtf->GetPos(), ptf->GetPos(), DirectionPoint);
	
	float ag1 = NormalizedAngle(AngleRange.first + (float)AERadToDeg(ptf->GetRot()));
	float ag2 = NormalizedAngle(AngleRange.second + (float)AERadToDeg(ptf->GetRot()));

	ag1 = (float)AEDegToRad(ag1);
	ag2 = (float)AEDegToRad(ag2);

	if (!(angle >= ag1 && angle <= ag2)) 
	{
		// ����� ���� ���� ���
		float distance_to_first = std::abs(angle - ag1);
		float distance_to_second = std::abs(angle - ag2);

		if (distance_to_first < distance_to_second) {
			angle = ag1; // first���� �� ����� ���
		}
		else {
			angle = ag2; // second���� �� ����� ���
		}
	}
	SetPlayerAngle(angle);
	// Step3. Based on the mouse position pos,rot setting

	dtf->SetPos(
		RotatePointAround(
			ptf->GetPos(),
			{ ptf->GetPos().x , ptf->GetPos().y + dtf->GetScale().y / 2 },
			angle
		)
	);
	dtf->SetRot(angle);
}

void CombatComp::SetPlayerAngle(float angle)
{
	pAngle = angle;
	std::cout << "Set Pangle : " << angle << std::endl;
}

float CombatComp::GetPlayerAngle()
{
	return pAngle;
}

void CombatComp::Update()
{
	if (isDrawDirection)
	{
		if (AEInputCheckTriggered(AEVK_LBUTTON))
		{
			isChaseDirection = false;
		}
		GameObject* directionArrow = GameObjectManager::GetInstance().GetObj("directionArrow");
		GameObject* player = GameObjectManager::GetInstance().GetObj("player");
		s32 px, py;
		AEInputGetCursorPosition(&px, &py);
		px -= 800;
		py -= 450;
		directionArrow->GetComponent<SpriteComp>()->SetAlpha(1);
		if (isChaseDirection)
		{
			directionArrow->
				GetComponent<CombatComp>()->
				DrawDirectionPegline(*directionArrow,
					*player,
					{ (float)px, (float)-py },
					{ -120.f, 120.f });
		}
	}
	else
	{
		GameObject* directionArrow = GameObjectManager::GetInstance().GetObj("directionArrow");
		directionArrow->GetComponent<SpriteComp>()->SetAlpha(0);
	}
}

void CombatComp::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		/*auto it = compData->find("color");
		color.r = it->begin().value();
		color.g = (it->begin() + 1).value();
		color.b = (it->begin() + 2).value();*/
	}
}

json CombatComp::SaveToJson()
{
	json data;
	data["type"] = TypeName;

	json compData;
	/*compData["color"] = { color.r, color.g, color.b };
	compData["textureName"] = textureName;*/
	data["compData"] = compData;

	return data;
}

BaseRTTI* CombatComp::CreateCombatComponent(GameObject* owner)
{
	BaseRTTI* p = new CombatComp(owner);
	owner->AddComponent<CombatComp>(static_cast<CombatComp*>(p));
	return p;
}
