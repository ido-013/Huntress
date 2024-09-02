// Author : sinu

#pragma once
#include "AEVec2.h"
#include "../GameObject/GameObject.h"
#include "../ComponentManager/EngineComponent.h"
#include "../Combat/Projectile.h"

#define DEFAULT_POWER 1.f
#define POWER_LIMIT 24.f

#define ANGLE_LIMIT AEDegToRad(120.f)

#define POWER_INTERVER 1.f
#define ANGLE_INTERVER AEDegToRad(0.1f)

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


	const float directionArrowWidth = 42;
	const float directionArrowHeight = 260 / (DEFAULT_POWER + POWER_LIMIT); // * 1~25

	CombatComp(GameObject* _owner);
	~CombatComp();
	
	enum TURN {
		NOBODYTURN = 0,
		PLAYERTURN = 1,
		ENEMYTURN = 2
	};
	static TURN turn; // 0 : nobody, 1 : player, 2 : enemy
	static TURN TurnChange();

	static bool isCombat;

	static bool isDrawDirection;
	static bool isChaseDirection;
	static bool isReadyLaunch;

	static bool isSetLaunchAngle;

	enum STATE
	{
		NONE = 0,
		CLEAR = 1,
		GAMEOVER = 2
	};

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
		NOTFOUND = 2
	};
	
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