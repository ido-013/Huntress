// Author : sinu

#pragma once
#include <iostream>
#include <fstream>
#include <queue>
#include "../ComponentManager/LogicComponent.h"
#include "../GameObject/GameObject.h"
#include "AEEngine.h"

// 물리 상수
#define GRAVITY 9.81f // 중력 가속도 (m/s^2) 9.81f
#define AIR_RESISTANCE_COEFFICIENT 0.01f // 공기 저항 계수
#define WIND_MAX 3 // -n ~ n

//시간비례 투사체 공격력 상수
//1에서 5로 갈수록 시간 비례 플레이어 투사체 공격력 계수 증가
#define TIME_ARANGE_1 0.5f
#define TIME_ARANGE_2 1.f
#define TIME_ARANGE_3 1.5f
#define TIME_ARANGE_4 2.f
#define TIME_ARANGE_5 2.3f

class Projectile : public LogicComponent
{
	enum ColState
	{
		None,
		Air,
		Ground,
		Character
	};

	// Variables
	float velocity;
	float theta;
	float mass;
	float time;
	float delay;
	AEVec2 initialVelocity;
	float startY;
	GameObject* projectile;
	
	~Projectile();
public:
	float launchTime;
	static float windSpeed;
	static float windAngle;
	static AEVec2 wind;
	Projectile(GameObject* _owner);
	Projectile(GameObject* _owner, float velocity_value, float theta_value);

	std::queue<GameObject::Type> oppoTypeQueue;
	ColState colState = None;

	// 트리거 변수
	static bool isLaunchProjectile;

	// 랜덤한 바람의 세기와 방향을 생성하는 함수 (라디안)
	static void GenerateRandomWind();
	// 투사체의 위치를 계산하는 함수
	void CalculateProjectileMotion();

	void SetVelocity(float value) { velocity = value; };
	float GetVelocity() const { return velocity; };
	void SetTheta(float value) { theta = value; };
	float GetTheta() const { return theta; };
	void SetProjectileObject(GameObject& value) { projectile = &value; };
	GameObject* GetProjectileObject() const { return projectile; };

	void UpdateCollision();

	void Update() override;
	void LoadFromJson(const json& data) override;
	json SaveToJson() override;

	static BaseRTTI* CreateCombatComponent(GameObject* owner);
	static constexpr const char* TypeName = "Projectile";
};