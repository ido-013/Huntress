// Author : sinu

#pragma once
#include <iostream>
#include <fstream>
#include "../ComponentManager/LogicComponent.h"
#include "../GameObject/GameObject.h"
#include "AEEngine.h"



class Projectile : public LogicComponent
{

	// Variables
	float velocity;
	float theta;
	float mass;
	float time;
	float delay;
	AEVec2 initialVelocity;
	AEVec2 wind;
	float startY;
	GameObject* projectile;
	
	~Projectile();
public:
	Projectile(GameObject* _owner);
	Projectile(GameObject* _owner, float velocity_value, float theta_value);
	
	// 물리 상수
	const float GRAVITY = 9.81f; // 중력 가속도 (m/s^2) 9.81f
	const float AIR_RESISTANCE_COEFFICIENT = 0.01f; // 공기 저항 계수

	// 트리거 변수
	static bool isLaunchProjectile;

	// 랜덤한 바람의 세기와 방향을 생성하는 함수 (라디안)
	void GenerateRandomWind(AEVec2& wind);
	// 투사체의 위치를 계산하는 함수
	void CalculateProjectileMotion();

	void SetVelocity(float value) { velocity = value; };
	float GetVelocity() const { return velocity; };
	void SetTheta(float value) { theta = value; };
	float GetTheta() const { return theta; };
	void SetProjectileObject(GameObject& value) { projectile = &value; };
	GameObject* GetProjectileObject() const { return projectile; };

	void Update() override;
	void LoadFromJson(const json& data) override;
	json SaveToJson() override;

	static BaseRTTI* CreateCombatComponent(GameObject* owner);
	static constexpr const char* TypeName = "Projectile";
};