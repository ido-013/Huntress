// Author : sinu

//include
#include "Combat.h"
#include "../Components/AnimatorComp.h"
#include "../Components/RigidbodyComp.h"
#include "../GameObjectManager/GameObjectManager.h"
#include "../Components/SpriteComp.h"
#include "../Components/PlayerComp.h"
#include "../Components/EnemyComp.h"
#include "../Components/AudioComp.h"
#include "../Combat/Projectile.h"
#include <cmath>
#include "AEInput.h"
#include "AEMath.h"
#include "../Utils/Size.h"
#include "../Components/SubtitleComp.h"
#include "../Camera/Camera.h"
#include <random>
#include <iostream>
#include "../Utils/Utils.h"

float delayTime = 0.2f;  // 2초 딜레이
float elapsedTime = 0.0f;  // 경과 시간 저장
f64 CombatComp::currTime = 0;
bool CombatComp::once = false;

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
pAngle(RAD90), eAngle(RAD90), pVelocity(0), eVelocity(0), pPower((int)(PLAYER_POWER_LIMIT / 2)), ePower((int)(PLAYER_POWER_LIMIT / 2)), AICombatSystemApplyWind(true), angleInterval(0), AICombatSystemObjectivePointCount(0), AICombatSystemEnemyGrade(Data::EnemyData::GRADE::Normal)
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
float AngleBetweenSegments(const AEVec2 p1, const AEVec2 p2, const AEVec2 p3, const AEVec2& p4) {
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
		f32 cx, cy;
		//AEGfxGetCamPosition(&cx, &cy);
		Camera::GetInstance().GetPos(&cx, &cy);
		s32 px, py; 
		AEInputGetCursorPosition(&px, &py);
		px -= windowWidthHalf;
		py -= windowHeightHalf;
		py = -py;

		{
			AEMtx33 mtx = Camera::GetInstance().GetMatrix();
			AEVec2 tmp1 = atf->GetPos();
			AEVec2 tmp2 = dtf->GetPos();
			AEVec2 tmp3 = { cx, cy };
			AEMtx33MultVec(&tmp1, &mtx, &tmp1);
			AEMtx33MultVec(&tmp2, &mtx, &tmp2);
			AEMtx33MultVec(&tmp3, &mtx, &tmp3);

			angle = AngleBetweenSegments(tmp1, tmp2,
				tmp1, { (float)px + tmp3.x, (float)py + tmp3.y });
		}
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
		while (EnemyAICombatSystem() == RESEARCH) 
		{ 
			std::cout << "Research..." << std::endl;
		}// AISystem
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

	projectile->GetComponent<SpriteComp>()->SetTexture("./Assets/Character/ArrowAttack/Arrow/Arrow.png");
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
		if (enemy->GetComponent<EnemyComp>()->enemyData->hp <= 0)
		{
			state = KILLENEMY;
			std::cout << "CLEAR! <KILLENEMY>" << std::endl;
			return;
		}
		else if (player->GetComponent<PlayerComp>()->playerData->hp <= 0)
		{
			state = KILLPLAYER;
			std::cout << "GAMEOVER <KILLPLAYER>" << std::endl;
			return;
		}
	}
	//낙사 코드
	if (enemy->GetComponent<TransformComp>()->GetPos().y < MAP_BOTTOM_MAX)
	{
		state = CLEAR;
		std::cout << "CLEAR!" << std::endl;
		return;
	}

	if (player->GetComponent<TransformComp>()->GetPos().y < MAP_BOTTOM_MAX)
	{
		state = GAMEOVER;
		std::cout << "GAMEOVER" << std::endl;
		return;
	}
}

