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
	1. �ش� ������ ������ �Ŀ�(�Ŀ��� 1���� 10��ŭ ����)��ŭ ������ �������� �׸�
	2. �÷��̾ �ڽ�(��)�� �������� x/-x���� �ľ� �� (-)2���� �˻�
	3. ���� �ش���� ������ �Ŀ��� �ø��� �Ŀ��� �ִ���� �÷������� ������ �ø�
	4. �������ص� ��ã���� ����Ʈ ������ ���� �Ǵ� ������ �ʰ� ���� ������
	*/
	AEVec2 p = player->GetComponent<TransformComp>()->GetPos();
	AEVec2 e = enemy->GetComponent<TransformComp>()->GetPos();

	ePower = 1.0f; // �ʱ� �Ŀ�

	while (ePower <= POWER_LIMIT)
	{
		float t = 0.0f;
		AEVec2 ptf = e;

		eVelocity = ePower + DEFAULT_POWER;

		float initialVelocityX = eVelocity * std::cos(eAngle);
		float initialVelocityY = eVelocity * std::sin(eAngle);

		while (true)
		{
			// ���� �ӵ� ��� (�ӵ��� ���� ���װ� �ٶ� ����)
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

			// �÷��̾�� ������ ��ġ�� ������� Ȯ��
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
				return HIT; // ����
			}

			// �ʺ��� �� ���� �������ٸ� ������ ���� ���
			if (ptf.y < -windowHeightHalf)
			{
				break;
			}
		}

		// �Ŀ��� ������Ŵ
		ePower += POWER_INTERVER;
	}

	// ���� ����
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
			
				// �ӽ� Ʈ����
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
			
				// �ӽ� Ʈ����
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
