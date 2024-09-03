// Author : sinu

#pragma once
#include <iostream>
#include <fstream>
#include "../ComponentManager/LogicComponent.h"
#include "../GameObject/GameObject.h"
#include "AEEngine.h"

// ���� ���
#define GRAVITY 9.81f // �߷� ���ӵ� (m/s^2) 9.81f
#define AIR_RESISTANCE_COEFFICIENT 0.01f // ���� ���� ���
#define WIND_MAX 5 // -n ~ n

class Projectile : public LogicComponent
{

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
	float windSpeed;
	float windAngle;
	static AEVec2 wind;
	Projectile(GameObject* _owner);
	Projectile(GameObject* _owner, float velocity_value, float theta_value);

	// Ʈ���� ����
	static bool isLaunchProjectile;

	// ������ �ٶ��� ����� ������ �����ϴ� �Լ� (����)
	void GenerateRandomWind(AEVec2& wind);
	// ����ü�� ��ġ�� ����ϴ� �Լ�
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