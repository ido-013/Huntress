// Author : sinu

//include
#include "Combat.h"
#include "../Components/TransformComp.h"
#include "../Components/RigidbodyComp.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Components/SpriteComp.h"
#include "../Components/PlayerComp.h"
#include "../Components/EnemyComp.h"
#include "../Combat/Projectile.h"
#include <cmath>
#include "AEInput.h"
#include "AEMath.h"
#include "../Utils/Size.h"

CombatComp::TURN CombatComp::turn = NOBODYTURN;
CombatComp::STATE CombatComp::state = NONE;

bool CombatComp::isCombat = false;

bool CombatComp::isDrawDirection = false;
bool CombatComp::isChaseDirection = false;
bool CombatComp::isReadyLaunch = false;

bool CombatComp::isSetLaunchAngle = false;

int CombatComp::ArrowCount = 0;

void CombatComp::DataUpdate()
{
	data.angle = turn == PLAYERTURN ? pAngle : turn == ENEMYTURN ? eAngle : 0;
	data.power = turn == PLAYERTURN ? pPower : turn == ENEMYTURN ? ePower : 0;
	//data.randomValue = ;
}

CombatComp::CombatComp(GameObject* _owner) : EngineComponent(_owner),
pAngle(0), eAngle(RAD90), pVelocity(0), eVelocity(0), pPower(8), ePower(5), AICombatSystemApplyWind(true)
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

void CombatComp::DrawDirectionPegline(GameObject& directionArrow,
	TURN turn, const std::pair<float, float> AngleRange)
{
	GameObject* attacker = turn == PLAYERTURN ? 
		GameObjectManager::GetInstance().GetObj("player") : 
		GameObjectManager::GetInstance().GetObj("enemy");
	// Variable Simplification
	TransformComp* dtf = directionArrow.GetComponent<TransformComp>();
	TransformComp* atf = attacker->GetComponent<TransformComp>();

	// Step1. Default pos,rot setting
	dtf->SetPos({ atf->GetPos().x , atf->GetPos().y + dtf->GetScale().y / 2 });
	dtf->SetRot(0);
	
	// Step2. Calculate angle and setting limit to based on limit value
	float angle = 0;
	if (turn == PLAYERTURN)
	{
		s32 px, py;
		AEInputGetCursorPosition(&px, &py);
		angle = AngleBetweenSegments(atf->GetPos(), dtf->GetPos(), 
			atf->GetPos(), { (float)px - windowWidthHalf, (float)-(py - windowHeightHalf) });
	}
	else
	{
		angle = eAngle;
	}

	float ag1 = NormalizedAngle((float)AERadToDeg(AngleRange.first) + (float)AERadToDeg(atf->GetRot()));
	float ag2 = NormalizedAngle((float)AERadToDeg(AngleRange.second) + (float)AERadToDeg(atf->GetRot()));

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

	if (turn == PLAYERTURN)
	{
		SetPlayerAngle(angle + (float)AEDegToRad(90));
		dtf->SetRot(angle);
	}
	else if (turn == ENEMYTURN)
	{
		EnemyAICombatSystem(); // AISystem
		dtf->SetRot(eAngle - RAD90);
	}
}

