// Author : sinu

//include
#include "Combat.h"
#include "../Components/TransformComp.h"
#include "../Components/RigidbodyComp.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Components/SpriteComp.h"
#include "../Components/PlayerComp.h"
#include "../Combat/Projectile.h"
#include <cmath>
#include "AEInput.h"
#include "AEMath.h"

bool CombatComp::isDrawDirection = false;
bool CombatComp::isChaseDirection = false;
bool CombatComp::isReadyLaunch = false;

GameObject* projectile = new GameObject("projectile");

CombatComp::CombatComp(GameObject* _owner) : EngineComponent(_owner), pAngle(0), eAngle(0), pVelocity(0), eVelocity(0)
{
	
}

CombatComp::~CombatComp()
{
}

// 두 점을 사용하여 벡터를 계산하는 함수
AEVec2 VectorFromPoints(const AEVec2& P1, const AEVec2& P2) {
	return { P2.x - P1.x, P2.y - P1.y };
}

// 기울기를 계산하는 함수
float GetSlope(const AEVec2& P1, const AEVec2& P2) { // defualt x axis
	return P2.y - P1.y / P2.x - P1.x;
}

// 두 점을 잇는 선분이 ?축과 이루는 각도를 구하는 함수
// P1 : 첫번째 점, P2 : 두번째 점, axis : 축 (0 <<< x축, 1 <<< y축)
float GetCacluateSlopeAngle(const AEVec2& P1, const AEVec2& P2, const int axis = 0)
{
	float theta = 0;
	// 1. 두 점을 잇는 벡터 계산
	AEVec2 V = VectorFromPoints(P1, P2);
	// 2. 벡터와 ?축 사이의 각도 계산
	theta = atanf(axis == 0 ? GetSlope(P1, P2) : GetSlope(P2, P1));
	// 3. 각도의 범위 조정 (라디안에서 디그리로) << 지금 필요 없음
	//RadianToDegree(theta);
	
	return theta;
}

// 한 점을 중심으로 다른 점을 회전시키는 기능을 수행하는 함수
AEVec2 RotatePointAround(const AEVec2& P, const AEVec2& Q, float theta)
{
	// 1. 벡터 이동
	AEVec2 Res = { Q.x - P.x, Q.y - P.y };
	// 2. 회전 변환
	Res = { (cosf(theta) * Res.x) + (-sinf(theta) * Res.y),
			(sinf(theta) * Res.x) + (cosf(theta) * Res.y) };
	// 3. 벡터 복원
	Res = { Res.x + P.x , Res.y + P.y };

	return Res;
}

// 두 벡터 사이의 각도를 계산하는 함수
float AngleBetweenVectors(const AEVec2& v1, const AEVec2& v2) {
	// 내적 계산
	float dot_product = v1.x * v2.x + v1.y * v2.y;

	// 벡터 크기 계산
	float norm_v1 = std::sqrt(v1.x * v1.x + v1.y * v1.y);
	float norm_v2 = std::sqrt(v2.x * v2.x + v2.y * v2.y);

	// 코사인 세타 계산
	float cos_theta = dot_product / (norm_v1 * norm_v2);

	// 각도(라디안 단위) 계산
	float angle = AEACos(cos_theta);
	// 각도를 도(degree) 단위로 변환 << 필요 x
	//RadianToDegree(angle);

	return angle;
}

// 두 선분 사이의 각도를 계산하는 함수
float AngleBetweenSegments(const AEVec2& p1, const AEVec2& p2, const AEVec2& p3, const AEVec2& p4) {
	// 선분 1과 선분 2의 벡터 계산
	AEVec2 v1 = VectorFromPoints(p1, p2);
	AEVec2 v2 = VectorFromPoints(p3, p4);
	
	// 두 벡터 사이의 각도 계산
	return v2.x < 0 ? AngleBetweenVectors(v1, v2) : -AngleBetweenVectors(v1, v2);
}

// 각도를 -180에서 180도 사이로 정규화
float NormalizedAngle(float angle) {
	angle = fmodf(angle + 180, 360);
	if (angle < 0) {
		angle += 360;
	}

	return angle - 180;
}