void CombatComp::ResetCombat()
{

	isCombat = true;
	state = READY;
	turn = PLAYERTURN;
	Projectile::isLaunchProjectile = false;
	isDrawDirection = false;
	isChaseDirection = true;
	isReadyLaunch = false;
	currTime = 0;
	ArrowCount = 0;
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
	AEVec2 op = p;
	AEVec2 e = enemy->GetComponent<TransformComp>()->GetPos();

	switch (AICombatSystemObjectivePointCount)
	{
	case -4:
		op = { p.x + -120, p.y };
		break;
	case -3:
		op = { p.x + -90, p.y };
		break;
	case -2:
		op = { p.x + -60, p.y };
		break;
	case -1:
		op = { p.x + -30, p.y };
		break;
	case 0:
		op = { p.x + 0, p.y };
		break;
	case 1:
		op = { p.x + 30, p.y };
		break;
	case 2:
		op = { p.x + 60, p.y };
		break;
	case 3:
		op = { p.x + 90, p.y };
		break;
	case 4:
		op = { p.x + 120, p.y };
		break;
	}

	// 초기 파워
	ePower = 1.0f;


	while (ePower <= PLAYER_POWER_LIMIT)
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
			float loc = sqrt((ptf.x - op.x) * (ptf.x - op.x) + (ptf.y - op.y) * (ptf.y - op.y));
			if (loc <= HIT_RADIUS)
			{
				isSetLaunchAngle = true;
				enemy->GetComponent<RigidbodyComp>()->SetVelocityX(0);
				std::cout << "HIT" << std::endl;
				//std::cout << "ptf : " << ptf.x << " , " << ptf.y << "\np : " << p.x << " , " << p.y <<  std::endl;
				//std::cout << "ePower : " << ePower <<  std::endl;
				//std::cout << "eAngle : " << AERadToDeg(eAngle) <<  std::endl;
				//std::cout << "x : " << ptf.x - p.x << "y : " << ptf.y - p.y <<  std::endl;
				//std::cout << loc << std::endl;
				return HIT; // 적중
			}

			// 맵보다 더 낮게 떨어졌다면 포물선 궤적 벗어남
			if (ptf.y < MAP_BOTTOM_MAX)
			{
				break;
			}
		}

		// 파워를 증가시킴
		ePower += POWER_INTERVER;
	}

	if (p.x < e.x ? eAngle > ANGLE_LIMIT + RAD90 : eAngle < ANGLE_LIMIT - RAD90)
	{
		if (enemy->GetComponent<EnemyComp>()->moveState)
		{
			std::cout << "Projectile : RESEARCH" << std::endl;
			enemy->GetComponent<EnemyComp>()->isMove = true;
			eAngle = RAD90;
			return RESEARCH;
		}
		else
		{
			ePower = ENEMY_POWER_LIMIT;
			eVelocity = ePower + DEFAULT_POWER;
			eAngle = p.x < e.x ? RAD10 * 2 + RAD90 : -(RAD10 * 2 + RAD90);
			isSetLaunchAngle = true;
			std::cout << "Projectile : NOT FOUND IN AICombatSystem" << std::endl;
			return NOTFOUND;
		}
	}

	// 각도 설정
	eAngle += p.x < e.x ? angleInterval : -angleInterval;

	return MISS;
}

int getRandomIntInRange(int n) 
{
	// 랜덤 시드 생성
	std::random_device rd;
	std::mt19937 gen(rd());
	// 범위: -n부터 n까지
	std::uniform_int_distribution<> dist(-n, n);

	// 랜덤 정수 반환
	return dist(gen);
}

void getDecreaseRange(int& n, int m)
{
	if (n == 0) return;
	bool negative = n < 0 ? true : false;
	n = abs(n);
	if (n - m < 0) n = 0; 
	else n = n - m;
	if(negative) n = -n;
}