void CombatComp::FireAnArrow(TURN turn, GameObject& directionArrow)
{
	GameObject* player = turn == PLAYERTURN ?
		GameObjectManager::GetInstance().GetObj("player") :
		GameObjectManager::GetInstance().GetObj("enemy");

	GameObject* projectile = new GameObject("projectile");
	projectile->type = GameObject::Projectile;

	projectile->AddComponent<TransformComp>();
	projectile->AddComponent<SpriteComp>();
	projectile->AddComponent<Projectile>();
	projectile->AddComponent<ColliderComp>();

	projectile->GetComponent<TransformComp>()->SetPos(player->GetComponent<TransformComp>()->GetPos());
	projectile->GetComponent<TransformComp>()->SetScale({ 28, 10 });

	projectile->GetComponent<SpriteComp>()->SetTexture("../Assets/Character/ArrowAttack/Arrow/Arrow.png");
	projectile->GetComponent<SpriteComp>()->SetAlpha(1);
	turn == PLAYERTURN ? pVelocity = DEFAULT_POWER + pPower : eVelocity = DEFAULT_POWER + ePower;
	projectile->GetComponent<Projectile>()->SetVelocity(turn == PLAYERTURN ? pVelocity : eVelocity);
	projectile->GetComponent<Projectile>()->SetTheta(turn == PLAYERTURN ? pAngle : eAngle);
	//std::cout << eVelocity << ", " <<  AERadToDeg(eAngle)<< std::endl;
	projectile->GetComponent<Projectile>()->SetProjectileObject(*projectile);
	projectile->GetComponent<Projectile>()->CalculateProjectileMotion();
	projectile->GetComponent<Projectile>()->isLaunchProjectile = true;

	projectile->GetComponent<ColliderComp>()->SetCollider();

	isReadyLaunch = false;
	CombatComp::ArrowCount++;
}

CombatComp::TURN CombatComp::TurnChange()
{
	if (!isCombat)
	{
		return NOBODYTURN;
	}
	return CombatComp::turn == PLAYERTURN ? ENEMYTURN : PLAYERTURN;
}

void CombatComp::checkState()
{
	GameObject* player = GameObjectManager::GetInstance().GetObj("player");
	GameObject* enemy = GameObjectManager::GetInstance().GetObj("enemy");
	if (isCombat && state == COMBAT)
	{
		if (enemy->GetComponent<EnemyComp>()->data.hp <= 0)
		{
			state = CLEAR;
			isCombat = false;
		}
		else if (player->GetComponent<PlayerComp>()->data.hp <= 0)
		{
			state = GAMEOVER;
			isCombat = false;
		}
	}
}

// Get&Set
void CombatComp::SetPlayerAngle(float angle)
{
	pAngle = angle;
	//std::cout << "Set Player Angle : " << AERadToDeg(angle) << std::endl;
}
float CombatComp::GetPlayerAngle()
{
	return pAngle;
}
void CombatComp::SetEnemyAngle(float angle)
{
	eAngle = angle;
	//std::cout << "Set Enemy Angle : " << AERadToDeg(angle) << std::endl;
}
float CombatComp::GetEnemyAngle()
{
	return eAngle;
}
void CombatComp::SetPlayerVelocity(float velocity)
{
	pVelocity = velocity;
	//std::cout << "Set Player Velocity : " << pVelocity << std::endl;
}
float CombatComp::GetPlayerVelocity()
{
	return pVelocity;
}
void CombatComp::SetEnemyVelocity(float velocity)
{
	eVelocity = velocity;
	//std::cout << "Set Enemy Velocity : " << eVelocity << std::endl;
}
float CombatComp::GetEnemyVelocity()
{
	return eVelocity;
}
void CombatComp::SetPlayerPower(float power)
{
	pPower = power;
}
float CombatComp::GetPlayerPower()
{
	return pPower;
}
void CombatComp::SetEnemyPower(float power)
{
	ePower = power;
}
float CombatComp::GetEnemyPower()
{
	return ePower;
}

void CombatComp::InitEnemyValue()
{
	eAngle = RAD90;
	eVelocity = DEFAULT_POWER;
	ePower = 0;
}

