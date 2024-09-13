// Author : sinu

//include
#include "Combat.h"
#include "../Components/TransformComp.h"
#include "../Components/AnimatorComp.h"
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
#include "../Components/SubtitleComp.h"
#include "../Camera/Camera.h"

float delayTime = 0.2f;  // 2�� ������
float elapsedTime = 0.0f;  // ��� �ð� ����
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
pAngle(RAD90), eAngle(RAD90), pVelocity(0), eVelocity(0), pPower((int)(PLAYER_POWER_LIMIT / 2)), ePower((int)(PLAYER_POWER_LIMIT / 2)), AICombatSystemApplyWind(true), angleInterval(0), AICombatSystemObjectivePointCount(0)
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
		f32 cx, cy;
		//AEGfxGetCamPosition(&cx, &cy);
		Camera::GetInstance().GetPos(&cx, &cy);
		s32 px, py; 
		AEInputGetCursorPosition(&px, &py);
		px -= windowWidthHalf;
		py -= windowHeightHalf;
		py = -py;
		angle = AngleBetweenSegments(atf->GetPos(), dtf->GetPos(),
			atf->GetPos(), { (float)px + cx, (float)py + cy });

		/*std::cout << "px,py : " << px << "," << -(py - windowHeightHalf) << "\n"
				  << "cx,cy : " << cx << "," << cy << "\n"
				  << "atf.x/y : " << (int)atf->GetPos().x << "," << (int)atf->GetPos().y << std::endl;*/
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

