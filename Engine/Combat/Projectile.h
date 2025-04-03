// Author : sinu

#pragma once
#include <iostream>
#include <fstream>
#include <queue>
#include "../ComponentManager/LogicComponent.h"
#include "../GameObject/GameObject.h"
#include "AEEngine.h"

// ���� ���
#define GRAVITY 9.81f // �߷� ���ӵ� (m/s^2) 9.81f
#define AIR_RESISTANCE_COEFFICIENT 0.01f // ���� ���� ���
#define WIND_MAX 3 // -n ~ n

//�ð���� ����ü ���ݷ� ���
//1���� 5�� ������ �ð� ��� �÷��̾� ����ü ���ݷ� ��� ����
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

	// Ʈ���� ����
	static bool isLaunchProjectile;

	// ������ �ٶ��� ����� ������ �����ϴ� �Լ� (����)
	static void GenerateRandomWind();
	// ����ü�� ��ġ�� ����ϴ� �Լ�
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