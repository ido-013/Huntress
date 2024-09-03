#pragma once

#include "../ComponentManager/LogicComponent.h"

class Data : public LogicComponent
{
public:
	class PlayerData
	{
	public:
		float hp;
		float damage;
		float armor;
		// �������̳� ���׷��̵� ��Ȳ �߰�
	};
	class EnemyData
	{
	public:
		float hp;
		float damage;
		float armor;
		enum GRADE {
			Normal,
			Elite,
			Boss
		}grade;
	};
	class CombatData
	{
	public:
		int randomValue;
		float windAngle;
		float windPower;
		float angle;
		float power;
		float moveGauge;
	};
};