void CombatComp::setWalkAnimation()
{



	


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
			std::cout << "CLEAR!" << std::endl;
			return;
		}
		else if (player->GetComponent<PlayerComp>()->playerData->hp <= 0)
		{
			state = KILLPLAYER;
			player->GetComponent<AnimatorComp>()->SetAnimation(false, 1, "Die");

			std::cout << "GAMEOVER" << std::endl;
			return;
		}
	}
	f32 x, y;
	//AEGfxGetCamPosition(&x, &y);
	Camera::GetInstance().GetPos(&x, &y);
	if (enemy->GetComponent<TransformComp>()->GetPos().y < -(windowHeightHalf * 10) + y)
	{
		state = CLEAR;
		std::cout << "CLEAR!" << std::endl;
		return;
	}

	if (player->GetComponent<TransformComp>()->GetPos().y < -(windowHeightHalf * 10) + y)
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
	AEVec2 op = p;
	AEVec2 e = enemy->GetComponent<TransformComp>()->GetPos();


	switch (AICombatSystemObjectivePointCount)
	{
	case -3:
		op = { p.x + -100, p.y };
		break;
	case -2:
		op = { p.x + -70, p.y };
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
		op = { p.x + 70, p.y };
		break;
	case 3:
		op = { p.x + 100, p.y };
		break;
	}

	ePower = 1.0f; // �ʱ� �Ŀ�

	while (ePower <= PLAYER_POWER_LIMIT)
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
				return HIT; // ����
			}

			// �ʺ��� �� ���� �������ٸ� ������ ���� ���
			if (ptf.y < -windowHeightHalf + (e.y > p.y ? p.y : e.y))
			{
				break;
			}
		}

		// �Ŀ��� ������Ŵ
		ePower += POWER_INTERVER;
	}
	
	enemy->GetComponent<TransformComp>()->ReverseX(p.x < e.x ? 0 : 1);

	// ���� ����
	eAngle += p.x < e.x ? angleInterval : -angleInterval;
	//std::cout << p.x << " " << e.x << std::endl;
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
			std::cout << "Projectile : NOT FOUND" << std::endl;
			return NOTFOUND;
		}
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
		//std::cout << "playerMoveGauge: " << player->GetComponent<PlayerComp>()->GetMovegauge() << std::endl;
		//std::cout << "enemyMoveGauge: " << enemy->GetComponent<EnemyComp>()->GetMovegauge() << std::endl;
		TransformComp* dtf = directionArrow->GetComponent<TransformComp>();
		TransformComp* ptf = player->GetComponent<TransformComp>();
		TransformComp* etf = enemy->GetComponent<TransformComp>();

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
						if (isChaseDirection == false)
						{
							player->GetComponent<PlayerComp>()->moveState = true;
							isChaseDirection = true;
							isReadyLaunch = false;
						}
						else
						{
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
					if (isReadyLaunch)
					{
						if (GameObjectManager::GetInstance().GetObj("player")->GetComponent<AnimatorComp>()->GetCurrentAnimation() != "ArrowAttack")
							GameObjectManager::GetInstance().GetObj("player")->GetComponent<AnimatorComp>()->SetAnimation(false, 0.3, "ArrowAttack");
						FireAnArrow(PLAYERTURN, *directionArrow);

					}
				}

				break;

			case ENEMYTURN: // enemy turn

				if (!Projectile::isLaunchProjectile)
				{
					Camera::GetInstance().SetPos(etf->GetPos().x, etf->GetPos().y);
				}
			
				// �ӽ� Ʈ����
				if (directionArrow->GetComponent<CombatComp>()->isDrawDirection == false && ArrowCount < 1)
				{
					std::cout << "ENEMYTURN" << std::endl;
					SubtitleComp::IntersectDissolveText({ {{(f32)-0.3,(f32)0.1}, 1, "ENEMY TURN", 1, 1, 1, 1}, 3, 1, 1 });
					switch (enemy->GetComponent<EnemyComp>()->enemyData->grade)
					{
					case Data::EnemyData::GRADE::Normal:
						AICombatSystemApplyWind = true;
						AICombatSystemObjectivePointCount = rand() % 7 - 3; // -3
						angleInterval = AEDegToRad(5.f);
						break;
					case Data::EnemyData::GRADE::Elite:
						AICombatSystemApplyWind = true;
						AICombatSystemObjectivePointCount = rand() % 5 - 2; // -2
						angleInterval = AEDegToRad(5.f);
						break;
					case Data::EnemyData::GRADE::Boss:
						AICombatSystemApplyWind = true;
						AICombatSystemObjectivePointCount = rand() % 3 - 1; // -1
						angleInterval = AEDegToRad(5.f);
						break;
					}
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
	else if (isCombat && state == READY)
	{
		GameObject* player = GameObjectManager::GetInstance().GetObj("player");
		TransformComp* ptf = player->GetComponent<TransformComp>();
		GameObject* enemy = GameObjectManager::GetInstance().GetObj("enemy");
		TransformComp* etf = enemy->GetComponent<TransformComp>();
		//2�ʰ� �÷��̾� ����
		if (currTime < 2)
		{
			player->GetComponent<PlayerComp>()->moveState = false;
			//AEGfxSetCamPosition(ptf->GetPos().x, ptf->GetPos().y);
			Camera::GetInstance().SetPos(ptf->GetPos().x, ptf->GetPos().y);
			if (once == false)
			{
				once = true;
				SubtitleComp::IntersectDissolveText({ {{(f32)-0.15,(f32)0.1}, 1, "READY", 1, 1, 1, 1}, 2, 0.7, 0.7 });
			}
		}
		//2�ʰ� �� ��ġ ����
		else if (currTime < 4)
		{
			//AEGfxSetCamPosition(etf->GetPos().x, etf->GetPos().y);
			Camera::GetInstance().SetPos(etf->GetPos().x, etf->GetPos().y);
			if (once == true)
			{
				once = false;
				SubtitleComp::IntersectDissolveText({ {{(f32)-0.1,(f32)0.1}, 1, "Set", 1, 1, 1, 1}, 2, 0.7, 0.7 });
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
			
				Camera::GetInstance().SetHeight(max(max(1, disX / width), max(1, disY / height)));
			}
			
			if (once == false)
			{
				once = true;
				SubtitleComp::IntersectDissolveText({ {{(f32)-0.12,(f32)0.1}, 1, "Go!!", 1, 1, 1, 1}, 2, 0.7, 0.7 });
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
		GameObject* player = GameObjectManager::GetInstance().GetObj("player");
		TransformComp* ptf = player->GetComponent<TransformComp>();
		GameObject* enemy = GameObjectManager::GetInstance().GetObj("enemy");
		TransformComp* etf = enemy->GetComponent<TransformComp>();
		//2�ʰ� �� ����
		if (currTime < 2)
		{
			player->GetComponent<PlayerComp>()->moveState = false; 
			
			//AEGfxSetCamPosition(etf->GetPos().x, etf->GetPos().y);
			Camera::GetInstance().SetPos(etf->GetPos().x, etf->GetPos().y);
			if (once == false)
			{
				once = true;
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
		GameObject* player = GameObjectManager::GetInstance().GetObj("player");
		TransformComp* ptf = player->GetComponent<TransformComp>();
		GameObject* enemy = GameObjectManager::GetInstance().GetObj("enemy");
		TransformComp* etf = enemy->GetComponent<TransformComp>();
		//2�ʰ� �÷��̾� ����
		if (currTime < 2)
		{
			player->GetComponent<PlayerComp>()->moveState = false; 
			//AEGfxSetCamPosition(ptf->GetPos().x, ptf->GetPos().y);
			Camera::GetInstance().SetPos(ptf->GetPos().x, ptf->GetPos().y);
			if (once == false)
			{
				once = true;
				SubtitleComp::IntersectDissolveText({ {{(f32)-0.3,(f32)0.1}, 1, "YOU LOSE", 1, 1, 1, 1}, 2, 0.7, 0.7 });
			}
		}
		else if (currTime < 4)
		{
			//AEGfxSetCamPosition(ptf->GetPos().x, ptf->GetPos().y);
			Camera::GetInstance().SetPos(ptf->GetPos().x, ptf->GetPos().y);
			if (once == false)
			{
				once = true;
				SubtitleComp::IntersectDissolveText({ {{(f32)-0.3,(f32)0.1}, 1, "GAME OVER", 1, 1, 1, 1}, 2, 0.7, 0.7 });
			}
		}
		else {
			once = false;
			state = GAMEOVER;
			currTime = 0;
		}
		currTime += AEFrameRateControllerGetFrameTime();
	}
	float deltaTime = (float) AEFrameRateControllerGetFrameTime();  // ������ ��� �ð� ��������
	elapsedTime += deltaTime;
	if (elapsedTime >= delayTime)
	{
		if (GameObjectManager::GetInstance().GetObj("enemy")->GetComponent<AnimatorComp>()->GetCurrentAnimation() != "walk")
		{
			GameObjectManager::GetInstance().GetObj("enemy")->GetComponent<AnimatorComp>()->SetAnimation(true, 1, "Walk");
		}
		if (GameObjectManager::GetInstance().GetObj("player")->GetComponent<AnimatorComp>()->GetCurrentAnimation() != "walk")
		{
			GameObjectManager::GetInstance().GetObj("player")->GetComponent<AnimatorComp>()->SetAnimation(true, 1, "walk");
		}
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
