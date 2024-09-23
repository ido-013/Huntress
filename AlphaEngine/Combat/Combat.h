// Author : sinu

#pragma once
#include "AEVec2.h"
#include "../GameObject/GameObject.h"
#include "../Components/TransformComp.h"
#include "../ComponentManager/EngineComponent.h"
#include "../Combat/Projectile.h"
#include "../Data/Data.h"

#define DEFAULT_POWER 1.f
#define PLAYER_POWER_LIMIT 24.f // 25
#define ENEMY_POWER_LIMIT 19.f // 20

#define ANGLE_LIMIT AEDegToRad(120.f)

#define POWER_INTERVER 1.f

#define RAD10 AEDegToRad(10.f)
#define RAD90 AEDegToRad(90.f)

#define MAP_BOTTOM_MAX -2500 // 맵 가장 아래

#define HIT_RADIUS 15.0f // 플레이어에 대한 적중 판정 반경

//붙어서 싸우기 방지를 위한 상수값

	//거리비례 AI 명중률 상수 
	//1에서 5로 갈수록 거리 비례 AI 명중률 감소
	#define DISTANCE_ARANGE_1 100
	#define DISTANCE_ARANGE_2 500
	#define DISTANCE_ARANGE_3 1000
	#define DISTANCE_ARANGE_4 1500
	#define DISTANCE_ARANGE_5 1800

	//시간비례 투사체 공격력 상수
	//1에서 5로 갈수록 시간 비례 플레이어 투사체 공격력 계수 증가
	#define TIME_ARANGE_1 1
	#define TIME_ARANGE_2 2
	#define TIME_ARANGE_3 3
	#define TIME_ARANGE_4 4
	#define TIME_ARANGE_5 5

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
	const float directionArrowHeight = 80 / (DEFAULT_POWER + PLAYER_POWER_LIMIT); // * 1~25

	CombatComp(GameObject* _owner); 
	~CombatComp();
	
	enum TURN {
		NOBODYTURN = 0,
		PLAYERTURN = 1,
		ENEMYTURN = 2
	};
	static TURN turn; // 0 : nobody, 1 : player, 2 : enemy
	static TURN TurnChange();

	static bool isCombat; // 전투 상태

	static bool isDrawDirection; // 조준 상태
	static bool isChaseDirection; // 조준선 고정 상태
	static bool isReadyLaunch; // 발사 준비 상태

	// AICombatSystem에서만 사용
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
	int AICombatSystemObjectivePointCount;
	Data::EnemyData::GRADE AICombatSystemEnemyGrade;
	GameObject* GetPlayerObject();
	TransformComp* GetPlayerTransform();
	GameObject* GetEnemyObject();
	TransformComp* GetEnemyTransform();
	int GetPlayerEnemyDistance();
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