void CombatComp::Update()
{
	GameObject* bg = GameObjectManager::GetInstance().GetObj("background");
	AudioComp* bga = bg->GetComponent<AudioComp>();
#ifdef _DEBUG
	if (AEInputCheckTriggered(AEVK_R))
	{
		state = GAMEOVER;
	}
	if (AEInputCheckTriggered(AEVK_N))
	{
		state = CLEAR;
	}
#endif // DEBUG
	if (isCombat && state == COMBAT)
	{
		GameObject* directionArrow = GameObjectManager::GetInstance().GetObj("directionArrow");
		TransformComp* dtf = directionArrow->GetComponent<TransformComp>();
		GameObject* player = GetPlayerObject();
		TransformComp* ptf = GetPlayerTransform();
		GameObject* enemy = GetEnemyObject();
		TransformComp* etf = GetEnemyTransform();
#ifdef _DEBUG
		if (AEInputCheckTriggered(AEVK_T))
		{
			std::cout << std::sqrt(std::pow(ptf->GetPos().x - etf->GetPos().x, 2) + std::pow(ptf->GetPos().y - etf->GetPos().y, 2)) << std::endl;
		}
#endif // DEBUG
		//적 스프라이트 x축 방향 설정
		enemy->GetComponent<TransformComp>()->ReverseX(ptf->GetPos().x < etf->GetPos().x ? 0 : 1);

		switch (CombatComp::turn)
		{
			case PLAYERTURN: // player turn

				if (!Projectile::isLaunchProjectile)
				{
					//AEGfxSetCamPosition(ptf->GetPos().x, ptf->GetPos().y);
					Camera::GetInstance().SetPos(ptf->GetPos().x, ptf->GetPos().y);
				}

				if (directionArrow->GetComponent<CombatComp>()->isDrawDirection == false && ArrowCount < 1)
				{
					SubtitleComp::IntersectDissolveText({ {{(f32)-0.3,(f32)0.1}, 1, "PLAYER TURN", 1, 1, 1, 1}, 3, 1, 1 });
					std::cout << "PLAYERTURN" << std::endl;
					directionArrow->GetComponent<CombatComp>()->isDrawDirection = true;
					directionArrow->GetComponent<CombatComp>()->isChaseDirection = true;
					directionArrow->GetComponent<SpriteComp>()->SetAlpha(1);
					Projectile::GenerateRandomWind();
				}
				if (AEInputCheckTriggered(AEVK_W))
				{
					if (directionArrow->GetComponent<CombatComp>()->pPower <= PLAYER_POWER_LIMIT)
					{
						directionArrow->GetComponent<CombatComp>()->pPower += 1;
						std::cout << "Increase Player Power : " << directionArrow->GetComponent<CombatComp>()->pPower << std::endl;
					}
				}
				if (AEInputCheckTriggered(AEVK_S))
				{
					if (directionArrow->GetComponent<CombatComp>()->pPower > DEFAULT_POWER)
					{
						directionArrow->GetComponent<CombatComp>()->pPower -= 1;
						std::cout << "Decrease Player Power : " << directionArrow->GetComponent<CombatComp>()->pPower << std::endl;
					}
				}

				if (isDrawDirection)
				{
					if (AEInputCheckTriggered(AEVK_LBUTTON))
					{
						if (isChaseDirection == false)
						{
							player->GetComponent<PlayerComp>()->moveState = true;
							isChaseDirection = true;
							isReadyLaunch = false;
						}
						else
						{
							player->GetComponent<TransformComp>()->ReverseX(ptf->GetPos().x > GetMouseCursorPositionX() + ptf->GetPos().x ? 0 : 1);
							std::cout << ptf->GetPos().x << " | " << GetMouseCursorPositionX() + ptf->GetPos().x << std::endl;
							player->GetComponent<PlayerComp>()->moveState = false;
							isChaseDirection = false;
							isReadyLaunch = true;
						}
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
					if (isReadyLaunch && ArrowCount < 1)
					{
						FireAnArrow(PLAYERTURN, *directionArrow);
					}
				}

				break;

			case ENEMYTURN: // enemy turn

				if (!Projectile::isLaunchProjectile)
				{
					Camera::GetInstance().SetPos(etf->GetPos().x, etf->GetPos().y);
				}
			
				if (directionArrow->GetComponent<CombatComp>()->isDrawDirection == false && ArrowCount < 1)
				{
					std::cout << "ENEMYTURN" << std::endl;
					SubtitleComp::IntersectDissolveText({ {{(f32)-0.3,(f32)0.1}, 1, "ENEMY TURN", 1, 1, 1, 1}, 3, 1, 1 });
					
					switch (enemy->GetComponent<EnemyComp>()->enemyData->grade)
					{
					case Data::EnemyData::GRADE::Normal:
						AICombatSystemApplyWind = true;
						AICombatSystemEnemyGrade = Data::EnemyData::GRADE::Normal;
						angleInterval = AEDegToRad(5.f);
						break;
					case Data::EnemyData::GRADE::Elite:
						AICombatSystemApplyWind = true;
						AICombatSystemEnemyGrade = Data::EnemyData::GRADE::Elite;
						angleInterval = AEDegToRad(5.f);
						break;
					case Data::EnemyData::GRADE::Boss:
						AICombatSystemApplyWind = true;
						AICombatSystemEnemyGrade = Data::EnemyData::GRADE::Boss;
						angleInterval = AEDegToRad(5.f);
						break;
					}
					if (GetPlayerEnemyDistance() < DISTANCE_ARANGE_1)
						AICombatSystemObjectivePointCount = 0;
					else if (GetPlayerEnemyDistance() < DISTANCE_ARANGE_2)
						AICombatSystemObjectivePointCount = 1;
					else if (GetPlayerEnemyDistance() < DISTANCE_ARANGE_3)
						AICombatSystemObjectivePointCount = 2;
					else if (GetPlayerEnemyDistance() < DISTANCE_ARANGE_4)
						AICombatSystemObjectivePointCount = 3;
					else if (GetPlayerEnemyDistance() < DISTANCE_ARANGE_5)
						AICombatSystemObjectivePointCount = 4;
					else
						AICombatSystemObjectivePointCount = 4;
					AICombatSystemObjectivePointCount = getRandomIntInRange(AICombatSystemObjectivePointCount);

					if (AICombatSystemEnemyGrade == Data::EnemyData::GRADE::Normal)
						getDecreaseRange(AICombatSystemObjectivePointCount, 0);
					else if (AICombatSystemEnemyGrade == Data::EnemyData::GRADE::Elite)
						getDecreaseRange(AICombatSystemObjectivePointCount, 1);
					else if (AICombatSystemEnemyGrade == Data::EnemyData::GRADE::Boss)
						getDecreaseRange(AICombatSystemObjectivePointCount, 2);

					std::cout << "AICombatSystemObjectivePointCount : " << AICombatSystemObjectivePointCount << std::endl;
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
					else
					{
						directionArrow->GetComponent<SpriteComp>()->SetAlpha(1);
						if (GetPlayerEnemyDistance() > DISTANCE_ARANGE_5)
						{
							directionArrow->GetComponent<SpriteComp>()->SetAlpha(0);
							while (EnemyAICombatSystem() == RESEARCH)
							{
								std::cout << "Research..." << std::endl;
							}// AISystem
						}

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
				}
				else
				{
					directionArrow->GetComponent<SpriteComp>()->SetAlpha(0);
				}
				if (isReadyLaunch && ArrowCount < 1)
				{
					static f64 timer = 0;
					timer += AEFrameRateControllerGetFrameTime();

					if (timer > 1)
					{
						timer = 0;
						FireAnArrow(ENEMYTURN, *directionArrow);
					}
				}

				break;
		}
		
		DataUpdate();
		checkState();
	}
	else if (isCombat && state == READY)
	{
		GameObject* player = GetPlayerObject();
		TransformComp* ptf = GetPlayerTransform();
		GameObject* enemy = GetEnemyObject();
		TransformComp* etf = GetEnemyTransform();
		//2초간 플레이어 고정
		if (currTime < 2)
		{
			player->GetComponent<PlayerComp>()->moveState = false;
			//AEGfxSetCamPosition(ptf->GetPos().x, ptf->GetPos().y);
			Camera::GetInstance().SetPos(ptf->GetPos().x, ptf->GetPos().y);
			Camera::GetInstance().SetHeight(1);

			if (once == false)
			{
				once = true;
				SubtitleComp::IntersectDissolveText({ {{(f32)-0.15,(f32)0.1}, 1, "READY", 1, 1, 1, 1}, 2, 0.7, 0.7 });

				bga->playAudio(0, "./Assets/Audio/soda-bottle-base-drum.mp3");
			}
		}
		//2초간 적 위치 고정
		else if (currTime < 4)
		{
			//AEGfxSetCamPosition(etf->GetPos().x, etf->GetPos().y);
			Camera::GetInstance().SetPos(etf->GetPos().x, etf->GetPos().y);

			if (once == true)
			{
				once = false;
				SubtitleComp::IntersectDissolveText({ {{(f32)-0.1,(f32)0.1}, 1, "Set", 1, 1, 1, 1}, 2, 0.7, 0.7 });

				bga->playAudio(0, "./Assets/Audio/soda-bottle-base-drum.mp3");
			}
		}
		else if (currTime < 6)
		{
			{
				//AEGfxSetCamPosition(ptf->GetPos().x, ptf->GetPos().y);
				Camera::GetInstance().SetPos((ptf->GetPos().x + etf->GetPos().x) / 2, 
											 (ptf->GetPos().y + etf->GetPos().y) / 2);

				float pad = 600;
				float disX = abs(ptf->GetPos().x - etf->GetPos().x) + pad;
				float disY = abs(ptf->GetPos().y - etf->GetPos().y) + pad;

				int width = AEGfxGetWindowWidth();
				int height = AEGfxGetWindowHeight();
			
				Camera::GetInstance().SetHeight(max(max(1, disX * 2 / width), max(1, disY * 2 / height)));
			}
			
			if (once == false)
			{
				once = true;
				SubtitleComp::IntersectDissolveText({ {{(f32)-0.12,(f32)0.1}, 1, "Go!!", 1, 1, 1, 1}, 2, 0.7, 0.7 });
				bga->playAudio(0, "./Assets/Audio/drum-hit.mp3");
			}
		}
		else {
			once = false;
			player->GetComponent<PlayerComp>()->moveState = true;
			state = COMBAT;
			currTime = 0;
			Camera::GetInstance().SetHeight(1);
		}
		currTime += AEFrameRateControllerGetFrameTime();
	}
	else if (isCombat && state == KILLENEMY)
	{
		GameObject* player = GetPlayerObject();
		TransformComp* ptf = GetPlayerTransform();
		GameObject* enemy = GetEnemyObject();
		TransformComp* etf = GetEnemyTransform();
		//2초간 적 고정
		if (currTime < 2)
		{
			player->GetComponent<PlayerComp>()->moveState = false; 
			
			//AEGfxSetCamPosition(etf->GetPos().x, etf->GetPos().y);
			Camera::GetInstance().SetPos(etf->GetPos().x, etf->GetPos().y);
			if (once == false)
			{
				once = true;
				bga->playAudio(0, "./Assets/Audio/tada-military.mp3");
				SubtitleComp::IntersectDissolveText({ {{(f32)-0.3,(f32)0.1}, 1, "YOU WIN!", 1, 1, 1, 1}, 2, 0.7, 0.7 });
			}
		}
		else {
			once = false;
			state = CLEAR;
			currTime = 0;
		}
		currTime += AEFrameRateControllerGetFrameTime();
	}
	else if (isCombat && state == KILLPLAYER)
	{
		GameObject* player = GetPlayerObject();
		TransformComp* ptf = GetPlayerTransform();
		GameObject* enemy = GetEnemyObject();
		TransformComp* etf = GetEnemyTransform();
		//2초간 플레이어 고정
		if (currTime < 2)
		{
			player->GetComponent<PlayerComp>()->moveState = false; 
			//AEGfxSetCamPosition(ptf->GetPos().x, ptf->GetPos().y);
			Camera::GetInstance().SetPos(ptf->GetPos().x, ptf->GetPos().y);
			if (once == false)
			{
				once = true;
				SubtitleComp::IntersectDissolveText({ {{(f32)-0.3,(f32)0.1}, 1, "YOU LOSE", 1, 1, 1, 1}, 2, 0.7, 0.7 });
				bga->playAudio(0, "./Assets/Audio/failfare.mp3");
			}
		}
		else
		{
			once = false;
			state = GAMEOVER;
			currTime = 0;
		}
		currTime += AEFrameRateControllerGetFrameTime();
	}
	else if (isCombat && state == GAMEOVER)
	{
		GameObject* player = GetPlayerObject();
		TransformComp* ptf = GetPlayerTransform();
		GameObject* enemy = GetEnemyObject();
		TransformComp* etf = GetEnemyTransform();
		if (currTime < 2)
		{
			Camera::GetInstance().SetPos(ptf->GetPos().x, ptf->GetPos().y);
			if (once == false)
			{
				once = true;
				SubtitleComp::IntersectDissolveText({ {{(f32)-0.3,(f32)0.1}, 1, "GAME OVER", 1, 1, 1, 1}, 2, 0.7, 0.7 });
			}
		}
		else
		{
			once = false;
			state = RESET;
			currTime = 0;
		}
		currTime += AEFrameRateControllerGetFrameTime();
	}
	float deltaTime = (float) AEFrameRateControllerGetFrameTime();  // 프레임 경과 시간 가져오기
	elapsedTime += deltaTime;
	if (elapsedTime >= delayTime)
	{
		elapsedTime = 0;
	}
}

void CombatComp::LoadFromJson(const json& data)
{
	auto compData = data.find("compData");

	if (compData != data.end())
	{
		auto it = compData->find("turn");
		turn = it.value();

		it = compData->find("state");
		state = it.value();

		it = compData->find("isCombat");
		isCombat = it.value();
	}
}

json CombatComp::SaveToJson()
{
	json data;
	data["type"] = TypeName;

	json compData;
	compData["turn"] = turn;
	compData["state"] = state;
	compData["isCombat"] = isCombat;
	data["compData"] = compData;

	return data;
}

BaseRTTI* CombatComp::CreateCombatComponent(GameObject* owner)
{
	BaseRTTI* p = new CombatComp(owner);
	owner->AddComponent<CombatComp>(static_cast<CombatComp*>(p));
	return p;
}

void CombatComp::InitEnemyValue()
{
	eAngle = RAD90;
	eVelocity = DEFAULT_POWER;
	ePower = 0;
}

GameObject* CombatComp::GetPlayerObject()
{
	return GameObjectManager::GetInstance().GetObj("player");
}

TransformComp* CombatComp::GetPlayerTransform()
{
	return GetPlayerObject()->GetComponent<TransformComp>();
}

GameObject* CombatComp::GetEnemyObject()
{
	return GameObjectManager::GetInstance().GetObj("enemy");
}

TransformComp* CombatComp::GetEnemyTransform()
{
	return GetEnemyObject()->GetComponent<TransformComp>();
}

int CombatComp::GetPlayerEnemyDistance()
{
	return (int)std::sqrt(std::pow(GetPlayerTransform()->GetPos().x - GetEnemyTransform()->GetPos().x, 2) + std::pow(GetPlayerTransform()->GetPos().y - GetEnemyTransform()->GetPos().y, 2));
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