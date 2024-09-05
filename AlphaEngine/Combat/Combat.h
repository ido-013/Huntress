// Author : sinu

#pragma once
#include "AEVec2.h"
#include "../GameObject/GameObject.h"
#include "../ComponentManager/EngineComponent.h"
#include "../Combat/Projectile.h"
#include "../Data/Data.h"

#define DEFAULT_POWER 1.f
#define POWER_LIMIT 19.f // 20

#define ANGLE_LIMIT AEDegToRad(120.f)

#define POWER_INTERVER 1.f

#define RAD90 AEDegToRad(90.f)

#define HIT_RADIUS 15.0f // �÷��̾ ���� ���� ���� �ݰ�

class CombatComp : public EngineComponent
{
	//player
	float pAngle;
	float pVelocity;
	float pPower;

	//enemy
	float eAngle;
	float eVelocity;
	float ePower;
public:
	Data::CombatData data;
	void DataUpdate();

	static int ArrowCount;

	const float directionArrowWidth = 42;
	const float directionArrowHeight = 80 / (DEFAULT_POWER + POWER_LIMIT); // * 1~25

	CombatComp(GameObject* _owner); 
	~CombatComp();
	
	enum TURN {
		NOBODYTURN = 0,
		PLAYERTURN = 1,
		ENEMYTURN = 2
	};
	static TURN turn; // 0 : nobody, 1 : player, 2 : enemy
	static TURN TurnChange();

	static bool isCombat; // ���� ����

	static bool isDrawDirection; // ���� ����
	static bool isChaseDirection; // ���ؼ� ���� ����
	static bool isReadyLaunch; // �߻� �غ� ����

	// AICombatSystem������ ���
	static bool isSetLaunchAngle;

	static bool once;
	static f64 currTime;

	enum STATE
	{
		NONE = 0,
		COMBAT = 1,
		CLEAR = 2,
		GAMEOVER = 3,
		READY = 4,
		STORE = 5,
		KILLPLAYER = 6,
		KILLENEMY = 7
	};
	static STATE state;
	void checkState();
	static void ResetCombat();
	void SetPlayerAngle(float angle);
	float GetPlayerAngle();
	void SetEnemyAngle(float angle);
	float GetEnemyAngle();
	void SetPlayerVelocity(float velocity);
	float GetPlayerVelocity();
	void SetEnemyVelocity(float velocity);
	float GetEnemyVelocity();
	void SetPlayerPower(float power);
	float GetPlayerPower();
	void SetEnemyPower(float power);
	float GetEnemyPower();

	void InitEnemyValue();

	bool AICombatSystemApplyWind;

	enum RESULT {
		HIT = 0,
		MISS = 1,
		RESEARCH = 2,
		NOTFOUND = 3
	};

	f32 angleInterval;
	RESULT EnemyAICombatSystem();

	void DrawDirectionPegline(GameObject& directionArrow,
		TURN turn, const std::pair<float, float> AngleRange);
	
	void FireAnArrow(TURN turn, GameObject& directionArrow);

	void Update() override;

	void LoadFromJson(const json& data) override;
	json SaveToJson() override;

	static BaseRTTI* CreateCombatComponent(GameObject* owner);
	static constexpr const char* TypeName = "CombatComp";
};