CombatComp::RESULT CombatComp::EnemyAICombatSystem()
{
	GameObject* player = GameObjectManager::GetInstance().GetObj("player");
	GameObject* enemy = GameObjectManager::GetInstance().GetObj("enemy");
	/*
	1. 해당 각도로 임의의 파워(파워는 1에서 10만큼 대입)만큼 가상의 포물선을 그림
	2. 플레이어가 자신(적)을 기준으로 x/-x인지 파악 후 (-)2도씩 검사
	3. 만약 해당되지 않으면 파워를 늘리고 파워를 최대까지 늘려봤으면 각도를 올림
	4. 끝까지해도 못찾으면 디폴트 값으로 날림 또는 날리지 않고 턴을 종료함
	*/
	AEVec2 p = player->GetComponent<TransformComp>()->GetPos();
	AEVec2 e = enemy->GetComponent<TransformComp>()->GetPos();

	ePower = 1.0f; // 초기 파워

	while (ePower <= POWER_LIMIT)
	{
		float t = 0.0f;
		AEVec2 ptf = e;

		eVelocity = ePower + DEFAULT_POWER;

		float initialVelocityX = eVelocity * std::cos(eAngle);
		float initialVelocityY = eVelocity * std::sin(eAngle);

		while (true)
		{
			// 현재 속도 계산 (속도에 공기 저항과 바람 적용)
			float velocityX = initialVelocityX + (AICombatSystemApplyWind ? Projectile::wind.x : 0);
			float velocityY = initialVelocityY + (AICombatSystemApplyWind ? Projectile::wind.y : 0);

			float airResistanceX = -AIR_RESISTANCE_COEFFICIENT
				* velocityX * std::abs(velocityX);// / mass;
			float airResistanceY = -AIR_RESISTANCE_COEFFICIENT
				* velocityY * std::abs(velocityY);// / mass;

			velocityX += airResistanceX * t;
			velocityY += airResistanceY * t - GRAVITY * t;

			float x = ptf.x + velocityX * t;
			float y = ptf.y + velocityY * t;

			ptf = { x, y };

			//std::cout << ptf.x << " , " << ptf.y << std::endl;

			t += static_cast<float>(AEFrameRateControllerGetFrameTime());

			// 플레이어와 포물선 위치가 가까운지 확인
			float loc = sqrt((ptf.x - p.x) * (ptf.x - p.x) + (ptf.y - p.y) * (ptf.y - p.y));
			if (loc <= HIT_RADIUS)
			{
				isSetLaunchAngle = true;
				//std::cout << "HIT" << std::endl;
				//std::cout << "ptf : " << ptf.x << " , " << ptf.y << "\np : " << p.x << " , " << p.y <<  std::endl;
				//std::cout << "ePower : " << ePower <<  std::endl;
				//std::cout << "eAngle : " << AERadToDeg(eAngle) <<  std::endl;
				//std::cout << "x : " << ptf.x - p.x << "y : " << ptf.y - p.y <<  std::endl;
				//std::cout << loc << std::endl;
				return HIT; // 적중
			}

			// 맵보다 더 낮게 떨어졌다면 포물선 궤적 벗어남
			if (ptf.y < -windowHeightHalf)
			{
				break;
			}
		}

		// 파워를 증가시킴
		ePower += POWER_INTERVER;
	}

	// 각도 설정
	eAngle += p.x < e.x ? ANGLE_INTERVER : -ANGLE_INTERVER;
	if (p.x < e.x ? eAngle > ANGLE_LIMIT + RAD90 : ANGLE_LIMIT - RAD90)
	{
		ePower = POWER_LIMIT / 2;
		eVelocity = ePower + DEFAULT_POWER;
		eAngle = p.x < e.x ? ANGLE_LIMIT / 2 + RAD90 : -(ANGLE_LIMIT / 2 + RAD90);
		isSetLaunchAngle = true;
		std::cout << "Projectile : NOTFOUND" << std::endl;
		enemy->GetComponent<EnemyComp>()->isMove = true;
		return NOTFOUND;
	}
	//std::cout << AERadToDeg(eAngle)<< std::endl;

	return MISS;
}