// dealer => 0(player) , 1(enemy)
void CombatComp::DrawDirectionPegline(GameObject& directionArrow,
	int dealer, const AEVec2& DirectionPoint, 
	const std::pair<float, float> AngleRange)
{
	GameObject* player = dealer == 0 ? GameObjectManager::GetInstance().GetObj("player") : GameObjectManager::GetInstance().GetObj("enemy");
	// Variable Simplification
	TransformComp* dtf = directionArrow.GetComponent<TransformComp>();
	TransformComp* ptf = player->GetComponent<TransformComp>();

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
		// 가까운 쪽의 각도 계산
		float distance_to_first = std::abs(angle - ag1);
		float distance_to_second = std::abs(angle - ag2);

		if (distance_to_first < distance_to_second) {
			angle = ag1; // first도에 더 가까운 경우
		}
		else {
			angle = ag2; // second도에 더 가까운 경우
		}
	}
	dealer == 0 ? SetPlayerAngle(angle + (float)AEDegToRad(90)) : SetEnemyAngle(angle + (float)AEDegToRad(90));
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

// dealer => 0(player) , 1(enemy)
void CombatComp::FireAnArrow(int dealer, GameObject& directionArrow)
{
	GameObject* player = dealer == 0 ?
		GameObjectManager::GetInstance().GetObj("player") :
		GameObjectManager::GetInstance().GetObj("enemy");
	projectile->AddComponent<TransformComp>();
	projectile->AddComponent<RigidbodyComp>();
	projectile->AddComponent<SpriteComp>();
	projectile->AddComponent<Projectile>();

	projectile->GetComponent<TransformComp>()->SetPos(player->GetComponent<TransformComp>()->GetPos());
	projectile->GetComponent<TransformComp>()->SetScale({ 28, 10 });

	projectile->GetComponent<SpriteComp>()->SetTexture("Assets/Character/ArrowAttack/Arrow/Arrow.png");
	projectile->GetComponent<SpriteComp>()->SetAlpha(1);
	pVelocity = 19;
	projectile->GetComponent<Projectile>()->SetVelocity(dealer == 0 ? pVelocity : eVelocity);
	projectile->GetComponent<Projectile>()->SetTheta(dealer == 0 ? pAngle : eAngle);
	projectile->GetComponent<Projectile>()->SetProjectileObject(*projectile);
	projectile->GetComponent<Projectile>()->CalculateProjectileMotion();
	projectile->GetComponent<Projectile>()->isLaunchProjectile = true;
	isReadyLaunch = false;

	if (dealer == 0)
	{
		player->GetComponent<PlayerComp>()->turn = false;
	}
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

void CombatComp::SetEnemyAngle(float angle)
{
	eAngle = angle;
}

float CombatComp::GetEnemyAngle()
{
	return eAngle;
}

void CombatComp::SetPlayerVelocity(float velocity)
{
	pVelocity = velocity;
}

float CombatComp::GetPlayerVelocity()
{
	return pVelocity;
}

void CombatComp::SetEnemyVelocity(float velocity)
{
	eVelocity = velocity;
}

float CombatComp::GetEnemyVelocity()
{
	return eVelocity;
}

void CombatComp::Update()
{
	if (isDrawDirection)
	{
		if (AEInputCheckTriggered(AEVK_LBUTTON))
		{
			isChaseDirection = false;
			isReadyLaunch = true;
		}
		GameObject* directionArrow = GameObjectManager::GetInstance().GetObj("directionArrow");
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
					0,
					{ (float)px, (float)-py },
					{ -60.f, 60.f });
		}
	}
	else
	{
		GameObject* directionArrow = GameObjectManager::GetInstance().GetObj("directionArrow");
		directionArrow->GetComponent<SpriteComp>()->SetAlpha(0);
	}

	if (AEInputCheckTriggered(AEVK_RBUTTON))
	{
		if (isReadyLaunch)
		{
			GameObject* player = GameObjectManager::GetInstance().GetObj("player");
			GameObject* directionArrow = GameObjectManager::GetInstance().GetObj("directionArrow");
			FireAnArrow(0, *directionArrow);
			isReadyLaunch = false;
		}
	}
}

void CombatComp::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");

	if (compData != data.end())
	{
	}
}

json CombatComp::SaveToJson()
{
	json data;
	data["type"] = TypeName;

	json compData;
	data["compData"] = compData;

	return data;
}

BaseRTTI* CombatComp::CreateCombatComponent(GameObject* owner)
{
	BaseRTTI* p = new CombatComp(owner);
	owner->AddComponent<CombatComp>(static_cast<CombatComp*>(p));
	return p;
}
