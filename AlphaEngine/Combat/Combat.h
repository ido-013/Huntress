// Author : sinu

#pragma once
#include "AEVec2.h"
#include "../GameObject/GameObject.h"
#include "../Components/TransformComp.h"
#include "../ComponentManager/EngineComponent.h"
#include "../Combat/Projectile.h"
#include "../Data/Data.h"
#include "../Data/Inventory.h"

#define SHOW_ENEMY_DIRECTION_ARROW false
#define SHOW_ENEMY_ORBIT false

#define DEFAULT_POWER 1.f
#define PLAYER_POWER_LIMIT 24.f // 25
#define ENEMY_POWER_LIMIT 19.f // 20

#define ANGLE_LIMIT AEDegToRad(120.f)

#define POWER_INTERVER 1.f
#define ANGLE_INTERVER AEDegToRad(2.f)

#define RAD10 AEDegToRad(10.f)
#define RAD90 AEDegToRad(90.f)

#define MAP_BOTTOM_MAX -2500 // �� ���� �Ʒ�
#define MAP_TOP_MAX 0 // �� ���� ��
#define MAP_LEFT_MAX -1500 // �� ���� ����
#define MAP_RIGHT_MAX 4000 // �� ���� ������

#define HIT_RADIUS 15.0f // �÷��̾ ���� ���� ���� �ݰ�

//�پ �ο�� ������ ���� �����
	//�Ÿ���� AI ���߷� ��� 
	//1���� 5�� ������ �Ÿ� ��� AI ���߷� ����
	#define DISTANCE_ARANGE_1 100
	#define DISTANCE_ARANGE_2 500
	#define DISTANCE_ARANGE_3 1000
	#define DISTANCE_ARANGE_4 1500
	#define DISTANCE_ARANGE_5 1800

#define DEFAULT_ORBIT_CIRCLE_COUNT 120
#define DEBUG_ORBIT_CIRCLE_COUNT 200
#define USE_ITEM_ORBIT_CIRCLE_COUNT 120

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

	static bool isCombat; // ���� ����
	static bool isLaunched;
	static bool isDrawDirection; // ���� ����
	static bool isChaseDirection; // ���ؼ� ���� ����
	static bool isReadyLaunch; // �߻� �غ� ����

	// AICombatSystem������ ���
	static bool isSetLaunchAngle;
	static bool isHit;
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
		KILLENEMY = 7,
		RESET = 8,
		STUN = 9
	};
	static STATE state;
	void checkState();
	static void ResetCombat();
	bool ObstacleCollisionCheck(std::vector<AEVec2>& coords);

	//item
	static std::map<Inventory::Item, bool> itemState;
	static bool isItemUsed;
	static void ItemCheck();
	static void SetItemState(bool isUsed);

	enum ItemUse {
		Big = 0,
		Stun = 1,
		Straight = 2,
		Orbit =3,
		None =4
	};
	static ItemUse ItemState;
	//orbit
	static int orbitCircleCount;
	std::vector<GameObject*> orbitDots;
	void InitOrbit();
	void SetOrbitAlpha(bool isView);
	void ShowOrbit();

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

	static std::vector<TransformComp*> blocks;

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