void CombatComp::Update()
{
	if (isCombat && state == COMBAT)
	{
		GameObject* directionArrow = GameObjectManager::GetInstance().GetObj("directionArrow");
		GameObject* player = GameObjectManager::GetInstance().GetObj("player");
		GameObject* enemy = GameObjectManager::GetInstance().GetObj("enemy");

		TransformComp* dtf = directionArrow->GetComponent<TransformComp>();
		TransformComp* ptf = player->GetComponent<TransformComp>();
		TransformComp* etf = enemy->GetComponent<TransformComp>();

		switch (CombatComp::turn)
		{
			case PLAYERTURN: // player turn
			
				// 임시 트리거
				if (AEInputCheckTriggered(AEVK_F) && ArrowCount < 1)
				{
					directionArrow->GetComponent<CombatComp>()->isDrawDirection = true;
					directionArrow->GetComponent<CombatComp>()->isChaseDirection = true;
				}
				if (AEInputCheckTriggered(AEVK_W))
				{
					directionArrow->GetComponent<CombatComp>()->pPower += 1;
					std::cout << "Increase Player Power : " << directionArrow->GetComponent<CombatComp>()->pPower << std::endl;
				}
				if (AEInputCheckTriggered(AEVK_S))
				{
					directionArrow->GetComponent<CombatComp>()->pPower -= 1;
					std::cout << "Decrease Player Power : " << directionArrow->GetComponent<CombatComp>()->pPower << std::endl;
				}
				if (AEInputCheckTriggered(AEVK_Q))
				{
					directionArrow->GetComponent<CombatComp>()->pAngle += AEDegToRad(1);
					std::cout << "Increase Player Angle : " << AERadToDeg(directionArrow->GetComponent<CombatComp>()->pAngle) << std::endl;
				}
				if (AEInputCheckTriggered(AEVK_E))
				{
					directionArrow->GetComponent<CombatComp>()->pAngle -= AEDegToRad(1);
					std::cout << "Decrease Player Angle : " << AERadToDeg(directionArrow->GetComponent<CombatComp>()->pAngle) << std::endl;
				}

				if (isDrawDirection)
				{
					if (AEInputCheckTriggered(AEVK_LBUTTON))
					{
						player->GetComponent<PlayerComp>()->moveState = false;
						isChaseDirection = false;
						isReadyLaunch = true;
					}				
					directionArrow->GetComponent<SpriteComp>()->SetAlpha(1);
					if (isChaseDirection)
					{
						directionArrow->
							GetComponent<CombatComp>()->
							DrawDirectionPegline(*directionArrow,
								PLAYERTURN, { -ANGLE_LIMIT, ANGLE_LIMIT });
					}

					dtf->SetScale({ directionArrowWidth, directionArrowHeight * pPower });
					dtf->SetPos(
						RotatePointAround(
							ptf->GetPos(),
							{ ptf->GetPos().x , ptf->GetPos().y + dtf->GetScale().y / 2 },
							pAngle - RAD90
						)
					);

				}

				if (AEInputCheckTriggered(AEVK_RBUTTON))
				{
					if (isReadyLaunch)
					{
						FireAnArrow(PLAYERTURN, *directionArrow);
					}
				}

				
				break;

			case ENEMYTURN: // enemy turn
			
				// 임시 트리거
				if (AEInputCheckTriggered(AEVK_F) && ArrowCount < 1)
				{
					directionArrow->GetComponent<CombatComp>()->isDrawDirection = true;
					directionArrow->GetComponent<CombatComp>()->isChaseDirection = true;
					SetEnemyAngle(RAD90);
				}
			 
				if (isDrawDirection)
				{
					if (isSetLaunchAngle)
					{
						isSetLaunchAngle = false;
						isChaseDirection = false;
						isReadyLaunch = true;
					}

					directionArrow->GetComponent<SpriteComp>()->SetAlpha(1);
					if (isChaseDirection)
					{
						directionArrow->
							GetComponent<CombatComp>()->
							DrawDirectionPegline(*directionArrow,
								ENEMYTURN, { -ANGLE_LIMIT, ANGLE_LIMIT });
					}

					dtf->SetScale({ directionArrowWidth, directionArrowHeight * ePower });
					dtf->SetPos(
						RotatePointAround(
							etf->GetPos(),
							{ etf->GetPos().x , etf->GetPos().y + dtf->GetScale().y / 2 },
							eAngle - RAD90
						)
					);
				}
				else
				{
					directionArrow->GetComponent<SpriteComp>()->SetAlpha(0);
				}
				if (isReadyLaunch)
				{
					FireAnArrow(ENEMYTURN, *directionArrow);
				}
				break;
		}
		DataUpdate();
		checkState();
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
